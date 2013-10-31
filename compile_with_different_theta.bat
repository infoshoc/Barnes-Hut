FOR /L %%i IN ( 0; 1; 20 ) DO ( 
	ECHO const coord_t THETA = 1.0 / %%i; > theta.hpp
	CALL g++ barnes_hut.cpp -o theta_%%i_part
)