//
// Created by jonas on 26/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_BULLET_H
#define GBA_SPRITE_ENGINE_PROJECT_BULLET_H
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_types.h>
#include <libgba-sprite-engine/gba_engine.h>

class Bullet {

private:

public:
    bool flipped;
    void correctFlip();
    std::unique_ptr<Sprite> BulletSprite;
    Bullet(SpriteBuilder<Sprite> builder,std::unique_ptr<Sprite> *source,int x, int y, int velocityX, int velocityY, bool flipped);
};



#endif //GBA_SPRITE_ENGINE_PROJECT_BULLET_H
