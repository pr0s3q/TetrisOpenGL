### Before building

```sh
git submodule init
git submodule update
```

### Problems with launching
On Linux Wayland, of you are getting `Cannot initialize GLEW`, go to `Engine\GLFW\CMakeLists.txt` and comment this line
```sh
cmake_dependent_option(GLFW_BUILD_WAYLAND "Build support for Wayland" ON "UNIX;NOT APPLE" OFF)
```