//
// Created by Gille on 1/26/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_ENTITY_H
#define GBA_SPRITE_ENGINE_PROJECT_ENTITY_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>
#include <libgba-sprite-engine/gba/tonc_types.h>
#include <libgba-sprite-engine/gba_engine.h>

class Entity {

protected:
    int hp;
    int ammo;
    int potion;
    int FirstAid;
    char ID;

    int PosX;
    int PosY;
    int speedX;
    int speedY;
    bool boolMoving;
    short int facingx = 0;
    short int facingy = 0;
    short int TimeBetweenShots = 20;
    short int ShotCooldown = 0;
    short int staticModel = 7;
    bool moveflag = false;
    int moveTimer = 0;
    bool boolFlipHori;

public:

    std::unique_ptr<Sprite> spriteEntity;
    //Global getters
    int getAmmo() const {return this->ammo;}
    int getPotions() const {return this->potion;}
    int getFirstAid() const {return this->FirstAid;}
    int getXcoord() const {return this->spriteEntity->getX();}
    int getYcoord() const {return this->spriteEntity->getY();}
    bool getMoving() const {return this->boolMoving;}
    short int getFaceX() const {return this->facingx;}
    short int getFaceY() const {return this->facingy;}

    Sprite * getSprite() const { return this->spriteEntity.get();}
    //std::shared_ptr<Weapon> getWeapon();

    //global setters
    bool shoot();
    void setParameters();//int speedX, int speedY);//, bool boolFlipHori, bool boolFlipVerti, int frameNumber);
    //void setWeapon(std::shared_ptr<Weapon> gun);

    //actions

    //constructor
    Entity(){}
    ~Entity(){printf("\n you died \n");}

};


#endif //GBA_SPRITE_ENGINE_PROJECT_ENTITY_H
