# Juego Tipo Mario - Alan Garcia Platformer

Un juego de plataformas estilo Mario Bros desarrollado en C++ usando raylib.

## 🎮 Características

- **Sistema de movimiento**: Salto doble, movimiento fluido
- **Combate**: Espada y escudo para defenderse
- **Enemigos**: Ladrones que patrullan el mapa
- **Cajas especiales**: Cajas amarillas con espadas que se pueden golpear
- **Mapa extendido**: Nivel largo estilo Mario Bros (3000 bloques)
- **Sistema de salud**: 3 corazones de vida
- **Timer**: 3 minutos para completar el nivel

## 🚀 Requisitos

- CMake 3.11 o superior
- Compilador C++17 (Visual Studio, MinGW, GCC, etc.)
- Conexión a Internet (para descargar raylib la primera vez)

## 📦 Instalación y Compilación

### Windows (PowerShell)

```powershell
# Usar el script de compilación
.\compile.ps1

# O manualmente
cd build
cmake ..
cmake --build . --config Release
```

### Linux/Mac

```bash
# Usar el script de compilación
chmod +x compile.sh
./compile.sh

# O manualmente
cd build
cmake ..
cmake --build . --config Release
```

## 🎯 Controles

- **Flechas** o **WASD**: Mover personaje
- **Espacio**: Saltar (doble salto disponible)
- **E** o **Clic Izquierdo**: Atacar con espada
- **Clic Derecho**: Activar escudo
- **R**: Reiniciar juego (cuando game over)
- **ESC**: Salir

## 🗺️ Estructura del Proyecto

```
juego_tipo_mario/
├── assets/          # Recursos del juego (sprites, texturas)
├── src/             # Código fuente
│   ├── main.cpp     # Punto de entrada
│   ├── Player.cpp   # Lógica del jugador
│   ├── Player.h
│   ├── Level.cpp    # Lógica del nivel
│   ├── Level.h
│   ├── Enemy.cpp    # Lógica de enemigos
│   └── Enemy.h
├── build/           # Directorio de compilación (generado)
├── CMakeLists.txt   # Configuración CMake
└── README.md        # Este archivo
```

## 🎨 Características del Juego

### Jugador
- Velocidad: 200 píxeles/segundo
- Salto: 450 píxeles de fuerza
- Salud: 3 corazones
- Tamaño: 32x64 píxeles

### Enemigos
- Velocidad: 80 píxeles/segundo (más lentos que el jugador)
- Tamaño: 80% del jugador (25.6x51.2 píxeles)
- Comportamiento: Patrullan en áreas específicas
- Animación de muerte: Caen y rotan antes de desaparecer

### Cajas Especiales
- **Cajas amarillas**: Contienen espadas
- **Efecto de rebote**: Se empujan hacia arriba al ser golpeadas
- **Animación de espada**: La espada sale desde dentro de la caja

## 🛠️ Desarrollo

### Agregar Nuevas Características

1. **Nuevos enemigos**: Editar `src/Enemy.cpp` y `src/Enemy.h`
2. **Nuevos niveles**: Modificar `src/Level.cpp`
3. **Nuevos controles**: Editar `src/Player.cpp`

### Compilar en Modo Debug

```powershell
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . --config Debug
```

## 📝 Notas

- El juego descarga raylib automáticamente la primera vez que se compila
- Los assets deben estar en la carpeta `assets/` relativa al ejecutable
- El mapa se genera proceduralmente cada vez que se inicia el juego

## 📄 Licencia

Este proyecto es de código abierto. Siéntete libre de modificarlo y usarlo.

## 👨‍💻 Autor

Desarrollado como proyecto de aprendizaje de C++ y desarrollo de juegos.

---

¡Disfruta del juego! 🎮

