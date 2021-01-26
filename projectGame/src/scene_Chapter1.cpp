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
    /*
    for (int i =0; i<spritesVector.size();i++)
    {
        spritesVector.pop_back();
    }
     */
    spritesVector = {};
    spritesVector.push_back(player1->getSprite());

    if (!BulletsVerti.empty()){
        for (int i=0; i < BulletsVerti.size(); i++) // niet '<=' anders plek pointer te ver
        {
            //BulletsVerti[i]->flipVertically(true);
            spritesVector.push_back(BulletsVerti[i].get());
        }
    }
    if (!BulletsHori.empty())
    {
        for (int i=0; i < BulletsHori.size(); i++) // niet '<=' anders plek pointer te ver
        {
            //BulletsHori[i]->flipHorizontally(true);
            spritesVector.push_back(BulletsHori[i].get());
        }
    }

    if(!enemies.empty())
    {
        for (int i=0; i < enemies.size(); i++) // niet '<=' anders plek pointer te ver
        {
            spritesVector.push_back(enemies[i].get());
        }

    }

    /*
    if(!Offbulletscreen.empty())
    {
        for (int i=0; i < Offbulletscreen.size(); i++) // niet '<=' anders plek pointer te ver
        {
            spritesVector.push_back(Offbulletscreen[i].get());
        }
    }
     */
    spritesVector.push_back(Offbulletscreen.get());

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
    //REG_DISPCNT = DCNT_MODE0 | DCNT_OBJ | DCNT_OBJ_1D | DCNT_BG0 | DCNT_BG1; //Als dit aanstaat kan bg index al vanaf 0. zoniet van index 1.
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
    player1 = (new Player(builder, 112, 72, 100, 2) );
    playerptr = player1;
    //player player1(builder, 112, 72, 100, 2);
    Offbulletscreen = builder
                                          .withData(BulletVertiTiles, sizeof(BulletVertiTiles))
                                          .withSize(SIZE_16_16)
                                          .withLocation(-32, -32)
                                          .withVelocity(0,0)
                                          .buildPtr();


    //TextStream::instance().setText("PRESS START", 3, 8);
    engine->enableText();
    TextStream::instance().setText(std::string("hp: "), 7, 5);
    /*
    bg_C3 = std::unique_ptr<Background>(new Background(1, tilesetOpenGameTiles, sizeof(tilesetOpenGameTiles), affinemap, sizeof(affinemap)));
    bg_C3.get()->useMapScreenBlock(8);
     */
    //engine->getTimer()->start();
    //engine->enqueueMusic(zelda_music_16K_mono, zelda_music_16K_mono_bytes);
}


/*
 * Player movement & key reads
 *
 */
void scene_Chapter1::tick(u16 keys) {

    if (ShotCooldown != 0) {ShotCooldown--;}
    OffScreen();

    //TextStream::instance().setText(engine->getTimer()->to_string(), 18, 1);
    if(pressingAorB && !((keys & KEY_A) || (keys & KEY_B))) {
        //engine->getTimer()->toggle();
        pressingAorB = false;
    }

    OldBulletSize = BulletsHori.size() + BulletsVerti.size();

    if(keys & KEY_START)
    {
        if(!engine->isTransitioning()) {
            //engine->enqueueSound(zelda_secret_16K_mono, zelda_secret_16K_mono_bytes);

            TextStream::instance() << "entered: starting next scene";

            //engine->transitionIntoScene(new FlyingStuffScene(engine), new FadeOutScene(2));
        }

    }

    if (keys & KEY_A)
    {

        if (player1->getFaceX() != 0 && OldBulletSize<=7 && ShotCooldown == 0) {shootSide();}
        else if (player1->getFaceY() != 0 && OldBulletSize<=7 && ShotCooldown == 0) {shootUp();}
        //engine.get()->updateSpritesInScene();
    }

    //setScrollMap(, int scrollX);
    player1->movePlayer(keys, &scrollX, &scrollY);
    //bg_C1->scroll(scrollY,scrollX);
    //moveTimerEnemy++;


    /* Have to udpate engine first before flipping models otherwise fucks the sprites?
     * For the enemies vector, need to make a class of enemy with hp/dmg/flip/...
     * With this class change the flip bool in the updatemovement();
     * Then with a for loop check the bool flip with enemyvector[i].flip if yes flip that one in the vector.
     *
     * */
    engine.get()->updateSpritesInScene();
    UpdateGame();
    if (player1->getFaceX() == -1) BulletsHori[BulletsHori.size()-1]->flipHorizontally(true);
    else if(player1->getFaceX() == 1) BulletsHori[BulletsHori.size()-1]->flipHorizontally(false);
    if (player1->getFaceY() == -1)  BulletsVerti[BulletsVerti.size()-1]->flipVertically(false);
    else if(player1->getFaceY() == 1) BulletsVerti[BulletsVerti.size()-1]->flipVertically(true);
    player1->setParameters();
    //enemies[loopEnemies]->setParameters();
    bg_C1.get()->scroll(scrollX, scrollY);

};

