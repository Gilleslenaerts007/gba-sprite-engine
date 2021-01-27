//
// Created by Gille on 12/14/2020.
//

#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/gba/tonc_memdef.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/effects/fade_out_scene.h>

#include "scene_Chapter1.h"
#include "scene_death.h"
#include "pixel_player.h"
#include "pixel_bullets.h"
#include "bg_Chapter1.h"
#include "../audio/shot.h"
#include "../audio/spawn.h"
#include "../audio/hit.h"
#include <algorithm>

std::vector<Background *> scene_Chapter1::backgrounds() {
    return {bg_C1.get()};
}

/*
 * Collect current sprites on the scene and pass to engine.
 */
std::vector<Sprite *> scene_Chapter1::sprites() {
    spritesVector = {};
    spritesVector.push_back(player1->getSprite());
    if (!BulletsVector.empty()){
        for (int i=0; i < BulletsVector.size(); i++) // niet '<=' anders plek pointer te ver
        {
            //BulletsVerti[i]->flipVertically(true);
            spritesVector.push_back(BulletsVector[i]->BulletSprite.get());
        }
    }
    if (!enemiesvector.empty())
    {
        for (int i=0; i < enemiesvector.size(); i++) // niet '<=' anders plek pointer te ver
        {
            //BulletsVerti[i]->flipVertically(true);
            spritesVector.push_back(enemiesvector[i]->enemysprite.get());
        }
    }
    spritesVector.push_back(Offbulletscreen.get());
    spritesVector.push_back(Offbulletscreen2.get());
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
     * Background handler
     *  MAPLAYOUT_32X32
        MAPLAYOUT_32X64
        MAPLAYOUT_64X32
        MAPLAYOUT_64X64
     */
    REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Als dit aanstaat kan bg index al vanaf 0. zoniet van index 1.
    backgroundPalette = std::unique_ptr<BackgroundPaletteManager>(new BackgroundPaletteManager(bgPal, sizeof(bgPal)));
    bg_C1 = std::unique_ptr<Background>(new Background(1, bgTiles, sizeof(bgTiles), bgMap, sizeof(bgMap), MAPLAYOUT_64X64));
    bg_C1.get()->useMapScreenBlock(26); //data size van tiles dus 16

    foregroundPalette = std::unique_ptr<ForegroundPaletteManager>(new ForegroundPaletteManager(sharedPal, sizeof(sharedPal)));
    player1 = (new Player(builder, 112, 72, 5, 2) );

    Offbulletscreen = builder
                                          .withData(BulletHoriTiles, sizeof(BulletHoriTiles))
                                          .withSize(SIZE_16_16)
                                          .withLocation(-32, -32)
                                          .withVelocity(0,0)
                                          .buildPtr();
    Offbulletscreen2 = builder
                                          .withData(BulletHoriTiles, sizeof(BulletHoriTiles))
                                          .withSize(SIZE_16_16)
                                          .withLocation(-32, -32)
                                          .withVelocity(0,0)
                                          .buildPtr();


    TextStream::instance().setText("KILLS: ", 0, 0);
    TextStream::instance().setText("LIVES: ", 1, 0);
    TextStream::instance().setText("enemies alive:" + std::to_string(enemiesvector.size()), 18, 0);
    //engine->enqueueMusic(zelda_music_16K_mono, zelda_music_16K_mono_bytes);
}


/*
 * Player movement & key reads
 *
 */
