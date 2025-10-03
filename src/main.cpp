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

        // ============================================
        // ДЕМОНСТРАЦИЯ matrix_equals
        // ============================================
        
        std::cout << "\n=== Testing matrix_equals function ===" << std::endl;
        
        // Тест 1: Создаем две одинаковые матрицы
        Matrix E = create_matrix(2, 2);
        Matrix F = create_matrix(2, 2);
        
        E.data[0][0] = 1.0; E.data[0][1] = 2.0;
        E.data[1][0] = 3.0; E.data[1][1] = 5.0;
        
        F.data[0][0] = 1.0; F.data[0][1] = 2.0;
        F.data[1][0] = 3.0; F.data[1][1] = 4.0;
        
        std::cout << "Matrix E:" << std::endl;
        print_matrix(E);
        std::cout << "Matrix F:" << std::endl;
        print_matrix(F);
        std::cout << "E equals F (tolerance 0.001): " 
                  << (matrix_equals(E, F, 0.001) ? "YES" : "NO") << std::endl;
        
        // Тест 2: Матрицы с небольшой погрешностью
        Matrix G = create_matrix(2, 2);
        G.data[0][0] = 1.001; G.data[0][1] = 2.001;
        G.data[1][0] = 3.001; G.data[1][1] = 4.001;
        
        std::cout << "\nMatrix G (slightly different from E):" << std::endl;
        print_matrix(G);
        std::cout << "E equals G with tolerance 0.01: " 
                  << (matrix_equals(E, G, 0.01) ? "YES" : "NO") << std::endl;
        std::cout << "E equals G with tolerance 0.0001: " 
                  << (matrix_equals(E, G, 0.0001) ? "YES" : "NO") << std::endl;
        
        // Тест 3: Матрицы разных размеров
        Matrix H = create_matrix(2, 3);
        std::cout << "\nMatrix H (different size 2x3):" << std::endl;
        print_matrix(H);
        std::cout << "E equals H (different sizes): " 
                  << (matrix_equals(E, H, 0.001) ? "YES" : "NO") << std::endl;
        
        // Тест 4: Сравнение матрицы с самой собой
        std::cout << "E equals E: " 
                  << (matrix_equals(E, E, 0.001) ? "YES" : "NO") << std::endl;

        // Освобождение памяти для новых матриц
        free_matrix(E);
        free_matrix(F);
        free_matrix(G);
        free_matrix(H);
        
        // ============================================
        // КОНЕЦ ДОБАВЛЕННОГО БЛОКА
        // ============================================

        // Освобождение памяти исходных матриц
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