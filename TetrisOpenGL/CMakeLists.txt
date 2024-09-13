cmake_minimum_required(VERSION 3.28)
project(TetrisOpenGL)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} Main.cpp
        src/BoardManager.cpp
        src/Tetris.cpp
        src/TetriminoCubeGroup.cpp
        src/Cube.cpp
        src/TetriminoCreator.cpp
        src/JsonWrapper.cpp
        src/TetriminoCube.cpp
        src/Settings.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")

target_link_libraries(${PROJECT_NAME} PRIVATE Engine)

# Copy .ttf file to destination directory
set(copy_source_dir "${CMAKE_SOURCE_DIR}/TetrisOpenGL")
set(copy_dest_dir "${CMAKE_BINARY_DIR}/TetrisOpenGL")
set(copy_file_name "OpenSans-Light.ttf")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${copy_dest_dir}
)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy "${copy_source_dir}/${copy_file_name}" "${copy_dest_dir}/${copy_file_name}"
        COMMENT "Copying ${copy_file_name} to build directory"
)

# Copy .png file to destination directory
set(copy_source_dir "${CMAKE_SOURCE_DIR}/TetrisOpenGL/res/textures")
set(copy_dest_dir "${CMAKE_BINARY_DIR}/TetrisOpenGL/res/textures")
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${copy_dest_dir}
)
add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${copy_source_dir}" "${copy_dest_dir}"
        COMMENT "Copying .png files to build directory"
)