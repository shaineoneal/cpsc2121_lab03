/*
 * Name: Shaine O'Neal 
 * Date Submitted: 9/27/2022
 * Lab Section: 004
 * Assignment Name: Finding Groups Using Recursion
 */

#include "Grouping.h"

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Implement the (parameterized) constructor and findGroup functions below

Grouping::Grouping(string inputFile) {
    ifstream file(inputFile);
    vector<GridSquare> group;
    string line;

    //if file is open
    if (file.is_open()) {
        //iterate through values in file and set them equal to 1 or 0
        for(int i = 0; i < 10; i++){
            getline(file, line);
            for (int j = 0; j < 10; j++)
            {
                if(line.at(j) == '.')
                    grid[i][j] = 0;
                else
                    grid[i][j] = 1;
            }
        }
    }
    else if(!file.is_open()) cout << "ERROR: File not found" << endl;
        
    file.close();
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++){
            if(grid[i][j] == 1) {
                group.clear();
                findGroup(i, j, group);
            }
        }
    }

}

//check if surrounding squares = 1 and create temp vector of squares
vector<GridSquare> Grouping::findSurrounding(int row, int col) {
    vector<GridSquare> surrounding;

    if(grid[row + 1][col] == 1) {
        surrounding.push_back(GridSquare(row + 1, col));
        grid[row + 1][col] = 3;
    }
    if(grid[row][col + 1] == 1) {
        surrounding.push_back(GridSquare(row, col + 1));
        grid[row][col + 1] = 3;
    }
    if(grid[row - 1][col] == 1) {
        surrounding.push_back(GridSquare(row - 1, col));
        grid[row - 1][col] = 3;
    }
    if(grid[row][col - 1] == 1) {
        surrounding.push_back(GridSquare(row, col - 1));
        grid[row][col - 1] = 3;
    }
    return surrounding;
}

void Grouping::findGroup(int row, int col, vector<GridSquare> group) {
    vector<GridSquare> surrounding = findSurrounding(row, col);

    if(grid[row][col] == 1) {
        group.push_back(GridSquare(row, col));
        grid[row][col] = 3;
    }

    //if surrounding vector is empty, add group to groups vector
    if(surrounding.empty()) { groups.push_back(group); }

    else {
        group.insert(group.end(), surrounding.begin(), surrounding.end());
        for(int i = 0; i < surrounding.size(); i++) {
            //group.push_back(surrounding.at(i));
            findGroup(surrounding.at(i).getRow(), surrounding.at(i).getCol(), group);
        }
        surrounding.clear();
    }

}

//Simple main function to test Grouping
//Be sure to comment out main() before submitting
int main()
{
    Grouping input1("input2.txt");
    input1.printGroups();
    
    return 0;
}

//Do not modify anything below

GridSquare::GridSquare() : row(0), col(0) {} //Default constructor, (0,0) square

GridSquare::GridSquare(int r, int c) : row(r), col(c) {} //(r,c) square

//Compare with == operator, used in test cases
bool GridSquare::operator== (const GridSquare r) const
{
    if ((row == r.row) && (col == r.col))
    {
        return true;
    }
    return false;
}

int GridSquare::getRow() //return row value
{
    return row;
}

int GridSquare::getCol() //return column value
{
    return col;
}

//Output using << operator, used in Grouping::printGroups()
//Function definition for <ostream> << <GridSquare>
ostream& operator<< (ostream& os, const GridSquare obj)
{
    os << "(" << obj.row << "," << obj.col << ")";
    return os;
}

Grouping::Grouping() : grid{},groups() {} //Default constructor, no groups

void Grouping::printGroups() //Displays grid's groups of squares
{
    for(int g=0; g<groups.size(); g++)
    {
        cout << "Group " << g+1 << ": ";
        for(int s=0; s<groups[g].size(); s++)
        {
            cout << " " << groups[g][s];
        }
        cout << endl;
    }
}

vector<vector<GridSquare>> Grouping::getGroups() //Needed in unit tests
{
    return groups;
}