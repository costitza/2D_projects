@echo off

if "%1"=="" (
    echo Usage: build *.cpp
    exit /b
)

if "%2"=="" (
    echo Specify the where you intend to build
    exit /b
)

g++ %1 ^
-ID:/sfml/SFML-2.6.1/include ^
-LD:/sfml/SFML-2.6.1/lib ^
-lsfml-graphics -lsfml-window -lsfml-system ^
-o %2

if %errorlevel%==0 (
    echo Build successful!
) else (
    echo Build failed!
)
