#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "user_post.h"
//#include <bits/stdc++.h>

using namespace std;

vector <User*> mutual_followers(User* first, User* second)
{
    vector <User*> null_vector;
    if (first == NULL || second == NULL)
    {
        return null_vector;
    }
    
    vector <User*> firstFollowers = first -> followers;
    vector <User*> secondFollowers = second -> followers;
    vector <User*> mutual;

    if (firstFollowers.size() == 0 || secondFollowers.size() == 0)
    {
        return null_vector;
    }
    
    for (int i = 0; i < firstFollowers.size(); i++)
    {
        for (int j = 0; j < secondFollowers.size(); j++)
        {
            if (firstFollowers[i] == secondFollowers[j])
            {
                mutual.push_back(firstFollowers[i]);
            }   
        }
    }
    return mutual;
}