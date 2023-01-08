#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

vector<User*> constructGraph(vector<User*>users)
{
    ifstream XMLfile("sample.xml");
    string tag = "";
    int user_index = -1;
    string line;
    string newLine;

    while (getline(XMLfile, line))
    {
        newLine = strip(line);

        //user
        if(newLine == "<user>")
        {
            tag = "<user>";
            continue;
        }

        //id
        if (newLine.substr(0,4) == "<id>")
        {
            int currID = getID(newLine);

            if (tag == "<user>")
            {
                bool exists = false;

                for (int i = 0; i < users.size(); i++)
                {
                    if (currID == users[i]->id)
                    {
                        exists = true;
                        user_index = i;
                    }
                }

                if (!exists)
                {
                    users.push_back(new User(currID));
                    user_index = users.size() - 1;
                }
                tag = "";
            }

            if (tag == "<follower>")
            {
                users[user_index] -> followersIDs.push_back(currID);

                bool exists = false;

                for (int i = 0; i < users.size(); i++)
                {
                    if (currID == users[i]->id)
                    {
                        exists = true;
                        users[user_index] ->followers.push_back(users[i]);
                    }
                }

                if (!exists)
                {
                    users.push_back(new User(currID));
                    for (int i = 0; i < users.size(); i++)
                    {
                        if (currID == users[i]->id)
                        {
                            users[user_index] ->followers.push_back(users[i]);
                        }
                    }
                }
                tag = "";
            }
            continue;
        }

        //name
        if (newLine.substr(0,6) == "<name>")
        {
            string name = getName(newLine);
            users[user_index] -> name = name;
            continue;
        }
        
        //body
        if(newLine == "<body>")
        {
            tag = "<body>";
            users[user_index] -> posts.push_back(new Post());
            users[user_index]->num_of_posts ++;
            continue;
        }
        if(tag == "<body>")
        {
            users[user_index] -> posts[users[user_index]->num_of_posts - 1] -> body = newLine;
            users[user_index] -> posts[users[user_index]->num_of_posts - 1] -> posterID = users[user_index] -> id;
            tag = "";
            continue;
        }

        //topic
        if(newLine == "<topic>")
        {
            tag = "<topic>";
            continue;
        }

        if(tag == "<topic>")
        {
            users[user_index] -> posts[users[user_index]->num_of_posts - 1] -> topics.push_back(newLine);
            tag = "";
            continue;
        }

        //follower
        if (newLine == "<follower>")
        {
            tag = "<follower>";
            continue;
        }
    }

    XMLfile.close();
    return users;
}