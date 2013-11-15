g++ generator.cpp -o generator
FOR /L %%i IN (300;300;30000) DO (
	CALL generator -bodynumber %%i -radius 1e5 -maxmass 1e4 > %%i.txt
)