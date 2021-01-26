//
// Created by jonas on 26/01/2021.
//

#include "scene_death.h"
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "scene_Chapter1.h"
#include <libgba-sprite-engine/effects/fade_out_scene.h>

void scene_death::load() {

    /*
     * Background handler
     *  MAPLAYOUT_32X32
        MAPLAYOUT_32X64
        MAPLAYOUT_64X32
        MAPLAYOUT_64X64
     */
/*
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 |
                  DCNT_BG1; //Als dit aanstaat kan bg index al vanaf 0. zoniet van index 1.
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bgPal, sizeof(bgPal)));
    bg_C1 = std::unique_ptr<Background>(new Background(1, bgTiles, sizeof(bgTiles), bgMap, sizeof(bgMap), MAPLAYOUT_64X64));
    bg_C1.get()->useMapScreenBlock(26); //data size van tiles dus 16
*/
    TextStream::instance().setText("YOU DIED", 15, 5);
    TextStream::instance().setText("PRESS START TO PLAY AGAIN ", 16, 5);
}
void scene_death::tick(u16 keys) {
    if(keys & KEY_START) {
        if (!engine->isTransitioning()) {
            //MUSIC?//engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);
            TextStream::instance() << "entered: starting next scene";
            engine->transitionIntoScene(new scene_Chapter1(engine), new FadeOutScene(2));
        }
    }
}