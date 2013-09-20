FOR %%i IN ( dir *.cpp ) DO (
	CALL g++ %%i -o %%i.exe
	CALL %%i.exe %1 %%i.txt
)