//
// Created by jonas on 26/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
#define GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_types.h>
#include <libgba-sprite-engine/gba_engine.h>
//#include "scene_Chapter1.h"
//#include "pixel_player.h"
//#include "pixel_bullets.h"
//#include "bg_Chapter1.h"

class enemy {
private:
public:

    bool ToBeRemoved = FALSE;
    bool flipped;
    std::unique_ptr<Sprite> enemysprite;
    enemy(SpriteBuilder<Sprite> builder,bool flipped);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
