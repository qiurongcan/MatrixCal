#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

#include "MatrixType.h"

Matrix* matrix_create(IndexType row, IndexType col, MatrixProperty MP)
{
    if (row <= 0 || col <= 0) {
        fprintf(stderr, "Error: Matrix dimensions must be positive\n");
        return NULL;
    }
    
    Matrix* mat = (Matrix*)malloc(sizeof(Matrix));
    if (!mat) {
        fprintf(stderr, "Error: Memory allocation failed for matrix structure\n");
        return NULL;
    }
    
    mat->matrix_rows = row;
    mat->matrix_cols = col;
    mat->MP = MP;
    
    // 分配行指针数组
    mat->matrix_data = (double**)malloc(row * sizeof(double*));
    if (!mat->matrix_data) {
        fprintf(stderr, "Error: Memory allocation failed for matrix rows\n");
        free(mat);
        return NULL;
    }
    
    // 分配每一行的内存
    for (int i = 0; i < row; i++) {
        mat->matrix_data[i] = (double*)malloc(col * sizeof(double));
        if (!mat->matrix_data[i]) {
            fprintf(stderr, "Error: Memory allocation failed for matrix row %d\n", i);
            // 释放已分配的内存
            for (int j = 0; j < i; j++) {
                free(mat->matrix_data[j]);
            }
            free(mat->matrix_data);
            free(mat);
            return NULL;
        }
        
        // 初始化为0
        for (int j = 0; j < col; j++) {
            mat->matrix_data[i][j] = 0.0;
        }
    }
    
    return mat;
}

void matrix_setproperty(Matrix* matrix, MatrixProperty MP)
{
    if (!matrix) return;
    matrix->MP = MP;
}

void matrix_destory(Matrix* matrix)
{
    if (!matrix) return;

    if (matrix->matrix_data)
    {
        for (int i = 0; i < matrix->matrix_rows; i++) {
            if (matrix->matrix_data[i]) {
                free(matrix->matrix_data[i]);
            }
        }            
        free(matrix->matrix_data);
    }
    free(matrix);
}

void matrix_set(Matrix* matrix, IndexType row, IndexType col, ValueType value)
{
    if (!matrix || row < 0 || row >= matrix->matrix_rows || col < 0 || col >= matrix->matrix_cols)
    {
        fprintf(stderr,"Error: Invalid matrix indices\n");
        return;
    }
    matrix->matrix_data[row][col] = value;
}

void matrix_setall(Matrix* matrix, ValueType value)
{
    if (!matrix) return;

    for (IndexType row = 0; row < matrix->matrix_rows; row ++)
    {
        for (IndexType col = 0; col < matrix->matrix_cols; col ++)
        {
            matrix->matrix_data[row][col] = value;
        }
    }
}

const ValueType matrix_get(const Matrix* matrix, IndexType row, IndexType col)
{
    if (!matrix || row < 0 || row >= matrix->matrix_rows || col < 0 || col >= matrix->matrix_cols)
    {
        fprintf(stderr,"Error: Invalid matrix indices\n");
        return 0.;
    }
    return matrix->matrix_data[row][col];
}

