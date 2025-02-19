//--------------------------------------------------------------
// File     : ub_Font_Arial_8x13.c
// Datum    : 18.02.2013
// Version  : 1.0
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
//
// Font-Settings : Monospace, Max-Width=16Pixel
// Ascii-Table   : First-Char = 32, Last-Char = 126
// Data-Layout   :
//        e.G. Ascii-'R'
//       "0x78,0x44,0x44,0x44,0x78,0x48,0x48,0x44,0x00,0x00"
//
//   0x78 = ".####..."
//   0x44 = ".#...#.."
//   0x44 = ".#...#.."
//   0x44 = ".#...#.."
//   0x78 = ".####..."
//   0x48 = ".#  #..."
//   0x48 = ".#  #..."
//   0x44 = ".#...#.."
//   0x00 = "........"
//   0x00 = "........"
//
//--------------------------------------------------------------

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "Font.h"

//--------------------------------------------------------------
// Font-Daten
// erstellt von UB mit PixelFontGenerator 1.0
//--------------------------------------------------------------
const uint8_t Arial_8x13[96][13] = {
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // Ascii = [ ]
{0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x10,0x00,0x00,0x00}, // Ascii = [!]
{0x28,0x28,0x28,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // Ascii = ["]
{0x14,0x14,0x14,0x7E,0x14,0x28,0x7E,0x28,0x28,0x28,0x00,0x00,0x00}, // Ascii = [#]
{0x3C,0x4A,0x4A,0x48,0x3C,0x0A,0x0A,0x4A,0x4A,0x3C,0x08,0x00,0x00}, // Ascii = [$]
{0x30,0x4A,0x4C,0x38,0x10,0x10,0x2C,0x52,0x12,0x0C,0x00,0x00,0x00}, // Ascii = [%]
{0x18,0x24,0x24,0x28,0x10,0x2A,0x4A,0x44,0x4A,0x3A,0x00,0x00,0x00}, // Ascii = [&]
{0x10,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // Ascii = [']
{0x00,0x04,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x08,0x08,0x04}, // Ascii = [(]
{0x00,0x20,0x10,0x10,0x08,0x08,0x08,0x08,0x08,0x08,0x10,0x10,0x20}, // Ascii = [)]
{0x10,0x38,0x10,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // Ascii = [*]
{0x00,0x00,0x10,0x10,0x10,0xFE,0x10,0x10,0x10,0x00,0x00,0x00,0x00}, // Ascii = [+]
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x00}, // Ascii = [,]
{0x00,0x00,0x00,0x00,0x00,0x00,0x3C,0x00,0x00,0x00,0x00,0x00,0x00}, // Ascii = [-]
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00}, // Ascii = [.]
{0x04,0x04,0x08,0x08,0x08,0x10,0x10,0x10,0x20,0x20,0x00,0x00,0x00}, // Ascii = [/]
{0x3C,0x42,0x42,0x42,0x4A,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [0]
{0x08,0x18,0x28,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00}, // Ascii = [1]
{0x3C,0x42,0x42,0x02,0x04,0x04,0x08,0x30,0x40,0x7E,0x00,0x00,0x00}, // Ascii = [2]
{0x3C,0x42,0x02,0x02,0x1C,0x02,0x02,0x42,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [3]
{0x04,0x0C,0x14,0x14,0x24,0x24,0x44,0x7E,0x04,0x04,0x00,0x00,0x00}, // Ascii = [4]
{0x7E,0x40,0x40,0x40,0x7C,0x42,0x02,0x02,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [5]
{0x1C,0x22,0x42,0x40,0x7C,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [6]
{0x7E,0x02,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x20,0x00,0x00,0x00}, // Ascii = [7]
{0x3C,0x42,0x42,0x42,0x3C,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [8]
{0x3C,0x42,0x42,0x42,0x42,0x3E,0x02,0x42,0x44,0x38,0x00,0x00,0x00}, // Ascii = [9]
{0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00}, // Ascii = [:]
{0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x10,0x10,0x10,0x00}, // Ascii = [;]
{0x00,0x00,0x02,0x0C,0x30,0x40,0x30,0x0C,0x02,0x00,0x00,0x00,0x00}, // Ascii = [<]
{0x00,0x00,0x00,0x7E,0x00,0x00,0x7E,0x00,0x00,0x00,0x00,0x00,0x00}, // Ascii = [=]
{0x00,0x00,0x40,0x30,0x0C,0x02,0x0C,0x30,0x40,0x00,0x00,0x00,0x00}, // Ascii = [>]
{0x3C,0x42,0x42,0x02,0x02,0x04,0x08,0x08,0x00,0x08,0x00,0x00,0x00}, // Ascii = [?]
{0x1C,0x22,0x42,0x4E,0x52,0x52,0x5E,0x40,0x20,0x1C,0x00,0x00,0x00}, // Ascii = [@]
{0x10,0x28,0x28,0x28,0x44,0x44,0x7C,0x44,0x82,0x82,0x00,0x00,0x00}, // Ascii = [A]
{0x7C,0x42,0x42,0x42,0x7C,0x42,0x42,0x42,0x42,0x7C,0x00,0x00,0x00}, // Ascii = [B]
{0x1C,0x22,0x42,0x40,0x40,0x40,0x40,0x42,0x22,0x1C,0x00,0x00,0x00}, // Ascii = [C]
{0x78,0x44,0x42,0x42,0x42,0x42,0x42,0x42,0x44,0x78,0x00,0x00,0x00}, // Ascii = [D]
{0x7E,0x40,0x40,0x40,0x7C,0x40,0x40,0x40,0x40,0x7E,0x00,0x00,0x00}, // Ascii = [E]
{0x7E,0x40,0x40,0x40,0x7C,0x40,0x40,0x40,0x40,0x40,0x00,0x00,0x00}, // Ascii = [F]
{0x1C,0x22,0x42,0x40,0x40,0x4E,0x42,0x42,0x22,0x1C,0x00,0x00,0x00}, // Ascii = [G]
{0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0x42,0x00,0x00,0x00}, // Ascii = [H]
{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,0x00}, // Ascii = [I]
{0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [J]
{0x42,0x44,0x48,0x48,0x50,0x70,0x48,0x48,0x44,0x42,0x00,0x00,0x00}, // Ascii = [K]
{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7E,0x00,0x00,0x00}, // Ascii = [L]
{0x82,0xC6,0xAA,0xAA,0x92,0x92,0x82,0x82,0x82,0x82,0x00,0x00,0x00}, // Ascii = [M]
{0x42,0x62,0x62,0x52,0x52,0x4A,0x4A,0x46,0x46,0x42,0x00,0x00,0x00}, // Ascii = [N]
{0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,0x00}, // Ascii = [O]
{0x7C,0x42,0x42,0x42,0x42,0x7C,0x40,0x40,0x40,0x40,0x00,0x00,0x00}, // Ascii = [P]
{0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x4A,0x24,0x1A,0x00,0x00,0x00}, // Ascii = [Q]
{0x7C,0x42,0x42,0x42,0x7C,0x44,0x44,0x42,0x42,0x42,0x00,0x00,0x00}, // Ascii = [R]
{0x3C,0x42,0x40,0x40,0x30,0x0C,0x02,0x02,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [S]
{0xFE,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00}, // Ascii = [T]
{0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [U]
{0x82,0x82,0x44,0x44,0x44,0x44,0x28,0x28,0x28,0x10,0x00,0x00,0x00}, // Ascii = [V]
{0x82,0x82,0x82,0x92,0x92,0xAA,0xAA,0xAA,0x44,0x44,0x00,0x00,0x00}, // Ascii = [W]
{0x42,0x24,0x24,0x18,0x10,0x08,0x18,0x24,0x24,0x42,0x00,0x00,0x00}, // Ascii = [X]
{0x82,0x44,0x44,0x28,0x28,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00}, // Ascii = [Y]
{0x7E,0x02,0x04,0x08,0x08,0x10,0x10,0x20,0x40,0x7E,0x00,0x00,0x00}, // Ascii = [Z]
{0x1C,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x1C}, // Ascii = [[]
{0x20,0x20,0x20,0x10,0x10,0x08,0x08,0x08,0x04,0x04,0x00,0x00,0x00}, // Ascii = [\]
{0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x38}, // Ascii = []]
{0x18,0x18,0x24,0x24,0x42,0x42,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // Ascii = [^]
{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00}, // Ascii = [_]
{0x20,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // Ascii = [`]
{0x00,0x00,0x00,0x3C,0x42,0x02,0x3E,0x42,0x46,0x3A,0x00,0x00,0x00}, // Ascii = [a]
{0x40,0x40,0x40,0x5C,0x62,0x42,0x42,0x42,0x62,0x5C,0x00,0x00,0x00}, // Ascii = [b]
{0x00,0x00,0x00,0x3C,0x42,0x40,0x40,0x40,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [c]
{0x02,0x02,0x02,0x3A,0x46,0x42,0x42,0x42,0x46,0x3A,0x00,0x00,0x00}, // Ascii = [d]
{0x00,0x00,0x00,0x3C,0x42,0x42,0x7E,0x40,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [e]
{0x0E,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,0x00}, // Ascii = [f]
{0x00,0x00,0x00,0x3A,0x46,0x42,0x42,0x42,0x46,0x3A,0x02,0x42,0x3C}, // Ascii = [g]
{0x40,0x40,0x40,0x5C,0x62,0x42,0x42,0x42,0x42,0x42,0x00,0x00,0x00}, // Ascii = [h]
{0x08,0x00,0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00}, // Ascii = [i]
{0x08,0x00,0x00,0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x70}, // Ascii = [j]
{0x40,0x40,0x40,0x44,0x48,0x50,0x70,0x48,0x44,0x42,0x00,0x00,0x00}, // Ascii = [k]
{0x38,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x00,0x00,0x00}, // Ascii = [l]
{0x00,0x00,0x00,0xFC,0x92,0x92,0x92,0x92,0x92,0x92,0x00,0x00,0x00}, // Ascii = [m]
{0x00,0x00,0x00,0x5C,0x62,0x42,0x42,0x42,0x42,0x42,0x00,0x00,0x00}, // Ascii = [n]
{0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x42,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [o]
{0x00,0x00,0x00,0x5C,0x62,0x42,0x42,0x42,0x62,0x5C,0x40,0x40,0x40}, // Ascii = [p]
{0x00,0x00,0x00,0x3A,0x46,0x42,0x42,0x42,0x46,0x3A,0x02,0x02,0x02}, // Ascii = [q]
{0x00,0x00,0x00,0x6C,0x32,0x20,0x20,0x20,0x20,0x20,0x00,0x00,0x00}, // Ascii = [r]
{0x00,0x00,0x00,0x3C,0x42,0x40,0x3C,0x02,0x42,0x3C,0x00,0x00,0x00}, // Ascii = [s]
{0x00,0x10,0x10,0x7C,0x10,0x10,0x10,0x10,0x10,0x0E,0x00,0x00,0x00}, // Ascii = [t]
{0x00,0x00,0x00,0x42,0x42,0x42,0x42,0x42,0x46,0x3A,0x00,0x00,0x00}, // Ascii = [u]
{0x00,0x00,0x00,0x82,0x44,0x44,0x44,0x28,0x28,0x10,0x00,0x00,0x00}, // Ascii = [v]
{0x00,0x00,0x00,0x92,0xAA,0xAA,0xAA,0xAA,0x44,0x44,0x00,0x00,0x00}, // Ascii = [w]
{0x00,0x00,0x00,0x44,0x28,0x10,0x10,0x10,0x28,0x44,0x00,0x00,0x00}, // Ascii = [x]
{0x00,0x00,0x00,0x42,0x22,0x24,0x14,0x14,0x08,0x08,0x08,0x10,0x60}, // Ascii = [y]
{0x00,0x00,0x00,0x7E,0x04,0x08,0x10,0x20,0x40,0x7E,0x00,0x00,0x00}, // Ascii = [z]
{0x18,0x10,0x10,0x10,0x10,0x20,0x20,0x10,0x10,0x10,0x10,0x10,0x18}, // Ascii = [{]
{0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10}, // Ascii = [|]
{0x18,0x08,0x08,0x08,0x08,0x04,0x04,0x08,0x08,0x08,0x08,0x08,0x18}, // Ascii = [}]
{0x00,0x00,0x00,0x00,0x32,0x4C,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, // Ascii = [~]
{0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF}  // Ascii = []
};

//--------------------------------------------------------------
// Font-Struktur
//--------------------------------------------------------------

TFTFontType ARIAL_8X13 = {(unsigned char*)Arial_8x13,FONT_TYPE_2BPP,8,13,32,127,NULL};
