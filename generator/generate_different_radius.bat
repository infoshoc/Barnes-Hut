DEL *.txt
g++ generator.cpp -o generator
FOR /L %%i IN (100;100000;10000000) DO (
	CALL generator -bodynumber 300 -radius %%i -maxmass 1e4 > %%i.txt
)