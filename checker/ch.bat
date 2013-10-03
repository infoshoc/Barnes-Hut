del verdict_*.v
del *.sol
FOR %%i IN (*.txt) DO (
	CALL bf.exe %%i %%i_bf.sol
	CALL bh.exe %%i %%i_bh.sol
	CALL checker.exe %%i_bf.sol %%i_bh.sol > verdict_%%i.v
)

