#include "log.h"
#ifdef __linux__
#    include <stdio.h>
#    include <stdlib.h>
#    include <string.h>
#    include <stdint.h>
#    include <unistd.h>
#    include <sys/mman.h>
#    include <fcntl.h>
#    include <ctype.h>
#    include "layout.h"

#    include <wayland-client.h>
#    include <xkbcommon/xkbcommon.h>

/* ---- globals ---- */
static struct wl_display  *g_display  = NULL;
static struct wl_registry *g_registry = NULL;
static struct wl_seat     *g_seat     = NULL;
static struct wl_keyboard *g_keyboard = NULL;

static struct xkb_context *g_xkb_ctx    = NULL;
static struct xkb_keymap  *g_xkb_keymap = NULL;
static struct xkb_state   *g_xkb_state  = NULL;

/* store last known layout (enum) */
static keyboard_layout_t g_last_layout = LAYOUT_UNKNOWN;

/* forward declarations */
static void compute_and_store_current_layout(void);

/* ---- helper: mapping layout name -> enum ----
   We perform a simple, robust check on the layout name string provided by xkb.
   Typical layout names: "us", "us(intl)", "en", "fa", "ir", "fa(phonetic)", etc.
*/
static keyboard_layout_t map_layout_name_to_enum(const char *name) {
    if (!name) return LAYOUT_UNKNOWN;

    char   lower[128];
    size_t i;
    for (i = 0; i < sizeof(lower) - 1 && name[i]; ++i)
        lower[i] = (char)tolower((unsigned char)name[i]);
    lower[i] = '\0';

    // check for Farsi / Persian indicators
    if (strstr(lower, "fa") != NULL || strstr(lower, "farsi") != NULL || strstr(lower, "ir") != NULL || strstr(lower, "persian") != NULL) {
        return LAYOUT_FARSI;
    }

    // check for English indicators
    if (strstr(lower, "us") != NULL || strstr(lower, "en") != NULL || strstr(lower, "gb") != NULL || strstr(lower, "uk") != NULL || strstr(lower, "eng") != NULL) {
        return LAYOUT_ENGLISH;
    }

    return LAYOUT_UNKNOWN;
}

/* ---- xkb / layout derivation ----
   Use xkb_keymap + xkb_state to get a layout index, then layout name, then map.
*/
static void compute_and_store_current_layout(void) {
    if (!g_xkb_keymap || !g_xkb_state) {
        g_last_layout = LAYOUT_UNKNOWN;
        return;
    }

    xkb_keycode_t min = xkb_keymap_min_keycode(g_xkb_keymap);
    xkb_keycode_t max = xkb_keymap_max_keycode(g_xkb_keymap);

    for (xkb_keycode_t key = min; key <= max; ++key) {
        int num_layouts_for_key = xkb_keymap_num_layouts_for_key(g_xkb_keymap, key);
        if (num_layouts_for_key <= 0) continue;

        xkb_layout_index_t layout_idx = xkb_state_key_get_layout(g_xkb_state, key);
        if (layout_idx == XKB_LAYOUT_INVALID) continue;

        const char *layout_name = xkb_keymap_layout_get_name(g_xkb_keymap, layout_idx);
        if (layout_name) {
            g_last_layout = map_layout_name_to_enum(layout_name);
            return;
        } else {
            // no human name: fall back to unknown
            g_last_layout = LAYOUT_UNKNOWN;
            return;
        }
    }

    g_last_layout = LAYOUT_UNKNOWN;
}

/* ---- Wayland listeners ---- */

/* wl_keyboard listener */
static void keyboard_handle_keymap(void *data, struct wl_keyboard *keyboard, uint32_t format, int fd, uint32_t size) {
    (void)data;
    (void)keyboard;
    if (fd < 0) return;

    void *map = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (map == MAP_FAILED) {
        close(fd);
        fprintf(stderr, "failed to mmap keymap\n");
        return;
    }

    if (g_xkb_keymap) {
        xkb_keymap_unref(g_xkb_keymap);
        g_xkb_keymap = NULL;
    }
    if (g_xkb_state) {
        xkb_state_unref(g_xkb_state);
        g_xkb_state = NULL;
    }

    if (!g_xkb_ctx) {
        g_xkb_ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
        if (!g_xkb_ctx) {
            fprintf(stderr, "failed to create xkb context\n");
            munmap(map, size);
            close(fd);
            return;
        }
    }

    g_xkb_keymap = xkb_keymap_new_from_string(g_xkb_ctx, (const char *)map, XKB_KEYMAP_FORMAT_TEXT_V1, XKB_KEYMAP_COMPILE_NO_FLAGS);
    munmap(map, size);
    close(fd);

    if (!g_xkb_keymap) {
        fprintf(stderr, "failed to compile xkb keymap\n");
        g_last_layout = LAYOUT_UNKNOWN;
        return;
    }

    g_xkb_state = xkb_state_new(g_xkb_keymap);
    if (!g_xkb_state) {
        fprintf(stderr, "failed to create xkb state\n");
        xkb_keymap_unref(g_xkb_keymap);
        g_xkb_keymap  = NULL;
        g_last_layout = LAYOUT_UNKNOWN;
        return;
    }

    compute_and_store_current_layout();
}

static void keyboard_handle_enter(void *data, struct wl_keyboard *keyboard, uint32_t serial, struct wl_surface *surface, struct wl_array *keys) {
    (void)data;
    (void)keyboard;
    (void)serial;
    (void)surface;
    (void)keys;
}

