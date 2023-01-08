#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector <User*> suggest(User* user)
{
    vector <User*> suggestedArr;
    User * suggestedFollower;

    if (user == NULL)
    {
        return suggestedArr;
    }
    
    for (int i = 0; i < user -> followers.size(); i++)
    {
        for (int j = 0; j < user -> followers[i] -> followers.size(); j++)
        {
            suggestedFollower = user -> followers[i] -> followers[j];
            //don't suggest me to me!
            if (suggestedFollower->id != user->id )
            {
                suggestedArr.push_back(suggestedFollower);
            }
        }
    }

    return suggestedArr;
}