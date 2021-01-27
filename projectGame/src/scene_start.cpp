//
// Created by Gille on 12/7/2020.
//



#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>
#include "scene_start.h"
#include "scene_Chapter1.h"
#include "bg_Menu.h"
#include "pixel_player.h"

/*
 * Current background on the scene?
 */
std::vector<Background *> scene_start::backgrounds() {
    return {bg.get()};
}

/*
 * Current sprites on the scene?
 */
std::vector<Sprite *> scene_start::sprites() {
    spritesVector.push_back(menu_char.get());
    spritesVector.push_back(menu_enemy.get());
    return { spritesVector };
}

/*
 * Declare a spritebuilder class of type class Sprite
 * sprite from class current scene (scene_start.h) = std::unique_ptr<Sprite> XXXXX;
 * assign spritebuilder to XXXXX
 * BUILDER has many many options make sure to check these !!!
 *
 * So for having 1 player moving around different levels maybe have a player scene ?
 * Other entities/enemies/boss are defined per scene class.
 */
void scene_start::load() {
    /*
     * Bij de palletten moeten de kleuren in 16bit formaat opgemaakt worden.
     * De tiles en map mogen 32bit opgemaakt/omgezet worden.
     * */
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(menuPal, sizeof(menuPal)));

    SpriteBuilder<Sprite> builder;

/*
 * Width x length
 */

    menu_char = builder
            .withData(PlayerFullTiles, sizeof(PlayerFullTiles))
            .withSize(SIZE_16_16)
            .withLocation(207, 142)
            .withinBounds()
            .buildPtr();
    menu_enemy = builder
               .withData(EnemyFullTiles, sizeof(EnemyFullTiles))
               .withSize(SIZE_16_16)
               .withLocation(182, 142)
               .withVelocity(rand() % 1, rand() % 1)
               .buildPtr();

    TextStream::instance().setText("Kill as much bandits ", 17, 0);
    TextStream::instance().setText("as possible !", 18, 0);
    TextStream::instance().setText("when ready PRESS START", 19, 0);

    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1;
    bg = std::unique_ptr<Background>(new Background(1, menuTiles, sizeof(menuTiles), menuMap, sizeof(menuMap)));
    bg.get()->useMapScreenBlock(16);
    //engine->getTimer()->start();
    //engine->enqueueMusic(zelda_music_16K_mono, zelda_music_16K_mono_bytes);
}

/*
 * deze functie loopt tot er geduwd wordt op een key (start menu)
 * if pressed check if engine transition is happening
 * call transition into new scene with engine paremeter & optional fadeout
 * if(!engine->isTransitioning())
 * engine->transitionIntoScene(new FlyingStuffScene(engine), new FadeOutScene(2));
 */

void scene_start::tick(u16 keys) {

    static int delay = 0;
    if(pressingAorB && !((keys & KEY_A) || (keys & KEY_B))) {
        //engine->getTimer()->toggle();
        pressingAorB = false;
    }

    if(keys & KEY_START) {
        if (!engine->isTransitioning()) {
            bg.get_deleter();
            //MUSIC?//engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);
            TextStream::instance() << "entered: starting next scene";
            engine->transitionIntoScene(new scene_Chapter1(engine), new FadeOutScene(2));
        }
    }

    else if((keys & KEY_A) || (keys & KEY_B))
    {
        pressingAorB = true;
    }

    delay++;

}