//
// Created by Gille on 1/26/2021.
//

#include "enemies_level1.h"
#include "pixel_player.h"


enemies_level1::enemies_level1(SpriteBuilder<Sprite> builder, int x, int y, int velX, int velY, char spriteID, int hp) {
    this->spriteEntity = builder
            .withData(EnemyFullTiles, sizeof(EnemyFullTiles))
            .withSize(SIZE_16_16)
            .withLocation(x, y)
            .withVelocity(velX, velY)
            .buildPtr();
    this->ID = spriteID;
    this->hp = hp;
}

void enemies_level1::trackPlayer(int *scrX, int *scrY, int *oldscrY, int *oldscrX, int trackX, int trackY){

    PosX = spriteEntity->getX();
    PosY = spriteEntity->getY();

    if (moveTimer >= 4)
    {
        moveflag = !moveflag;
        moveTimer = 0;
    }
    if ( (PosX == trackX) || (PosY == trackY) )
    {
        //enemyshoot();
        spriteEntity->animateToFrame(staticModel);
        spriteEntity->flipHorizontally(boolFlipHori);
        return;
    }
    else
    {
        trackingY = abs (PosY - trackY);
        trackingX = abs (PosX - trackX);

        if (trackingX < trackingY)
        {
            if (PosX > trackX)
            {
                if(moveflag)spriteEntity->animateToFrame(7);
                else spriteEntity->animateToFrame(8);
                staticModel = 7;
                facingx = 0;
                //engine.get()->updateSpritesInScene();
                boolFlipHori = true;
                //enemies[loopEnemies]->flipHorizontally(true);
                PosX--;
                //this->speedX = -1;
            }
            else
            {
                if(moveflag)spriteEntity->animateToFrame(7);
                else spriteEntity->animateToFrame(8);
                staticModel = 8;
                facingx = -1;
                boolFlipHori = false;
                //enemies[loopEnemies]->flipHorizontally(false);
                PosX++;
                //this->speedX = +1;
            }
        }
        else if (trackingY < trackingX)
        {
            if (PosY < trackY)
            {
                if(this->moveflag)spriteEntity->animateToFrame(3);
                else spriteEntity->animateToFrame(2);
                this->staticModel = 1;
                PosY++;
                //this->speedY = +1;
            }
            else
            {
                if(this->moveflag)spriteEntity->animateToFrame(5);
                else spriteEntity->animateToFrame(6);
                staticModel = 4;
                PosY--;
                //this->speedY = -1;
            }
        }
        this->moveTimer++;
    }

    if (oldscrX == scrX){
        spriteEntity->moveTo(PosX, PosY);
    }
    if (oldscrX > scrX){
        boolFlipHori = false;
        spriteEntity->moveTo(PosX-1, PosY);
    }
    else if (oldscrX < scrX){
        boolFlipHori = true;
        spriteEntity->moveTo(PosX+1, PosY);
    }
    if (oldscrY > scrY){
        spriteEntity->moveTo(PosX, PosY-1);
    }
    else if (oldscrY < scrY){
        spriteEntity->moveTo(PosX, PosY+1);
    }


}

