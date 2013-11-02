DEL g++\*
MKDIR g++
DEL msbuild\*
MKDIR msbuild
FOR /L %%i IN ( 1; 1; 20 ) DO ( 
	ECHO const coord_t THETA = 1.0 / %%i; > theta.hpp
	CALL g++ barnes_hut.cpp
	MOVE a.exe g++\theta_%%i_part.exe
	CALL MSBuild Barnes-Hut.vcxproj /p:Configuration=Release
	MOVE Release\Barnes-Hut.exe msbuild\theta_%%i_part.exe
)