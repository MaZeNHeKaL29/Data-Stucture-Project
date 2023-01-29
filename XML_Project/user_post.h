#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "neededFunctions.h"

using namespace std;

//building class
class Post
{
public:
    vector <string> topics;
    string body;
    int posterID;
};

class User
{
public:
    int id;
    string name;
    int num_of_posts;
    vector<Post*> posts;
    vector <User*> followers;
    vector <int> followersIDs;

    User(int thisID)
    {
        this->id = thisID;
        num_of_posts = 0;
    }
    User()
    {
        num_of_posts = 0;
    }
};
vector <User*> users;