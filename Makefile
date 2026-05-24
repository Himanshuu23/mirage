CC = gcc
NVCC = nvcc
CFLAGS = -Iinclude -O2
TARGET = ptx-emu
SRCS = src/main.c src/lexer.c src/parser.c src/emulator.c

MSVC_BIN = C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.44.35207/bin/Hostx64/x64
SDK_INCLUDE = C:/Program Files (x86)/Windows Kits/10/Include/10.0.26100.0/ucrt
SDK_LIB_UM = C:/Program Files (x86)/Windows Kits/10/Lib/10.0.26100.0/um/x64
SDK_LIB_UCRT = C:/Program Files (x86)/Windows Kits/10/Lib/10.0.26100.0/ucrt/x64

ifeq ($(OS),Windows_NT)
	NVCC_FLAGS = -ccbin "$(MSVC_BIN)" -I "$(SDK_INCLUDE)" -L "$(SDK_LIB_UM)" -L "$(SDK_LIB_UCRT)"
else
	NVCC_FLAGS =
endif

.PHONY: all clean emu gpu 1m cpu

all: emu cpu

emu:
	$(CC) $(SRCS) $(CFLAGS) -o $(TARGET)

cpu:
	$(CC) vector_add_cpu.c -O2 -o vector_add_cpu

gpu:
	$(NVCC) vector_add.cu -o vector_add_gpu $(NVCC_FLAGS)

1m:
	$(NVCC) vector_add_1m.cu -o vector_add_1m $(NVCC_FLAGS)

clean:
ifeq ($(OS),Windows_NT)
	del /f /q *.exe *.lib *.exp 2>nul || true
else
	rm -f $(TARGET) vector_add_gpu vector_add_1m vector_add_cpu
endif
