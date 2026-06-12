<<<<<<< HEAD
find_package(GTest REQUIRED CONFIG)
find_package(SDL2 REQUIRED CONFIG)
find_package(SDL2_image REQUIRED CONFIG)
find_package(SDL2_ttf REQUIRED CONFIG)
find_package(SDL2_mixer REQUIRED CONFIG)
=======
find_package(gtest REQUIRED CONFIG)
>>>>>>> 96d8643 (Compile SDL2 with the tests, add more tests)

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

<<<<<<< HEAD
if(UNIX AND NOT APPLE)
    target_link_libraries(NeoBirchLib PUBLIC
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
    )
else()
    target_link_libraries(NeoBirchLib PUBLIC
        SDL2::SDL2
        SDL2_image::SDL2_image 
        sdl_ttf::sdl_ttf
        SDL2_mixer::SDL2_mixer
    )
endif()
=======
target_link_libraries(NeoBirchLib PUBLIC
    SDL2::SDL2-static
    SDL2_image::SDL2_image
    sdl_ttf::sdl_ttf
    SDL2_mixer::SDL2_mixer
)

>>>>>>> 96d8643 (Compile SDL2 with the tests, add more tests)

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

# Register tests with CTest
gtest_discover_tests(NeoBirchTests)
