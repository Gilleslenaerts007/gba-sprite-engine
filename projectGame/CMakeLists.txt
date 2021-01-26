project(projectGame)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp src/scene_start.cpp src/scene_start.h src/bg_Menu.h src/scene_Chapter1.cpp src/scene_Chapter1.h src/bg_Chapter1.h src/pixel_player.h src/player.cpp src/player.h src/weapon.cpp src/weapon.h src/pixel_bullets.h src/Bullet.cpp src/Bullet.h src/enemy.cpp src/enemy.h src/scene_death.cpp src/scene_death.h)
target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
