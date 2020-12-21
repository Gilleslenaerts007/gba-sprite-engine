//
// Created by Gille on 12/14/2020.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "scene_Chapter1.h"
#include "pixel_player.h"
#include "bg_Chapter1.h"

std::vector<Background *> scene_Chapter1::backgrounds() {
    return {bg_C1.get()};//, bg_C2.get(), bg_C3.get()};
}

/*
 * Current sprites on the scene?
 */
std::vector<Sprite *> scene_Chapter1::sprites() {
    return { player.get(), enemy.get() };
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
void scene_Chapter1::load() {
    /*
     * Bij de palletten moeten de kleuren in 16bit formaat opgemaakt worden.
     * De tiles en map mogen 32bit opgemaakt/omgezet worden.
     * */

    /*
     * Background handler
     *  MAPLAYOUT_32X32
        MAPLAYOUT_32X64
        MAPLAYOUT_64X32
        MAPLAYOUT_64X64
     */
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Als dit aanstaat kan bg index al vanaf 0. zoniet van index 1.
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bg500Pal, sizeof(bg500Pal)));
    bg_C1 = std::unique_ptr<Background>(new Background(0, bg500Tiles, sizeof(bg500Tiles), bg500Map, sizeof(bg500Map), MAPLAYOUT_64X64));
    bg_C1.get()->useMapScreenBlock(16); //data size van tiles dus 16

    /*
    bg_C2 = std::unique_ptr<Background>(new Background(1, bg1Tiles, sizeof(bg1Tiles), bg1Map, sizeof(bg1Map), MAPLAYOUT_64X64));
    bg_C2.get()->useMapScreenBlock(16);
     */


    /*
     * Sprite handler
     * Width x length
     */
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(SharedPlayerPal, sizeof(SharedPlayerPal)));
    SpriteBuilder<Sprite> builder;
    SpriteBuilder<AffineSprite> affineBuilder;



    enemy = affineBuilder
            .withData(FrontPlayerTiles, sizeof(FrontPlayerTiles))
            .withSize(SIZE_16_16)
            //.withVelocity(1, 1)
            .withLocation(1, 1)
            //.withVelocity(1, 1)
            .buildPtr();
    player = affineBuilder
            .withData(FrontPlayerTiles, sizeof(FrontPlayerTiles))
            .withSize(SIZE_16_16)
            .withLocation(112, 72)
            .withAnimated(2, 5)
            //.withVelocity(1, 1)
            .withinBounds()
            .buildPtr();
    /*
    bullet = builder
            .withData(piskelTiles, sizeof(piskelTiles))
            .withSize(SIZE_8_8)
            .withLocation(100, 50)
            .buildPtr();
    */

    //TextStream::instance().setText("PRESS START", 3, 8);
    /*
    bg_C3 = std::unique_ptr<Background>(new Background(1, tilesetOpenGameTiles, sizeof(tilesetOpenGameTiles), affinemap, sizeof(affinemap)));
    bg_C3.get()->useMapScreenBlock(8);
     */
    //engine->getTimer()->start();
    //engine->enqueueMusic(zelda_music_16K_mono, zelda_music_16K_mono_bytes);
}


/*
 * Need a function that when pressing left or right, the player also rotates slightly into the direction he is pressing.
 * pressing left, rotates the player down or up depending on the angle he is in.
 *
 */
void scene_Chapter1::tick(u16 keys) {
    //TextStream::instance().setText(engine->getTimer()->to_string(), 18, 1);
    static int x,y, jumpcount = 0;
    static bool jump = 0;
    if(pressingAorB && !((keys & KEY_A) || (keys & KEY_B))) {
        //engine->getTimer()->toggle();
        pressingAorB = false;
    }

    if(keys & KEY_START)
    {
        if(!engine->isTransitioning()) {
            //engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);

            TextStream::instance() << "entered: starting next scene";

            //engine->transitionIntoScene(new FlyingStuffScene(engine), new FadeOutScene(2));
        }

    }
    else if(keys & allkeycheck) {

        playerPosX = player->getX();
        playerPosY = player->getY();

        if (keys & KEY_LEFT) {
            if (scrollX > 0 && playerPosX <= 112) { scrollX -= 1; player->setVelocity(0,0);}
            else player->setVelocity(-1, 0);
        } else if (keys & KEY_RIGHT) {
            if (scrollX < 260 && playerPosX >= 112) { scrollX += 1; player->setVelocity(0,0);}
            else player->setVelocity(+1, 0);
        } else if (keys & KEY_UP) {
            if (scrollY > 0 && playerPosY <= 72) { scrollY -= 1; player->setVelocity(0,0);}
            else player->setVelocity(0, -1);
        } else if (keys & KEY_DOWN) {
            if (scrollY < 340 && playerPosY >= 72) { scrollY += 1; player->setVelocity(0,0);}
            else player->setVelocity(0, +1);
            player->animateToFrame(1);
        } else if ((keys & KEY_A) || (keys & KEY_B)) {
            pressingAorB = true;
        }
    }
    else player->setVelocity(0, 0); rotation = 0;
//player->stopAnimating();

    //rotation += rotationDiff;
    //enemy.get()->rotate(rotation);
    player.get()->rotate(rotation);
    bg_C1.get()->scroll(scrollX, scrollY);

};
