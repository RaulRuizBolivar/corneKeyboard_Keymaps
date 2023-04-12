#include QMK_KEYBOARD_H
#include "keycodes.h"

#ifdef OLED_ENABLE
#    include "oled.c"
#endif

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
#    include "rgb.c"
#endif

// clang-format
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,KC_QUOTE,KC_COMMA,  KC_DOT,    KC_P,    KC_Y,                         KC_F,    KC_G,    KC_C,    KC_R,   KC_L,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     CTL_T(KC_ESC),KC_A,  KC_O,    KC_E,    KC_U,    KC_I,                         KC_D,    KC_H,    KC_T,    KC_N, KC_S, KC_MINUS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,KC_SCLN,  KC_Q,    KC_J,    KC_K,    KC_X,                         KC_B,  KC_M, KC_W, KC_V,KC_Z,   RSFT_T(KC_KP_SLASH),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_LALT,LT(1,KC_SPC),GUI_T(KC_ENT),   GUI_T(KC_ENT),LT(2,KC_SPC), KC_RGUI
                                      //`--------------------------'  `--------------------------'

  ),
  
  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_LALT, XXXXXXX   ,KC_UP    , XXXXXXX , XXXXXXX,              XXXXXXX  ,XXXXXXX ,  XXXXXXX , XXXXXXX, QK_BOOT, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
CTL_T(KC_ESC),KC_RGUI,KC_LEFT,KC_DOWN,KC_RIGHT,XXXXXXX,                       XXXXXXX , XXXXXXX,XXXXXXX ,XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_LSFT, XXXXXXX   , XXXXXXX   , XXXXXXX   , XXXXXXX   ,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RSFT_T(KC_KP_SLASH),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    KC_LGUI, _______,  GUI_T(KC_ENT),   GUI_T(KC_ENT),LT(3,KC_SPC), KC_RGUI
                                      //`--------------------------'  `--------------------------'
  ),
  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, XXXXXXX, XXXXXXX ,KC_LBRC , KC_RBRC, XXXXXXX,                    KC_KP_PLUS  ,KC_1 ,  KC_2 , KC_3, KC_KP_SLASH, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
CTL_T(KC_ESC),KC_LPRN,KC_RPRN,KC_EQL,S(KC_DOT),KC_SLASH,                        KC_KP_MINUS , KC_4,KC_5 ,KC_6, KC_KP_ASTERISK, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX , KC_LCBR, KC_RCBR,XXXXXXX,                      XXXXXXX, KC_7   ,    KC_8,    KC_9, KC_0   , RSFT_T(KC_KP_SLASH),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                    KC_LGUI,LT(3,KC_SPC),GUI_T(KC_ENT),  GUI_T(KC_ENT),_______, KC_RGUI
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,  KC_AT, KC_CIRC, KC_AMPR, KC_PERC,                      SGUI(KC_KP_SLASH),  KC_LPRN , KC_RPRN, XXXXXXX, XXXXXXX, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
CTL_T(KC_ESC), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_KP_SLASH,  XXXXXXX, XXXXXXX, KC_EQL, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, RSFT_T(KC_KP_SLASH),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        KC_LGUI,_______,KC_ENT,   KC_ENT, _______, KC_RGUI
                                      //`--------------------------'  `--------------------------'
  ),
};
// clang-format off

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
layer_state_t layer_state_set_user(layer_state_t state) {
    /* For any layer other than default, save current RGB state and switch to layer-based RGB */
    if (layer_state_cmp(state, 0)) {
        restore_rgb_config();
    } else {
        uint8_t layer = get_highest_layer(state);
        if (layer_state_cmp(layer_state, 0)) save_rgb_config();
        rgb_by_layer(layer);
    }
    return state;
}
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
#ifdef OLED_ENABLE
    if (record->event.pressed) {
        oled_timer = timer_read();
        is_key_processed = true;
        add_keylog(keycode);
    }
#endif

    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            return false;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            return false;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        case RGB_MOD:
        case RGB_TOG:
        case RGB_HUI:
        case RGB_HUD:
        case RGB_SAI:
        case RGB_SAD:
        case RGB_VAI:
        case RGB_VAD:
        case RGB_SPI:
        case RGB_SPD:
            /* Override layer-based RGB and resume RGB effect to be able to preview changes */
            if (record->event.pressed) {
                restore_rgb_config();
                process_rgb(keycode, record);
                save_rgb_config();
            }
            return false;
        case RGBRST:
            if (record->event.pressed) {
#    ifdef RGBLIGHT_ENABLE
                eeconfig_update_rgblight_default();
                rgblight_enable();
#    elif RGB_MATRIX_ENABLE
                eeconfig_update_rgb_matrix_default();
                rgb_matrix_enable();
#    endif
                save_rgb_config();
            }
            return false;
#endif
    }
    return true;
}
