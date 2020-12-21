//
// Created by Gille on 12/14/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PIXEL_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PIXEL_PLAYER_H

#endif //GBA_SPRITE_ENGINE_PROJECT_PIXEL_PLAYER_H

//======================================================================
//
//	piskel, 32x32@8,
//	+ palette 32 entries, not compressed
//	+ 16 tiles not compressed
//	Total size: 64 + 1024 = 1088
//
//	Time-stamp: 2020-12-09, 17:53:01
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

const unsigned int SidewaysWalkingPlayerTiles[64] __attribute__((aligned(4)))=
        {
                0x03030000,0x03030303,0x01010300,0x01010101,0x01010103,0x01010101,0x01010103,0x01010101,
                0x01010103,0x01010101,0x01010103,0x01010101,0x01010103,0x01010101,0x01010103,0x01010101,
                0x03030303,0x00000303,0x01010101,0x00030101,0x03010101,0x00030103,0x01010101,0x00030101,
                0x01010101,0x00030103,0x01010101,0x00030103,0x01010101,0x03010101,0x01010101,0x03010101,
                0x01010300,0x01010101,0x01030000,0x01010101,0x03000000,0x01010101,0x03000000,0x02030202,
                0x03000000,0x02030202,0x03000000,0x03030101,0x00000000,0x04040403,0x03000000,0x03040404,
                0x01010101,0x00030101,0x03030101,0x00000303,0x01010101,0x00000003,0x03020202,0x00000000,
                0x03020202,0x00000000,0x03040404,0x00000000,0x04040403,0x00000003,0x04040300,0x00000304,
        };
const unsigned int FrontPlayerTiles[64] __attribute__((aligned(4)))=
        {
                0x03030000,0x03030303,0x01010300,0x01010101,0x01010103,0x01010101,0x01010103,0x01010101,
                0x01010103,0x01010303,0x01010103,0x01010101,0x01010103,0x01010303,0x01010103,0x01010303,
                0x03030303,0x00000303,0x01010101,0x00030101,0x01010101,0x03010101,0x01010101,0x03010101,
                0x03030101,0x03010101,0x01010101,0x03010101,0x03030101,0x03010101,0x03030101,0x03010101,
                0x01010300,0x01010303,0x01030000,0x01010101,0x02010300,0x01010101,0x02010103,0x02020202,
                0x02010103,0x02020202,0x03010103,0x03040404,0x03030300,0x00030404,0x03000000,0x00030404,
                0x03030101,0x00030101,0x01010101,0x00000301,0x01010101,0x00030102,0x02020202,0x03010102,
                0x02020202,0x03010102,0x04040403,0x03010103,0x04040300,0x00030303,0x04040300,0x00000003,
        };
const unsigned int FrontWalkingPlayerTiles[64] __attribute__((aligned(4)))=
        {
                0x03030000,0x03030303,0x01010300,0x01010101,0x01010103,0x01010101,0x01010103,0x01010101,
                0x01010103,0x01010303,0x01010103,0x01010101,0x01010103,0x01010303,0x01010103,0x01010303,
                0x03030303,0x00000303,0x01010101,0x00030101,0x01010101,0x03010101,0x01010101,0x03010101,
                0x03030101,0x03010101,0x01010101,0x03010101,0x03030101,0x03010101,0x03030101,0x03010101,
                0x01010300,0x01010303,0x01030000,0x01010101,0x02010300,0x01010101,0x02010103,0x02020202,
                0x02010103,0x02020202,0x03010103,0x03040404,0x03030300,0x00030404,0x00000000,0x00000000,
                0x03030101,0x00030101,0x01010101,0x00000301,0x01010101,0x00030102,0x02020202,0x03010103,
                0x03020202,0x03010101,0x03040403,0x03010101,0x04040300,0x00030303,0x04040300,0x00000003,
        };
const unsigned int SidewaysPlayerTiles[64] __attribute__((aligned(4)))=
        {
                0x03030000,0x03030303,0x01010300,0x01010101,0x01010103,0x01010101,0x01010103,0x01010101,
                0x01010103,0x01010101,0x01010103,0x01010101,0x01010103,0x01010101,0x01010103,0x01010101,
                0x03030303,0x00000303,0x01010101,0x00030101,0x03010101,0x00030103,0x01010101,0x00030101,
                0x01010101,0x00030103,0x01010101,0x00030103,0x01010101,0x03010101,0x01010101,0x03010101,
                0x01010300,0x01010101,0x01030000,0x01010101,0x03000000,0x01010101,0x03000000,0x02030202,
                0x03000000,0x02030202,0x03000000,0x04030101,0x00000000,0x04040403,0x00000000,0x04040403,
                0x01010101,0x00030101,0x03030101,0x00000303,0x01010101,0x00000003,0x03020202,0x00000000,
                0x03020202,0x00000000,0x00030304,0x00000000,0x00000304,0x00000000,0x00000304,0x00000000,
        };
const unsigned short SharedPlayerPal[6] __attribute__((aligned(4)))=
        {
                0x0000,0x3F1E,0x0C0E,0x14A5,0x0500,
        };