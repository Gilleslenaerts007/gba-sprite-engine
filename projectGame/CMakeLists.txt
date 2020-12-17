project(projectGame)

add_executable(${PROJECT_NAME}.elf
        src/main.cpp src/scene_start.cpp src/scene_start.h src/manneke.h src/bg1.h src/scene_Chapter1.cpp src/scene_Chapter1.h src/bg_Chapter1.h src/pixel_player.h src/enemies_Chapter1.h src/pixel_menu.h src/player.cpp src/player.h src/weapon.cpp src/weapon.h)
target_link_libraries(${PROJECT_NAME}.elf gba-sprite-engine)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -v -O binary ${PROJECT_NAME}.elf ${PROJECT_NAME}.gba
        )
