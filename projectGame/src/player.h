//
// Created by Gille on 12/17/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_types.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Entity.h"

class Player : public Entity {
private:

public:

    //void setParameters();//int speedX, int speedY);//, bool boolFlipHori, bool boolFlipVerti, int frameNumber);
    void movePlayer(u16 input, int *scrX, int *scrY);
    bool shoot();

    //constructor
    Player(SpriteBuilder<Sprite> builder, int x, int y, char spriteID,int hp=100);
    ~Player(){};
};


#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
