//
// Created by Gille on 1/26/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_ENEMIES_LEVEL1_H
#define GBA_SPRITE_ENGINE_PROJECT_ENEMIES_LEVEL1_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_types.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Entity.h"
#include "Player.h"

class enemies_level1 : public Entity {

private:

    //int oldScrollX;
    //int oldScrollY;
    int trackingX;
    int trackingY;
    short int MoveSpeed = 3;

public:

    void trackPlayer(int *scrX, int *scrY, int *oldscrY, int *oldscrX, int trackX, int trackY);

    //constructor
    enemies_level1(SpriteBuilder<Sprite> builder, int x, int y,int velX, int velY, char spriteID, int hp=50);
    ~enemies_level1(){};
};


#endif //GBA_SPRITE_ENGINE_PROJECT_ENEMIES_LEVEL1_H
