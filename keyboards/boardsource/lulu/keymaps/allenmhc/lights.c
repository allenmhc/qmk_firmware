#include <stdio.h>

#ifdef RGB_MATRIX_ENABLE

/*
 * Backlights (underglow)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |   3  |      |   4  |      |   5  |      |                    |      |  40  |      |  39  |      |  38  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |   2  |      |   1  |      |  0   |      |-------|    |-------|      |  35  |      |  36  |      |  37  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 *
 * Per-key LEDs
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  11  |  10  |   9  |   8  |   7  |   6  |                    |  41  |  42  |  43  |  44  |  45  |  46  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  12  |  13  |  14  |  15  |  16  |  17  |                    |  52  |  51  |  50  |  49  |  48  |  47  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  23  |  22  |  21  |  20  |  19  |  18  |-------.    ,-------|  53  |  54  |  55  |  56  |  57  |  58  |
 * |------+------+------+------+------+------|   30  |    |   65  |------+------+------+------+------+------|
 * |  24  |  25  |  26  |  27  |  28  |  29  |-------|    |-------|  64  |  63  |  62  |  61  |  60  |  59  |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |  34  |  33  |  32  | /   31  /       \  66  \  |  67  |  68  |  69  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

const RGB white = { r: 255, g: 255, b: 255 };
const RGB red = { r: 255, g: 0, b: 0 };
const RGB olive = { r: 128, g: 128, b: 0 };
const RGB ledoff = { r: 0, g: 0, b: 0 };
const RGB green = { r: 0, g: 255, b: 0 };
const RGB maroon = { r: 128, g: 0, b: 0 };
const RGB amber = { r: 255, g: 194, b: 0 };
const RGB blue = { r: 46, g: 103, b: 248 };
const RGB fuchsia = { r: 255, g: 0, b: 255 };

void _rgb_matrix_set_color_indices(uint8_t* indices, uint8_t size, RGB color) {
  for (uint8_t i = 0; i < size; i++) {
    rgb_matrix_set_color(indices[i], color.r, color.g, color.b);
  }
}

// Underglow
void _set_underglow_lights(void) {
  uint8_t UNDERGLOW_PRIMARY_INDICES[8] = { 2, 3, 4, 5, 37, 38, 39, 40 };
  uint8_t UNDERGLOW_SECONDARY_INDICES[4] = { 0, 1, 35, 36 };

  RGB layer_color = maroon;
  uint8_t layer = get_highest_layer(layer_state);
  switch (layer) {
    case _RAISE: layer_color = blue; break;
    case _LOWER: layer_color = green; break;
    case _ADJUST: layer_color = fuchsia; break;
  }
  _rgb_matrix_set_color_indices(UNDERGLOW_PRIMARY_INDICES, 8, layer_color);
  _rgb_matrix_set_color_indices(UNDERGLOW_SECONDARY_INDICES, 4, amber);
}

// Lighting up the RAISE and LOWER layer keys
void _set_layerkey_lights(void) {
  uint8_t LAYERKEY_INDICES[2] = { 34, 69 };
  const RGB gray = {r: 64, g: 64, b: 64 };
  _rgb_matrix_set_color_indices(LAYERKEY_INDICES, 2, gray);
}

// Lighting up specific useful keys per layer
void _set_raise_layer_lights(void) {
  // Layer key highlight
  uint8_t LAYERKEY_INDEX[1] = { 34 };
  _rgb_matrix_set_color_indices(LAYERKEY_INDEX, 1, white);
  uint8_t OFFLAYERKEY_INDEX[1] = { 69 };
  _rgb_matrix_set_color_indices(OFFLAYERKEY_INDEX, 1, ledoff);

  // Symbols and non-alphanumeric keys
  uint8_t SYMBOLKEYS_INDICES[2] = { 11, 47 };
  const RGB teal = { r: 0, g: 128, b: 128 };
  _rgb_matrix_set_color_indices(SYMBOLKEYS_INDICES, 2, teal);

  // System/LED functions
  uint8_t SYSTEMKEYS_INDICES[9] = { 18, 19, 20, 27, 28, 29, 31, 32, 33 };
  _rgb_matrix_set_color_indices(SYSTEMKEYS_INDICES, 9, olive);

  // Special SLEEP function
  uint8_t BOOTKEY_INDEX[1] = { 30 };
  _rgb_matrix_set_color_indices(BOOTKEY_INDEX, 1, red);
}

void _set_lower_layer_lights(void) {
  // Layer key highlight
  uint8_t LAYERKEY_INDEX[1] = { 69 };
  _rgb_matrix_set_color_indices(LAYERKEY_INDEX, 1, white);
  uint8_t OFFLAYERKEY_INDEX[1] = { 34 };
  _rgb_matrix_set_color_indices(OFFLAYERKEY_INDEX, 1, ledoff);

  // Navigation keys
  uint8_t NAVKEYS_INDICES[8] = { 14, 20, 21, 22, 49, 55, 56, 57 };
  _rgb_matrix_set_color_indices(NAVKEYS_INDICES, 8, green);

  // Home/End/PageUp/PageDn
  uint8_t NAVJUMPKEYS_INDICES[4] = { 46, 47, 58, 59 };
  const RGB violet = { r: 155, g: 38, b: 182 };
  _rgb_matrix_set_color_indices(NAVJUMPKEYS_INDICES, 4, violet);

  // Special BOOT function
  uint8_t BOOTKEY_INDEX[1] = { 65 };
  _rgb_matrix_set_color_indices(BOOTKEY_INDEX, 1, red);
}

void _set_adjust_layer_lights(void) {
  uint8_t LAYERKEY_INDICES[2] = { 34, 69 };
  _rgb_matrix_set_color_indices(LAYERKEY_INDICES, 2, white);
}

void _set_qwerty_layer_lights(void) {
  // Navigation keys
  uint8_t NAVKEYS_INDICES[4] = { 32, 33, 67, 68 };
  _rgb_matrix_set_color_indices(NAVKEYS_INDICES, 4, green);
}

bool rgb_matrix_indicators_user(void) {
  // Post init code 
  _set_underglow_lights();
  _set_layerkey_lights();

  uint8_t layer = get_highest_layer(layer_state);
  switch (layer) {
    case _RAISE: _set_raise_layer_lights(); break;
    case _LOWER: _set_lower_layer_lights(); break;
    case _ADJUST: _set_adjust_layer_lights(); break;
    case _QWERTY: _set_qwerty_layer_lights(); break;
  }

  return true;
}

#endif // RGB_MATRIX_ENABLE