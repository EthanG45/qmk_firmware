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

#pragma once

#define DYNAMIC_KEYMAP_LAYER_COUNT 6

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#ifdef RGB_MATRIX_ENABLE
/* The pin connected to the data pin of the LEDs */
#define WS2812_DI_PIN GP3
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200
#define RGB_MATRIX_DEFAULT_ON true         // RGB enabled by default
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR   // Default mode when EEPROM cleared
#define RGB_MATRIX_DEFAULT_VAL 200         // Default brightness
#define RGB_MATRIX_DEFAULT_HUE 0           // Default hue
#define RGB_MATRIX_DEFAULT_SAT 0           // Default saturation (0 = white)

/* The number of LEDs connected (7 Snowflake, 34 Underglow) */
#define DRIVER_LED_TOTAL 41
#define RGBLED_NUM 41
#define RGB_MATRIX_LED_COUNT 41

/* Caps locks LED index default is 0 (LED1 on PCB) */
#define CAPS_LOCK_LED_INDEX 0

/* Enable RGB MATRIX effects - only solid color */
#define ENABLE_RGB_MATRIX_SOLID_COLOR
#endif
