//
// Created by Gille on 1/26/2021.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "scene_death.h"
#include "bg_Menu.h"
#include "pixel_player.h"
#include "scene_Chapter1.h"
#include "scene_start.h"
#include "../audio/death.h"

scene_death::scene_death(const std::shared_ptr<GBAEngine> &engine) : Scene(engine){}

std::vector<Background *> scene_death::backgrounds() {
    return {bg.get()};
}


std::vector<Sprite *> scene_death::sprites() {
    return {};
}

void scene_death::load() {
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(menuPal, sizeof(menuPal)));
    engine.get()->enqueueSound(death, death_bytes, 16000);
    //REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1;
    bg = std::unique_ptr<Background>(new Background(1, menuTiles, sizeof(menuTiles), menuMap, sizeof(menuMap)));
    bg.get()->useMapScreenBlock(26);

    TextStream::instance().setText("You have died !.... ", 8, 5);
}

void scene_death::tick(u16 keys) {

    if(keys & KEY_START) {
            bg.get_deleter();
            engine->setScene(new scene_start(engine));
    }

}