g++ generator.cpp -o generator
FOR /L %%i IN (20000;20000;500000) DO (
	CALL generator -bodynumber %%i -radius 1e5 -maxmass 1e4 > %%i.txt
)