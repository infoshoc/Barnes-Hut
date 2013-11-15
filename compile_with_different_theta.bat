DEL g++\*
MKDIR g++
DEL msbuild\*
MKDIR msbuild
FOR /L %%i IN ( 5; 5; 100 ) DO ( 
	ECHO const coord_t THETA = 0.01 * %%i; > theta.hpp
	CALL g++ barnes_hut.cpp
	MOVE a.exe g++\%%i.exe
	CALL MSBuild Barnes-Hut.vcxproj /p:Configuration=Release
	MOVE Release\Barnes-Hut.exe msbuild\%%i.exe
)