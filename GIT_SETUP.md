# Guía para Subir el Proyecto a Git

## 📋 Pasos para inicializar y subir a Git

### 1. Inicializar el repositorio Git (si no está inicializado)

```powershell
git init
```

### 2. Agregar todos los archivos al staging

```powershell
git add .
```

### 3. Hacer el primer commit

```powershell
git commit -m "Initial commit: Juego tipo Mario con raylib"
```

### 4. Agregar el repositorio remoto (GitHub, GitLab, etc.)

```powershell
# Para GitHub
git remote add origin https://github.com/TU_USUARIO/TU_REPOSITORIO.git

# O para SSH
git remote add origin git@github.com:TU_USUARIO/TU_REPOSITORIO.git
```

### 5. Subir el código

```powershell
# Primera vez (establecer upstream)
git push -u origin main

# O si tu rama se llama master
git push -u origin master
```

## 🔄 Comandos útiles para actualizaciones futuras

### Ver el estado del repositorio
```powershell
git status
```

### Agregar cambios específicos
```powershell
git add src/Player.cpp
git add src/Level.cpp
```

### Hacer commit de cambios
```powershell
git commit -m "Descripción de los cambios realizados"
```

### Subir cambios
```powershell
git push
```

### Ver el historial de commits
```powershell
git log
```

## 📝 Notas importantes

- **NO subir**: El directorio `build/` está en `.gitignore` y no se subirá
- **SÍ subir**: Los archivos fuente en `src/`, `assets/`, `CMakeLists.txt`, etc.
- **Archivos Python**: Los scripts `.py` se subirán (útil para procesar assets)

## 🚨 Si ya tienes un repositorio remoto

Si ya tienes un repositorio en GitHub/GitLab y quieres conectar este proyecto:

```powershell
git remote add origin URL_DEL_REPOSITORIO
git branch -M main  # O master según tu configuración
git push -u origin main
```

## 🔍 Verificar qué se va a subir

Antes de hacer commit, puedes ver qué archivos se agregarán:

```powershell
git status
```

Esto mostrará los archivos que están listos para commit y los que no están siendo rastreados.

