#include "../include/Matrix.hpp"


int main() {
    Matrix* test_a = matrix_create(4,3);
    Matrix* test_b = matrix_create(4,3);

    matrix_setall(test_a,10);
    matrix_setall(test_b,7);
    matrix_add(test_a,1,1,3);
    Matrix* test_a_t = matrix_transpose(test_a);

    Matrix* test_c = matrix_multiply(test_a_t,test_b);

    matrix_print(test_a);
    matrix_print(test_a_t);
    matrix_print(test_b);
    matrix_print(test_c);

    return 0;
}