//
// Created by Gille on 12/17/2020.
//

#include "player.h"
#include "pixel_player.h"
#include <vector>

Player::Player(SpriteBuilder<Sprite> builder, int x, int y, int lives, char spriteID) {
    this->spriteplayer = builder
            .withSize(SIZE_16_16)
            .withLocation(x, y)
            .withData(PlayerFullTiles, sizeof(PlayerFullTiles))
            .withinBounds()
            .buildPtr();
    this->playerID = spriteID;
    this->lives = lives;
}
void  Player::Shoot(SpriteBuilder<Sprite> builder, std::vector<Bullet*> *DestVector, std::unique_ptr<Sprite> *SpriteTemp) {
    if (this->shotcooldown == 0)
    {
        DestVector->push_back(new Bullet(builder , SpriteTemp, this->playerPosX,this->playerPosY,this->playerfacingx,this->playerfacingy,FALSE));
        this->shotcooldown = this->timebetweenshots;
    }
}

void Player::movePlayer(u16 input, int *scrX, int *scrY) {

    if (moveTimerPlayer >= 7)
    {
        moveflag = !moveflag;
        moveTimerPlayer = 0;
    }

    if(input & allkeycheck)
    {

        this->playerPosX = spriteplayer->getX();
        this->playerPosY = spriteplayer->getY();

        switch (input) {
            case KEY_LEFT:
                if (moveflag)spriteplayer->animateToFrame(7);
                else spriteplayer->animateToFrame(8);
                staticPlayerModel = 8;
                boolFlipHori = true;
                //scroll X-1
                if (*scrX > 0 && playerPosX <= 112) {
                    *scrX = *scrX-1;
                    speedX = 0;
                    speedY = 0;
                }
                else{
                    speedX = -1;
                    speedY = 0;
                }
                playerfacingx = -1;
                playerfacingy = 0;
                break;

            case KEY_RIGHT:
                if (moveflag)spriteplayer->animateToFrame(7);
                else spriteplayer->animateToFrame(8);
                staticPlayerModel = 7;
                boolFlipHori = false;
                //scroll X+1
                if (*scrX < 260 && playerPosX >= 112) {
                    *scrX = *scrX+1;
                    speedX = 0;
                    speedY = 0;
                }
                else{
                    speedX = +1;
                    speedY = 0;
                }
                playerfacingx = 1;
                playerfacingy = 0;
                break;

            case KEY_DOWN:
                if (moveflag)spriteplayer->animateToFrame(3);
                else spriteplayer->animateToFrame(2);
                staticPlayerModel = 1;
                //scroll Y+1
                if (*scrY < 340 && playerPosY >= 72) {
                    *scrY = *scrY+1;
                    speedX = 0;
                    speedY = 0;
                }
                else{
                    speedX = 0;
                    speedY = +1;
                }
                playerfacingx = 0;
                playerfacingy = 1;
                break;

            case KEY_UP:
                if (moveflag)spriteplayer->animateToFrame(5);
                else spriteplayer->animateToFrame(6);
                staticPlayerModel = 4;
                //scroll Y-1
                if (*scrY > 0 && playerPosY <= 72) {
                    *scrY = *scrY-1;
                    speedX = 0;
                    speedY = 0;
                }
                else{
                    speedX = 0;
                    speedY = -1;
                }

                playerfacingx = 0;
                playerfacingy = -1;
                break;

            default:
                speedX = 0;
                speedY = 0;
                staticPlayerModel = staticPlayerModel;
                boolMoving = false;
                break;

        }
        this->boolMoving = true;
    }
    else
    {
        boolMoving = false;
        this->spriteplayer->setVelocity(0, 0);
        speedX = 0;
        speedY = 0;
        this->spriteplayer->animateToFrame(staticPlayerModel);
        this->spriteplayer->flipHorizontally(boolFlipHori);
    }

    moveTimerPlayer++;
}

void Player::setPlayerParameters(){
    this->spriteplayer->setVelocity(speedX, speedY);
    //this->spriteplayer->animateToFrame(staticPlayerModel);
    this->spriteplayer->flipHorizontally(boolFlipHori);
}

void Player::setBuilder(SpriteBuilder<Sprite> builder, int x, int y) {
    this->spriteplayer = builder
            .withSize(SIZE_16_16)
            .withLocation(x, y)
            .withData(PlayerFullTiles, sizeof(PlayerFullTiles))
            .buildPtr();
}