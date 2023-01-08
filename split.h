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