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
- matrix_det
- matrix_sub
  
## Makefile

样例Makefile文件：

~~~cmake
# 编译器设置
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O3 -lm
INCLUDES = -I.

# 目标可执行文件名
TARGET = myprogram

# 源文件
SRCS = Main.c

# 对象文件
OBJS = $(SRCS:.c=.o)

# 头文件依赖
HEADERS = Matrix.hpp MatrixType.hpp

# 默认目标
all: $(TARGET)

# 链接生成可执行文件
$(TARGET): $(OBJS)
    $(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# 编译主文件
main.o: main.c $(HEADERS)
    $(CC) $(CFLAGS) $(INCLUDES) -c main.c

# 编译头文件1的源文件
Matrix.o: Matrix.hpp MatrixType.hpp
    $(CC) $(CFLAGS) $(INCLUDES) -c Matrix.hpp

# 编译头文件2的源文件
MatrixType.o: Matrix.hpp MatrixType.hpp
    $(CC) $(CFLAGS) $(INCLUDES) -c MatrixType.hpp
~~~

## TODO

- matrix_inv