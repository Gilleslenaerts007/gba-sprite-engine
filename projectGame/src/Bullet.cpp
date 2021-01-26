//
// Created by jonas on 26/01/2021.
//

#include "Bullet.h"

Bullet::Bullet(SpriteBuilder<Sprite> builder,std::unique_ptr<Sprite> *source ,int x, int y, int velocityX, int velocityY, bool flipped){
    this->BulletSprite = builder.withVelocity(velocityX*2,velocityY*2)
            .withLocation(x,y)
            .buildWithDataOf(*source->get());
    this->flipped = flipped ;
}
void Bullet::correctFlip() {
    this->BulletSprite->flipHorizontally(flipped);
    this->BulletSprite->flipVertically(flipped);
}