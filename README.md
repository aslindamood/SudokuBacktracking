# SudokuBacktracking
Sudoku puzzle solver using backtracing<br/>
The solver efficiently iterates through the cells by modelling the sudoku puzzle as a grid of constraints.

# Features
The program solves sudoku puzzles of any difficulty.<br/>
Puzzles to solve can be inputted as plain text from files

# How to Use
Creating a Puzzle object initializes an empty sudoku puzzle.<br/>
Calling readFromFile(filename) reads in a puzzle- Formatting examples can be found in tests/..<br/>
Calling solve() initializes the backtrace and displays statistics when a solution is found.

# Credits
Written 11/17 by Allister Lindamood and Peter Trinh
