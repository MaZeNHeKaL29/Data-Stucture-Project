#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

vector <string> splitted(string str)
{
    string s;
    stringstream ss(str);
    vector<string> v;
    while (getline(ss, s, ' '))
    {
		v.push_back(s);
	}
    return v;
}

int getID(string newLine)
{
    int i = 4;
    while (newLine[i] != '<')
    {
        i++;
    }
    int id = stoi(newLine.substr(4, i - 4));
    return id;
}

string getName(string newLine)
{
    int i = 6;
    while (newLine[i] != '<')
    {
        i++;
    }
    string name = newLine.substr(6, i - 6);
    return name;
}

string strip(string line)
{
   int i = 0;
   while(line[i] == ' ')
   {
      i++;
   }
   string f = line.substr(i);
   return f;
}
