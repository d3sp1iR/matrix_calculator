# Используем официальный образ с компилятором GCC
FROM gcc:12.2.0

# Установка дополнительных зависимостей (doxygen, graphviz)
RUN apt-get update && apt-get install -y \
    doxygen \
    graphviz \
    && rm -rf /var/lib/apt/lists/*

# Установка рабочей директории внутри контейнера
WORKDIR /app

# Копирование всех исходных файлов в контейнер
COPY . .

# Компиляция основной программы и тестов
RUN g++ -o matrix_app src/matrix.cpp src/main.cpp
RUN g++ -o test_app src/matrix.cpp src/test.cpp

# Генерация документации
RUN doxygen Doxyfile

# Команда по умолчанию: запуск тестов
CMD ["./test_app"]