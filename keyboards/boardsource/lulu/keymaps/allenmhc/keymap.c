// Copyright 2022 Cole Smith <cole@boadsource.xyz>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _RAISE,
    _LOWER,
    _ADJUST
};

#include "oled.c"
#include "lights.c"

enum custom_keycodes {
    SMTD_KEYCODES_BEGIN = SAFE_RANGE,
    CKC_Z, // reads as C(ustom) + KC_A, but you may give any name here
    CKC_X,
    CKC_C,
    CKC_V,
    CKC_M,
    CKC_COMM,
    CKC_DOT,
    CKC_SLSH,
    SMTD_KEYCODES_END,
};
#include "sm_td.h"

#define RAISE TT(_RAISE)
#define LOWER TT(_LOWER)
#define OSM_SFT OSM(MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | Grave|   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  ]   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  [   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   -   |    |   =   |------+------+------+------+------+------|
 * | Left |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | Right|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | RAISE|  Up  | Shift | /BackSP /       \Enter \  | Space| Down | LOWER|
 *                   |      |      |       |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  QK_GESC,  KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_RBRC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
  KC_LCTL,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOTE,
  KC_LEFT,  CKC_Z,  CKC_X,   CKC_C,   CKC_V,   KC_B, KC_MINS,   KC_EQL,  KC_N,    CKC_M,   CKC_COMM,CKC_DOT, CKC_SLSH,KC_RIGHT,
                             RAISE,   KC_UP,OSM_SFT, KC_BSPC,   KC_ENT,  KC_SPC,  KC_DOWN, LOWER
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | Home |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |                    |   ^  |   *  |  *   |   (  |   )  | End  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |PageUp|
 * |------+------+------+------+------+------|       |    | BOOT  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |PageDn|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /  Del  /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
   KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_HOME,
  _______, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_END,
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_PGUP,
  _______, _______, _______, _______, _______, _______, XXXXXXX, QK_BOOT, _______, _______, _______, _______, _______, KC_PGDN,
                             _______, _______, _______, KC_DEL,  _______, _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |      |      |      |      |      |                    |      |      |      |  F11 |  F12 |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |   \  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      | HUE+ | SAT+ | VAL+ |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------| SLEEP |    |       |------+------+------+------+------+------|
 * |      |      |      | HUE- | SAT- | VAL- |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      | RGBF | RGBR | /RGB_TOG/       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  KC_GRV,  _______, _______, _______, _______, _______,                    _______, _______, _______, KC_F11,  KC_F12,  _______,
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, KC_BSLS,
  _______, _______, _______, RGB_HUI, RGB_SAI, RGB_VAI,                    _______, _______, _______, _______, _______, _______,
  _______, _______, _______, RGB_HUD, RGB_SAD, RGB_VAD, KC_SLEP, XXXXXXX,  _______, _______, _______, _______, _______, _______,
                             _______, RGB_MOD,RGB_RMOD, RGB_TOG, _______,  _______, _______, _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // Process SMTD first
  if (!process_smtd(keycode, record)) {
    return false;
  }

  // Send LCtrl (which gets translated into ♾️ in Karabiner) on Caps tap
  // Send CapsLock (which gets translated into ⌃ in Karabiner) on Caps hold
  switch (keycode) {
    case LT(0, KC_LCTL):
      if (record->tap.count && record->event.pressed) {
        set_oneshot_mods(MOD_BIT(KC_LCTL));
      } else if (record->event.pressed) {
        register_code(KC_CAPS);
      } else {
        unregister_code(KC_CAPS);
      }
      return false;
    break;
  }
  return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Give more time for ∞ to respond to a tap
    case LT(0, KC_LCTL):
      return 300;
    default:
      return TAPPING_TERM;
  }
}

// ==============================================
// SMTD
// https://github.com/stasmarkin/sm_td/
void on_smtd_action(uint16_t keycode, smtd_action action, uint8_t tap_count) {
    switch (keycode) {
        SMTD_MT(CKC_Z, KC_Z, KC_CAPS)
        SMTD_MT(CKC_X, KC_X, KC_LEFT_ALT)
        SMTD_MT(CKC_C, KC_C, KC_LEFT_GUI)
        SMTD_MT(CKC_V, KC_V, KC_LSFT)
        SMTD_MT(CKC_M, KC_M, KC_RSFT)
        SMTD_MT(CKC_COMM, KC_COMM, KC_RIGHT_GUI)
        SMTD_MT(CKC_DOT, KC_DOT, KC_RIGHT_ALT)
        SMTD_MT(CKC_SLSH, KC_SLSH, KC_CAPS)
    }
}