static void keyboard_handle_leave(void *data, struct wl_keyboard *keyboard, uint32_t serial, struct wl_surface *surface) {
    (void)data;
    (void)keyboard;
    (void)serial;
    (void)surface;
}

static void keyboard_handle_key(void *data, struct wl_keyboard *keyboard, uint32_t serial, uint32_t time, uint32_t key, uint32_t state) {
    (void)data;
    (void)keyboard;
    (void)serial;
    (void)time;
    (void)key;
    (void)state;
    if (g_xkb_state && g_xkb_keymap) {
        compute_and_store_current_layout();
    }
}

static void keyboard_handle_modifiers(void *data, struct wl_keyboard *keyboard, uint32_t serial, uint32_t mods_depressed, uint32_t mods_latched, uint32_t mods_locked, uint32_t group) {
    (void)data;
    (void)keyboard;
    (void)serial;
    if (!g_xkb_state) return;

    xkb_state_update_mask(g_xkb_state, mods_depressed, mods_latched, mods_locked, 0, 0, group);

    compute_and_store_current_layout();
}

static const struct wl_keyboard_listener keyboard_listener = {.keymap = keyboard_handle_keymap, .enter = keyboard_handle_enter, .leave = keyboard_handle_leave, .key = keyboard_handle_key, .modifiers = keyboard_handle_modifiers};

/* wl_seat listener */
static void seat_handle_capabilities(void *data, struct wl_seat *seat, enum wl_seat_capability caps) {
    (void)data;
    if ((caps & WL_SEAT_CAPABILITY_KEYBOARD) && !g_keyboard) {
        g_keyboard = wl_seat_get_keyboard(seat);
        wl_keyboard_add_listener(g_keyboard, &keyboard_listener, NULL);
    } else if (!(caps & WL_SEAT_CAPABILITY_KEYBOARD) && g_keyboard) {
        wl_keyboard_destroy(g_keyboard);
        g_keyboard = NULL;
    }
}

static void seat_handle_name(void *data, struct wl_seat *seat, const char *name) {
    (void)data;
    (void)seat;
    (void)name;
}

static const struct wl_seat_listener seat_listener = {.capabilities = seat_handle_capabilities, .name = seat_handle_name};

/* wl_registry listener */
static void registry_handle_global(void *data, struct wl_registry *registry, uint32_t id, const char *interface, uint32_t version) {
    (void)data;
    if (strcmp(interface, wl_seat_interface.name) == 0) {
        g_seat = wl_registry_bind(registry, id, &wl_seat_interface, 5);
        wl_seat_add_listener(g_seat, &seat_listener, NULL);
    }
}

static void registry_handle_global_remove(void *data, struct wl_registry *registry, uint32_t id) {
    (void)data;
    (void)registry;
    (void)id;
}

static const struct wl_registry_listener registry_listener = {.global = registry_handle_global, .global_remove = registry_handle_global_remove};


int wayland_init_keyboard_layout(void) {
    if (g_display) return 0; // already initialized

    g_display = wl_display_connect(NULL);
    if (!g_display) {
        LOG_FATAL("failed to connect to wayland display");
        return -1;
    }

    g_registry = wl_display_get_registry(g_display);
    if (!g_registry) {
        LOG_FATAL("failed to get registry");
        wl_display_disconnect(g_display);
        g_display = NULL;
        return -1;
    }

    wl_registry_add_listener(g_registry, &registry_listener, NULL);

    /* Roundtrip to get initial globals (seat, etc.) and possibly initial keymap */
    wl_display_roundtrip(g_display);
    wl_display_roundtrip(g_display);

    if (!g_xkb_ctx) {
        g_xkb_ctx = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
        if (!g_xkb_ctx) {
            // non-fatal; keymap handler will create one if needed
        }
    }

    return 0;
}

keyboard_layout_t wayland_get_keyboard_layout(void) {
    return g_last_layout;
}


void wayland_close_keyboard_layout(void) {
    if (g_keyboard) {
        wl_keyboard_destroy(g_keyboard);
        g_keyboard = NULL;
    }
    if (g_seat) {
        wl_seat_destroy(g_seat);
        g_seat = NULL;
    }
    if (g_registry) {
        wl_registry_destroy(g_registry);
        g_registry = NULL;
    }
    if (g_display) {
        wl_display_disconnect(g_display);
        g_display = NULL;
    }

    if (g_xkb_state) {
        xkb_state_unref(g_xkb_state);
        g_xkb_state = NULL;
    }
    if (g_xkb_keymap) {
        xkb_keymap_unref(g_xkb_keymap);
        g_xkb_keymap = NULL;
    }
    if (g_xkb_ctx) {
        xkb_context_unref(g_xkb_ctx);
        g_xkb_ctx = NULL;
    }

    g_last_layout = LAYOUT_UNKNOWN;
}

/* ---- optional small test main (uncomment to test manually) ----
int main(void) {
    if (wayland_init_keyboard_layout() != 0) return 1;

    for (int i = 0; i < 200; ++i) {
        wl_display_dispatch_pending(g_display);
        keyboard_layout_t l = wayland_get_keyboard_layout();
        if (l == LAYOUT_ENGLISH) printf("Detected layout: ENGLISH\n");
        else if (l == LAYOUT_FARSI) printf("Detected layout: FARSI\n");
        else printf("Detected layout: UNKNOWN\n");
        usleep(100000);
    }

    wayland_close_keyboard_layout();
    return 0;
}
*/

#endif