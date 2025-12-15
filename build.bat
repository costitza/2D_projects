@echo off

:: Check if at least one argument was given
if "%~1"=="" (
    echo Usage: build [files.cpp...] -o [output_name.exe]
    echo Example: build classes/main.cpp classes/Player.cpp -o main.exe
    exit /b
)

:: %* passes ALL arguments you typed (file names, flags, etc.)
:: We append the SFML includes and libraries at the end.
g++ %* ^
-ID:/sfml/SFML-2.6.1/include ^
-LD:/sfml/SFML-2.6.1/lib ^
-lsfml-graphics -lsfml-window -lsfml-system

if %errorlevel%==0 (
    echo Build successful!
) else (
    echo Build failed!
)