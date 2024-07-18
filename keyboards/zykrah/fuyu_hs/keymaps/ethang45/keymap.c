/*
Copyright 2022 Zykrah

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

// use safe_range to avoid overwriting
enum custom_keycodes {
    ALFRED = SAFE_RANGE,
    AP_DICT,
    AP_DOND,
    AP_GLOB,
    DOCK,
    NTFN_CTR,
    CLNDR,
    LOCK,
    SCRSHT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // KC_WSCH is spotlight
  // KC_NUM is clear key on macos (unused)
  // KC_F11 shows desktop
  // todo setup keyboard backlight keys
  [0] = LAYOUT_tkl_ansi_numpad(
    KC_ESC,           KC_BRID, KC_BRIU, KC_BRID, KC_BRIU, AP_DICT, KC_MPRV, KC_MPLY, KC_MNXT, AP_DOND, KC_MUTE, KC_VOLD, KC_VOLU,          KC_MCTL, KC_LPAD,  LOCK,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,  CLNDR,    ALFRED,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_F11,  DOCK,     KC_WSCH,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_PGUP, NTFN_CTR, KC_HOME,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   KC_PGDN, KC_UP,    KC_END,
    KC_LCTL, KC_LOPT, KC_LCMD,                   KC_SPC,                                      KC_RCMD, KC_ROPT, KC_RCTL, AP_GLOB,          KC_LEFT, KC_DOWN,  KC_RGHT),


  [1] = LAYOUT_tkl_ansi_numpad(
    KC_TRNS,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_TRNS, KC_F10,  KC_F11,  KC_F12,           KC_F13,  KC_F14,  KC_F15,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS,                KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case AP_GLOB: // globe key
            if (record->event.pressed) {
                host_consumer_send(AC_NEXT_KEYBOARD_LAYOUT_SELECT);
                layer_on(1);
            } else {
                layer_off(1);
                host_consumer_send(0);
            }
            return false;
        case LOCK: // lock key
            if (record->event.pressed) {
                host_consumer_send(AL_LOCK);
            } else {
                host_consumer_send(0);
            }
            return false;
        case AP_DICT: // dictation
            if (record->event.pressed) {
                host_consumer_send(0xCF);
            } else {
                host_consumer_send(0);
            }
            return false;
        case AP_DOND: // do not disturb
            if (record->event.pressed) {
                host_system_send(0x9B);
            } else {
                host_system_send(0);
            }
            return false;
        case ALFRED: // alfred search
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_SPC);
            }
            return false;
        case NTFN_CTR: // notification center
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_LOPT);
                register_code(KC_LCTL);
                register_code(KC_LCMD);
                register_code(KC_N);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LOPT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LCMD);
                unregister_code(KC_NUM);
            }
            return false;
        case DOCK: // macOS dock
            if (record->event.pressed) {
                register_code(KC_LOPT);
                register_code(KC_LCMD);
                register_code(KC_D);
            } else {
                unregister_code(KC_LOPT);
                unregister_code(KC_LCMD);
                unregister_code(KC_D);
            }
            return false;
        case SCRSHT: // screenshot app
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_LCMD);
                register_code(KC_5);
            } else {
                unregister_code(KC_LSFT);
                unregister_code(KC_LCMD);
                unregister_code(KC_5);
            }
            return false;
        case CLNDR: // calendar 366 ii
            if (record->event.pressed) {
                register_code(KC_LOPT);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_LOPT);
                unregister_code(KC_SPC);
            }
            return false;
        default:
            return true;   // Process all other keycodes normally
    }
    return true;
}

// todo figure out this caps lock led stuff
// Code for Caps Locks indicator
// #if defined(RGB_MATRIX_ENABLE) && defined(CAPS_LOCK_LED_INDEX)

// #    if !defined(CAPS_LOCK_MAX_BRIGHTNESS)
// #        define CAPS_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
// #    endif

// #    if !defined(CAPS_LOCK_VAL_STEP)
// #        define CAPS_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
// #    endif

// bool rgb_matrix_indicators_user(void) {
//     if (host_keyboard_led_state().caps_lock) {
//         uint8_t b = rgb_matrix_get_val();
//         if (b < CAPS_LOCK_VAL_STEP) {
//             b = CAPS_LOCK_VAL_STEP;
//         } else if (b < (CAPS_LOCK_MAX_BRIGHTNESS - CAPS_LOCK_VAL_STEP)) {
//             b += CAPS_LOCK_VAL_STEP; // one step more than current brightness
//         } else {
//             b = CAPS_LOCK_MAX_BRIGHTNESS;
//         }
//         rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, b, b, b); // white, with the adjusted brightness
//     }
//     return false;
// }

// #endif

// Code used to lower the brightness of the indicator LEDs (Snowflake LEDs)
// #if defined(RGB_MATRIX_ENABLE)

// #    define INDICATOR_RGB_DIVISOR 4
// extern rgb_led_t rgb_matrix_ws2812_array[DRIVER_LED_TOTAL];
// bool             rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
//     for (uint8_t i = led_min; i < led_max; i++) {
//         if (g_led_config.flags[i] & LED_FLAG_INDICATOR) {
//             RGB temp_rgb = {0};
//             temp_rgb.r   = rgb_matrix_ws2812_array[i].r / INDICATOR_RGB_DIVISOR;
//             temp_rgb.g   = rgb_matrix_ws2812_array[i].g / INDICATOR_RGB_DIVISOR;
//             temp_rgb.b   = rgb_matrix_ws2812_array[i].b / INDICATOR_RGB_DIVISOR;
//             rgb_matrix_set_color(i, temp_rgb.r, temp_rgb.g, temp_rgb.b);
//         }

// #    if !defined(ENABLE_UNDERGLOW)
//         if (g_led_config.flags[i] & LED_FLAG_UNDERGLOW) {
//             rgb_matrix_set_color(i, 0, 0, 0);
//         }
//             #    endif
//     }
//     return false;
// }

// #endif
