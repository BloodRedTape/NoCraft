cmake_minimum_required(VERSION 3.10)

project(Minecraft)

set(SOURCES
    sources/main.cpp
    sources/minecraft.cpp 
    sources/player.cpp
    sources/render/render_2d.cpp
    sources/render/chunk_renderer.cpp
    sources/render/world_renderer.cpp
    sources/render/mesh_builder.cpp
    sources/render/texture_atlas.cpp
    sources/render/camera.cpp
    sources/render/mesh.cpp
    sources/render/ui_renderer.cpp
    sources/world/block.cpp
    sources/world/world.cpp
    sources/world/generators/biome.cpp
    sources/world/generators/extreme_world_generator.cpp
    sources/world/generators/natural_world_generator.cpp
    sources/scenes/scene.cpp
    sources/scenes/game_scene.cpp
    sources/scenes/main_menu_scene.cpp
    sources/layers/game_pause_layer.cpp
    sources/layers/inventory_layer.cpp
)

add_subdirectory(StraitX/Engine)

add_executable(Minecraft ${SOURCES})
target_include_directories(Minecraft PUBLIC sources)
target_link_libraries(Minecraft StraitX)