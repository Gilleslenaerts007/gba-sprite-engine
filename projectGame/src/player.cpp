//
// Created by Gille on 12/17/2020.
//

#include "player.h"
#include "pixel_player.h"
#include "scene_Chapter1.h"


player::player(SpriteBuilder<Sprite> builder, int x, int y, int hp, char spriteID) {
    this->spriteplayer = builder
            .withSize(SIZE_16_16)
            .withLocation(x, y)
            .withData(PlayerFullTiles, sizeof(PlayerFullTiles))
            .buildPtr();
    this->playerID = spriteID;
}
void player::movePlayer(u16 input, scene_Chapter1* scene) {

    if(input & allkeycheck)
    {
        if (moveTimerPlayer >= 7)
        {
            moveflag = !moveflag;
            moveTimerPlayer = 0;
        }

        this->playerPosX = spriteplayer->getX();
        this->playerPosY = spriteplayer->getY();
        boolMoving = true;
        moveTimerPlayer++;

        switch (input) {
            case KEY_LEFT:
                if (moveflag)spriteplayer->animateToFrame(7);
                else spriteplayer->animateToFrame(8);
                staticPlayerModel = 8;
                boolFlipHori = true;
                if (scene->getScrollXMap() > 0 && playerPosX <= 112) {
                    scene->setScrollMap(scene->getScrollYMap(),scene->getScrollXMap()-1);
                    speedX = 0;
                    speedY = 0;
                }
                else spriteplayer->setVelocity(-1, 0);
                playerfacingx = -1;
                playerfacingy = 0;
                break;

            case KEY_RIGHT:
                if (moveflag)spriteplayer->animateToFrame(7);
                else spriteplayer->animateToFrame(8);
                staticPlayerModel = 7;
                boolFlipHori = false;
                if (scene->getScrollXMap() < 260 && playerPosX >= 112) {
                    scene->setScrollMap(scene->getScrollYMap(),scene->getScrollXMap()+1);
                    speedX = 0;
                    speedY = 0;
                }
                else spriteplayer->setVelocity(+1, 0);
                playerfacingx = 1;
                playerfacingy = 0;
                break;

            case KEY_DOWN:
                if (moveflag)spriteplayer->animateToFrame(3);
                else spriteplayer->animateToFrame(2);
                staticPlayerModel = 1;
                if (scene->getScrollYMap() < 340 && playerPosY >= 72) {
                    scene->setScrollMap(scene->getScrollYMap()+1,scene->getScrollXMap());;
                    speedX = 0;
                    speedY = 0;
                }
                else spriteplayer->setVelocity(0, +1);
                playerfacingx = 0;
                playerfacingy = 1;
                break;

            case KEY_UP:
                if (moveflag)spriteplayer->animateToFrame(5);
                else spriteplayer->animateToFrame(6);
                staticPlayerModel = 4;
                if (scene->getScrollYMap() > 0 && playerPosY <= 72) {
                    scene->setScrollMap(scene->getScrollYMap()-1,scene->getScrollXMap());
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
    }
    else
    {
        boolMoving = false;
        this->spriteplayer->setVelocity(0, 0);
        this->spriteplayer->animateToFrame(staticPlayerModel);
        this->spriteplayer->flipHorizontally(boolFlipHori);
    }


}

void player::setPlayerParameters(){
    this->spriteplayer->setVelocity(speedX, speedY);
    this->spriteplayer->animateToFrame(staticPlayerModel);
    this->spriteplayer->flipHorizontally(boolFlipHori);
}