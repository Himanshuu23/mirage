# mirage

A modern PTX emulator written in C99 from scratch. Reads a `.ptx` file and executes it on CPU, simulating what an NVIDIA GPU would do. Zero dependencies.

The only PTX emulator that supports PTX ISA 8.5 (CUDA 12.6).

## What It Does

Takes a PTX kernel, runs it on CPU with a simulated GPU thread model, produces correct output.

```
Input (.ptx)
     ↓
Lexer → Tokens
     ↓
Parser → Instruction structs
     ↓
Emulator → Executes per thread, simulating GPU thread/block model
     ↓
Output → Same results as real GPU execution
```

## Building

```bash
make emu
```

No cmake. No dependencies. Just gcc.

## Usage

```bash
./ptx-emu test.ptx
```

## Benchmarks

Ran the same vector addition kernel on the PTX emulator (CPU) and a real NVIDIA RTX 2050 GPU.

**4 elements — emulator wins (GPU launch overhead dominates):**
```
PTX Emulator (CPU) : 0.004 ms
Real GPU           : 0.70 ms
```

**1 million elements — GPU wins:**
```
PTX Emulator (CPU) : 4.47 ms
Real GPU           : 0.17 ms
Speedup            : ~27x
```

To reproduce:

```bash
# CPU
make cpu
./vector_add_cpu

# GPU (requires CUDA 12.6 + NVIDIA GPU)
make gpu
./vector_add_gpu
```

On Windows with MSVC, the Makefile handles the flags automatically via Developer Command Prompt for VS 2022.

## Supported Instructions

| Instruction | Description |
|---|---|
| `add.f32`, `sub.f32`, `mul.f32`, `div.f32` | Float arithmetic |
| `add.u32`, `sub.u32`, `mul.u32` | Integer arithmetic |
| `ld.global.f32`, `st.global.f32` | Global memory load/store |
| `ld.param.u64` | Kernel parameter load |
| `mov.f32`, `mov.u32` | Register move |
| `cvta.to.global.u64` | Address conversion |
| `ret` | Return |

## Architecture

| File | What It Does |
|---|---|
| `src/lexer.c` | Tokenises PTX source into tokens |
| `src/parser.c` | Parses tokens into instruction structs |
| `src/emulator.c` | Executes instructions, simulates GPU thread model |
| `src/main.c` | Entry point, loads PTX file, runs emulator |
| `test.ptx` | Sample PTX kernel (vector addition) |
| `vector_add.cu` | Same kernel in CUDA for GPU comparison |
| `vector_add_1m.cu` | 1M element benchmark for GPU |
| `vector_add_cpu.c` | 1M element benchmark for CPU (no CUDA needed) |

## PTX ISA Version

Targets PTX ISA 8.5 (shipped with CUDA 12.6). Current latest is PTX ISA 9.2 (CUDA 13.2) — contributions to expand instruction coverage welcome.

## License

MIT
