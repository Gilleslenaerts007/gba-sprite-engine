//
// Created by Gille on 12/14/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SCENE_CHAPTER1_H
#define GBA_SPRITE_ENGINE_PROJECT_SCENE_CHAPTER1_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/background/background.h>

#define Xlimit 500
#define Ylimit 500

class scene_Chapter1 : public Scene {

private:
    std::vector<Sprite *> spritesVector;
    std::unique_ptr<Sprite>  enemy;
    std::vector<std::unique_ptr<Sprite >> enemies;
    std::unique_ptr<Sprite>  player;
    std::unique_ptr<Sprite> bullet;
    SpriteBuilder<Sprite> builder;
    SpriteBuilder<AffineSprite> affineBuilder;

    std::unique_ptr<Background> bg_C1;
    std::unique_ptr<Background> bg_C2;
    std::unique_ptr<Background> bg_C3;
    bool pressingAorB = false;
    bool updateSprites;
    bool moving;

    int scrollX, scrollY;
    int rotation;
    int rotationDiff = 128;

    //Enemie vars
    int spawnerTime = 0;
    int totalEnemies = 10;
    int currentEnemies = 0;

    //Player vars
    int playerPosX;
    int playerPosY;
    short int staticPlayerModel = 7;
    bool moveflag = false;
    short int movetimer = 0;


public:

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;
    /*
     * Need func to update a vector of sprites with bullets going off the current bounds of the player on the map
     */
    void UpdateGame();

    scene_Chapter1(std::shared_ptr<GBAEngine> engine) : Scene(engine), rotation(0), rotationDiff(128), scrollX(0), scrollY(0) {}

    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_PROJECT_SCENE_CHAPTER1_H
