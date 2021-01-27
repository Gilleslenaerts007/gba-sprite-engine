//
// Created by Gille on 1/26/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SCENE_DEATH_H
#define GBA_SPRITE_ENGINE_PROJECT_SCENE_DEATH_H

#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/sprites/sprite.h>
#include <libgba-sprite-engine/sprites/affine_sprite.h>
#include <libgba-sprite-engine/background/background.h>

class scene_death : public Scene {
public:

    std::unique_ptr<Background> bg;

    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    scene_death(const std::shared_ptr<GBAEngine> &engine);

    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_PROJECT_SCENE_DEATH_H
