all:
	msbuild TetrisOpenGL.sln /p:Configuration=Debug /p:Platform=x64
	@echo "Copying .ttf and .png files"
	@powershell ./copy.ps1 Debug

allRelease:
	msbuild TetrisOpenGL.sln /p:Configuration=Release /p:Platform=x64
	@echo "Copying .ttf and .png files"
	@powershell ./copy.ps1 Release

clean:
	msbuild TetrisOpenGL.sln /t:Clean /p:Configuration=Debug /p:Platform=x64
	@echo "Removing .ttf and .png files from Debug"
	@powershell ./clean.ps1 Debug
	@echo "Removing .ttf and .png files from Release"
	msbuild TetrisOpenGL.sln /t:Clean /p:Configuration=Release /p:Platform=x64
	@powershell ./clean.ps1 Release

rebuild: clean all

rebuildRelease: clean allRelease