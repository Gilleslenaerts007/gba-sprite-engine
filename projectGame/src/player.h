//
// Created by Gille on 12/17/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
#define GBA_SPRITE_ENGINE_PROJECT_PLAYER_H

#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/sprite_builder.h>


class player : public Sprite {
private:
    //std::shared_ptr<Weapon> ak;
    int ammo;
    int potion;
    int FirstAid;
    std::unique_ptr<Sprite> spriteplayer;

public:

    //Global player getters
    int getAmmo() const {return ammo;}
    int getPotions() const {return potion;}
    int getFirstAid() const {return FirstAid;}
    int getXcoord();
    int getYcoord();
    //std::shared_ptr<Weapon> getWeapon();

    //global player setters
    void movePlayer (bool up, bool down, bool left, bool right);
    void setBuilder(SpriteBuilder<Sprite> builder, int x, int y);
    bool playerShoot();
    //void setWeapon(std::shared_ptr<Weapon> gun);

};


#endif //GBA_SPRITE_ENGINE_PROJECT_PLAYER_H