void scene_Chapter1::UpdateGame() {


    //COLLISION

    if ( currentEnemies <= totalEnemies)
    {
        if (player1->getMoving() && (spawnerTime >= 20) ) //         if (boolPlayerMoving && spawnerTime <= 5000) //
        {
            //enemies.push_back( (new enemies_level1(builder, rand()%GBA_SCREEN_WIDTH +1, rand()%GBA_SCREEN_HEIGHT+1, rand() % 1, rand() % 1, 2) ) );
            enemies.push_back( builder
                                       .withData(EnemyFullTiles, sizeof(EnemyFullTiles))
                                       .withSize(SIZE_16_16)
                                               //.withVelocity(1, 1)
                                       .withLocation(rand()%GBA_SCREEN_WIDTH +1, rand()%GBA_SCREEN_HEIGHT+1)
                                       .withVelocity(rand() % 1, rand() % 1)
                                       .buildPtr());
            spawnerTime = 0;
            currentEnemies++;
            engine->updateSpritesInScene();
        }
        else spawnerTime++;
    }

    if (!enemies.empty() )
    {
        UpdateMovements();
    }

    TextStream::instance().setText(std::to_string(player1->getHP()), 5, 16);
    /*
    if (OldBulletSize != BulletsHori.size()+BulletsVerti.size())
    {
        engine.get()->updateSpritesInScene();
    }
     ¨*/

}

