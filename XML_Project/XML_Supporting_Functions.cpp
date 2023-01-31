
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <fstream>
#include <functional>
#include <queue>
#include "XML_Supporting_Functions.h"

using namespace std;
using namespace System;

//convert system string to standard string
void System2StdString(String^ s, string& os) {
    using namespace Runtime::InteropServices;
    const char* chars =
        (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
    os = chars;
    Marshal::FreeHGlobal(IntPtr((void*)chars));
}


tag_Type tag_type;

stack<xml_node*> xml_parent;
stack<char> symbol;

//function to print XML(For Debugging only)
void print_XML(xml_node* node, char no_tabs)
{
    cout << "<" << node->get_name() << ">";
    if (node->get_value() != "")
    {
        cout << endl;
        for (char i = 0; i < no_tabs; i++)
        {
            cout << "   ";
        }
    }
    char i = 0;
    for (auto& ch : node->get_value())
    {
        if (i > 30 && ch == ' ')
        {
            cout << endl;
            for (char i = 0; i < no_tabs; i++)
            {
                cout << "   ";
            }
            i = 0;
        }
        else
        {
            cout << ch;
            i++;
        }
    }
    for (auto& ch : node->get_children())
    {
        cout << endl;
        for (char i = 0; i < no_tabs; i++)
            cout << "   ";
        no_tabs++;
        print_XML(ch, no_tabs);
        no_tabs--;
    }
    cout << endl;
    for (char i = 0; i < no_tabs - 1; i++)
        cout << "   ";
    if (node->get_name().at(0) != '!' && node->get_name().at(0) != '?')
    {
        cout << "</" << node->get_name() << ">";
    }

}


//function to convert xml to be represented in a tree
xml_node* xml2tree(string xml_filename)
{
    //a root to XML thats will be ignored later
    xml_node* root = new xml_node("XML");
    xml_parent.push(root);
    string xml; // a string to have xml file
    string tagname; //a tagname
    string value = "";   //value  inside each tag
    //read XML
    ifstream MyReadFile(xml_filename);
    //a boolean to indicate whether we are reading a value or not
    bool is_value;
    while (getline(MyReadFile, xml))
    {
        //make tag deafult as opening tag

        tag_type = opening_tag;
        for (auto& ch : xml)
        {
            switch (ch)
            {
            case '<':
                if (!(xml_parent.empty()))
                    xml_parent.top()->set_value(value);
                value = "";
                is_value = false;
                break;
            case '>':
                //if the tag is an opening tag -> save its name and add it as child to top of stacl
                //if the tag is a closing tag -> pop it from the stack as the tag is done reading
                if (tag_type == opening_tag)
                {
                    xml_node* node = new xml_node(tagname);
                    if (!(xml_parent.empty()))
                        xml_parent.top()->add_children(node);
                    xml_parent.push(node);
                }
                else if (tag_type == closing_tag)
                {
                    if (!(xml_parent.empty()))
                        xml_parent.pop();
                    tag_type = opening_tag;
                }
                tagname = "";
                value = "";
                is_value = true;
                break;
                //if there is '/' then this tag is a closing tag
            case '/':
                tag_type = closing_tag;
                break;
            case ' ':
                if (value != "" && is_value && value.back() != ' ')
                {
                    value.push_back(ch);
                }
                else if (tagname != "")
                {
                    tagname.push_back(ch);
                }
                break;
            case '\n':
                if (value != "" && is_value)
                {
                    value.push_back(ch);
                }
                break;
            default:
                if (is_value)
                {
                    value.push_back(ch);
                }
                else
                {
                    tagname.push_back(ch);
                }
                break;
            }
        }
    }
    xml_node* node = root->get_children().at(0);
    return node;
}

//function to convert tree xml to json format
void xml_tree2json(xml_node* node, string& json, int no_tabs, bool is_array)
{
    string name;
    for (auto& ch : node->get_name())
    {
        if (ch == ' ')
        {
            break;
        }
        name.push_back(ch);
    }
    bool array_node = is_array;
    if (name.at(0) != '!' && name.at(0) != '?')
    {
        if (!array_node)
        {
            json.push_back('"');
            json += name;
            json.push_back('"');
            json += ": ";
            if (node->get_value() == "")
            {
                json.push_back('{');
            }
            else
            {
                int i = 0;
                json.push_back('"');
                for (auto& ch : node->get_value())
                {
                    json.push_back(ch);
                    i++;
                }
                json.push_back('"');
                json.push_back(',');
            }
        }
        else
        {
            no_tabs++;
            json += "\r\n";
            if (node->get_value() == "")
            {
                for (int i = 0; i < no_tabs - 1; i++)
                {
                    json += "   ";
                }
                json.push_back('{');
            }
            else
            {
                for (int i = 0; i < no_tabs; i++)
                {
                    json += "   ";
                }
                json.push_back('"');
                int i;
                for (auto& ch : node->get_value())
                {
                    json.push_back(ch);
                    i++;
                }
                json.push_back('"');
                json.push_back(',');
            }
        }
        vector<xml_node*> children = node->get_children();
        is_array = false;
        for (int i = 0; i < children.size(); i++)
        {
            json += "\r\n";
            for (int i = 0; i < no_tabs; i++)
            {
                json += "   ";
            }
            if ((i + 1 < children.size()) && !is_array)
            {
                string name1;
                string name2;
                for (auto& ch : children.at(i)->get_name())
                {
                    if (ch == ' ')
                    {
                        break;
                    }
                    name1.push_back(ch);
                }
                for (auto& ch : children.at(i + 1)->get_name())
                {
                    if (ch == ' ')
                    {
                        break;
                    }
                    name2.push_back(ch);
                }
                if (name1 == name2)
                {
                    is_array = true;
                    json.push_back('"');
                    json += name1;
                    json.push_back('"');
                    json += ": [";
                }
            }
            no_tabs++;
            xml_tree2json(children.at(i), json, no_tabs, is_array);
            no_tabs--;
        }
        if (node->get_value() == "" && name.at(0) != '!' && name.at(0) != '?' && (is_array || children.size() > 0))
        {
            if (json.back() == ',')
            {
                json.pop_back();
            }
        }
        if (node->get_value() == "" && name.at(0) != '!' && name.at(0) != '?')
        {
            if (is_array)
            {
                json += "\r\n";
                for (int j = 0; j < no_tabs; j++)
                {
                    json += "   ";
                }
                json.push_back(']');
            }
            json += "\r\n";
            for (int j = 0; j < no_tabs - 1; j++)
            {
                json += "   ";
            }
            json.push_back('}');
            if (array_node || children.size() > 0)
            {
                json.push_back(',');
            }
        }
    }
    else
    {
        vector<xml_node*> children = node->get_children();
        is_array = false;
        for (int i = 0; i < children.size(); i++)
        {
            xml_tree2json(children.at(i), json, no_tabs, is_array);
        }
    }
}

//function to convert xml tree to be represented in xml format
void xml_tree2xml(xml_node* node, string& xml, char no_tabs)
{
    xml = xml + "<" + node->get_name() + ">";
    if (node->get_value() != "")
    {
        xml += "\r\n";
        for (char i = 0; i < no_tabs; i++)
        {
            xml += "   ";
        }
    }
    char i = 0;
    for (auto& ch : node->get_value())
    {
        xml.push_back(ch);
        i++;
    }
    for (auto& ch : node->get_children())
    {
        xml += "\r\n";
        for (char i = 0; i < no_tabs; i++)
            xml += "   ";
        no_tabs++;
        xml_tree2xml(ch, xml, no_tabs);
        no_tabs--;
    }
    xml += "\r\n";
    for (char i = 0; i < no_tabs - 1; i++)
    {
        xml += "   ";
    }
    if (node->get_name().at(0) != '!' && node->get_name().at(0) != '?')
    {
        xml = xml + "</" + node->get_name() + ">";
    }
}

//function to minify xml
void xml_minify(xml_node* node, string& xml)
{
    string name;
    string value;
    name = node->get_name();
    name.erase(remove(name.begin(), name.end(), '\r'), name.end());
    name.erase(remove(name.begin(), name.end(), '\n'), name.end());
    name.erase(remove(name.begin(), name.end(), '\t'), name.end());
    for (int i = 0; i < 32; i++)
    {
        name.erase(remove(name.begin(), name.end(), i), name.end());
    }
    xml = xml + "<" + name + ">";
    value = node->get_value();
    value.erase(remove(value.begin(), value.end(), ' '), value.end());
    value.erase(remove(value.begin(), value.end(), '\r'), value.end());
    value.erase(remove(value.begin(), value.end(), '\n'), value.end());
    value.erase(remove(value.begin(), value.end(), '\t'), value.end());
    for (int i = 0; i < 32; i++)
    {
        value.erase(remove(value.begin(), value.end(), i), value.end());
    }
    xml = xml + value;
    for (auto& ch : node->get_children())
    {
        xml_minify(ch, xml);
    }
    if (node->get_name().at(0) != '!' && node->get_name().at(0) != '?')
    {
        xml = xml + "</" + node->get_name() + ">";
    }
}