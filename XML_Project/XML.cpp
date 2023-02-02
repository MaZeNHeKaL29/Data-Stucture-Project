#include "XML_Form.h"
#include "most_influencer.h"
#include "most_active.h"
#include "mutual_followers.h"
#include "suggest.h"
#include "searchForPosts.h"
#include "graphConstruction.h"
#include "neededFunctions.h"
#include "graphVisualization.h"
#include "user_post.h"
#include "trend.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <fstream>
#include <functional>
#include <queue>
#include "XML_Supporting_Functions.h"
#include "check_correct_xml.h"
#include "compress_decompress.h"


using namespace std;
using namespace System;

//GUI Function to convert xml format to json
void XMLProject::XML_Form::xml2json(String^ str_filename, String^& str_json)
{
    string filename;
    //convert system string to standard string
    System2StdString(str_filename, filename);
    //read file and read it line by line
    xml_node* xml_tree = xml2tree(filename);
    string json;
    json.push_back('{');
    json += "\r\n";
    json += "   ";
    xml_tree2json(xml_tree, json, 2, false);
    if (json.back() == ',')
    {
        json.pop_back();
    }
    json += "\r\n";
    json.push_back('}');
    cout << endl << "########################" <<endl<< json;
    str_json = gcnew String(json.data());
    filename.erase(remove(filename.begin(), filename.end(), '.'), filename.end());
    ofstream out(filename + ".json");
    out << json;
    out.close();
}

//GUI function to prettify XML
void XMLProject::XML_Form::xmlprettify(String^ str_filename, String^& str_xml)
{
    string filename;
    //convert system string to standard string
    System2StdString(str_filename, filename);
    //read file and read it line by line
    xml_node* xml_tree = xml2tree(filename);
    string xml;
    xml_tree2xml(xml_tree, xml, 1);
    cout << endl << "########################" << endl << xml;
    str_xml = gcnew String(xml.data());
    filename.erase(remove(filename.begin(), filename.end(), '.'), filename.end());
    ofstream out(filename + "pretty.xml");
    out << xml;
    out.close();
}

//GUI Function to minify XML
void XMLProject::XML_Form::xmlminify(String^ str_filename, String^& str_xml_mini)
{
    string filename;
    //convert system string to standard string
    System2StdString(str_filename, filename);
    string xml_mini;
    xml_node* xml_tree = xml2tree(filename);
    xml_minify(xml_tree, xml_mini);
    cout << endl << "########################" << endl << xml_mini;
    str_xml_mini = gcnew String(xml_mini.data());
    filename.erase(remove(filename.begin(), filename.end(), '.'), filename.end());
    ofstream out(filename + "mini.xml");
    out << xml_mini;
    out.close();
}


//GUI Function for compression
void XMLProject::XML_Form::compress(String^ str_filename)
{
    string filename;
    //convert system string to standard string
    System2StdString(str_filename, filename);
    string xml_mini;
    xml_node* xml_tree = xml2tree(filename);
    filename.erase(remove(filename.begin(), filename.end(), '.'), filename.end());
    ofstream out(filename + "mini2.xml");
    xml_minify2(xml_tree, xml_mini);
    out << xml_mini;
    out.close();
    compression(filename + "mini2.xml");
}


//GUI Function for Decompression
void XMLProject::XML_Form::decompress(String^ str_filename)
{
    string filename;
    string xml_de = "";
    //convert system string to standard string
    System2StdString(str_filename, filename);
    Decompression(filename, xml_de);
    filename.erase(remove(filename.begin(), filename.end(), '.'), filename.end());
    ofstream out(filename + ".xml");
    out<<xml_de;
    out.close();
    xml_node* xml_tree = xml2tree(filename + ".xml");
    xml_de = "";
    out.open(filename + ".xml");
    xml_tree2xml(xml_tree, xml_de, 1);
    out << xml_de;
    out.close();
}





//GUI Function to check XML
void XMLProject::XML_Form::check_xml(String^ str_filename, String^& xml_error)
{
    string lines[MAX_LINES];
    int noOfLines;
    string filename;
    //convert system string to standard string
    System2StdString(str_filename, filename);

    noOfLines = readXML(filename, lines);

   
    string error;

    isValid(lines, noOfLines, error);

    

    error += "\r\n\r\n";

    for (int i = 0; i < noOfLines; i++)
    {
        //printf("line %2d ", i + 1);
        //cout << lines[i] << endl;
        error += "line ";
        error += to_string(i + 1);
        error += "  ";
        error += lines[i];
        error += "\r\n";
    }

    cout << error << endl;

    xml_error = gcnew String(error.data());
}