void scene_Chapter1::tick(u16 keys) {

    if (pause) {
        TextStream::instance().setText("Difficulty going up..", 4, 37);
        TextStream::instance().setText("press ready", 5, 37);
        //MUSIC?//engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);
        if (keys & KEY_START) {
                pause = false;
                TextStream::instance().clear();
            }
        }
    else{

        if(pressingAorB && !((keys & KEY_A) || (keys & KEY_B))) {
            pressingAorB = false;
        }

        TextStream::instance().setText("enemies alive:"+ std::to_string(enemiesvector.size()), 18, 0);
        TextStream::instance().setText("KILLS:"+ std::to_string(player1->getPlayerKills()), 0, 0);
        TextStream::instance().setText("LIVES:"+ std::to_string(player1->getPlayerLives()), 1, 0);
        if (player1->shotcooldown != 0) { player1->shotcooldown --; }
        OffScreen();

        if (keys & KEY_A || pressingAorB)
        {
            //engine->enqueueMusic(shot, shot_bytes);
            engine.get()->enqueueSound(shot, shot_bytes, 16000);
            if (player1->getPlayerFaceX() != 0 )
            {
                update = TRUE;
                player1->Shoot(builder,&BulletsVector,&Offbulletscreen);
            }
            else {
                update = TRUE;
                player1->Shoot(builder,&BulletsVector,&Offbulletscreen2);
            }
        }

        player1->movePlayer(keys, &scrollX, &scrollY);
        moveTimerEnemy++;

        /* Have to udpate engine first before flipping models otherwise fucks the sprites?
         * For the enemies vector, need to make a class of enemy with hp/dmg/flip/...
         * With this class change the flip bool in the updatemovement();
         * Then with a for loop check the bool flip with enemyvector[i].flip if yes flip that one in the vector.
         *
         * */
        if (update){
            engine.get()->updateSpritesInScene();
            ~update;
        }

        UpdateGame();

        player1->setPlayerParameters();
        for (int i = 0 ; i < enemiesvector.size();i++)
        {
            enemiesvector[i]->correctFlip();
        }
        for (int i = 0 ; i < BulletsVector.size();i++)
        {
            BulletsVector[i]->correctFlip();
        }
        bg_C1.get()->scroll(scrollX, scrollY);
    }

}

void scene_Chapter1::UpdateGame() {


    if ( enemiesvector.size() <= totalEnemies)
    {
        if (player1->getPlayerMoving() && (spawnerTime >= 20) ) //         if (boolPlayerMoving && spawnerTime <= 5000) //
        {
            enemiesvector.push_back(new enemy(builder,FALSE));
            spawnerTime = 0;
            currentEnemies++;
            update = TRUE;
            engine.get()->enqueueSound(spawn, spawn_bytes, 16000);
            //engine->updateSpritesInScene();
        }
        else spawnerTime++;
    }

    if (!enemiesvector.empty() )
    {
        UpdateMovements();
    }

    //COLLISION
    for (int i = 0 ; i < BulletsVector.size() ; i++){
        for (int x = 0 ; x < enemiesvector.size(); x++)
        {
            if (BulletsVector[i]->BulletSprite->collidesWith(*enemiesvector[x]->enemysprite))
            {   enemiesvector[x]->enemysprite->moveTo(-32,-32);
                enemiesvector[x]->enemysprite->setVelocity(0,0);
                BulletsVector[i]->BulletSprite->moveTo(-32,-32);
                BulletsVector[i]->BulletSprite->setVelocity(0,0);
                update = TRUE;
                enemiesvector.erase(enemiesvector.begin()+x);
                //enemies.resize(enemies.size()-1);
                player1->addPlayerKill();
                break;
            }
        }
    }
    for (int i = 0; i<enemiesvector.size(); i++)
    {
        if (enemiesvector[i]->enemysprite->collidesWith(*player1->spriteplayer))
        {
            enemiesvector.erase(enemiesvector.begin()+i);
            player1->lives--;
            engine.get()->enqueueSound(hit, hit_bytes, 16000);
        }
    }

    if (player1->getPlayerKills() > 10){
        UpgradeLevel();
    }
    if(player1->getPlayerLives() <= 0) {
        if (!engine->isTransitioning()) {
            TextStream::instance() << "YOU HAVE DIED.......";
            enemiesvector.clear();
            BulletsVector.clear();
            bg_C1.get_deleter();
            engine->transitionIntoScene(new scene_death(engine), new FadeOutScene(2));
        }
    }


}

