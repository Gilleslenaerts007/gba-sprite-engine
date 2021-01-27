//
// Created by Gille on 12/14/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SCENE_CHAPTER1_H
#define GBA_SPRITE_ENGINE_PROJECT_SCENE_CHAPTER1_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/background/background.h>
#include "player.h"
#include "Bullet.h"
#include "enemy.h"
#define Xlimit 500
#define Ylimit 500

class scene_Chapter1 : public Scene {
private:
    //Game vars

    SpriteBuilder<Sprite> builder;
    Player* player1;
    std::vector<enemy*> enemiesvector;
    std::vector<Bullet*> BulletsVector;
    std::unique_ptr<Sprite> Offbulletscreen;
    std::unique_ptr<Sprite> Offbulletscreen2;
    std::vector<Sprite *> spritesVector;


    std::unique_ptr<Background> bg_C1;

    bool pressingAorB = false;

    int scrollX, scrollY;
    bool update = FALSE ;
    bool pause = false ;

    //Enemie vars
    int spawnerTime;
    int totalEnemies = 4;
    int currentEnemies = 0;
    int enemyPosX;
    int enemyPosY;
    int moveTimerEnemy;
    bool moveflagEnemy = false;
    int loopEnemies;
    int trackingY;
    int trackingX;
    short int staticEnemyModel = 7;
    int oldScrollX, oldScrollY;
    short int enemyMoveSpeed = 3;



public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    //getters


    //Setters
    scene_Chapter1(std::shared_ptr<GBAEngine> engine) : Scene(engine),scrollX(0), scrollY(0) {}

    //actions
    void UpdateGame();
    void UpdateMovements();
    void OffScreen();
    void UpgradeLevel();

    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_PROJECT_SCENE_CHAPTER1_H