//GUI Function to correct XML
void XMLProject::XML_Form::correct_xml(String^ str_filename, String^& xml_error)
{
    string lines[MAX_LINES];
    int noOfLines;
    string filename;
    //convert system string to standard string
    System2StdString(str_filename, filename);

    string xml_corrected;

    noOfLines = readXML(filename, lines);
    correctXML(lines, noOfLines, MAX_ERRORS);
    createXML(lines, noOfLines, filename);

    //print read file
    for (int i = 0; i < noOfLines; i++)
    {
        printf("line %2d ", i + 1);
        cout << lines[i] << endl;
        xml_corrected += lines[i];
        xml_corrected += "\r\n";
    }
    ofstream out(filename + "corrected.xml");
    out << xml_corrected;
    out.close();

    xml_error = gcnew String(xml_corrected.data());

}


//GUI Function to represent XML in graph
void XMLProject::XML_Form::graph(String^ str_filename, String^& information)
{
    users.clear();
    string filename;
    System2StdString(str_filename, filename);
    //construction
    users = constructGraph(users, filename);
    string xml_information;
    if (!(most_influencer(users) == NULL))
    {
        xml_information = "Most Influencer : ";
        xml_information += "\r\nMost Influencer User's ID is ";
        xml_information += to_string(most_influencer(users)->id);
    }
    if (!(most_active(users) == NULL))
    {
        xml_information += "\r\n\r\nMost Active : ";
        xml_information += "\r\nMost Active User's ID is ";
        xml_information += to_string(most_active(users)->id);
    }
    if (users.size() >= 2)
    {
        xml_information += "\r\n\r\nMutual Friends : ";
        if (mutual_followers(users[0], users[1]).size() != 0)
        {
            xml_information += "\r\nThe IDs of Mutual Followers between 1 and 2 is : ";
            for (int i = 0; i < (mutual_followers(users[0], users[1]).size()); i++)
            {
                xml_information += to_string(mutual_followers(users[0], users[1])[i]->id);
                xml_information += "\t";
            }
        }
        else
        {
            xml_information += "\r\n No Mutual Friends between User 1 and User 2";
        }
    }
    if (users.size() >= 3)
    {
        if (mutual_followers(users[1], users[2]).size() != 0)
        {
            xml_information += "\r\nThe IDs of Mutual Followers between 2 and 3 is : ";
            for (int i = 0; i < (mutual_followers(users[1], users[2]).size()); i++)
            {
                xml_information += to_string(mutual_followers(users[1], users[2])[i]->id);
                xml_information += "\t";
            }
        }
        else
        {
            xml_information += "\r\n No Mutual Friends between User 2 and User 3";
        }
    }
    xml_information += "\r\n";
    if (users.size() > 0)
    {
        xml_information += "\r\nSuggested Followers :";
    }
    for (int i = 0; i < users.size(); i++)
    {
        if (suggest(users[i]).size() == 0)
        {
            xml_information += "\r\nNo Suggested Followers for ";
            xml_information += to_string(i + 1);
        }
        else
        {
            xml_information += "\r\nThe IDs of Suggested Followers to  ";
            xml_information += to_string(i + 1);
            xml_information += " : ";
            for (int j = 0; j < (suggest(users[i]).size()); j++)
            {
                xml_information += "\t";
                xml_information += to_string(suggest(users[i])[j]->id);
            }
        }
    }
    if (trend(users) != "")
    {
        xml_information += "\r\n\r\nTrend Topic is ";
        xml_information += trend(users);
    }
    //visualization
    visualizeGraph(users);

    information = gcnew String(xml_information.data());
}

//GUI Function for POST Search
void XMLProject::XML_Form::search_graph(String^ str_filename,String^ search, String^ type, String^& post)
{
    string std_search;
    string std_type;
    System2StdString(search,std_search);
    System2StdString(type, std_type);
    string post_std;
    transform(std_type.begin(), std_type.end(), std_type.begin(), ::tolower);
    cout << std_search;
    cout << std_type;
    vector <Post*> posts = searchForPosts(std_search, std_type, users);
    if (posts.size() == 0)
    {
        post_std = "Nothing Found";
    }
    else
    {
        post_std = "";
        for (int i = 0; i < posts.size(); i++)
        {
            post_std += "Post ";
            post_std += to_string(i + 1);
            post_std += "\r\n";
            post_std += "User's ID :  ";
            post_std += to_string(posts[i]->posterID);
            post_std += "\r\n";
            post_std += "\r\n\r\n";
            post_std += posts[i]->body;
            post_std += "\r\n\r\n\r\n";
        }
    }
    post = gcnew String(post_std.data());
}