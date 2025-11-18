#include "Matrix.h"


int main() {
    Timer timer;
    start_timer(&timer);
    // 
    Matrix* test_a = matrix_create(50,50, General);
    matrix_setall(test_a,1);
    ValueType det = matrix_det(test_a);
    // 
    stop_timer(&timer);
    printf("Matrix Det : %f\n", det);
    printf("Solver Time : %f (ms)\n",get_elapsed_time(&timer) * 1e3);
    
    return 0;
}