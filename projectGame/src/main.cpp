#include <libgba-sprite-engine/scene.h>
#include <libgba-sprite-engine/gba_engine.h>
#include <libgba-sprite-engine/background/text.h>
#include <libgba-sprite-engine/background/text_stream.h>
#include <libgba-sprite-engine/palette/palette_manager.h>
#include <libgba-sprite-engine/allocator.h>

#include "scene_start.h"
#include <time.h>

int main() {
    std::shared_ptr<GBAEngine> engine(new GBAEngine());

    srand (time(NULL));
    scene_start* startScene = new scene_start(engine);
    engine->setScene(startScene);
    while (true) {
        engine->update();
        //engine->delay(1000);
    }

    return 0;
}