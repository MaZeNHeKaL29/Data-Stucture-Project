#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <bits/stdc++.h>
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
            this -> id = thisID;
            num_of_posts = 0;
        }
        User()
        {
            num_of_posts =0;
        }
};
vector <User*> users;

//analysis
#include "most_influencer.h"
#include "most_active.h"
#include "mutual_followers.h"
#include "suggest.h"
#include "searchForPosts.h"
#include "graphConstruction.h"
#include "graphVisualization.h"
#include "trend.h"

int main()
{
    //construction
    users = constructGraph(users);

    //trivial test
    cout << users[0] -> id << endl;
    cout << users[0] -> name << endl;
    cout << users[0] -> num_of_posts << endl;
    cout << users[0] -> posts[0] -> body << endl;
    cout << users[0] -> posts[0] -> topics[1] << endl;
    cout << users[0] -> posts[0] -> posterID << endl;
    cout << users[0] -> posts[0] -> topics[0] << endl;
    cout << users[0] ->followersIDs[0] << endl;
    cout << users[0] ->followersIDs[1] << endl; 
    cout << users[0] -> followers[0] -> id << endl;
    cout << users[0] -> followers[1] -> id << endl;
    cout << "most influencer user's id is " << most_influencer(users) -> id << endl;
    cout << "most active user's id is " << most_active(users) -> id << endl;
    cout << "the ids of mutual followers between 2 and 3 is just: " << mutual_followers(users[1], users[2])[0] -> id << endl;
    cout << "the ids of suggested followers to 3 just: " << suggest(users[2])[0]->id << endl;
    cout << "the id of the user that wrote about education is: " << searchForPosts("education", "topic",users)[0] -> posterID << endl;
    cout << "trend topic is: " << trend(users) << endl;

    //visualization
    visualizeGraph(users);
}