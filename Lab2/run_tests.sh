#!/bin/bash

# Step 1: Создание папки build, если она не существует
if [ ! -d "build" ]; then
  mkdir build
fi

# Step 2: Переход в папку build
cd build

# Step 3: Генерация файлов сборки через CMake
cmake ..
if [ $? -ne 0 ]; then
  echo "Ошибка при генерации файлов сборки!"
  exit 1
fi

# Step 4: Компиляция проекта
cmake --build .
if [ $? -ne 0 ]; then
  echo "Ошибка при компиляции!"
  exit 1
fi

# Step 5: Запуск тестов, если компиляция прошла успешно
if [ -f "./runTests" ]; then
  ./runTests
else
  echo "Файл runTests не найден!"
fi