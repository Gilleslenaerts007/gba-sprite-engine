//
// Created by Gille on 1/26/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
#define GBA_SPRITE_ENGINE_PROJECT_ENEMY_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_types.h>
#include <libgba-sprite-engine/gba_engine.h>

class enemy {
private:
public:
    void correctFlip();
    bool flipped;
    std::unique_ptr<Sprite> enemysprite;
    enemy(SpriteBuilder<Sprite> builder,bool flipped);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_ENEMY_H
