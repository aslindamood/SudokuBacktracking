//	Allister Lindamood - aslindamood@alaska.edu
//  Peter Trinh - pptrinh@alaska.edu
//
//	Homework assignment 4
//	11/16/17
//
//	main.cpp
//	A test routine for the sudoku CSP-solving algorithms
//

#include "puzzle.hpp"

int main()
{
    Puzzle puzzle;
    puzzle.readFromFile("tests/17-1.txt");
    puzzle.print();
    puzzle.solve();
    puzzle.print();
    return 0;
}
