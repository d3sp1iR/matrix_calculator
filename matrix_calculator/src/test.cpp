#include <cassert>
#include <iostream>
#include "matrix.h"

void test_matrix_addition() {
    std::cout << "Testing matrix addition... ";

    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;

    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;

    Matrix result = matrix_add(A, B);

    assert(result.data[0][0] == 6);
    assert(result.data[0][1] == 8);
    assert(result.data[1][0] == 10);
    assert(result.data[1][1] == 12);

    free_matrix(A);
    free_matrix(B);
    free_matrix(result);

    std::cout << "PASSED!" << std::endl;
}

void test_invalid_addition() {
    std::cout << "Testing invalid addition... ";

    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(3, 3);

    try {
        Matrix result = matrix_add(A, B);
        assert(false); // Если сюда попали, тест не пройден
    } catch (const std::exception& e) {
        // Ожидаемое поведение - исключение
        assert(std::string(e.what()) == "Matrix dimensions must match for addition");
    }

    free_matrix(A);
    free_matrix(B);
    std::cout << "PASSED!" << std::endl;
}

int main() {
    test_matrix_addition();
    test_invalid_addition();
    std::cout << "All tests passed successfully!" << std::endl;
    return 0;
}