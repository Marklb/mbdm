@echo off
REM mkdir build32 & pushd build32
REM cmake -G "Visual Studio 14 2015" ../
REM popd
mkdir build64 & pushd build64
REM cmake -G "Visual Studio 14 2015 Win64" ../
cmake -G "Visual Studio 15 Win64" ../
REM cmake ../
popd
REM cmake --build build32 --config Release
cmake --build build64 --config Release
REM cmake --build build32
REM cmake --build build64
