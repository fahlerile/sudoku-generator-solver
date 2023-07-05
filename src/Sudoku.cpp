#include <iostream>
#include <algorithm>
#include <sstream>
#include "Sudoku.h"

// initialize and generate a random sudoku
Sudoku::Sudoku(float drop_ratio)
{
    // set all elements in the grid equal to 0
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            this->grid[i][j] = 0;
        }
    }

    this->create_seed();
    this->generate(drop_ratio);
}

// load the sudoku grid from a string
Sudoku::Sudoku(string sudoku_str)
{
    string line;
    std::stringstream sudoku_stream(sudoku_str);
    int row = 0;

    while (std::getline(sudoku_stream, line))
    {
        for (int i = 0; i < PUZZLE_SIZE; i++)
        {
            this->grid[row][i] = line[i] - '0';
        }
        row++;
    }
}

// print the sudoku grid
void Sudoku::print_grid()
{
    // loop through every element in grid
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            if (this->grid[i][j] == 0)
                std::cout << " ";
            else
                std::cout << this->grid[i][j];

            // if the current column number is a multiple of 3 and if it is not the last one
            if ((j + 1) % 3 == 0 && (j + 1) != PUZZLE_SIZE)
                std::cout << " │ ";
            else
                std::cout << " ";
        }

        std::cout << std::endl;

        // if the current row number is a multiple of 3 and if it is not the last one
        if ((i + 1) % 3 == 0 && (i + 1) != PUZZLE_SIZE)
        {
            std::cout << "──────┼───────┼──────" << std::endl;
        }
    }
}

// Fill sudoku's empty diagonal boxes with random numbers
void Sudoku::fill_empty_diagonal_box(int index)
{
    int start = index * 3;
    int random_numerals[9];

    // fill numerals array with numerals from 1 to 9
    for (int i = 0; i < 9; i++)
    {
        random_numerals[i] = i+1;
    }

    std::random_shuffle(std::begin(random_numerals), std::end(random_numerals));

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->grid[start+i][start+j] = random_numerals[i*3+j];
        }
    }
}

// creates a random solved sudoku grid
void Sudoku::create_seed()
{
    this->fill_empty_diagonal_box(0);
    this->fill_empty_diagonal_box(1);
    this->fill_empty_diagonal_box(2);

    this->solve_grid();
}

// checks if it is possible to insert {num} at cell (row, col)
bool Sudoku::is_safe(int row, int col, int num)
{
    return (this->can_insert_in_row(row, num) &&
            this->can_insert_in_col(col, num) &&
            this->can_insert_in_block(row, col, num));
}

bool Sudoku::can_insert_in_row(int row, int num)
{
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        if (this->grid[row][i] == num)
        {
            return false;
        }
    }
    return true;
}

bool Sudoku::can_insert_in_col(int col, int num)
{
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        if (this->grid[i][col] == num)
        {
            return false;
        }
    }
    return true;
}

bool Sudoku::can_insert_in_block(int row, int col, int num)
{
    int row_block_index = row / 3;
    int col_block_index = col / 3;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (this->grid[(row_block_index*3)+i][(col_block_index*3)+j] == num)
            {
                return false;
            }
        }
    }
    return true;
}

// find unassigned value in sudoku grid and write its coords in arguments
bool Sudoku::find_unassigned(int &row, int &col)
{
    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            if (this->grid[i][j] == UNASSIGNED)
            {
                row = i;
                col = j;
                return true;
            }
        }
    }
    return false;
}

// solve a sudoku grid
bool Sudoku::solve_grid()
{
    int row, col;
    int num;

    // if there is no unassigned value, it's solved!
    if (!this->find_unassigned(row, col))
        return true;

    // fill numerals array with numerals from 1 to 9
    int random_numerals[9];
    for (int i = 0; i < 9; i++)
        random_numerals[i] = i+1;

    // shuffle this array
    std::random_shuffle(std::begin(random_numerals), std::end(random_numerals));

    // bruteforce every possible number (which are in random order to increase random)
    for (int i = 0; i < 9; i++)
    {
        num = random_numerals[i];

        // if we can insert {num} here
        if (this->is_safe(row, col, num))
        {
            // insert {num} here
            this->grid[row][col] = num;

            // recursively continue to insert numbers
            if (this->solve_grid())
                return true;

            // if there is an impossible situation, unassign and try
            // another number that we can insert
            this->grid[row][col] = UNASSIGNED;
        }
    }
    return false;
}

// generates a random sudoku grid (NOTE: need to `create_seed` first!)
void Sudoku::generate(float drop_ratio)
{
    const int size_mask_array = PUZZLE_SIZE * PUZZLE_SIZE;
    int mask_array[size_mask_array];

    // determine the number of elements to be dropped
    // and fill that much of an array with zeros, the rest are 1s
    int num_zeros = drop_ratio * size_mask_array;
    int i = 0;

    for (; i < num_zeros; i++)
        mask_array[i] = 0;

    for (; i < size_mask_array; i++)
        mask_array[i] = 1;

    std::random_shuffle(std::begin(mask_array), std::end(mask_array));

    for (i = 0; i < PUZZLE_SIZE; i++)
    {
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            if (mask_array[(i*9)+j] == 0)
                this->grid[i][j] = UNASSIGNED;
        }
    }
}

string Sudoku::export_str()
{
    std::stringstream output;

    for (int i = 0; i < PUZZLE_SIZE; i++)
    {
        for (int j = 0; j < PUZZLE_SIZE; j++)
        {
            output << this->grid[i][j];
        }
        output << "\n";
    }

    return output.str();
}
