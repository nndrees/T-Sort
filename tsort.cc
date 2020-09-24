#include <cassert>
#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <algorithm>
#include <time.h>
using namespace std;

vector<int> dfs (int node, vector<vector<bool> > &matrix, vector<bool> &visit)
{
  visit[node] = true;
   vector<int> where;
  for (int i = 0; i < matrix[node].size(); i++)
  {
    vector <bool> temp = matrix.at(node);
    if (matrix[node][i] && !visit[i])
    {
      vector<int> answer = (dfs (i, matrix, visit));
      where.insert(where.end(), answer.begin(), answer.end());
    }
  }
  where.push_back(node + 1);
  return where;
}

int
main (int argc, char *argv[])
{
  int x;
  int y;
  int z;
  vector<vector<bool> > matrix;
  ifstream inFile;
  ifstream inFile2;
  inFile.open (argv[1]);
  inFile2.open (argv[1]);
  assert (NULL != inFile);
  vector <int> elem;

  //reads in Verticies
  while (inFile2 >> z)
  {
    elem.push_back(z);
  }

  //Buble sorts Verticies
  int temp;
  for(int i =0 ; i <= elem.size(); i++)
   {
     for(int j = 0; j < 4; j++)
     {
      if(elem.at(j) > elem.at(j+1))
       {
        temp = elem.at(j);
        elem.at(j)=elem.at(j+1);
        elem.at(j+1)=temp;
       }
     }
   }

   //finds the numner of Verticies
   int nodeNum = elem.back();

  //sets everything to false
  for (int r = 0; r<nodeNum; r++)
  {
    vector<bool> row;
    for (int c = 0; c<nodeNum; c++)
    {
      row.push_back(false);
    }
    matrix.push_back(row);
  }

//gets imput from file
  while (inFile >> x >> y)
  {
    vector<bool> row;
    row = matrix.at(x-1);
    bool thisA = true;
    row.at(y-1) = true;
    matrix.at(x-1) = row;
  }

  /*prints out the matrix of the given file
  int sizeM = matrix.size();
  for (int r = 0; r < sizeM; r++)
  {
        vector<bool> temp = matrix.at(r);
    for (int c = 0; c < temp.size(); c++)
    {
      cout << temp.at(c) << " ";
    }
    cout << endl;
  }

prints out the original information from the file
  for (int r = 0; r < matrix.size(); r++)
  {
    vector<bool> temp = matrix.at(r);
    for (int c = 0; c < temp.size(); c++)
    {
      if (temp.at(c))
      {
	cout << r + 1 << " " << c + 1 << endl;
}
    }
  }
*/

//Starts the timer for the lenght of the program
clock_t tStart = clock();

//Start of the topological sorting
vector <bool> visit(nodeNum, false);
vector<int> answer;
for(int i = 0; i < visit.size(); i++)
{
  if (!visit[i])
  {
    vector <int> where = dfs(i, matrix, visit);
    answer.insert(answer.end(), where.begin(), where.end());
  }
}
reverse(answer.begin(), answer.end());

//prints our relevant information
cout << endl;
cout<<"The number of Verticies: " << nodeNum << endl;
  for ( int i = 0; answer.size() > i; i++)
  {
    cout << answer.at(i) << ", ";
  }
  cout <<endl;
  cout << "Time taken to sort the Verticies:  " << (clock() - tStart) << endl;
  cout << endl;

  inFile.close ();
  inFile2.close();
  return 0;
}
