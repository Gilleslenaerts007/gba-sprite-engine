//
// Created by jonas on 26/01/2021.
//


#include "enemy.h"
#include "pixel_player.h"

enemy::enemy(SpriteBuilder<Sprite> builder,bool flipped) {
    this->enemysprite = builder
            .withData(EnemyFullTiles, sizeof(EnemyFullTiles))
            .withSize(SIZE_16_16)
                    //.withVelocity(1, 1)
            .withLocation(rand()%GBA_SCREEN_WIDTH +1, rand()%GBA_SCREEN_HEIGHT+1)
            .withVelocity(rand() % 1, rand() % 1)
            .buildPtr();
    this->flipped = flipped ;
}