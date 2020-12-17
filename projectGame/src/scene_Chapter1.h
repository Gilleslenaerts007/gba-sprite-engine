//
// Created by Gille on 12/14/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SCENE_CHAPTER1_H
#define GBA_SPRITE_ENGINE_PROJECT_SCENE_CHAPTER1_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/background/background.h>

class scene_Chapter1 : public Scene {

private:
    std::unique_ptr<AffineSprite>  enemy;
    std::unique_ptr<AffineSprite>  player;
    std::unique_ptr<Sprite> bullet;
    std::unique_ptr<Background> bg_C1;
    bool pressingAorB = false;

    int scrollX, scrollY;
    int rotation;
    int rotationDiff = 128;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    scene_Chapter1(std::shared_ptr<GBAEngine> engine) : Scene(engine), rotation(0), rotationDiff(128), scrollX(0), scrollY(0) {}

    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_PROJECT_SCENE_CHAPTER1_H
