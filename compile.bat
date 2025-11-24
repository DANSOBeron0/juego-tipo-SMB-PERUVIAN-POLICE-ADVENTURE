@echo off
echo Compilando el juego...
cd build
cmake --build . --config Release
if %ERRORLEVEL% EQU 0 (
    echo.
    echo Compilacion exitosa!
    echo El ejecutable esta en: build\Release\game.exe
) else (
    echo.
    echo Error en la compilacion!
)
pause

