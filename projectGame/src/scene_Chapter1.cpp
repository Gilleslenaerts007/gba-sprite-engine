//
// Created by Gille on 12/14/2020.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>

#include "scene_Chapter1.h"
#include "pixel_player.h"
#include "pixel_bullets.h"
#include "bg_Chapter1.h"
#include <algorithm>
std::vector<Background *> scene_Chapter1::backgrounds() {
    return {bg_C1.get()};//, bg_C2.get(), bg_C3.get()};
}

/*
 * Current sprites on the scene?
 */
std::vector<Sprite *> scene_Chapter1::sprites() {
    spritesVector = {};
    spritesVector.push_back(player.get());

    /*
    for (int i=0; i < bullets.size(); i++)
    {
        spritesVector.push_back(bullets.get());
    }
     */

        if (Bullets.size() != 0){
            for (int i=0; i < Bullets.size(); i++) // niet '<=' anders plek pointer te ver
            {
                spritesVector.push_back(Bullets[i].get());
            }
        }

    spritesVector.push_back(bulletHori.get());


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
    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));

    TimeBetweenShots = 15;


    player = builder
            .withData(PlayerFullTiles, sizeof(PlayerFullTiles))
            .withSize(SIZE_16_16)
            .withLocation(112, 72)
            //.withVelocity(1, 1)
            .withinBounds()
            .buildPtr();

    bulletVerti = builder
            .withData(BulletVertiTiles, sizeof(BulletVertiTiles))
            .withSize(SIZE_16_16)
            .withLocation(112, 72)
            .buildPtr();
    bulletHori = builder
            .withData(BulletHoriTiles, sizeof(BulletHoriTiles))
            .withSize(SIZE_16_16)
            .withLocation(-32, -32)
            .buildPtr();



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
    if (ShotCooldown != 0) {ShotCooldown--;}
    //TextStream::instance().setText(engine->getTimer()->to_string(), 18, 1);
    if(pressingAorB && !((keys & KEY_A) || (keys & KEY_B))) {
        //engine->getTimer()->toggle();
        pressingAorB = false;
    }
    int OldBulletSize;
    OldBulletSize = Bullets.size();
    if(keys & KEY_START)
    {
        if(!engine->isTransitioning()) {
            //engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);

            TextStream::instance() << "entered: starting next scene";

            //engine->transitionIntoScene(new FlyingStuffScene(engine), new FadeOutScene(2));
        }

    }




    if(keys & allkeycheck)
    {
        if (keys & KEY_A)
        {
            if (Bullets.size()<=10 && ShotCooldown == 0){shoot();}
            //player->animateToFrame(staticPlayerModel);
            player->flipHorizontally(boolPlayerFlipHori);
        }

        playerPosX = player->getX();
        playerPosY = player->getY();

        if (movetimer >= 7)
        {
            moveflag = !moveflag;
            movetimer = 0;
        }

        switch(keys)
        {
            case KEY_LEFT:  if(moveflag)player->animateToFrame(7);
                            else player->animateToFrame(8);
                            staticPlayerModel = 7;
                            boolPlayerFlipHori = true;
                            if (scrollX > 0 && playerPosX <= 112) { scrollX -= 1; player->setVelocity(0,0);}
                            else player->setVelocity(-1, 0);
                            playerfacingx = -1;
                            playerfacingy = 0;
                            break;

            case KEY_RIGHT: if(moveflag)player->animateToFrame(7);
                            else player->animateToFrame(8);
                            boolPlayerFlipHori = false;
                            staticPlayerModel = 7;
                            if (scrollX < 260 && playerPosX >= 112) { scrollX += 1; player->setVelocity(0,0);}
                            else player->setVelocity(1, 0);
                            playerfacingx = 1;
                            playerfacingy = 0;
                            break;

            case KEY_DOWN:  if(moveflag)player->animateToFrame(3);
                            else player->animateToFrame(2);
                            boolPlayerFlipHori = false;
                            staticPlayerModel = 1;
                            if (scrollY < 340 && playerPosY >= 72) { scrollY += 1; player->setVelocity(0,0);}
                            else  player->setVelocity(0, 1);
                            playerfacingx = 0;
                            playerfacingy = 1;
                            break;

            case KEY_UP:    playerfacingx = 0;
                            playerfacingy = -1;
                            ShotCooldown=0;
                            if(moveflag)player->animateToFrame(5);
                            else player->animateToFrame(6);
                            boolPlayerFlipHori = false;
                            staticPlayerModel = 4;
                            if (scrollY > 0 && playerPosY <= 72) { scrollY -= 1; player->setVelocity(0,0);}
                            else player->setVelocity(0, -1);
                            break;
            /*
            case KEY_A:     if (Bullets.size()<=10 && ShotCooldown == 0){shoot();}
                            break;
            */
            /*case KEY_UP:    if(moveflag)player->animateToFrame(5);
                            else player->animateToFrame(6);
                            player->flipHorizontally(false);
                            staticPlayerModel = 4;
                            if (scrollY > 0 && playerPosY <= 72) { scrollY -= 1; player->setVelocity(0,0);}
                            else player->setVelocity(0, -1);
                            break;
                            */

        }
        player->flipHorizontally(boolPlayerFlipHori);
        movetimer++;
        moving = true;
    }
    else
    {
        player->setVelocity(0, 0);
        rotation = 0;
        player->animateToFrame(staticPlayerModel);

        moving = false;
        boolPlayerShootHori = false;
        boolPlayerShootVerti = false;
    }

    //rotation += rotationDiff;
    //enemy.get()->rotate(rotation);
    //player.get()->rotate(rotation);


    OffScreen();
    if (OldBulletSize != Bullets.size())
    {
        engine.get()->updateSpritesInScene();
    }
    bg_C1.get()->scroll(scrollX, scrollY);
//    UpdateGame();

};
void scene_Chapter1::shoot() {
    Bullets.push_back(builder
                                                .withData(BulletHoriTiles, sizeof(BulletHoriTiles))
                                                .withSize(SIZE_16_16)
                                                .withLocation(player->getX(), player->getY())
                                                .withVelocity(playerfacingx*2,playerfacingy*2)
                                                .buildPtr());
    TextStream::instance().setText(std::string("bullets on screen: ") + std::to_string(Bullets.size()), 1, 1);
    ShotCooldown = TimeBetweenShots;
}
void scene_Chapter1::OffScreen() {
/*
    Bullets.erase(
            std::remove_if(Bullets.begin(), Bullets.end(), [](std::unique_ptr<Sprite> &s) { return s->isOffScreen(); }),
            Bullets.end());
*/

    for (int i = 0 ; i<Bullets.size();i++)
    {
        if (Bullets[i]->isOffScreen())
        {
            Bullets.erase(std::remove(Bullets.begin(), Bullets.end(), Bullets[i]));
            engine.get()->updateSpritesInScene();
//            engine->update();
        }
    }


}

void scene_Chapter1::UpdateGame() {

    if ( currentEnemies <= totalEnemies)
    {
        if (moving && spawnerTime <= 5000)
        {
            enemies.push_back( builder
                                       .withData(EnemyFullTiles, sizeof(EnemyFullTiles))
                                       .withSize(SIZE_16_16)
                                               //.withVelocity(1, 1)
                                       .withLocation(rand() % player->getX(), rand() % player->getY())
                                       .withVelocity(rand() % 1, rand() % 1)
                                       .buildPtr());
            spawnerTime = 0;
            currentEnemies++;
            updateSprites = true;
        }
        spawnerTime++;
    }


    /*
    if (updateSprites) {
        engine->updateSpritesInScene();
        updateSprites = false;
    }
    */
}
