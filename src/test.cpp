void test_matrix_equals() {
    std::cout << "Testing matrix equality... ";
    
    // Тест 1: Равные матрицы
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);
    
    A.data[0][0] = 1.0; A.data[0][1] = 2.0;
    A.data[1][0] = 3.0; A.data[1][1] = 4.0;
    
    B.data[0][0] = 1.0; B.data[0][1] = 2.0;
    B.data[1][0] = 3.0; B.data[1][1] = 4.0;
    
    assert(matrix_equals(A, B, 0.0001) == true);
    
    // Тест 2: Матрицы с небольшой погрешностью
    Matrix C = create_matrix(2, 2);
    C.data[0][0] = 1.00001; C.data[0][1] = 2.00001;
    C.data[1][0] = 3.00001; C.data[1][1] = 4.00001;
    
    assert(matrix_equals(A, C, 0.001) == true);  // В пределах допуска
    assert(matrix_equals(A, C, 0.000001) == false); // За пределами допуска
    
    // Тест 3: Матрицы разных размеров
    Matrix D = create_matrix(2, 3);
    assert(matrix_equals(A, D, 0.001) == false);
    
    // Тест 4: Пустые матрицы
    Matrix E = create_matrix(0, 0);
    Matrix F = create_matrix(0, 0);
    assert(matrix_equals(E, F, 0.001) == true);
    
    // Тест 5: Одна матрица nullptr
    Matrix G;
    G.data = nullptr;
    G.rows = 0;
    G.cols = 0;
    assert(matrix_equals(E, G, 0.001) == false);
    
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    free_matrix(E);
    free_matrix(F);
    
    std::cout << "PASSED!" << std::endl;
}