//
// Created by Gille on 1/26/2021.
//

#include "Entity.h"

void Entity::setParameters(){
    this->spriteEntity->setVelocity(this->speedX, this->speedY);
    //this->spriteplayer->animateToFrame(staticPlayerModel);
    this->spriteEntity->flipHorizontally(this->boolFlipHori);
}