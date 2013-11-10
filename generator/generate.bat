g++ generator.cpp -o generator
FOR /L %%i IN (300;300;30000) DO (
	CALL generator -bodynumber %%i > body_number_%%i.txt
)