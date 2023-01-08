#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

User * most_active(vector <User*> users)
{
    vector <int> activesIDs;
    vector <int> repeats;

    if (users[0] == NULL)
    {
        return NULL;
    }

    int id;
    int repeat;

    for (int i = 0; i < users.size(); i++)
    {
        id = users[i] -> id;
        repeat = users[i] -> followersIDs.size();
        activesIDs.push_back(id);
        repeats.push_back(repeat);
    }

    int max = repeats[0];
    int mostActiveID = activesIDs[0];

    for (int i = 0; i < repeats.size(); i++)
    {
        if (repeats[i] > max)
        {
            max = repeats[i];
            mostActiveID = activesIDs[i];
        }
    }

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i] -> id == mostActiveID)
        {
            return users[i];
        }
    }

    return NULL;
}