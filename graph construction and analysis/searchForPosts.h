#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector <Post*> searchForPosts(string word, string typo, vector<User*> users)
{
    vector <Post*> posts;
    vector <string> splittedPost;

    for (int i = 0; i < users.size(); i++)
    {
        for (int j = 0; j < users[i] -> posts.size(); j++)
        {
            Post* checkedPost = users[i] -> posts[j];

            //search for topics
            if (typo == "topic")
            {
                for (int k = 0; k < checkedPost -> topics.size(); k++)
                {
                    if (word == checkedPost -> topics[k])
                    {
                        posts.push_back(checkedPost);
                    }
                }
            }
            
            //searching for body
            if (typo == "word")
            {
                splittedPost = splitted(checkedPost -> body);
                for (int m = 0; m < splittedPost.size(); m++)
                {
                    if (word == splittedPost[m])
                    {
                        posts.push_back(checkedPost);
                    }
                }
            }
        }
    }
    
    return posts;
} 