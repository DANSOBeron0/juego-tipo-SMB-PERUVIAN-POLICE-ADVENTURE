# Script de compilacion para el juego
# Ejecutar desde PowerShell: .\compile.ps1

Write-Host "========================================" -ForegroundColor Cyan
Write-Host "Compilando el juego..." -ForegroundColor Yellow
Write-Host "========================================" -ForegroundColor Cyan
Write-Host ""

# Cambiar al directorio build
Set-Location -Path "build"

# Verificar si CMakeLists.txt existe en el directorio padre
if (-not (Test-Path "..\CMakeLists.txt")) {
    Write-Host "Error: No se encontro CMakeLists.txt en el directorio raiz" -ForegroundColor Red
    Set-Location -Path ".."
    exit 1
}

# Compilar el proyecto
Write-Host "Ejecutando CMake build..." -ForegroundColor Green
cmake --build . --config Release

# Verificar si la compilacion fue exitosa
if ($LASTEXITCODE -eq 0) {
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Green
    Write-Host "Compilacion exitosa!" -ForegroundColor Green
    Write-Host "========================================" -ForegroundColor Green
    Write-Host ""
    Write-Host "El ejecutable esta en: build\Release\game.exe" -ForegroundColor Cyan
    Write-Host ""
    
    # Preguntar si desea ejecutar el juego
    $ejecutar = Read-Host "¿Deseas ejecutar el juego ahora? (S/N)"
    if ($ejecutar -eq "S" -or $ejecutar -eq "s") {
        Write-Host "Ejecutando el juego..." -ForegroundColor Green
        Start-Process ".\Release\game.exe"
    }
} else {
    Write-Host ""
    Write-Host "========================================" -ForegroundColor Red
    Write-Host "Error en la compilacion!" -ForegroundColor Red
    Write-Host "========================================" -ForegroundColor Red
    Write-Host ""
}

# Volver al directorio raiz
Set-Location -Path ".."

