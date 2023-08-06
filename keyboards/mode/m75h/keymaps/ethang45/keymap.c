/*
Copyright 2020 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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

enum layers{
    MAC_BASE,
    MAC_FN
};

enum custom_keycodes {
    FN_LAYR = SAFE_RANGE,
    ALFRED,
    SIRI,
    SCRSHT,
    KC_SPOTLIGHT,
    KC_DICTATION,
    KC_DO_NOT_DISTURB,
    KC_LOCK_SCREEN,
    KC_MISSION_CONTROL_ETHAN,
    KC_LAUNCHPAD_ETHAN,
    KC_LOPTN,
    KC_ROPTN,
    KC_LCMMD,
    KC_RCMMD
};

#define KC_MCTL KC_MISSION_CONTROL_ETHAN
#define KC_LPAD KC_LAUNCHPAD_ETHAN
#define KC_SPLT KC_SPOTLIGHT
#define KC_DICT KC_DICTATION
#define KC_DOND KC_DO_NOT_DISTURB
#define KC_LCK KC_LOCK_SCREEN

static uint8_t mac_keycode[4] = { KC_LOPT, KC_ROPT, KC_LCMD, KC_RCMD };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [MAC_BASE] = LAYOUT(
        KC_ESC  , KC_BRID  , KC_BRIU  , KC_MCTL  , ALFRED  ,          KC_DICT  , KC_MPRV,  KC_MPLY  , KC_MNXT  , KC_DOND  , KC_MUTE , KC_VOLD , KC_VOLU,           KC_LCK ,
        KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6,   KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,          KC_HOME,
        KC_TAB  , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y,   KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H,   KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,                   KC_PGDN,
        KC_LSFT ,          KC_Z   , KC_X   , KC_C   , KC_V   , KC_B,   KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP  , KC_END ,
        KC_LCTL , KC_LOPTN, KC_LCMMD,                            KC_SPC,                            KC_RCMMD, FN_LAYR  ,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [MAC_FN] = LAYOUT(
        KC_TRNS, KC_F1, KC_F2, KC_F3, KC_F4,          KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                            KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case FN_LAYR:
            if (record->event.pressed) {
                register_code(KC_APFN);
                layer_on(1);
            } else {
                layer_off(1);
                unregister_code(KC_APFN);
            }
            return false;
        case KC_MISSION_CONTROL_ETHAN:
            if (record->event.pressed) {
                host_consumer_send(0x29F);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_SPOTLIGHT:
            if (record->event.pressed) {
                host_consumer_send(0x221);
            } else {
                host_consumer_send(0);
            }
            return false;
        case KC_DICTATION:
            if (record->event.pressed) {
                host_consumer_send(0xCF);
            } else {
                host_consumer_send(0);
            }
            return false;
        case KC_DO_NOT_DISTURB:
            if (record->event.pressed) {
                host_system_send(0x9B);
            } else {
                host_system_send(0);
            }
            return false;
        case KC_LOCK_SCREEN:
            if (record->event.pressed) {
                host_consumer_send(0x19E);
            } else {
                host_consumer_send(0);
            }
            return false;
        case KC_LAUNCHPAD_ETHAN:
            if (record->event.pressed) {
                host_consumer_send(0x2A0);
            } else {
                host_consumer_send(0);
            }
            return false;  // Skip all further processing of this key
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false;  // Skip all further processing of this key
        case ALFRED:
            if (record->event.pressed) {
                register_code(KC_LCMD);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_LCMD);
                unregister_code(KC_SPC);
            }
            return false;
        case SIRI:
            if (record->event.pressed) {
                register_code(KC_APFN);
                register_code(KC_SPC);
            } else {
                unregister_code(KC_APFN);
                unregister_code(KC_SPC);
            }
            return false;
        case SCRSHT:
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