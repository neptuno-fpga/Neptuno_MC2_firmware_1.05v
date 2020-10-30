//
// Multicore 2
//
// Copyright (c) 2017-2020 - Victor Trucco
//
// Additional code, debug and fixes: Diogo Patrão
//
// All rights reserved
//
// Redistribution and use in source and synthezised forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
//
// Redistributions in synthesized form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// Neither the name of the author nor the names of other contributors may
// be used to endorse or promote products derived from this software without
// specific prior written permission.
//
// THIS CODE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// You are responsible for any legal issues arising from your use of this code.
//

#ifndef CHARROM_H
#define CHARROM_H

/*
Write protect.  Characters are defined in columns, not rows, LSB first
. . . . . . . .
. . * * * . . .
. * . . . * . .
. * . . . * . .
* * * * * * * .
* * * * * * * .
* * * * * * * .
. . . . . . . .
0x70,0x7c,0x72,0x72,0x72,0x7c,0x70,0x00,0x00

Write enable
. . . . . . . .
. . . . . * * .
. . . . * . . *
. . . . * . . *
* * * * * * . .
* * * * * * . .
* * * * * * . .
. . . . . . . .
0x70,0x70,0x70,0x70,0x7c,0x72,0x02,0x0c

Middle Dot
. . . . . . . .
. . . . . . . .
. . . * * . . .
. . . * * . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
. . . . . . . .
0x00,0x00,0x00,0x0c,0x0c,0x00,0x00,0x00

*/

