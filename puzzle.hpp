//	Allister Lindamood - aslindamood@alaska.edu
//  Peter Trinh - pptrinh@alaska.edu
//
//	Homework assignment 4
//	11/15/17
//
//	puzzle.hpp
//	A class for representing and solving sodoku puzzles
//

#ifndef PUZZLE_HPP
#define PUZZLE_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <bitset>

struct Puzzle
{
    Puzzle() //default constructor- sets entire puzzle to zeros
    {
        for(int i=0; i<81; i++)
            field[i]=0;
        for(int i=0; i<81; i++)
            if(!field[i])
                domain.push_back(i);
    }

    bool readFromFile(std::string filename) //does what it says on the tin
    {
        std::ifstream input;
        input.open(filename.c_str());
        if(!input)
            return 0;
        char inputBuf;
        int index=0;
        while(input>>inputBuf && index<81)
            if(inputBuf>47)
            {
                field[index]=inputBuf-48;
                index++;
            }
        input.close();
        domain.clear();
        for(int i=0; i<81; i++)
            if(!field[i])
                domain.push_back(i);
        return 1;
    }

    void print() //does what it says on the tin
    {
        for(int i=0; i<9; i++)
        {
            if(i && !(i%3))
                std::cout << "\n";
            for(int j=0; j<9; j++)
            {
                if(j && !(j%3))
                    std::cout << " ";
                std::cout << field[i*9+j];
            }
            std::cout << "\n";
        }
        std::cout << std::endl; //flush buffers
    }

    inline int gridTranslate(const int gridspace, const int offset) //because the 3x3 sub-grid is really weird to translate from a linear array, this function exists
    {
        int row=((int)(gridspace/3))*3+(int)(offset/3); //lol
        int column=(gridspace%3)*3+offset%3;
        return row*9+column;
    }

    std::bitset<9> generateConstraints(int playingAt) //generates a rule set for a given position
    {
        std::bitset<9> output;
        output.set();
        int row=playingAt/9;
        int column=playingAt%9;
        int grid=(int)(row/3)*3+(int)(column/3);
        for(int i=0; i<9; i++)
        {
            if(field[row*9+i])
                output.set(field[row*9+i]-1, false); //horizontal 1-9
            if(field[i*9+column])
                output.set(field[i*9+column]-1, false); //vertical 1-9
            if(field[gridTranslate(grid, i)])
                output.set(field[gridTranslate(grid, i)]-1, false); //grid square 1-9
        }
        return output;
    }

    void solve() //does what it says on the tin
    {
        int forwards=0;
        int backtracks=0;
        std::stack<std::bitset<9> > rulesets;
        rulesets.push(generateConstraints(domain[0]));
        for(unsigned int i=0; i<domain.size();)
        {
            forwards++;
            if(rulesets.top().none() && i>0) //if no available moves, backtrack
            {
                rulesets.pop();
                i--; //lol
                rulesets.top().set(field[domain[i]]-1, 0); //add the current value of the previous tile to the previous constraints
                field[domain[i]]=0; //reset previous tile
                backtracks++;
                continue;
            }
            for(int j=0; j<9; j++) //try to find a move
                if(rulesets.top()[j])
                {
                    field[domain[i]]=j+1;
                    i++;
                    if(i<domain.size())
                        rulesets.push(generateConstraints(domain[i]));
                    break;
                }
        }
        std::cout << "Puzzle solved. " << "Forward iterations: " << forwards << ", backtrack iterations: " << backtracks << std::endl;
    }

    int field[81];
    std::vector<int> domain;
};

#endif // PUZZLE_HPP
