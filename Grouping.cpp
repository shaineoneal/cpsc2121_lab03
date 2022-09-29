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
#include <algorithm>

using namespace std;

#define GRID_WIDTH 10
#define MIN_GROUP_SIZE 2

//Implement the (parameterized) constructor and findGroup functions below

Grouping::Grouping(string inputFile) {
    ifstream file(inputFile);
    vector<GridSquare> group;
    string line;
//    file.open(inputFile);
    if (file.is_open())
    {
        // loop thru file row by row
        for(int i = 0; i < GRID_WIDTH; i++){
            // grab current line
            getline(file, line);

            // loop thru line char by char
            for (int j = 0; j < GRID_WIDTH; j++)
            {
                if(line.at(j) == '.') // if char is a . , set grid cell to 0
                    grid[i][j] = 0;
                else
                    grid[i][j] = 1; // else set grid cell to 1
            }
        }
    }
    else if(!file.is_open()) {
        cout << "ERROR: File not found" << endl; // file is not open, exit
        exit(EXIT_FAILURE);
    }
    file.close(); // close file



    // loop thru grid row by row
    for (int i = 0; i < GRID_WIDTH; i++) {

        // loop thru grid col by col
        for (int j = 0; j < GRID_WIDTH; j++){
            group.clear(); // clear group vector
            if(grid[i][j] == 1) { // if grid cell is 1, call findGroup
                group = findGroup(i, j, group);
            }
        }
    }

}

vector<GridSquare> Grouping::findGroup(int row, int col, vector<GridSquare> group) {
    bool element_exists_in_groups = false;

    // check if grid cell is X (represented as 1)
    if(grid[row][col] == 1) {

        // iterate thru groups
        for(int i = 0; i < groups.size(); i++) {

            // iterate thru group
            for(int j = 0; j < groups.at(i).size(); j++) {
                // check if current grid cell is in groups
                if(groups.at(i).at(j).getRow() == row && groups.at(i).at(j).getCol() == col) {
                    element_exists_in_groups = true;
                } else {
                    element_exists_in_groups = false;
                }
            }
        }

        // if cell is not in group and if cell is not in groups, add to group
        if(find(group.begin(), group.end(), GridSquare(row, col)) == group.end() && !element_exists_in_groups) {
            group.push_back(GridSquare(row, col));
            // grid[row][col] = -1; // mark grid cell as checked
        }
        

        // if cell to the right is in bounds and is X and is not in group and is not in groups, add to group and call findGroup
        if((col+1) <= GRID_WIDTH && grid[row][col + 1] == 1 && find(group.begin(), group.end(), GridSquare(row, col+1)) == group.end() && !element_exists_in_groups) {
            group.push_back(GridSquare(row, col + 1));
            
            group = findGroup(row, col + 1, group);

            // remove groups of 1 or 0 cells
            if(group.size() < MIN_GROUP_SIZE) {
                group.clear();
            }

            return group;
        }

        // if cell above is in bounds and is X, call findGroup
        if((row+1) <= GRID_WIDTH && grid[row + 1][col] == 1 && find(group.begin(), group.end(), GridSquare(row+1, col)) == group.end() && !element_exists_in_groups) {
            group.push_back(GridSquare(row + 1, col));
            
            group = findGroup(row + 1, col, group); 

            // remove groups of 1 or 0 cells
            if(group.size() < MIN_GROUP_SIZE) {
                group.clear();
            }

            return group;
        }

        // if cell to the left is in bounds and is X, call findGroup
        if((col-1) <= GRID_WIDTH && grid[row][col - 1] == 1 && find(group.begin(), group.end(), GridSquare(row, col-1)) == group.end() && !element_exists_in_groups) {
            group.push_back(GridSquare(row, col - 1));
            
            group = findGroup(row, col - 1, group);

            // remove groups of 1 or 0 cells
            if(group.size() < MIN_GROUP_SIZE) {
                group.clear();
            }

            return group;
        }

        // if cell below is in bounds and is X, call findGroup
        if((row-1) <= GRID_WIDTH && grid[row - 1][col] == 1 && find(group.begin(), group.end(), GridSquare(row-1, col)) == group.end() && !element_exists_in_groups) {
            group.push_back(GridSquare(row - 1, col));
            
            group = findGroup(row - 1, col, group);

            // remove groups of 1 or 0 cells
            if(group.size() < MIN_GROUP_SIZE) {
                group.clear();
            }

            return group;
        }
               
    }
    if(!group.empty() && group.size() >= MIN_GROUP_SIZE && !element_exists_in_groups) groups.push_back(group); // if group is valid, add to groups vector

    // if the code makes it here, a group was not found. return empty vector
    group.clear();
    return group;
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