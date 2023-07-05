add_library(sudoku_class Sudoku.cpp)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} sudoku_class)
