g++ generator.cpp -o generator
FOR /L %%i IN (2;423;30000) DO (
	CALL generator -bodynumber %%i > body_number_%%i.txt
)