/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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
#include "config.h"
#include "rgb_matrix_map.h"

// EEPROM Memory. Avoid writing too much as it has limited writes
typedef union {
    uint32_t raw;
    struct {
        uint8_t layer :4;
    };
} user_config_t;

user_config_t user_config;

// Layer Aliases
enum layers {
    _BASE = 0, // Default Layer
    _VIM = 1,  // Vim Layer
    _JAP = 2,  // Japanese Layer
    _FN = 3    // Funtion Layer
};

enum new_keycodes {
    KCM_CAPS = SAFE_RANGE
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [_BASE] = LAYOUT(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        MO(_FN),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,  KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_VIM] = LAYOUT(
        KC_ESC,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          KC_MUTE,
        KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        LT(_FN, KC_ESC), KC_A,KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,           KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL,  KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_FN] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, TO(_BASE), TO(_VIM), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, EE_CLR,          _______,
        _______, _______, _______, _______, RGB_VAI, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, KC_CAPS, RGB_HUI, DB_TOGG, NK_TOGG, _______, _______, _______, _______,          KC_MPLY, RGB_MOD, _______,
        _______, _______, KC_SCRL,                            _______,                            KC_MPRV, _______, KC_MNXT, RGB_SPD, RGB_RMOD, RGB_SPI
    )
};
// clang-format on

/*
    Time delay to interpret a key press as a hold
    See config.h for time value
*/
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        default:
            return TAPPING_TERM;
    }
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

/*
    Runs after keyboard is intialized
    Set start RGB here
*/
void keyboard_post_init_user(void) {
    debug_enable=true;
    // debug_matrix=true;

    user_config.raw = eeconfig_read_user();
    layer_on(user_config.layer);
    // layer_on(_VIM); // Set layer to VIM. Less annoyance during development
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    // printf("post_process_record_user: ");

    // Update EEPROM Layer if layer is changed
    uint8_t cur_layer = get_highest_layer(layer_state);
    if (cur_layer != _FN && cur_layer != user_config.layer) {
        // printf("CHANGING LAYER to %d\n", cur_layer);
        user_config.layer = cur_layer;
        eeconfig_update_user(user_config.raw);
    }
}

/*
    RGB Behavior
*/
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state)) {
        case _FN:
            // Layer Transition Keys
            rgb_matrix_set_color(LED_FN, RGB_DARK_GREEN);
            // rgb_matrix_set_color(LED_CAPS, RGB_GREEN);

            // Discord Muting
            rgb_matrix_set_color(LED_LALT, RGB_GREEN_YELLOW);

            // Music Controls
            rgb_matrix_set_color(LED_RALT, RGB_SEA_GREEN);
            rgb_matrix_set_color(LED_RSFT, RGB_SEA_GREEN);
            rgb_matrix_set_color(LED_RCTL, RGB_SEA_GREEN);

            if (layer_state_is(_VIM)) {
                rgb_matrix_set_color(LED_2, RGB_CYAN_DIM);
            } else { // BASE LAYER LED
                rgb_matrix_set_color(LED_1, RGB_CYAN_DIM);
            }
        break;
    };
    return false;
}

/*
    Called when EEPROM (Persistent Memory) is reset by user
*/
void eeconfig_init_user(void) {
    user_config.raw = 0; // Clear EEPROM Struct
    user_config.layer = 1; // VIM Layer
    rgb_matrix_enable();
    rgb_matrix_sethsv(120, 100, 0);
    rgb_matrix_mode(1);
    rgb_matrix_set_speed(64);
    eeconfig_update_user(user_config.raw); // Write Struct to EEPROM.
}

// OPTIMIZATIONS
uint16_t keycode_config(uint16_t keycode) { return keycode; }
uint8_t mod_config(uint8_t mod) { return mod; }