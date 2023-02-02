#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <fstream>
#include <functional>
#include <queue>

using namespace std;
using namespace System;

//class for xml node represented like a tree
class xml_node {
private:
    string name;
    string value;
    vector<xml_node*> children;
public:
    xml_node(string s)
    {
        this->name = s;
    }
    void add_children(xml_node* child)
    {
        children.push_back(child);
    }
    void set_value(string value)
    {
        this->value = value;
    }
    string get_name(void)
    {
        return name;
    }
    string get_value(void)
    {
        return value;
    }
    vector<xml_node*> get_children(void)
    {
        return children;
    }
};

//an enum defining whether tag is an opening or closing tag
typedef enum {
    opening_tag, closing_tag
}tag_Type;




//convert system string to standard string
void System2StdString(String^ s, string& os);


//function to print XML(For Debugging only)
void print_XML(xml_node* node, char no_tabs);

//function to convert xml to be represented in a tree
xml_node* xml2tree(string xml_filename);

//function to convert tree xml to json format
void xml_tree2json(xml_node* node, string& json, int no_tabs, bool is_array);

//function to convert xml tree to be represented in xml format
void xml_tree2xml(xml_node* node, string& xml, char no_tabs);

//function to minify xml
void xml_minify(xml_node* node, string& xml);

//function to minify xml
void xml_minify2(xml_node* node, string& xml);