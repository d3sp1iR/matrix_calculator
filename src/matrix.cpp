#include "matrix.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cmath>

Matrix create_matrix(int rows, int cols) {
    // 1. Проверка корректности размеров
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix dimensions must be positive integers");
    }
    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;
    // 2. Выделение памяти для массива указателей
    mat.data = new double*[rows];
    if (mat.data == nullptr) {
        throw std::bad_alloc();
    }
    // 3. Выделение памяти для каждой строки
    for (int i = 0; i < rows; i++) {
        mat.data[i] = new double[cols];
        if (mat.data[i] == nullptr) {
            // Освобождаем уже выделенную память при ошибке
            for (int j = 0; j < i; j++) {
                delete[] mat.data[j];
            }
            delete[] mat.data;
            throw std::bad_alloc();
        }
        
        // 4. Инициализация нулями
        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = 0.0;
        }
    }
     return mat;
}

void free_matrix(Matrix m) {
    // Защита от двойного освобождения
    if (m.data == nullptr) {
        return;
    }

    // Освобождение памяти каждой строки
    for (int i = 0; i < m.rows; i++) {
        if (m.data[i] != nullptr) {
            delete[] m.data[i];
        }
    }
    // Освобождение массива указателей
    delete[] m.data;

    // Опционально: обнуление структуры для предотвращения использования после освобождения
    // (работает с копией структуры, поэтому в вызывающем коде указатель станет невалидным)
    m.data = nullptr;
    m.rows = 0;
    m.cols = 0;
}

Matrix matrix_add(Matrix a, Matrix b) {
    // Проверка совместимости размеров
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Matrix dimensions must match for addition");
    }

    Matrix result = create_matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

Matrix matrix_multiply(Matrix a, Matrix b) {
    // Проверка совместимости размеров
    if (a.cols != b.rows) {
        throw std::invalid_argument("Number of columns in A must equal number of rows in B");
    }

    Matrix result = create_matrix(a.rows, b.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.data[i][j] = 0.0;
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }
    return result;
}

void print_matrix(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]" << std::endl;
        return;
    }

    std::cout << std::fixed << std::setprecision(2);

    const int MAX_ROWS_TO_SHOW = 10;
    const int MAX_COLS_TO_SHOW = 8;
    bool show_summary = (m.rows > MAX_ROWS_TO_SHOW || m.cols > MAX_COLS_TO_SHOW);
    int rows_to_show = show_summary ? MAX_ROWS_TO_SHOW : m.rows;
    int cols_to_show = show_summary ? MAX_COLS_TO_SHOW : m.cols;

    for (int i = 0; i < rows_to_show; i++) {
        if (show_summary && i == MAX_ROWS_TO_SHOW / 2 && m.rows > MAX_ROWS_TO_SHOW) {
            std::cout << "[...";
            for (int j = 0; j < cols_to_show - 2; j++) {
                std::cout << "      ";
            }
            std::cout << "...]" << std::endl;
            continue;
        }

        std::cout << "[";
        for (int j = 0; j < cols_to_show; j++) {
            if (show_summary && j == MAX_COLS_TO_SHOW / 2 && m.cols > MAX_COLS_TO_SHOW) {
                std::cout << " ... ";
                continue;
            }
            std::cout << std::setw(6) << m.data[i][j];
            if (j < cols_to_show - 1) {
                std::cout << " ";
            }
        }
        std::cout << "]";

        if (show_summary && m.cols > MAX_COLS_TO_SHOW) {
            std::cout << " ...";
        }
        std::cout << std::endl;
    }

    if (show_summary && m.rows > MAX_ROWS_TO_SHOW) {
        std::cout << "[...";
        for (int j = 0; j < std::min(cols_to_show, m.cols); j++) {
            std::cout << " ... ";
        }
        std::cout << "...]" << std::endl;
    }

    if (show_summary) {
        std::cout << "Matrix " << m.rows << "×" << m.cols 
                  << " (showing first " << rows_to_show << "×" << cols_to_show << ")"
                  << std::endl;
    }
}

bool matrix_equals(Matrix a, Matrix b, double tolerance) {
    // Проверка на одинаковые размеры
    if (a.rows != b.rows || a.cols != b.cols) {
        return false;
    }
    
    // Проверка на nullptr
    if (a.data == nullptr || b.data == nullptr) {
        return a.data == b.data; // Обе должны быть nullptr или обе не nullptr
    }
    
    // Поэлементное сравнение с учетом погрешности
    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            double diff = std::abs(a.data[i][j] - b.data[i][j]);
            if (diff > tolerance) {
                return false;
            }
        }
    }
    
    return true;
}