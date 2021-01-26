//
// Created by Gille on 12/17/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_types.h>
#include <libgba-sprite-engine/gba_engine.h>
#include "Bullet.h"

class Player {
private:


    int kills = 0;
    int ammo;
    int potion;
    int FirstAid;
    char playerID;

    int playerPosX;
    int playerPosY;
    int speedX;
    int speedY;
    bool boolMoving;
    short int playerfacingx = 0;
    short int playerfacingy = 0;
    short int staticPlayerModel = 7;
    bool moveflag = false;
    int moveTimerPlayer = 0;
    bool boolFlipHori;
    short int OldBulletSize;
    int timebetweenshots = 30;

public:
    int lives;
    int shotcooldown = 0 ;
    std::unique_ptr<Sprite> spriteplayer;
    //Global player getters
    int getAmmo() const {return ammo;}
    int getPotions() const {return potion;}
    int getFirstAid() const {return FirstAid;}
    int getXcoord() const {return spriteplayer->getX();}
    int getYcoord() const {return spriteplayer->getY();}
    bool getPlayerMoving() const {return this->boolMoving;}
    short int getPlayerFaceX() const {return this->playerfacingx;}
    short int getPlayerFaceY() const {return this->playerfacingy;}
    short int getPlayerLives() const {return this->lives;}
    int getPlayerKills() const {return this->kills;}

    Sprite * getSprite() const { return spriteplayer.get();}

    //global player setters
    void setPlayerParameters();//int speedX, int speedY);//, bool boolFlipHori, bool boolFlipVerti, int frameNumber);
    void addPlayerKill() {this->kills++;}
    void resetPlayerKill() {this->kills=0;}
    //void setWeapon(std::shared_ptr<Weapon> gun);

    //actions
    void movePlayer(u16 input, int *scrX, int *scrY);
    void Shoot(SpriteBuilder<Sprite> builder,std::vector<Bullet*> *DestVector,std::unique_ptr<Sprite> *SpriteTemp);

    //constructor
    Player(SpriteBuilder<Sprite> builder, int x, int y, int lives, char spriteID);
};


#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
