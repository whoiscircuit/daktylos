#ifdef __linux__
#include <wayland-client.h>
#include <xkbcommon/xkbcommon.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include "layout.h"

typedef struct {
    struct xkb_context *ctx;
    struct xkb_keymap *keymap;
    struct xkb_state *state;
    uint32_t group;
    int have_keymap;
    int have_modifiers;
} wayland_ctx_t;

static void
registry_global(void *data, struct wl_registry *registry,
                uint32_t id, const char *interface, uint32_t version) {
    struct wl_compositor **compositor = data;
    struct wl_seat **seat = (struct wl_seat **)(((char *)data) + sizeof(struct wl_compositor *));

    if (strcmp(interface, wl_compositor_interface.name) == 0) {
        *compositor = wl_registry_bind(registry, id, &wl_compositor_interface, 1);
    } else if (strcmp(interface, wl_seat_interface.name) == 0) {
        *seat = wl_registry_bind(registry, id, &wl_seat_interface, 1);
    }
}

static void
keyboard_keymap(void *data, struct wl_keyboard *keyboard,
                uint32_t format, int fd, uint32_t size) {
    wayland_ctx_t *ctx = data;

    if (format != WL_KEYBOARD_KEYMAP_FORMAT_XKB_V1) {
        close(fd);
        return;
    }

    void *map_str = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (map_str == MAP_FAILED) {
        close(fd);
        return;
    }

    ctx->keymap = xkb_keymap_new_from_string(ctx->ctx, map_str,
                                             XKB_KEYMAP_FORMAT_TEXT_V1,
                                             XKB_CONTEXT_NO_FLAGS);
    munmap(map_str, size);
    close(fd);

    if (ctx->keymap) {
        ctx->state = xkb_state_new(ctx->keymap);
        ctx->have_keymap = 1;
    }
}

static void
keyboard_modifiers(void *data, struct wl_keyboard *keyboard,
                   uint32_t serial,
                   uint32_t mods_depressed,
                   uint32_t mods_latched,
                   uint32_t mods_locked,
                   uint32_t group) {
    wayland_ctx_t *ctx = data;

    if (ctx->state) {
        xkb_state_update_mask(ctx->state,
                              mods_depressed,
                              mods_latched,
                              mods_locked,
                              0, 0, group);
    }
    ctx->group = group;
    ctx->have_modifiers = 1;
}

static const struct wl_keyboard_listener keyboard_listener = {
    .keymap = keyboard_keymap,
    .enter = NULL,
    .leave = NULL,
    .key = NULL,
    .modifiers = keyboard_modifiers,
    .repeat_info = NULL,
};

static const struct wl_registry_listener registry_listener = {
    .global = registry_global,
    .global_remove = NULL,
};

keyboard_layout_t wayland_get_keyboard_layout(void) {
    struct wl_display *display = wl_display_connect(NULL);
    if (!display) {
        return LAYOUT_UNKNOWN;
    }

    struct wl_registry *registry = wl_display_get_registry(display);

    struct wl_compositor *compositor = NULL;
    struct wl_seat *seat = NULL;
    void *bind_data = &compositor;  // hack to pass two pointers

    wl_registry_add_listener(registry, &registry_listener, bind_data);

    if (wl_display_roundtrip(display) < 0) {
        goto cleanup;
    }

    if (!compositor || !seat) {
        goto cleanup;
    }

    wayland_ctx_t ctx = {0};
    ctx.ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
    if (!ctx.ctx) {
        goto cleanup;
    }

    struct wl_keyboard *keyboard = wl_seat_get_keyboard(seat);
    wl_keyboard_add_listener(keyboard, &keyboard_listener, &ctx);

    if (wl_display_roundtrip(display) < 0) {
        goto cleanup;
    }

    if (!ctx.have_keymap) {
        goto cleanup;
    }

    if (!ctx.have_modifiers) {
        ctx.group = 0;  // assume default group
    }

    xkb_layout_index_t layout_idx = xkb_state_serialize_layout(ctx.state, XKB_STATE_LAYOUT_EFFECTIVE);
    const char *layout_name = xkb_keymap_layout_get_name(ctx.keymap, layout_idx);
    if (!layout_name) {
        goto cleanup;
    }

    keyboard_layout_t layout = get_layout_from_string((char *)layout_name);

cleanup:
    if (ctx.state) {
        xkb_state_unref(ctx.state);
    }
    if (ctx.keymap) {
        xkb_keymap_unref(ctx.keymap);
    }
    if (ctx.ctx) {
        xkb_context_unref(ctx.ctx);
    }
    if (keyboard) {
        wl_keyboard_destroy(keyboard);
    }
    if (seat) {
        wl_seat_destroy(seat);
    }
    if (compositor) {
        wl_compositor_destroy(compositor);
    }
    if (registry) {
        wl_registry_destroy(registry);
    }
    if (display) {
        wl_display_disconnect(display);
    }
    return ctx.have_keymap ? layout : LAYOUT_UNKNOWN;
}

#endif