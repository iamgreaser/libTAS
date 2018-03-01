/*
    Copyright 2015-2018 Clément Gallet <clement.gallet@ens-lyon.org>

    This file is part of libTAS.

    libTAS is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    libTAS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with libTAS.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "sdlkeyboardlayout.h"
#include "../logging.h"

namespace libtas {

static const SDL_Keycode SDL_default_keymap[SDL_NUM_SCANCODES] = {
    0, 0, 0, 0,
    'a',
    'b',
    'c',
    'd',
    'e',
    'f',
    'g',
    'h',
    'i',
    'j',
    'k',
    'l',
    'm',
    'n',
    'o',
    'p',
    'q',
    'r',
    's',
    't',
    'u',
    'v',
    'w',
    'x',
    'y',
    'z',
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    SDLK_RETURN,
    SDLK_ESCAPE,
    SDLK_BACKSPACE,
    SDLK_TAB,
    SDLK_SPACE,
    '-',
    '=',
    '[',
    ']',
    '\\',
    '#',
    ';',
    '\'',
    '`',
    ',',
    '.',
    '/',
    SDLK_CAPSLOCK,
    SDLK_F1,
    SDLK_F2,
    SDLK_F3,
    SDLK_F4,
    SDLK_F5,
    SDLK_F6,
    SDLK_F7,
    SDLK_F8,
    SDLK_F9,
    SDLK_F10,
    SDLK_F11,
    SDLK_F12,
    SDLK_PRINTSCREEN,
    SDLK_SCROLLLOCK,
    SDLK_PAUSE,
    SDLK_INSERT,
    SDLK_HOME,
    SDLK_PAGEUP,
    SDLK_DELETE,
    SDLK_END,
    SDLK_PAGEDOWN,
    SDLK_RIGHT,
    SDLK_LEFT,
    SDLK_DOWN,
    SDLK_UP,
    SDLK_NUMLOCKCLEAR,
    SDLK_KP_DIVIDE,
    SDLK_KP_MULTIPLY,
    SDLK_KP_MINUS,
    SDLK_KP_PLUS,
    SDLK_KP_ENTER,
    SDLK_KP_1,
    SDLK_KP_2,
    SDLK_KP_3,
    SDLK_KP_4,
    SDLK_KP_5,
    SDLK_KP_6,
    SDLK_KP_7,
    SDLK_KP_8,
    SDLK_KP_9,
    SDLK_KP_0,
    SDLK_KP_PERIOD,
    0,
    SDLK_APPLICATION,
    SDLK_POWER,
    SDLK_KP_EQUALS,
    SDLK_F13,
    SDLK_F14,
    SDLK_F15,
    SDLK_F16,
    SDLK_F17,
    SDLK_F18,
    SDLK_F19,
    SDLK_F20,
    SDLK_F21,
    SDLK_F22,
    SDLK_F23,
    SDLK_F24,
    SDLK_EXECUTE,
    SDLK_HELP,
    SDLK_MENU,
    SDLK_SELECT,
    SDLK_STOP,
    SDLK_AGAIN,
    SDLK_UNDO,
    SDLK_CUT,
    SDLK_COPY,
    SDLK_PASTE,
    SDLK_FIND,
    SDLK_MUTE,
    SDLK_VOLUMEUP,
    SDLK_VOLUMEDOWN,
    0, 0, 0,
    SDLK_KP_COMMA,
    SDLK_KP_EQUALSAS400,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    SDLK_ALTERASE,
    SDLK_SYSREQ,
    SDLK_CANCEL,
    SDLK_CLEAR,
    SDLK_PRIOR,
    SDLK_RETURN2,
    SDLK_SEPARATOR,
    SDLK_OUT,
    SDLK_OPER,
    SDLK_CLEARAGAIN,
    SDLK_CRSEL,
    SDLK_EXSEL,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    SDLK_KP_00,
    SDLK_KP_000,
    SDLK_THOUSANDSSEPARATOR,
    SDLK_DECIMALSEPARATOR,
    SDLK_CURRENCYUNIT,
    SDLK_CURRENCYSUBUNIT,
    SDLK_KP_LEFTPAREN,
    SDLK_KP_RIGHTPAREN,
    SDLK_KP_LEFTBRACE,
    SDLK_KP_RIGHTBRACE,
    SDLK_KP_TAB,
    SDLK_KP_BACKSPACE,
    SDLK_KP_A,
    SDLK_KP_B,
    SDLK_KP_C,
    SDLK_KP_D,
    SDLK_KP_E,
    SDLK_KP_F,
    SDLK_KP_XOR,
    SDLK_KP_POWER,
    SDLK_KP_PERCENT,
    SDLK_KP_LESS,
    SDLK_KP_GREATER,
    SDLK_KP_AMPERSAND,
    SDLK_KP_DBLAMPERSAND,
    SDLK_KP_VERTICALBAR,
    SDLK_KP_DBLVERTICALBAR,
    SDLK_KP_COLON,
    SDLK_KP_HASH,
    SDLK_KP_SPACE,
    SDLK_KP_AT,
    SDLK_KP_EXCLAM,
    SDLK_KP_MEMSTORE,
    SDLK_KP_MEMRECALL,
    SDLK_KP_MEMCLEAR,
    SDLK_KP_MEMADD,
    SDLK_KP_MEMSUBTRACT,
    SDLK_KP_MEMMULTIPLY,
    SDLK_KP_MEMDIVIDE,
    SDLK_KP_PLUSMINUS,
    SDLK_KP_CLEAR,
    SDLK_KP_CLEARENTRY,
    SDLK_KP_BINARY,
    SDLK_KP_OCTAL,
    SDLK_KP_DECIMAL,
    SDLK_KP_HEXADECIMAL,
    0, 0,
    SDLK_LCTRL,
    SDLK_LSHIFT,
    SDLK_LALT,
    SDLK_LGUI,
    SDLK_RCTRL,
    SDLK_RSHIFT,
    SDLK_RALT,
    SDLK_RGUI,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    SDLK_MODE,
    SDLK_AUDIONEXT,
    SDLK_AUDIOPREV,
    SDLK_AUDIOSTOP,
    SDLK_AUDIOPLAY,
    SDLK_AUDIOMUTE,
    SDLK_MEDIASELECT,
    SDLK_WWW,
    SDLK_MAIL,
    SDLK_CALCULATOR,
    SDLK_COMPUTER,
    SDLK_AC_SEARCH,
    SDLK_AC_HOME,
    SDLK_AC_BACK,
    SDLK_AC_FORWARD,
    SDLK_AC_STOP,
    SDLK_AC_REFRESH,
    SDLK_AC_BOOKMARKS,
    SDLK_BRIGHTNESSDOWN,
    SDLK_BRIGHTNESSUP,
    SDLK_DISPLAYSWITCH,
    SDLK_KBDILLUMTOGGLE,
    SDLK_KBDILLUMDOWN,
    SDLK_KBDILLUMUP,
    SDLK_EJECT,
    SDLK_SLEEP,
};

static const SDL1::SDLKey SDL1_default_keymap[SDL_NUM_SCANCODES] = {
    SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_a,
    SDL1::SDLK_b,
    SDL1::SDLK_c,
    SDL1::SDLK_d,
    SDL1::SDLK_e,
    SDL1::SDLK_f,
    SDL1::SDLK_g,
    SDL1::SDLK_h,
    SDL1::SDLK_i,
    SDL1::SDLK_j,
    SDL1::SDLK_k,
    SDL1::SDLK_l,
    SDL1::SDLK_m,
    SDL1::SDLK_n,
    SDL1::SDLK_o,
    SDL1::SDLK_p,
    SDL1::SDLK_q,
    SDL1::SDLK_r,
    SDL1::SDLK_s,
    SDL1::SDLK_t,
    SDL1::SDLK_u,
    SDL1::SDLK_v,
    SDL1::SDLK_w,
    SDL1::SDLK_x,
    SDL1::SDLK_y,
    SDL1::SDLK_z,
    SDL1::SDLK_1,
    SDL1::SDLK_2,
    SDL1::SDLK_3,
    SDL1::SDLK_4,
    SDL1::SDLK_5,
    SDL1::SDLK_6,
    SDL1::SDLK_7,
    SDL1::SDLK_8,
    SDL1::SDLK_9,
    SDL1::SDLK_0,
    SDL1::SDLK_RETURN,
    SDL1::SDLK_ESCAPE,
    SDL1::SDLK_BACKSPACE,
    SDL1::SDLK_TAB,
    SDL1::SDLK_SPACE,
	SDL1::SDLK_MINUS,
	SDL1::SDLK_EQUALS,
	SDL1::SDLK_LEFTBRACKET,
	SDL1::SDLK_RIGHTBRACKET,
	SDL1::SDLK_BACKSLASH,
	SDL1::SDLK_HASH,
	SDL1::SDLK_SEMICOLON,
	SDL1::SDLK_QUOTE,
	SDL1::SDLK_BACKQUOTE,
	SDL1::SDLK_COMMA,
	SDL1::SDLK_PERIOD,
	SDL1::SDLK_SLASH,
    SDL1::SDLK_CAPSLOCK,
    SDL1::SDLK_F1,
    SDL1::SDLK_F2,
    SDL1::SDLK_F3,
    SDL1::SDLK_F4,
    SDL1::SDLK_F5,
    SDL1::SDLK_F6,
    SDL1::SDLK_F7,
    SDL1::SDLK_F8,
    SDL1::SDLK_F9,
    SDL1::SDLK_F10,
    SDL1::SDLK_F11,
    SDL1::SDLK_F12,
    SDL1::SDLK_PRINT,
	SDL1::SDLK_SCROLLOCK,
    SDL1::SDLK_PAUSE,
    SDL1::SDLK_INSERT,
    SDL1::SDLK_HOME,
    SDL1::SDLK_PAGEUP,
    SDL1::SDLK_DELETE,
    SDL1::SDLK_END,
    SDL1::SDLK_PAGEDOWN,
    SDL1::SDLK_RIGHT,
    SDL1::SDLK_LEFT,
    SDL1::SDLK_DOWN,
    SDL1::SDLK_UP,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_KP_DIVIDE,
    SDL1::SDLK_KP_MULTIPLY,
    SDL1::SDLK_KP_MINUS,
    SDL1::SDLK_KP_PLUS,
    SDL1::SDLK_KP_ENTER,
    SDL1::SDLK_KP1,
    SDL1::SDLK_KP2,
    SDL1::SDLK_KP3,
    SDL1::SDLK_KP4,
    SDL1::SDLK_KP5,
    SDL1::SDLK_KP6,
    SDL1::SDLK_KP7,
    SDL1::SDLK_KP8,
    SDL1::SDLK_KP9,
    SDL1::SDLK_KP0,
    SDL1::SDLK_KP_PERIOD,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_POWER,
    SDL1::SDLK_KP_EQUALS,
    SDL1::SDLK_F13,
    SDL1::SDLK_F14,
    SDL1::SDLK_F15,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_HELP,
    SDL1::SDLK_MENU,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_SYSREQ,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_CLEAR,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_LCTRL,
    SDL1::SDLK_LSHIFT,
    SDL1::SDLK_LALT,
    SDL1::SDLK_LMETA,
    SDL1::SDLK_RCTRL,
    SDL1::SDLK_RSHIFT,
    SDL1::SDLK_RALT,
    SDL1::SDLK_RMETA,
    SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN, SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_MODE,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
    SDL1::SDLK_UNKNOWN,
};

SDL_Scancode GetScanFromKey(SDL_Keycode keycode){
    for (int i=0; i<static_cast<int>(SDL_NUM_SCANCODES); i++)
        if (SDL_default_keymap[i] == keycode)
            return static_cast<SDL_Scancode>(i);
    return SDL_SCANCODE_UNKNOWN;
}

SDL_Scancode GetScanFromKey1(SDL1::SDLKey key){
    for (int i=0; i<static_cast<int>(SDL_NUM_SCANCODES); i++)
        if (SDL1_default_keymap[i] == key)
            return static_cast<SDL_Scancode>(i);
    return SDL_SCANCODE_UNKNOWN;
}

/* Override */ SDL_Keycode SDL_GetKeyFromScancode(SDL_Scancode scancode)
{
    debuglog(LCF_SDL | LCF_KEYBOARD, __func__, " called with scancode ", (int)scancode);
    SDL_Keycode keycode = SDL_default_keymap[scancode];
    debuglog(LCF_SDL | LCF_KEYBOARD, "   returning ", keycode);
    return keycode;
}

/* Override */ SDL_Scancode SDL_GetScancodeFromKey(SDL_Keycode key)
{
    debuglog(LCF_SDL | LCF_KEYBOARD, __func__, " called with key ", key);
    SDL_Scancode scancode = GetScanFromKey(key);
    debuglog(LCF_SDL | LCF_KEYBOARD, "   returning ", scancode);
    return scancode;
}

}