void scene_Chapter1::UpdateMovements(){
    if (!enemiesvector.empty()) {
        enemyPosX = enemiesvector[loopEnemies]->enemysprite->getX();
        enemyPosY = enemiesvector[loopEnemies]->enemysprite->getY();
        if (moveTimerEnemy >= 4) {
            moveflagEnemy = !moveflagEnemy;
            moveTimerEnemy = 0;
        }
        if (enemyPosX == player1->getXcoord())
        {
            if (enemyPosY < player1->getYcoord())
            {
                if (moveflagEnemy)enemiesvector[loopEnemies]->enemysprite->animateToFrame(3);
                else enemiesvector[loopEnemies]->enemysprite->animateToFrame(2);
                staticEnemyModel = 1;
                enemyPosY++;
            }
            else
            {
                if (moveflagEnemy)enemiesvector[loopEnemies]->enemysprite->animateToFrame(5);
                else enemiesvector[loopEnemies]->enemysprite->animateToFrame(6);
                staticEnemyModel = 4;
                enemyPosY--;
            }

        }
        else if (enemyPosY == player1->getYcoord())
        {
            if (enemyPosX < player1->getXcoord())
            {
                if (moveflagEnemy)enemiesvector[loopEnemies]->enemysprite->animateToFrame(7);
                else enemiesvector[loopEnemies]->enemysprite->animateToFrame(8);
                staticEnemyModel = 8;
                enemiesvector[loopEnemies]->flipped = FALSE;
                enemyPosX++;
            }
            else
            {
                if (moveflagEnemy)enemiesvector[loopEnemies]->enemysprite->animateToFrame(7);
                else enemiesvector[loopEnemies]->enemysprite->animateToFrame(8);
                staticEnemyModel = 7;
                enemiesvector[loopEnemies]->flipped = TRUE;
                enemiesvector[loopEnemies]->enemysprite->flipHorizontally(true);
                enemyPosX--;
            }
        }
        else {
            trackingY = abs(enemyPosY - player1->getYcoord());
            trackingX = abs(enemyPosX - player1->getXcoord());

            if (trackingX < trackingY) {
                if (enemyPosX > player1->getXcoord()) {
                    if (moveflagEnemy)enemiesvector[loopEnemies]->enemysprite->animateToFrame(7);
                    else enemiesvector[loopEnemies]->enemysprite->animateToFrame(8);
                    staticEnemyModel = 7;
                    enemiesvector[loopEnemies]->flipped = TRUE;
                    enemiesvector[loopEnemies]->enemysprite->flipHorizontally(true);
                    enemyPosX--;
                } else {
                    if (moveflagEnemy)enemiesvector[loopEnemies]->enemysprite->animateToFrame(7);
                    else enemiesvector[loopEnemies]->enemysprite->animateToFrame(8);
                    staticEnemyModel = 8;
                    enemiesvector[loopEnemies]->flipped = FALSE ;
                    enemyPosX++;
                }

            } else if (trackingY < trackingX) {
                if (enemyPosY < player1->getYcoord()) {
                    if (moveflagEnemy)enemiesvector[loopEnemies]->enemysprite->animateToFrame(3);
                    else enemiesvector[loopEnemies]->enemysprite->animateToFrame(2);
                    staticEnemyModel = 1;
                    enemyPosY++;
                } else {
                    if (moveflagEnemy)enemiesvector[loopEnemies]->enemysprite->animateToFrame(5);
                    else enemiesvector[loopEnemies]->enemysprite->animateToFrame(6);
                    staticEnemyModel = 4;
                    enemyPosY--;
                }
            }
            moveTimerEnemy++;
        }

        if (oldScrollX == scrollX) {
            enemiesvector[loopEnemies]->enemysprite->moveTo(enemyPosX, enemyPosY);
        }
        if (oldScrollX > scrollX) {
            enemiesvector[loopEnemies]->enemysprite->moveTo(enemyPosX + enemyMoveSpeed, enemyPosY);
            enemiesvector[loopEnemies]->enemysprite->flipHorizontally(false);
        } else if (oldScrollX < scrollX) {
            enemiesvector[loopEnemies]->enemysprite->moveTo(enemyPosX - enemyMoveSpeed, enemyPosY);
            enemiesvector[loopEnemies]->enemysprite->flipHorizontally(true);
        }
        if (oldScrollY > scrollY) {
            enemiesvector[loopEnemies]->enemysprite->moveTo(enemyPosX, enemyPosY + enemyMoveSpeed);
        } else if (oldScrollY < scrollY) {
            enemiesvector[loopEnemies]->enemysprite->moveTo(enemyPosX, enemyPosY - enemyMoveSpeed);
        }

        if (loopEnemies < enemiesvector.size() - 1) {
            loopEnemies++;
        } else loopEnemies = 0;

        //engine.get()->updateSpritesInScene();
        oldScrollX = scrollX;
        oldScrollY = scrollY;
    }
}

void scene_Chapter1::OffScreen() {

    for (int i = 0; i < BulletsVector.size(); i++) {
        if (BulletsVector[i]->BulletSprite->isOffScreen()) {
            BulletsVector.erase(std::remove(BulletsVector.begin(), BulletsVector.end(), BulletsVector[i]));
//            engine.get()->updateSpritesInScene();
            //engine->update();
            update = TRUE;
        }
    }
}

void scene_Chapter1::UpgradeLevel() {
    //enemyMoveSpeed++;
    if (totalEnemies < 11)
    {
        totalEnemies = totalEnemies+1;
    }
    player1->resetPlayerKill();
    pause = true;
}
