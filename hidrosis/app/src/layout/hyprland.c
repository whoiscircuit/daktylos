#ifdef __linux__
#include <stdio.h>
#include <cJSON.h>
#include <layout.h>
#include <log.h>

char *exec_cmd(const char *cmd) {
    FILE *fp;
    char *output = NULL;
    size_t size = 0;
    char buffer[4096];

    fp = popen(cmd, "r");
    if (!fp) {
        perror("popen");
        return NULL;
    }

    while (fgets(buffer, sizeof(buffer), fp)) {
        size_t len = strlen(buffer);
        char *new_output = realloc(output, size + len + 1);
        if (!new_output) {
            free(output);
            pclose(fp);
            return NULL;
        }
        output = new_output;
        memcpy(output + size, buffer, len);
        size += len;
        output[size] = '\0';
    }

    pclose(fp);
    return output;
}

keyboard_layout_t hyprland_get_keyboard_layout(void) {
    char *json_text = exec_cmd("hyprctl devices -j");
    if (!json_text) {
        LOG_ERROR("Failed to run hyprctl");
        return 1;
    }

    cJSON *root = cJSON_Parse(json_text);
    if (!root) {
        LOG_ERROR("Failed to parse JSON from hyprctl");
        free(json_text);
        return LAYOUT_UNKNOWN;
    }

    cJSON *keyboards = cJSON_GetObjectItem(root, "keyboards");
    if (!cJSON_IsArray(keyboards)) {
        LOG_ERROR("No keyboards array found in hyprctl output");
        cJSON_Delete(root);
        free(json_text);
        return LAYOUT_UNKNOWN;
    }

    cJSON *keyboard;
    keyboard_layout_t layout = LAYOUT_UNKNOWN;
    cJSON_ArrayForEach(keyboard, keyboards) {
        cJSON *main_item = cJSON_GetObjectItem(keyboard, "main");
        if (cJSON_IsBool(main_item) && cJSON_IsTrue(main_item)) {
            cJSON *keymap = cJSON_GetObjectItem(keyboard, "active_keymap");
            if (cJSON_IsString(keymap)) {
                layout = get_layout_from_string(keymap->valuestring);
            }
        }
    }
    cJSON_Delete(root);
    free(json_text);
    return layout;
}
#endif