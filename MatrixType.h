#ifndef _MATRIX_TYPE_HPP_
#define _MATRIX_TYPE_HPP_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef enum
{
    General,
    Hermitian,
    Triangular
} MatrixProperty;

typedef enum
{
    LU,
    LDL,
    TRIANGULAR
} MatrixSolver;

typedef int    IndexType;
typedef double ValueType;

typedef struct {
    clock_t start_time;
    clock_t end_time;
} Timer;

void start_timer(Timer *t) {
    t->start_time = clock();
}

void stop_timer(Timer *t) {
    t->end_time = clock();
}

double get_elapsed_time(Timer *t) {
    return ((double)(t->end_time - t->start_time)) / CLOCKS_PER_SEC;
}

typedef struct
{
    ValueType ** matrix_data;
    IndexType    matrix_rows;
    IndexType    matrix_cols;
    MatrixProperty MP;
} Matrix;

// 初始化和销毁
Matrix* matrix_create(IndexType row, IndexType col, MatrixProperty MP);
void    matrix_setproperty(Matrix* matrix, MatrixProperty MP);
void    matrix_destory(Matrix* matrix);

// set,get,add,setall,addmatrix,print基本操作
void    matrix_set(Matrix* matrix, IndexType row, IndexType col, ValueType value);
void    matrix_setall(Matrix* matrix, ValueType value);
const ValueType  matrix_get(const Matrix* matrix, IndexType row, IndexType col);
void    matrix_print(const Matrix* matrix);

// 矩阵运算
Matrix* matrix_transpose(Matrix* matrix);

void    matrix_add(Matrix* matrix, IndexType row, IndexType col, ValueType value);
Matrix* matrix_addmatrix(Matrix* matrix_a, Matrix* matrix_b);

void    matrix_scale(Matrix* matrix, ValueType scalar);
Matrix* matrix_multiply(Matrix* matrix_a, Matrix* matrix_b);

// 计算逆矩阵和矩阵行列式
// Matrix* matrix_inv(const Matrix* matrix);
ValueType  matrix_det(Matrix* matrix);
Matrix*    matrix_sub(Matrix* matrix, IndexType i, IndexType j);

// 矩阵特性
bool matrix_is_symmetric(const Matrix* matrix, double tolerance);

#endif 