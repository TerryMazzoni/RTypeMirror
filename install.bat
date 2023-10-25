@echo off
echo Building r-type_server and r-type_client...

set BUILD_DIR=build

for /f %%a in ('"wmic cpu get NumberOfCores | findstr [0-9]"') do set NUM_CORES=%%a

cmake -B %BUILD_DIR%
cmake --build %BUILD_DIR% --config Release --parallel %NUM_CORES%

copy Release\r-type_server.exe .
copy Release\r-type_client.exe .
echo Build completed. .exe files are in the Release directory.
pause