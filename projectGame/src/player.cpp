//
// Created by Gille on 12/17/2020.
//

#include "player.h"
#include "pixel_player.h"
#include <libgba-sprite-engine/gba_engine.h>
#include "scene_Chapter1.h"


Player::Player(SpriteBuilder<Sprite> builder, int x, int y,char spriteID, int hp) {
    this->spriteEntity = builder
            .withSize(SIZE_16_16)
            .withLocation(x, y)
            .withData(PlayerFullTiles, sizeof(PlayerFullTiles))
            .withinBounds()
            .buildPtr();
    this->ID = spriteID;
    this->hp = hp;
}
void Player::movePlayer(u16 input, int *scrX, int *scrY) {

    if (this->moveTimer >= 7)
    {
        this->moveflag = !this->moveflag;
        this->moveTimer = 0;
    }

    if(input & allkeycheck)
    {

        this->PosX = this->spriteEntity->getX();
        this->PosY = this->spriteEntity->getY();

        switch (input) {
            case KEY_LEFT:
                if (moveflag)this->spriteEntity->animateToFrame(7);
                else this->spriteEntity->animateToFrame(8);
                this->staticModel = 8;
                boolFlipHori = true;
                //scroll X-1
                if (*scrX > 0 && this->PosX <= 112) {
                    *scrX = *scrX-1;
                    speedX = 0;
                    speedY = 0;
                }
                else{
                    speedX = -1;
                    speedY = 0;
                }
                this->facingx = -1;
                this->facingy = 0;
                break;

            case KEY_RIGHT:
                if (moveflag)this->spriteEntity->animateToFrame(7);
                else this->spriteEntity->animateToFrame(8);
                this->staticModel = 7;
                boolFlipHori = false;
                //scroll X+1
                if (*scrX < 260 && this->PosX >= 112) {
                    *scrX = *scrX+1;
                    speedX = 0;
                    speedY = 0;
                }
                else{
                    speedX = +1;
                    speedY = 0;
                }
                this->facingx = 1;
                this->facingy = 0;
                break;

            case KEY_DOWN:
                if (moveflag)this->spriteEntity->animateToFrame(3);
                else this->spriteEntity->animateToFrame(2);
                this->staticModel = 1;
                //scroll Y+1
                if (*scrY < 340 && this->PosY >= 72) {
                    *scrY = *scrY+1;
                    speedX = 0;
                    speedY = 0;
                }
                else{
                    speedX = 0;
                    speedY = +1;
                }
                this->facingx = 0;
                this->facingy = 1;
                break;

            case KEY_UP:
                if (moveflag)this->spriteEntity->animateToFrame(5);
                else this->spriteEntity->animateToFrame(6);
                this->staticModel = 4;
                //scroll Y-1
                if (*scrY > 0 && this->PosY <= 72) {
                    *scrY = *scrY-1;
                    speedX = 0;
                    speedY = 0;
                }
                else{
                    speedX = 0;
                    speedY = -1;
                }

                this->facingx = 0;
                this->facingy = -1;
                break;

            default:
                speedX = 0;
                speedY = 0;
                this->staticModel = staticModel;
                boolMoving = false;
                break;

        }
        this->boolMoving = true;
    }
    else
    {
        this->boolMoving = false;
        this->spriteEntity->setVelocity(0, 0);
        this->speedX = 0;
        this->speedY = 0;
        this->spriteEntity->animateToFrame(this->staticModel);
        this->spriteEntity->flipHorizontally(this->boolFlipHori);
    }

    this->moveTimer++;
}