void matrix_print(const Matrix* matrix)
{
    if (!matrix) {
        printf("Matrix is NULL\n");
        return;
    }
    printf("Matrix %dx%d:\n", matrix->matrix_rows, matrix->matrix_cols);
    if (matrix->MP == General)
    {
        printf("Matrix Property: General\n");
    }else if (matrix->MP == Hermitian) 
    {
        printf("Matrix Property: Hermitian\n");
    }else
    {
        printf("Matrix Property: Triangular\n");
    }
    // 
    for (int i = 0; i < matrix->matrix_rows; i++) {
        for (int j = 0; j < matrix->matrix_cols; j++) {
            printf("%8.3f ", matrix->matrix_data[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

Matrix* matrix_transpose(Matrix* matrix)
{
    if (!matrix) return NULL;

    Matrix* result = matrix_create(matrix->matrix_cols, matrix->matrix_rows, General);
    if (!result) return NULL;

    for (IndexType row = 0; row < matrix->matrix_rows; row ++)
    {
        for (IndexType col = 0; col < matrix->matrix_cols; col ++)
        {
            result->matrix_data[col][row] = matrix->matrix_data[row][col];
        }
    }

    return result;
}

void matrix_add(Matrix* matrix, IndexType row, IndexType col, ValueType value)
{
    if (!matrix || row < 0 || row >= matrix->matrix_rows || col < 0 || col >= matrix->matrix_cols)
    {
        fprintf(stderr,"Error: Invalid matrix indices\n");
        return;
    }
    matrix->matrix_data[row][col] += value;
}

Matrix* matrix_addmatrix(Matrix* matrix_a, Matrix* matrix_b)
{
    if (!matrix_a || !matrix_b 
        || matrix_a->matrix_rows != matrix_b->matrix_rows 
        || matrix_a->matrix_cols != matrix_b->matrix_cols) 
    {
        fprintf(stderr, "Error: Matrix dimensions must match for addition\n");
        return NULL;
    }
    
    Matrix* result = matrix_create(matrix_a->matrix_rows, matrix_b->matrix_cols, General);
    if (!result) return NULL;
    
    for (int i = 0; i < matrix_a->matrix_rows; i++) {
        for (int j = 0; j < matrix_a->matrix_cols; j++) {
            result->matrix_data[i][j] = matrix_a->matrix_data[i][j] + 
                                        matrix_b->matrix_data[i][j];
        }
    }
    
    return result;
}

void matrix_scale(Matrix* matrix, ValueType scalar)
{
    for (int i = 0; i < matrix->matrix_rows; i++) {
        for (int j = 0; j < matrix->matrix_cols; j++) {
            matrix->matrix_data[i][j] *= scalar;
        }
    }
}

Matrix* matrix_multiply(Matrix* matrix_a, Matrix* matrix_b)
{
    if (!matrix_a || !matrix_b || matrix_a->matrix_cols != matrix_b->matrix_rows) {
        fprintf(stderr, "Error: Matrix dimensions incompatible for multiplication\n");
        return NULL;
    }

    Matrix* result = matrix_create(matrix_a->matrix_rows, matrix_b->matrix_cols, General);
    if (!result) return NULL;

    for (IndexType i = 0; i < matrix_a->matrix_rows; i++)
    {
        for (IndexType j = 0; j < matrix_b->matrix_cols; j++)
        {
            double sum = 0.0;
            for (IndexType k = 0; k < matrix_a->matrix_cols; k++)
            {
                sum += matrix_a->matrix_data[i][k] * matrix_b->matrix_data[k][j];
            }
            result->matrix_data[i][j] = sum;
        }
    }

    return result;
}

// 
bool matrix_is_symmetric(const Matrix* matrix, double tolerance) {
    if (!matrix) return 0;
    
    // 快速检查：非方阵肯定不对称
    if (matrix->matrix_rows != matrix->matrix_cols) return false;
    
    // 对角线优化：只检查上三角部分
    for (int i = 0; i < matrix->matrix_rows; i++) {
        // 对每行，从i+1开始检查，避免重复比较
        for (int j = i + 1; j < matrix->matrix_cols; j++) {
            // 使用直接比较，避免函数调用开销
            double diff = matrix->matrix_data[i][j] - matrix->matrix_data[j][i];
            if (diff < 0) diff = -diff;  // 手动取绝对值，比fabs快
            if (diff > tolerance) {
                return false;  // 发现不对称立即返回
            }
        }
    }
    return true;
}

Matrix*    matrix_sub(Matrix* matrix, IndexType i, IndexType j)
{
    Matrix* sub_matrix = matrix_create(matrix->matrix_rows - 1, matrix->matrix_cols - 1, General);
    if (!sub_matrix) return NULL;

    for (IndexType index_i = 0; index_i < matrix->matrix_rows; index_i++)
    {
        for (IndexType index_j = 0; index_j < matrix->matrix_cols; index_j++)
        {
            if (index_i != i && index_j != j)
            {
                IndexType sub_i = (index_i < i) ? index_i : index_i - 1;
                IndexType sub_j = (index_j < j) ? index_j : index_j - 1;

                sub_matrix->matrix_data[sub_i][sub_j] = matrix->matrix_data[index_i][index_j];               
            }
        }
    }
    return sub_matrix;
}

ValueType  matrix_det(Matrix* matrix)
{
    if (matrix->matrix_cols != matrix->matrix_rows)
    {
        fprintf(stderr,"Error: Not Square Matrix");
        return 0;
    }

    int N = matrix->matrix_cols;
    // 使用一维数组存储以提高缓存效率
    double *flat = (double*)malloc(N * N * sizeof(double));
    int *pivot = (int*)malloc(N * sizeof(int));
    
    // 展平矩阵
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            flat[i * N + j] = matrix->matrix_data[i][j];
        }
        pivot[i] = i;
    }
    
    int sign = 1;
    
    for (int k = 0; k < N; k++) {
        // 部分选主元
        int max_row = k;
        double max_val = fabs(flat[k * N + k]);
        
        for (int i = k + 1; i < N; i++) {
            double abs_val = fabs(flat[i * N + k]);
            if (abs_val > max_val) {
                max_val = abs_val;
                max_row = i;
            }
        }
        
        if (max_row != k) {
            // 交换行（使用memcpy提高效率）
            double temp_row[N];
            memcpy(temp_row, &flat[k * N], N * sizeof(double));
            memcpy(&flat[k * N], &flat[max_row * N], N * sizeof(double));
            memcpy(&flat[max_row * N], temp_row, N * sizeof(double));
            
            int temp_idx = pivot[k];
            pivot[k] = pivot[max_row];
            pivot[max_row] = temp_idx;
            sign = -sign;
        }
        
        double pivot_val = flat[k * N + k];
        if (fabs(pivot_val) < 1e-15) {
            free(flat);
            free(pivot);
            return 0.0;
        }
        
        // 向量化友好的更新
        for (int i = k + 1; i < N; i++) {
            double factor = flat[i * N + k] / pivot_val;
            flat[i * N + k] = factor;
            
            for (int j = k + 1; j < N; j++) {
                flat[i * N + j] -= factor * flat[k * N + j];
            }
        }
    }
    
    double det = sign;
    for (int i = 0; i < N; i++) {
        det *= flat[i * N + i];
    }
    
    free(flat);
    free(pivot);
    return det;
}

#endif 