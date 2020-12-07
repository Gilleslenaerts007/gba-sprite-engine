//
// Created by Gille on 12/7/2020.
//

#ifndef GBA_SPRITE_ENGINE_PROJECT_SCENE_START_H
#define GBA_SPRITE_ENGINE_PROJECT_SCENE_START_H

#include <libgba-sprite-engine/scene.h>

class scene_start : public Scene {

private:
    std::unique_ptr<Sprite> animation;
    std::unique_ptr<Sprite> finalFantasyGuy;
    std::unique_ptr<Sprite> smiley;
    bool pressingAorB = false;

public:
    std::vector<Sprite *> sprites() override;
    std::vector<Background *> backgrounds() override;

    scene_start(std::shared_ptr<GBAEngine> engine) : Scene(engine) {}

    void load() override;
    void tick(u16 keys) override;

};


#endif //GBA_SPRITE_ENGINE_PROJECT_SCENE_START_H
