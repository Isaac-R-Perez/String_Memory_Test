@echo off

IF NOT EXIST build mkdir build

pushd build

cl -Zi ..\String_Memory_Test.cpp

popd build