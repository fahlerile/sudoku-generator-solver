// try to solve impossible configuration
// get `export_str` done

#include <iostream>
#include <ctime>
#include <fstream>
#include <sstream>
#include "Sudoku.h"

int main()
{
    // use current timestamp for initializing random number generaton
    std::srand(unsigned(std::time(0)));

    Sudoku sudoku(0.5);
    sudoku.print_grid();
    std::cout << sudoku.export_str();

    // std::ifstream file("../src/sudoku.txt");
    // std::stringstream sudoku_grid;
    // string line;

    // while(file >> line)
    // {
    //     sudoku_grid << line << "\n";
    // }

    // file.close();

    // Sudoku sudoku(sudoku_grid.str());
    // sudoku.print_grid();

    // std::cout << std::endl;

    // sudoku.solve_grid();
    // sudoku.print_grid();
}