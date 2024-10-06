cmake_minimum_required(VERSION 3.28)
project(Engine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

add_subdirectory(GLFW)
add_subdirectory(GLEW)

add_library(${PROJECT_NAME} STATIC src/Entity.cpp
        src/Game.cpp
        src/GuiManager.cpp
        src/Vector2.cpp
        src/Color.cpp
        ImGui/imgui_widgets.cpp
        ImGui/imgui_tables.cpp
        ImGui/imgui_impl_opengl3.cpp
        ImGui/imgui_impl_glfw.cpp
        ImGui/imgui_draw.cpp
        ImGui/imgui.cpp
        stb/stb_image.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/GLFW/include")
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/GLEW/include")
target_link_libraries(${PROJECT_NAME} PUBLIC glfw libglew_static)