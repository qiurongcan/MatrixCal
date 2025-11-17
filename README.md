# MatrixCal

实现矩阵的基本运算功能，目前已经实现的包括：

- matrix_creat 
- matrix_setproperty
- matrix_destory
- matrix_set
- matrix_setall
- matrix_get
- matrix_print
- matrix_transpose
- matrix_add
- matrix_addmatrix
- matrix_scale
- matrix_multiply
- matrix_is_symmetric

# CMakeLists
样例CMake文件：
~~~cmake
cmake_minimum_required(VERSION 3.20)
project(MyMatrixSolver)

file(GLOB_RECURSE TARGET_SRC  "src/*.cpp")
file(GLOB_RECURSE TARGET_INC  "include/*.hpp")
set(TARGET_SRC ${TARGET_SRC}  ${TARGET_INC})

set(TARGET "matrix_solver")
set(TARGET_SRC src/main.cpp)

add_executable(${TARGET} ${TARGET_SRC})
~~~

# TODO
- matrix_det
- matrix_inv