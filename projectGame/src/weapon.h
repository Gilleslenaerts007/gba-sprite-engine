//
// Created by Gille on 12/17/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_WEAPON_H
#define GBA_SPRITE_ENGINE_PROJECT_WEAPON_H

#include <string>
#include <vector>

class Weapon{

public:
    int getPrice()const{return this->price;}
    std::string getName() const {return this->name;}
    /*
     * These printouts have to be changed to textstreams ingame.
    void PrintStats()const{std::cout<<" Gun stats "<<endl;
        std::cout<<" \t >> Weapon: "<<this->name << endl;
        std::cout<<" \t >> damage: "<<this->baseDamage<<endl;
        std::cout<<" \t >> attachments: "<<this->attachment<<endl;
        std::cout<<" \t >> Accuracy: "<<this->accuracy << endl;
        std::cout<<" \t >> Ammo: "<<this->ammo<<endl;
        std::cout<<" \t >> Mag: "<<this->magazine<<endl;}
    std::string GetWeaponName()const{return this->name;}
    */
    virtual int GetDamage()
    {
        if (rand()%100<=accuracy){
            return (baseDamage + (2*attachment));
        }
        else return 0;
    }
    int getAmmo()const{return ammo;}

private:
    int baseDamage;
    int attachment;
    int accuracy;
    int ammo;
    int magazine;
    int price;
    std::string name;

    void PowerUp(const int stats){
        this->baseDamage+=stats;
        //this->accuracy+=stats;
    }


    void Attach(){attachment += 1 ;}

    void LowerAmmo(const int bullets){
        this->ammo -= bullets;
    }
    int getBaseDamage()const{return baseDamage;}
    int getAccuracy()const{return accuracy;}
    int getMagazine() const {return magazine;}
    int getAttachMent() const {return attachment;}

protected:

};



#endif //GBA_SPRITE_ENGINE_PROJECT_WEAPON_H
