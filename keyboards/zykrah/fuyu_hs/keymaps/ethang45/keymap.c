#include QMK_KEYBOARD_H

enum custom_keycodes {
    CCNT = SAFE_RANGE, // use safe_range to avoid overwriting
    CLNDR,
    DOCK,
    DOND,
    EMJI,
    GLOB,
    LOCK,
    NTFN,
    RCAST,
    SDTP,
    SSHT,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_tkl_ansi_numpad(
    KC_ESC,           KC_BRID, KC_BRIU, RGB_VAD, RGB_VAI, EMJI,    KC_MPRV, KC_MPLY, KC_MNXT, DOND,    KC_MUTE, KC_VOLD, KC_VOLU,          KC_MCTL, KC_LPAD, LOCK,
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          SDTP,    RCAST,   CLNDR,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          DOCK,    CCNT,    SSHT,
    KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,                    KC_PGUP, NTFN,    KC_HOME,
    KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,                   KC_PGDN, KC_UP,   KC_END,
    KC_LCTL, KC_LOPT, KC_LCMD,                   KC_SPC,                                      KC_RCMD, KC_ROPT, KC_RCTL, GLOB,             KC_LEFT, KC_DOWN, KC_RGHT),


  [1] = LAYOUT_tkl_ansi_numpad(
    KC_TRNS,          KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_F13,  KC_F14,  KC_F15,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,           KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS,
    KC_LSFT,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_RSFT,                   KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,                                     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS),

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GLOB: // globe key
            if (record->event.pressed) {
                host_consumer_send(AC_NEXT_KEYBOARD_LAYOUT_SELECT);
                layer_on(1);
            } else {
                layer_off(1);
                host_consumer_send(0);
            }
            return false;
        case LOCK: // lock (Ctrl+Cmd+Q)
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LCMD);
                register_code(KC_Q);
            } else {
                unregister_code(KC_LCTL);
                unregister_code(KC_LCMD);
                unregister_code(KC_Q);
            }
            return false;
        case CCNT: // control center (Globe+C)
            if (record->event.pressed) {
                host_consumer_send(AC_NEXT_KEYBOARD_LAYOUT_SELECT);
                register_code(KC_C);
            } else {
                unregister_code(KC_C);
                host_consumer_send(0);
            }
            return false;
        case EMJI: // emoji viewer (Cmd+Ctrl+Space)
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_LCTL);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_LCTL);
                unregister_code(KC_SPC);
            }
            return false;
        case DOND: // do not disturb
            if (record->event.pressed) {
                host_system_send(0x9B);
            } else {
                host_system_send(0);
            }
            return false;
        case RCAST: // raycast launcher
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_SPC);
            }
            return false;
        case NTFN: // notification center (Globe + N)
            if (record->event.pressed) {
                host_consumer_send(AC_NEXT_KEYBOARD_LAYOUT_SELECT);
                register_code(KC_N);
            } else {
                unregister_code(KC_N);
                host_consumer_send(0);
            }
            return false;
        case DOCK: // macOS dock (Globe + A)
            if (record->event.pressed) {
                host_consumer_send(AC_NEXT_KEYBOARD_LAYOUT_SELECT);
                register_code(KC_A);
            } else {
                unregister_code(KC_A);
                host_consumer_send(0);
            }
            return false;
        case CLNDR: // calendar (Cmd+Opt+Space)
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_LOPT);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_LOPT);
                unregister_code(KC_SPC);
            }
            return false;
        case SDTP: // show desktop (Globe+H)
            if (record->event.pressed) {
                host_consumer_send(AC_NEXT_KEYBOARD_LAYOUT_SELECT);
                register_code(KC_H);
            } else {
                unregister_code(KC_H);
                host_consumer_send(0);
            }
            return false;
        case SSHT: // screenshot (Shift+Cmd+5)
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
        default:
            return true;   // Process all other keycodes normally
    }
    return true;
}

// Caps lock indicator: turn entire keyboard green at max brightness when caps lock is on
bool rgb_matrix_indicators_user(void) {
    if (host_keyboard_led_state().caps_lock) {
        // Set all LEDs to green at max brightness
        for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
            rgb_matrix_set_color(i, 0, 255, 0);  // RGB: green
        }
    }
    return false;
}

/* DICTATION (for future reference):
case AP_DICT:
    if (record->event.pressed) {
        host_consumer_send(0xCF);  // Dictation on macOS
    } else {
        host_consumer_send(0);
    }
    return false;
*/

/* LOCK SCREEN using AL_LOCK (for future reference):
case LOCK:
    if (record->event.pressed) {
        host_consumer_send(AL_LOCK);  // Lock screen on macOS
    } else {
        host_consumer_send(0);
    }
    return false;
*/

/* NOTES:
 * KC_WSCH is spotlight
 * KC_NUM is clear key on macos (unused)
 * KC_F11 shows desktop by default on macos
 */
