all:
	msbuild TetrisOpenGL.sln /p:Configuration=Debug /p:Platform=x64
	@echo "Copying .ttf and .png files"
	@cp "TetrisOpenGL\OpenSans-Light.ttf" "x64\Debug\OpenSans-Light.ttf"
	@mkdir -p "x64\Debug\res\textures"
	@cp "TetrisOpenGL\res\textures\img.png" "x64\Debug\res\textures\img.png"

allRelease:
	msbuild TetrisOpenGL.sln /p:Configuration=Release /p:Platform=x64
	@echo "Copying .ttf and .png files"
	@cp "TetrisOpenGL\OpenSans-Light.ttf" "x64\Release\OpenSans-Light.ttf"
	@mkdir -p "x64\Release\res\textures"
	@cp "TetrisOpenGL\res\textures\img.png" "x64\Release\res\textures\img.png"

clean:
	msbuild TetrisOpenGL.sln /t:Clean /p:Configuration=Debug /p:Platform=x64
	rm -rf "x64/Debug"
	msbuild TetrisOpenGL.sln /t:Clean /p:Configuration=Release /p:Platform=x64
	rm -rf "x64/Release"

rebuild: clean all

rebuildRelease: clean allRelease