$param = $args[0]

Copy-Item -Path ".\TetrisOpenGL\OpenSans-Light.ttf" -Destination ".\x64\$param"
New-Item -ItemType Directory -Force -Path ".\x64\$param\res\textures" | Out-Null
Copy-Item -Path ".\TetrisOpenGL\res\textures\img.png" -Destination ".\x64\$param\res\textures"