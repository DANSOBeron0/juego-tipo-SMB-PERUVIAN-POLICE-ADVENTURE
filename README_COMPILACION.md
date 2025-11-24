# Guía de Compilación

## Compilar desde PowerShell

### Método 1: Usar el script (Recomendado)
```powershell
.\compile.ps1
```

### Método 2: Comandos manuales

#### Primera vez (configurar CMake):
```powershell
cd build
cmake ..
cd ..
```

#### Compilar:
```powershell
cd build
cmake --build . --config Release
cd ..
```

#### Compilar y ejecutar en un solo comando:
```powershell
cd build; cmake --build . --config Release; cd ..; .\build\Release\game.exe
```

### Método 3: Todo en uno (primera vez)
```powershell
# Desde la raíz del proyecto
cd build
cmake ..
cmake --build . --config Release
cd ..
```

## Ubicación del ejecutable

Después de compilar, el ejecutable estará en:
```
build\Release\game.exe
```

## Requisitos

- CMake 3.11 o superior
- Compilador C++ (Visual Studio, MinGW, etc.)
- Conexión a Internet (para descargar raylib la primera vez)

## Notas

- La primera compilación puede tardar más porque descarga y compila raylib
- Las compilaciones posteriores serán más rápidas
- El script `compile.ps1` pregunta si deseas ejecutar el juego después de compilar

