#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

//who is the most influencer user (has the most followers)
User * most_influencer(vector <User*> users)
{
    vector <int> influencersIDs;
    vector <int> repeats;
    if (users[0] == NULL)
    {
        return NULL;
    }
    else
    {
        influencersIDs.push_back(users[0] -> id);
        repeats.push_back(0);
    }
    
    int id;
    bool exists = false; 

    for (int i = 0; i < users.size(); i++)
    {
        for (int j = 0; j < users[i]-> followersIDs.size(); j++)
        {
            id = users[i]-> followersIDs[j];

            for (int k = 0; k < influencersIDs.size(); k++)
            {
                if (id == influencersIDs[k])
                {
                    exists = true;
                    repeats[k]++;
                }

                if (!exists)
                {
                    influencersIDs.push_back(id);
                    repeats.push_back(1);
                }
            }
        }
    }

    int max = repeats[0];
    int mostInfluencerID = influencersIDs[0];

    for (int i = 0; i < repeats.size(); i++)
    {
        if (repeats[i] > max)
        {
            max = repeats[i];
            mostInfluencerID = influencersIDs[i];
        }
    }

    for (int i = 0; i < users.size(); i++)
    {
        if (users[i] -> id == mostInfluencerID)
        {
            return users[i];
        }
    }
    return NULL;
}