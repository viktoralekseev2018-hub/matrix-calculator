#include <gtest/gtest.h>
#include "matrix.h"

TEST(MatrixIdentityTest, CreateIdentityMatrix) {
    Matrix identity = matrix_identity(3);

    EXPECT_EQ(identity.rows, 3);
    EXPECT_EQ(identity.cols, 3);
    EXPECT_NE(identity.data, nullptr);

    // Проверяем, что матрица действительно единичная
    EXPECT_DOUBLE_EQ(identity.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(identity.data[0][1], 0.0);
    EXPECT_DOUBLE_EQ(identity.data[0][2], 0.0);

    EXPECT_DOUBLE_EQ(identity.data[1][0], 0.0);
    EXPECT_DOUBLE_EQ(identity.data[1][1], 1.0);
    EXPECT_DOUBLE_EQ(identity.data[1][2], 0.0);

    EXPECT_DOUBLE_EQ(identity.data[2][0], 0.0);
    EXPECT_DOUBLE_EQ(identity.data[2][1], 0.0);
    EXPECT_DOUBLE_EQ(identity.data[2][2], 1.0);

    free_matrix(identity);
}

TEST(MatrixIdentityTest, IdentityMatrix1x1) {
    Matrix identity = matrix_identity(1);

    EXPECT_EQ(identity.rows, 1);
    EXPECT_EQ(identity.cols, 1);
    EXPECT_DOUBLE_EQ(identity.data[0][0], 1.0);

    free_matrix(identity);
}

TEST(MatrixIdentityTest, IdentityMatrix2x2) {
    Matrix identity = matrix_identity(2);

    EXPECT_EQ(identity.rows, 2);
    EXPECT_EQ(identity.cols, 2);

    // Проверяем диагональные элементы
    EXPECT_DOUBLE_EQ(identity.data[0][0], 1.0);
    EXPECT_DOUBLE_EQ(identity.data[1][1], 1.0);

    // Проверяем недиагональные элементы
    EXPECT_DOUBLE_EQ(identity.data[0][1], 0.0);
    EXPECT_DOUBLE_EQ(identity.data[1][0], 0.0);

    free_matrix(identity);
}

TEST(MatrixIdentityTest, InvalidSize) {
    EXPECT_THROW(matrix_identity(0), std::invalid_argument);
    EXPECT_THROW(matrix_identity(-1), std::invalid_argument);
    EXPECT_THROW(matrix_identity(-5), std::invalid_argument);
}

TEST(MatrixIdentityTest, IdentityMatrixProperties) {
    Matrix identity = matrix_identity(3);
    Matrix A = create_matrix(3, 3);

    // Заполняем матрицу A произвольными значениями
    A.data[0][0] = 1; A.data[0][1] = 2; A.data[0][2] = 3;
    A.data[1][0] = 4; A.data[1][1] = 5; A.data[1][2] = 6;
    A.data[2][0] = 7; A.data[2][1] = 8; A.data[2][2] = 9;

    // Проверяем свойство I × A = A
    Matrix result1 = matrix_multiply(identity, A);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_DOUBLE_EQ(result1.data[i][j], A.data[i][j]);
        }
    }

    // Проверяем свойство A × I = A
    Matrix result2 = matrix_multiply(A, identity);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            EXPECT_DOUBLE_EQ(result2.data[i][j], A.data[i][j]);
        }
    }

    free_matrix(identity);
    free_matrix(A);
    free_matrix(result1);
    free_matrix(result2);
}

TEST(MatrixIdentityTest, LargeIdentityMatrix) {
    // Тест для матрицы большего размера
    const int size = 5;
    Matrix identity = matrix_identity(size);

    EXPECT_EQ(identity.rows, size);
    EXPECT_EQ(identity.cols, size);

    // Проверяем все элементы
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (i == j) {
                EXPECT_DOUBLE_EQ(identity.data[i][j], 1.0);
            } else {
                EXPECT_DOUBLE_EQ(identity.data[i][j], 0.0);
            }
        }
    }

    free_matrix(identity);
}
