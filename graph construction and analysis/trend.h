#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

string trend(vector<User*>users)
{
    vector<string>topicsT;
    vector<int>repeatsT;
    string trend;
    string topic;
    bool exists = false;

    for (int i = 0; i < users.size(); i++)
    {
        for (int j = 0; j < users[i]->posts.size(); j++)
        {
            for (int m = 0; m < users[i]->posts[j]->topics.size(); m++)
            {
                topic = users[i]->posts[j]->topics[m];

                for (int k = 0; k < topicsT.size(); k++)
                {
                    if (topicsT[k] == topic)
                    {
                        exists = true;
                        repeatsT[k]++;
                    }
                }

                if (!exists)
                {
                    topicsT.push_back(topic);
                    repeatsT.push_back(1);
                }

                if (topicsT.size() == 0)
                {
                    topicsT.push_back(users[i]->posts[j]->topics[m]);
                    repeatsT.push_back(1);
                }
            }
        }
    }

    int max = repeatsT[0];

    for (int i = 0; i < repeatsT.size(); i++)
    {
        if (repeatsT[i] > max)
        {
            max = repeatsT[i];
        }
    }
    for (int i = 0; i < repeatsT.size(); i++)
    {
        if (repeatsT[i] == max)
        {
            trend = topicsT[i];
            break;
        }
    }
    return trend;
}