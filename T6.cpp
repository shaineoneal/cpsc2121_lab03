#include "Grouping.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
  bool correct = false;
  int groupNum = 0;
  int totalSize = 0;

  int groupCount = 1;
  int sizeTest[] = {26};
  bool groupTestPass[] = {false};


  Grouping input("input2.txt");
  vector<vector<GridSquare>> groups;
  groups = input.getGroups();

  for (int g=0; g<groupCount; g++)
  {
    for (int i=0; i<groups.size(); i++)
    {
      if(sizeTest[g] == groups[i].size())
      {
        groupTestPass[g] = true;
      }
    }
  }

  correct = groupTestPass[0];
  for (int g=1; g<groupCount; g++)
  {
    correct = correct && groupTestPass[g];
  }

  for (int i=0; i<groups.size(); i++)
  {
    totalSize += groups[i].size();
  }

  if (totalSize != 26)
  {
    correct = false;
  }

  //ASSERT_EQ(correct, true);
  if (correct != true)
  {
    cout << "expected/correct value true, actual value when testing " << correct << ".\n";
    return 1;
  }

  return 0;
}