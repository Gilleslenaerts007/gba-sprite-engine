//
// Created by jonas on 26/01/2021.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SCENE_DEATH_H
#define GBA_SPRITE_ENGINE_PROJECT_SCENE_DEATH_H

#include <libgba-sprite-engine/scene.h>


class scene_death : public Scene {
private:
    //int rotation,rotationDiff, scrollX, scrollY;
    std::unique_ptr<Background> bg;
public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    scene_death(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;
    //scene_death(std::shared_ptr<GBAEngine> engine) : Scene(engine), rotation(0), rotationDiff(128), scrollX(0), scrollY(0) {}

};


#endif //GBA_SPRITE_ENGINE_PROJECT_SCENE_DEATH_H
