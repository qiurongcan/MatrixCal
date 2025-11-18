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

# 清理生成的文件
clean:
	rm -f $(OBJS) $(TARGET)

# 重新编译
rebuild: clean all

# 安装（如果需要）
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

# 伪目标
.PHONY: all clean rebuild install