#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"
#include "keymap_jp.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |  Alt |Adjust|Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
    [_QWERTY] = LAYOUT(
        KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T,                   KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G,                   KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B,                  KC_N, KC_M, KC_COMM, KC_DOT, KC_UP, KC_ENT,
        KC_LCTRL, KC_LGUI, KC_LALT, RAISE, LOWER, KC_SPC,       KC_LANG1, LOWER, RAISE, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_LOWER] = LAYOUT(
        KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                     KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_DEL,
        KC_EXLM, KC_AT, KC_HASH, KC_DLR, KC_PERC, JP_AMPR,      KC_AMPR, JP_LPRN, JP_RPRN, S(JP_BSLS), JP_CIRC, JP_YEN,
        KC_LSFT, _______, _______, _______, _______, _______,   JP_AT, JP_LBRC, JP_RBRC, KC_SLSH, KC_HOME, KC_ENT,
        ADJUST, _______, _______, RAISE, LOWER, ADJUST,         KC_LANG2, LOWER, RAISE, _______, KC_END, _______
    ),

    [_RAISE] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,               KC_F7, KC_F8, KC_F9, KC_F10, S(KC_MINS), KC_BSPC,
        _______, _______, _______, _______, _______, _______,   KC_F11, KC_F12, _______, S(JP_BSLS), S(JP_CIRC), S(JP_YEN),
        _______, _______, _______, _______, _______, _______,   S(JP_AT), S(JP_LBRC), S(JP_RBRC), S(KC_SLSH), KC_PGUP, _______,
        _______, _______, _______, _______, _______, _______,   _______, _______, _______, _______, KC_PGDOWN, _______
    ),

    [_ADJUST] = LAYOUT(
        BL_TOGG, BL_STEP, BL_ON, BL_OFF, BL_INC, BL_DEC,        _______, _______, _______, _______, _______, _______,
        RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI,   _______, _______, _______, _______, _______, _______,
        _______, _______, RGB_VAD, RGB_VAI, _______, _______,   _______, _______, _______, _______, _______, _______,
        RESET, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______, _______
    )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
