### Before building

```sh
git submodule init
git submodule update
```

### Building from terminal
In repository root directory (where the README.md is located) type
```sh
cmake .
cmake --build .
```

### Problems with launching
On Linux Wayland, of you are getting `Cannot initialize GLEW`, go to `Engine\GLFW\CMakeLists.txt` and comment this line
```sh
cmake_dependent_option(GLFW_BUILD_WAYLAND "Build support for Wayland" ON "UNIX;NOT APPLE" OFF)
```

On MacOS shaders may not compile. I blame Apple for that, since they have problems supporting OpenGL