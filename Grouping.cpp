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
//    file.open(inputFile);
    if (file.is_open())
    {
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
            group.clear();
            findGroup(i, j, group);
        }
    }

}


void Grouping::findGroup(int row, int col, vector<GridSquare> group) {

    if(grid[row][col] == 1) {
        group.push_back(GridSquare(row, col));
        grid[row][col] = 3;

        if(grid[row][col + 1] == 1) {
            findGroup(row, col + 1, group);
            if(groups.back().at(0) == group.at(0)){
                group.clear();
            }
            return;
        }
        if(grid[row + 1][col] == 1) {
            findGroup(row + 1, col, group); 
            if(groups.back().at(0) == group.at(0)){
                group.clear();
            }
            return;
        }
        if(grid[row][col - 1] == 1) {
            findGroup(row, col - 1, group);
            if(groups.back().at(0) == group.at(0)){
                group.clear();
            }
            return;
        }
        if(grid[row - 1][col] == 1) {
            findGroup(row - 1, col, group);
            if(groups.back().at(0) == group.at(0)){
                group.clear();
            }
            return;
        }
               
    }
    if(!group.empty()) groups.push_back(group);
}

istream& operator>> (istream& is, Grouping& obj) {
    
    return is;
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