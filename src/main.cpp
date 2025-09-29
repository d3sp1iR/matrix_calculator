#include <iostream>
#include "matrix.h"

int main() {
    try {
        // Создание и заполнение матриц
        Matrix A = create_matrix(2, 2);
        Matrix B = create_matrix(2, 2);

        A.data[0][0] = 1; A.data[0][1] = 2;
        A.data[1][0] = 3; A.data[1][1] = 4;

        B.data[0][0] = 5; B.data[0][1] = 6;
        B.data[1][0] = 7; B.data[1][1] = 8;

        // Выполнение операций
        Matrix C = matrix_add(A, B);
        Matrix D = matrix_multiply(A, B);

        // Вывод результатов
        std::cout << "Matrix A:" << std::endl;
        print_matrix(A);

        std::cout << "Matrix B:" << std::endl;
        print_matrix(B);

        std::cout << "A + B:" << std::endl;
        print_matrix(C);

        std::cout << "A * B:" << std::endl;
        print_matrix(D);

        // Освобождение памяти
        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
        free_matrix(D);

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}