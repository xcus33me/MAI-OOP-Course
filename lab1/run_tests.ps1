if (-not (Test-Path -Path "build")) {
    mkdir build
}

cd build

cmake ..

cmake --build .

if (Test-Path -Path "Debug/runTests.exe") {
    Start-Process "Debug/runTests.exe" -NoNewWindow -Wait
} else {
    Write-Host "Файл Debug/runTests.exe не найден!"
}