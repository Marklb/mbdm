@echo off
REM mkdir build32 & pushd build32
REM cmake -G "Visual Studio 14 2015" ../
REM popd
mkdir build64 & pushd build64
cmake -G "Visual Studio 14 2015 Win64" ../
popd
REM cmake --build build32 --config Release
cmake --build build64 --config Release
REM cmake --build build32
REM cmake --build build64