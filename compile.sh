#!/bin/bash
echo "Compilando el juego..."
cd build
cmake --build . --config Release
if [ $? -eq 0 ]; then
    echo ""
    echo "Compilacion exitosa!"
    echo "El ejecutable esta en: build/Release/game.exe"
else
    echo ""
    echo "Error en la compilacion!"
fi

