/* Copyright 2021 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "q5.h"

const matrix_row_t matrix_mask[] = {
    0b111111111111111111,
    0b111111111111111111,
    0b111111111111111111,
    0b111111111111111111,
    0b111111111111111111,
    0b111111111111101111,
};

#ifdef DIP_SWITCH_ENABLE

bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) { return false;}
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}

#endif  // DIP_SWITCH_ENABLE

#if defined(RGB_MATRIX_ENABLE) && (defined(CAPS_LOCK_LED_INDEX) || defined(NUM_LOCK_LED_INDEX))
    #if defined(CAPS_LOCK_LED_INDEX)
        #define CAPS_LOCK_MAX_BRIGHTNESS 0xFF
        #ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
            #undef CAPS_LOCK_MAX_BRIGHTNESS
            #define CAPS_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
        #endif

        #define CAPS_LOCK_VAL_STEP 8
        #ifdef RGB_MATRIX_VAL_STEP
            #undef CAPS_LOCK_VAL_STEP
            #define CAPS_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
        #endif
    #endif

    #if defined(NUM_LOCK_LED_INDEX)
        #define NUM_LOCK_MAX_BRIGHTNESS 0xFF
        #ifdef RGB_MATRIX_MAXIMUM_BRIGHTNESS
            #undef NUM_LOCK_MAX_BRIGHTNESS
            #define NUM_LOCK_MAX_BRIGHTNESS RGB_MATRIX_MAXIMUM_BRIGHTNESS
        #endif

        #define NUM_LOCK_VAL_STEP 8
        #ifdef RGB_MATRIX_VAL_STEP
            #undef NUM_LOCK_VAL_STEP
            #define NUM_LOCK_VAL_STEP RGB_MATRIX_VAL_STEP
        #endif
    #endif

    __attribute__((weak)) void rgb_matrix_indicators_kb(void) {
        #if defined(CAPS_LOCK_LED_INDEX)
        if (host_keyboard_led_state().caps_lock) {
            uint8_t b = rgb_matrix_get_val();
            if (b < CAPS_LOCK_VAL_STEP) {
                b = CAPS_LOCK_VAL_STEP;
            } else if (b < (CAPS_LOCK_MAX_BRIGHTNESS - CAPS_LOCK_VAL_STEP)) {
                b += CAPS_LOCK_VAL_STEP;  // one step more than current brightness
            } else {
                b = CAPS_LOCK_MAX_BRIGHTNESS;
            }
            rgb_matrix_set_color(CAPS_LOCK_LED_INDEX, b, b, b);  // white, with the adjusted brightness    }
        }
        #endif
        #if defined(NUM_LOCK_LED_INDEX)
        if (host_keyboard_led_state().num_lock) {
            uint8_t v = rgb_matrix_get_val();
            if (v < NUM_LOCK_VAL_STEP) {
                v = NUM_LOCK_VAL_STEP;
            } else if (v < (NUM_LOCK_MAX_BRIGHTNESS - NUM_LOCK_VAL_STEP)) {
                v += NUM_LOCK_VAL_STEP;  // one step more than current brightness
            } else {
                v = NUM_LOCK_MAX_BRIGHTNESS;
            }
            rgb_matrix_set_color(NUM_LOCK_LED_INDEX, v, v, v);  // white, with the adjusted brightness    }
        }
        #endif
    }

#endif  // CAPS_LOCK_LED_INDEX or CAPS_LOCK_LED_INDEX
