cmake_minimum_required(VERSION 3.24)
project(I2PFinalProject)
include("./vcpkg/scripts/buildsystems/vcpkg.cmake")

function (copy_dlls target)
    if (WIN32)
        add_custom_command (
            TARGET "${target}" POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy -t "$<TARGET_FILE_DIR:${target}>"
                    "$<TARGET_RUNTIME_DLLS:${target}>" COMMAND_EXPAND_LISTS
        )
    endif ()
endfunction ()

find_package(Allegro REQUIRED)
find_package(Freetype REQUIRED)
find_package(PNG REQUIRED)
find_package(BZip2 REQUIRED)
find_package(ZLIB REQUIRED)

add_executable(Game Final_Codes/main.c Final_Codes/game.c Final_Codes/menu_scene.c Final_Codes/bullet.c Final_Codes/enemy.c Final_Codes/player.c Final_Codes/game_scene.c Final_Codes/loading_scene.c Final_Codes/map.c Final_Codes/setting_scene.c Final_Codes/UI.c Final_Codes/utility.c Final_Codes/weapon.c)
target_include_directories(Game PRIVATE lib/allegro5/include)
target_link_libraries(Game PUBLIC ZLIB::ZLIB BZip2::BZip2 PNG::PNG Freetype::Freetype)
target_link_libraries(Game PUBLIC Allegro::allegro Allegro::allegro_main Allegro::allegro_font Allegro::allegro_ttf Allegro::allegro_image Allegro::allegro_audio Allegro::allegro_acodec Allegro::allegro_primitives)
copy_dlls(Game)
file(COPY Final_Codes/Assets DESTINATION ${CMAKE_BINARY_DIR})