void scene_Chapter1::UpdateMovements(){

    enemyPosX = enemies[loopEnemies]->getX();
    enemyPosY = enemies[loopEnemies]->getY();
    if (moveTimerEnemy >= 2)
    {
        moveflagEnemy = !moveflagEnemy;
        moveTimerEnemy = 0;
    }

    if ( (enemyPosX == player1->getXcoord()) || (enemyPosY == player1->getYcoord()) )
    {
        //enemyshoot();
        enemies[loopEnemies]->animateToFrame(staticEnemyModel);
    }
    else
    {
        trackingY = abs (enemyPosY - player1->getYcoord());
        trackingX = abs (enemyPosX - player1->getXcoord());

        if (trackingX < trackingY)
        {
            if (enemyPosX > player1->getXcoord())
            {
                if(moveflagEnemy)enemies[loopEnemies]->animateToFrame(7);
                else enemies[loopEnemies]->animateToFrame(8);
                staticEnemyModel = 7;
                enemies[loopEnemies]->flipHorizontally(true);
                enemyPosX--;
            }
            else
            {
                if(moveflagEnemy)enemies[loopEnemies]->animateToFrame(7);
                else enemies[loopEnemies]->animateToFrame(8);
                staticEnemyModel = 8;
                enemies[loopEnemies]->flipHorizontally(false);
                enemyPosX++;
            }
        }
        else if (trackingY < trackingX)
        {
            if (enemyPosY < player1->getYcoord())
            {
                if(moveflagEnemy)enemies[loopEnemies]->animateToFrame(3);
                else enemies[loopEnemies]->animateToFrame(2);
                staticEnemyModel = 1;
                enemyPosY++;
            }
            else
            {
                if(moveflagEnemy)enemies[loopEnemies]->animateToFrame(5);
                else enemies[loopEnemies]->animateToFrame(6);
                staticEnemyModel = 4;
                enemyPosY--;
            }
        }
        moveTimerEnemy++;
    }

    if (oldScrollX == scrollX){
        enemies[loopEnemies]->moveTo(enemyPosX, enemyPosY);
    }
    if (oldScrollX > scrollX){
        enemies[loopEnemies]->moveTo(enemyPosX+enemyMoveSpeed, enemyPosY);
    }
    else if (oldScrollX < scrollX){
        enemies[loopEnemies]->moveTo(enemyPosX-enemyMoveSpeed, enemyPosY);
    }
    if (oldScrollY > scrollY){
        enemies[loopEnemies]->moveTo(enemyPosX, enemyPosY+enemyMoveSpeed);
    }
    else if (oldScrollY < scrollY){
        enemies[loopEnemies]->moveTo(enemyPosX, enemyPosY-enemyMoveSpeed);
    }

    if (loopEnemies < enemies.size() -1 )
    {
        loopEnemies++;
    }
    else loopEnemies = 0;

    oldScrollX = scrollX;
    oldScrollY = scrollY;

    //enemies[loopEnemies]->trackPlayer(&scrollX, &scrollY, &oldScrollX, &oldScrollY, player1->getXcoord() , player1->getYcoord() );
    /*
    if (oldScrollX == scrollX){
        enemies[loopEnemies]->spriteEntity->moveTo(enemies[loopEnemies]->getXcoord(), enemies[loopEnemies]->getYcoord());
    }
    if (oldScrollX > scrollX){
        //enemies[loopEnemies]->flipHorizontally(false);
        enemies[loopEnemies]->spriteEntity->moveTo(enemies[loopEnemies]->getXcoord()+2, enemies[loopEnemies]->getYcoord());
    }
    else if (oldScrollX < scrollX){
        //enemies[loopEnemies]->flipHorizontally(true);
        enemies[loopEnemies]->spriteEntity->moveTo(enemies[loopEnemies]->getXcoord()-2, enemies[loopEnemies]->getYcoord());
    }
    if (oldScrollY > scrollY){
        enemies[loopEnemies]->spriteEntity->moveTo(enemies[loopEnemies]->getXcoord(), enemies[loopEnemies]->getYcoord()+2);
    }
    else if (oldScrollY < scrollY){
        enemies[loopEnemies]->spriteEntity->moveTo(enemies[loopEnemies]->getXcoord(), enemies[loopEnemies]->getYcoord()-2);
    }
    if (loopEnemies < enemies.size() -1 )
    {
        loopEnemies++;
    }
    else loopEnemies = 0;
    oldScrollX = scrollX;
    oldScrollY = scrollY;
    */
    //engine.get()->updateSpritesInScene();
}

void scene_Chapter1::shootUp() {
    BulletsVerti.push_back(builder
                              .withData(BulletVertiTiles, sizeof(BulletVertiTiles))
                              .withSize(SIZE_16_16)
                              .withLocation(player1->getXcoord(), player1->getYcoord())
                              .withVelocity(player1->getFaceX()*2,player1->getFaceY()*2)
                              .buildPtr());
    //TextStream::instance().setText(std::string("bullets on screen: ") + std::to_string(Bullets.size()), 1, 1);
    // //engine.get()->updateSpritesInScene();
    ShotCooldown = TimeBetweenShots;
}

void scene_Chapter1::shootSide() {
    BulletsHori.push_back(builder
                               .withData(BulletHoriTiles, sizeof(BulletHoriTiles))
                              .withSize(SIZE_16_16)
                              .withLocation(player1->getXcoord(), player1->getYcoord())
                              .withVelocity(player1->getFaceX()*2,player1->getFaceY()*2)
                              .buildPtr());
    //engine.get()->updateSpritesInScene();
    ShotCooldown = TimeBetweenShots;
}
void scene_Chapter1::OffScreen() {

    for (int i = 0 ; i<BulletsHori.size();i++)
    {
        if (BulletsHori[i]->isOffScreen())
        {
            BulletsHori.erase(std::remove(BulletsHori.begin(), BulletsHori.end(), BulletsHori[i]));
            engine.get()->updateSpritesInScene();
           //engine->update();
        }
    }

    for (int i = 0 ; i<BulletsVerti.size();i++)
    {
        if (BulletsVerti[i]->isOffScreen())
        {
            BulletsVerti.erase(std::remove(BulletsVerti.begin(), BulletsVerti.end(), BulletsVerti[i]));
            engine.get()->updateSpritesInScene();
            //engine->update();
        }
    }
}
