find_package(GTest REQUIRED CONFIG)

set(LIB_SOURCES
    ../src/Vector2D.cpp
    ../src/ECS/ECS.cpp
)


set(TEST_SOURCES
    main.cpp
    testComponents.cpp
    testVector2D.cpp
)

add_library(NeoBirchLib STATIC ${LIB_SOURCES})

target_include_directories(NeoBirchLib PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)

if(LINUX)
    target_link_libraries(NeoBirchLib PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
    )
else()
    target_link_libraries(NeoBirchLib PRIVATE
        SDL2::SDL2
        SDL2_image::SDL2_image 
        sdl_ttf::sdl_ttf
        SDL2_mixer::SDL2_mixer
    )
endif()


add_executable(NeoBirchTests ${TEST_SOURCES})
target_compile_definitions(NeoBirchTests PRIVATE SDL_MAIN_HANDLED)

target_include_directories(NeoBirchTests PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/../include"
)

target_link_libraries(NeoBirchTests PRIVATE
    NeoBirchLib
    GTest::gtest
)

include(GoogleTest)

gtest_discover_tests(NeoBirchTests)