// *character font
unsigned char charfont[128][8] =
{
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 0    [0x0]
        {0x55,0x55,0x55,0x55,0x55,0x55,0x55,0x55},         // 1    [0x1]
        {0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A,0x2A},         // 2    [0x2]
        {0x14,0x14,0x14,0x14,0x14,0x14,0x14,0x14},         // 3    [0x3]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 4    [0x4]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 5    [0x5]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 6    [0x6]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 7    [0x7]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 8    [0x8]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 9    [0x9]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 10   [0xa]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 11   [0xb]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 12   [0xc]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 13   [0xd]
        {0x00,0xc0,0xc0,0xe0,0x78,0x1f,0x00,0xff},         // 14   [0xe] atari logo left
        {0xff,0x00,0x1f,0x78,0xe0,0xc0,0xc0,0x00},         // 15   [0xf] atari logo right
        {0x08,0x08,0x1C,0x1C,0x3E,0x3E,0x7F,0x7F},         // 16   [0x10] arrow left
        {0x7F,0x7F,0x3E,0x3E,0x1C,0x1C,0x08,0x08},         // 17   [0x11] arrow right
        {0x00,0x10,0x18,0x7c,0x7c,0x18,0x10,0x00},         // 18   [0x12] arrow up
        {0x00,0x10,0x30,0x7c,0x7c,0x30,0x10,0x00},         // 19   [0x13] arrow down
        {0x1C,0x1C,0x1C,0x1C,0x1C,0x1C,0x00,0x00},         // 20   [0x14]
        {0x00,0x00,0x1C,0x1C,0x1C,0x1C,0x1C,0x1C},         // 21   [0x15]
        {0x00,0x7C,0x7C,0x38,0x38,0x10,0x10,0x00},         // 22   [0x16] mini arrow right
        {0x70,0x7c,0x72,0x72,0x72,0x7c,0x70,0x00},         // 23   [0x17] write protect
        {0x70,0x70,0x70,0x70,0x7c,0x72,0x02,0x0c},         // 24   [0x18] write enable
        {0x3e,0x3e,0x22,0x22,0x22,0x3e,0x3e,0x00},         // 25   [0x19] unchecked checkbox
        {0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x3e,0x00},         // 26   [0x1a] checked checkbox
        {0x00,0x00,0x00,0x0c,0x0c,0x00,0x00,0x00},         // 27   [0x1b] middle dot
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 28   [0x1c]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 29   [0x1d]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 30   [0x1e]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 31   [0x1f]
        {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},         // 32   [0x20]
        {0x00,0x00,0x00,0x5F,0x5F,0x00,0x00,0x00},         // 33   [0x21]
        {0x00,0x03,0x03,0x00,0x03,0x03,0x00,0x00},         // 34   [0x22]
        {0x14,0x7F,0x7F,0x14,0x7F,0x7F,0x14,0x00},         // 35   [0x23]
        {0x00,0x24,0x2E,0x6B,0x6B,0x3A,0x12,0x00},         // 36   [0x24]
        {0x4C,0x6A,0x36,0x18,0x6C,0x56,0x32,0x00},         // 37   [0x25]
        {0x30,0x7E,0x4F,0x59,0x77,0x3A,0x68,0x40},         // 38   [0x26]
        {0x00,0x00,0x04,0x07,0x03,0x00,0x00,0x00},         // 39   [0x27]
        {0x00,0x00,0x1C,0x3E,0x63,0x41,0x00,0x00},         // 40   [0x28]
        {0x00,0x00,0x41,0x63,0x3E,0x1C,0x00,0x00},         // 41   [0x29]
        {0x08,0x2A,0x3E,0x1C,0x1C,0x3E,0x2A,0x08},         // 42   [0x2a]
        {0x00,0x08,0x08,0x3E,0x3E,0x08,0x08,0x00},         // 43   [0x2b]
        {0x00,0x00,0x80,0xE0,0x60,0x00,0x00,0x00},         // 44   [0x2c]
        {0x00,0x08,0x08,0x08,0x08,0x08,0x08,0x00},         // 45   [0x2d]
        {0x00,0x00,0x00,0x60,0x60,0x00,0x00,0x00},         // 46   [0x2e]
        {0x40,0x60,0x30,0x18,0x0C,0x06,0x03,0x01},         // 47   [0x2f]
        {0x00,0x3E,0x7F,0x59,0x4D,0x7F,0x3E,0x00},         // 48   [0x30]
        {0x00,0x04,0x06,0x7F,0x7F,0x00,0x00,0x00},         // 49   [0x31]
        {0x00,0x42,0x63,0x71,0x59,0x4F,0x46,0x00},         // 50   [0x32]
        {0x00,0x22,0x63,0x49,0x49,0x7F,0x36,0x00},         // 51   [0x33]
        {0x18,0x1C,0x16,0x13,0x7F,0x7F,0x10,0x00},         // 52   [0x34]
        {0x00,0x27,0x67,0x45,0x45,0x7D,0x39,0x00},         // 53   [0x35]
        {0x00,0x3C,0x7E,0x4B,0x49,0x79,0x30,0x00},         // 54   [0x36]
        {0x00,0x01,0x01,0x71,0x79,0x0F,0x07,0x00},         // 55   [0x37]
        {0x00,0x36,0x7F,0x49,0x49,0x7F,0x36,0x00},         // 56   [0x38]
        {0x00,0x06,0x4F,0x49,0x69,0x3F,0x1E,0x00},         // 57   [0x39]
        {0x00,0x00,0x00,0x66,0x66,0x00,0x00,0x00},         // 58   [0x3a]
        {0x00,0x00,0x80,0xE6,0x66,0x00,0x00,0x00},         // 59   [0x3b]
        {0x00,0x08,0x08,0x14,0x14,0x22,0x22,0x00},         // 60   [0x3c]
        {0x00,0x14,0x14,0x14,0x14,0x14,0x14,0x00},         // 61   [0x3d]
        {0x00,0x22,0x22,0x14,0x14,0x08,0x08,0x00},         // 62   [0x3e]
        {0x00,0x02,0x03,0x51,0x59,0x0F,0x06,0x00},         // 63   [0x3f]
        {0x3E,0x7F,0x41,0x5D,0x55,0x1F,0x1E,0x00},         // 64   [0x40]
        {0x00,0x7E,0x7F,0x09,0x09,0x7F,0x7E,0x00},         // 65   [0x41]
        {0x00,0x7F,0x7F,0x49,0x49,0x7F,0x36,0x00},         // 66   [0x42]
        {0x00,0x1C,0x3E,0x63,0x41,0x41,0x41,0x00},         // 67   [0x43]
        {0x00,0x7F,0x7F,0x41,0x63,0x3E,0x1C,0x00},         // 68   [0x44]
        {0x00,0x7F,0x7F,0x49,0x49,0x41,0x41,0x00},         // 69   [0x45]
        {0x00,0x7F,0x7F,0x09,0x09,0x01,0x01,0x00},         // 70   [0x46]
        {0x00,0x3E,0x7F,0x41,0x49,0x7B,0x7A,0x00},         // 71   [0x47]
        {0x00,0x7F,0x7F,0x08,0x08,0x7F,0x7F,0x00},         // 72   [0x48]
        {0x00,0x00,0x41,0x7F,0x7F,0x41,0x00,0x00},         // 73   [0x49]
        {0x00,0x20,0x60,0x40,0x40,0x7F,0x3F,0x00},         // 74   [0x4a]
        {0x7F,0x7F,0x08,0x1C,0x36,0x63,0x41,0x00},         // 75   [0x4b]
        {0x00,0x7F,0x7F,0x40,0x40,0x40,0x40,0x00},         // 76   [0x4c]
        {0x7F,0x7F,0x06,0x0C,0x06,0x7F,0x7F,0x00},         // 77   [0x4d]
        {0x7F,0x7F,0x06,0x0C,0x18,0x7F,0x7F,0x00},         // 78   [0x4e]
        {0x00,0x3E,0x7F,0x41,0x41,0x7F,0x3E,0x00},         // 79   [0x4f]
        {0x00,0x7F,0x7F,0x09,0x09,0x0F,0x06,0x00},         // 80   [0x50]
        {0x3E,0x7F,0x41,0x61,0x7F,0x7E,0x40,0x00},         // 81   [0x51]
        {0x00,0x7F,0x7F,0x09,0x19,0x7F,0x66,0x00},         // 82   [0x52]
        {0x00,0x26,0x6F,0x4D,0x59,0x7B,0x32,0x00},         // 83   [0x53]
        {0x00,0x01,0x01,0x7F,0x7F,0x01,0x01,0x00},         // 84   [0x54]
        {0x00,0x3F,0x7F,0x40,0x40,0x7F,0x3F,0x00},         // 85   [0x55]
        {0x00,0x0F,0x3F,0x70,0x70,0x3F,0x0F,0x00},         // 86   [0x56]
        {0x7F,0x7F,0x30,0x18,0x30,0x7F,0x7F,0x00},         // 87   [0x57]
        {0x41,0x63,0x36,0x1C,0x1C,0x36,0x63,0x41},         // 88   [0x58]
        {0x01,0x03,0x06,0x7C,0x7C,0x06,0x03,0x01},         // 89   [0x59]
        {0x61,0x71,0x59,0x4D,0x47,0x43,0x41,0x00},         // 90   [0x5a]
        {0x00,0x00,0x7F,0x7F,0x41,0x41,0x00,0x00},         // 91   [0x5b]
        {0x01,0x03,0x06,0x0C,0x18,0x30,0x60,0x40},         // 92   [0x5c]
        {0x00,0x00,0x41,0x41,0x7F,0x7F,0x00,0x00},         // 93   [0x5d]
        {0x08,0x0C,0x06,0x03,0x06,0x0C,0x08,0x00},         // 94   [0x5e]
        {0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x00},         // 95   [0x5f]
        {0x00,0x00,0x00,0x03,0x07,0x04,0x00,0x00},         // 96   [0x60]
        {0x00,0x20,0x74,0x54,0x54,0x7C,0x78,0x00},         // 97   [0x61]
        {0x00,0x7F,0x7F,0x44,0x44,0x7C,0x38,0x00},         // 98   [0x62]
        {0x00,0x38,0x7C,0x44,0x44,0x44,0x00,0x00},         // 99   [0x63]
        {0x00,0x38,0x7C,0x44,0x44,0x7F,0x7F,0x00},         // 100  [0x64]
        {0x00,0x38,0x7C,0x54,0x54,0x5C,0x18,0x00},         // 101  [0x65]
        {0x00,0x04,0x7E,0x7F,0x05,0x05,0x00,0x00},         // 102  [0x66]
        {0x00,0x18,0xBC,0xA4,0xA4,0xFC,0x7C,0x00},         // 103  [0x67]
        {0x00,0x7F,0x7F,0x04,0x04,0x7C,0x78,0x00},         // 104  [0x68]
        {0x00,0x00,0x00,0x3D,0x7D,0x40,0x00,0x00},         // 105  [0x69]
        {0x00,0x80,0x80,0x80,0xFD,0x7D,0x00,0x00},         // 106  [0x6a]
        {0x00,0x7F,0x7F,0x10,0x38,0x6C,0x44,0x00},         // 107  [0x6b]
        {0x00,0x00,0x00,0x3F,0x7F,0x40,0x00,0x00},         // 108  [0x6c]
        {0x7C,0x7C,0x0C,0x18,0x0C,0x7C,0x78,0x00},         // 109  [0x6d]
        {0x00,0x7C,0x7C,0x04,0x04,0x7C,0x78,0x00},         // 110  [0x6e]
        {0x00,0x38,0x7C,0x44,0x44,0x7C,0x38,0x00},         // 111  [0x6f]
        {0x00,0xFC,0xFC,0x24,0x24,0x3C,0x18,0x00},         // 112  [0x70]
        {0x00,0x18,0x3C,0x24,0x24,0xFC,0xFC,0x00},         // 113  [0x71]
        {0x00,0x7C,0x7C,0x04,0x04,0x0C,0x08,0x00},         // 114  [0x72]
        {0x00,0x48,0x5C,0x54,0x54,0x74,0x20,0x00},         // 115  [0x73]
        {0x00,0x04,0x3F,0x7F,0x44,0x44,0x00,0x00},         // 116  [0x74]
        {0x00,0x3C,0x7C,0x40,0x40,0x7C,0x7C,0x00},         // 117  [0x75]
        {0x00,0x1C,0x3C,0x60,0x60,0x3C,0x1C,0x00},         // 118  [0x76]
        {0x3C,0x7C,0x60,0x30,0x60,0x7C,0x3C,0x00},         // 119  [0x77]
        {0x44,0x6C,0x38,0x10,0x38,0x6C,0x44,0x00},         // 120  [0x78]
        {0x00,0x1C,0xBC,0xE0,0x60,0x3C,0x1C,0x00},         // 121  [0x79]
        {0x00,0x44,0x64,0x74,0x5C,0x4C,0x44,0x00},         // 122  [0x7a]
        {0x00,0x08,0x08,0x3E,0x77,0x41,0x41,0x00},         // 123  [0x7b]
        {0x00,0x00,0x00,0x7F,0x7F,0x00,0x00,0x00},         // 124  [0x7c]
        {0x00,0x41,0x41,0x77,0x3E,0x08,0x08,0x00},         // 125  [0x7d]
        {0x02,0x01,0x01,0x03,0x02,0x02,0x01,0x00},         // 126  [0x7e]
        {0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x7F,0x00}          // 127  [0x7f]
};

#endif

