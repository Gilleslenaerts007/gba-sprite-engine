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
#include "pixel_menu.h"
#include "manneke.h"
#include "bg1.h"
//#include "sample_sound.h"

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
    return { menu_picker.get() };
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
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(piskelPal, sizeof(piskelPal)));
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(testmapPal, sizeof(testmapPal)));

    SpriteBuilder<Sprite> builder;

/*
 * Width x length
 */

    menu_picker = builder
            .withData(piskelTiles, sizeof(piskelTiles))
            .withSize(SIZE_32_32)
            .withLocation(100, 50)
            .withinBounds()
            .buildPtr();

    TextStream::instance().setText("PRESS START", 3, 8);

    bg = std::unique_ptr<Background>(new Background(2, testmapTiles, sizeof(testmapTiles), testmapMap, sizeof(testmapMap)));
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
            //MUSIC?//engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);
            TextStream::instance() << "entered: starting next scene";
            engine->transitionIntoScene(new scene_Chapter1(engine), new FadeOutScene(2));
        }
    }
    else if(keys & KEY_UP)
    {
        if (menu_picker->getY() >= 40 && delay >= 10)
        {
            delay=0;
            menu_picker->moveTo(menu_picker->getX(), menu_picker->getY() - 10);
        }
    }
    else if(keys & KEY_DOWN)
    {
        if (menu_picker->getY() <= 80 && delay >= 10)
        {
            delay=0;
            menu_picker->moveTo(menu_picker->getX(), menu_picker->getY() + 10);
        }
    }

    else if((keys & KEY_A) || (keys & KEY_B))
    {
        pressingAorB = true;
    }

    delay++;

}