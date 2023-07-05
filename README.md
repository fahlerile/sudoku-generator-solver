# sudoku-generator-solver

A sudoku generator and solver in C++. Well, it is more a library than a meaningful program. I have looked at [this](https://github.com/vaithak/Sudoku-Generator) while making this project.

# Build

No dependencies.

```bash
mkdir build
cd build
cmake ..
make
```

The binary will be in `bin/` directory

# Documentation

## `Sudoku`

```cpp
Sudoku(float drop_ratio);
Sudoku(string sudoku_str);
```

You can either provide `drop_ratio`, which will generate random grid for you with `drop_ratio` of zeros in it, or give `sudoku_str`, which will read and load it.

## `Sudoku::print_grid`

```cpp
void print_grid();
```

Prints a current sudoku grid.

## `Sudoku::create_seed`

```cpp
void create_seed();
```

Create a random fully solved sudoku grid.

## `Sudoku::solve_grid`

```cpp
bool solve_grid();
```

Solves a current grid. `true` if success, `false` if impossible configuration.

## `Sudoku::export_txt`

```cpp
bool export_txt(string path);
```

Exports a current grid as a string.

## `Sudoku::generate`

```cpp
void generate(float drop_ratio);
```

Generate a grid with `drop_ratio` zero values. NOTE: need to call `create_seed()` first!