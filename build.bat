@echo off
setlocal

set BUILD_TYPE=%1
if "%BUILD_TYPE%"=="" set BUILD_TYPE=Debug

if not exist build mkdir build
cd build

cmake .. -DCMAKE_BUILD_TYPE=%BUILD_TYPE%
if errorlevel 1 exit /b 1

cmake --build . --config %BUILD_TYPE% --parallel %NUMBER_OF_PROCESSORS%
if errorlevel 1 exit /b 1

endlocal
