all:
	msbuild TetrisOpenGL.sln /p:Configuration=Debug /p:Platform=x64

allRelease:
	msbuild TetrisOpenGL.sln /p:Configuration=Release /p:Platform=x64

clean:
	msbuild TetrisOpenGL.sln /t:Clean /p:Configuration=Debug /p:Platform=x64
	msbuild TetrisOpenGL.sln /t:Clean /p:Configuration=Release /p:Platform=x64

rebuild: clean all

rebuildRelease: clean allRelease