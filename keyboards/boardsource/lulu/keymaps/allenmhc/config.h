/*
Copyright 2022 Rocco Meli <@RMeli>

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

#define MASTER_LEFT
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_LAYER_STATE_ENABLE // Share layer state between sides
#define SPLIT_WPM_ENABLE
#define SPLIT_WATCHDOG_ENABLE
#define TAPPING_TOGGLE 2
#define DEBOUNCE 10
#define MAX_DEFERRED_EXECUTORS 10

#define TAPPING_TERM_PER_KEY
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS
#define ONESHOT_TAP_TOGGLE 10
#define ONESHOT_TIMEOUT 500

#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_DEFAULT_HUE 30
#    define RGBLIGHT_DEFAULT_SAT 192
#    define RGBLIGHT_DEFAULT_VAL 200
#endif

#ifdef RGB_MATRIX_ENABLE
// Configure RGB Matrix
#    define RGB_MATRIX_KEYPRESSES // enable keypress effects
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP
#    define RGB_MATRIX_DEFAULT_HUE 20
#    define RGB_MATRIX_DEFAULT_SAT 192
#    define RGB_MATRIX_DEFAULT_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS
// Disable RGB Matrix effects (from lulu/config.h)
#    undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#    undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#    undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#    undef ENABLE_RGB_MATRIX_BREATHING
#    undef ENABLE_RGB_MATRIX_BAND_SAT
#    undef ENABLE_RGB_MATRIX_BAND_VAL
// Enable RGB Matrix effects
#    define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#    define ENABLE_RGB_MATRIX_SOLID_COLOR
#    define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif
