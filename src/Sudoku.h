#pragma once
using std::string;

const int PUZZLE_SIZE = 9;
const int UNASSIGNED = 0;

class Sudoku
{
    private:
        int grid[PUZZLE_SIZE][PUZZLE_SIZE];

        void fill_empty_diagonal_box(int index);
        bool find_unassigned(int &row, int &col);

        bool can_insert_in_row(int row, int num);
        bool can_insert_in_col(int col, int num);
        bool can_insert_in_block(int row, int col, int num);
        bool is_safe(int row, int col, int num);

    public:
        void print_grid();
        void create_seed();
        bool solve_grid();
        string export_str();
        void generate(float drop_ratio);

    Sudoku(float drop_ratio);
    Sudoku(string sudoku_str);
};