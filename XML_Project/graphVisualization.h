#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

void visualizeGraph(vector<User*>users)
{
    ofstream visualize;
    visualize.open("graphVisualization.dot");
    visualize << "digraph visualize" << endl << "{" << endl;
    for (int i = 0; i < users.size(); i++)
    {
        for (int j = 0; j < users[i]->followers.size(); j++)
        {
            visualize << users[i] -> id << "->" << users[i]->followers[j] -> id << endl;
        }
    }
    visualize << "}" << endl;
    visualize.close();
    system("dot -Tpng -O graphVisualization.dot");
}