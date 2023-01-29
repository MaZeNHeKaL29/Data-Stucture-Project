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


#define MAX_LINES 1000

using namespace std;
using namespace System;
#if 0

void check_symbols_name(char ch);


//an enum defining wether tag is an opening or closing tag
typedef enum {
    opening_tag, closing_tag
}tag_type;

tag_type tag;




string xml;     //string for xml file
string xml_error; //string added to visually represent error in a line
string filename;  //string for file name of xml file
stack<char> stack_symbols;  //stack for symbols to check consistency
stack<string> stack_tags;   //stack for tag names to check consistency
bool error_line = false;    //boolean to show if there is an error in a line
string tagname = "";
//a vector for tagnames in our XML file
vector<string> tag_names = { "users",
                            "user",
                            "id",
                            "name",
                            "posts",
                            "post",
                            "topic",
                            "topics",
                            "body",
                            "followers",
                            "follower"
                            };

//an enum for tag names to have a certain value
typedef enum {
    users,user,id,name,posts,post,topic,topics,body,followers,follower
}tag_values;


//convert system string to standard string
void System2StdString(String^ s, string& os) {
    using namespace Runtime::InteropServices;
    const char* chars =
        (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
    os = chars;
    Marshal::FreeHGlobal(IntPtr((void*)chars));
}

int tag_index = 0;

void check_tagname(void)
{
    if (!(stack_tags.empty()))
    {
        for (tag_index = 0; tag_index < tag_names.size() && !(stack_tags.empty()); tag_index++)
        {
            if (!stack_tags.top().compare(tag_names.at(tag_index)))
            {
                break;
            }
        }
    
        switch (tag_index)
        {
        case users:
            stack_tags.pop();
            if (!(stack_tags.empty()))
            {
                xml_error += "          <-------- Error";
                stack_tags.pop();
            }
            stack_tags.push(tag_names.at(tag_index));
            break;
        case user:
            
            break;
        case id :
            error_line = true;
            stack_tags.pop();
            break;
        case name :
            error_line = true;
            stack_tags.pop();
            break;
        case posts:
            
            break;
        case post:
            break;
        case topic:
            break;
        case topics:
            break;
        case body:
            break;
        case followers:
            if (tag == opening_tag)
            {
                stack_tags.pop();
                if (!(stack_tags.empty()) && !stack_tags.top().compare("posts"))
                {
                    xml_error += "        <-------- Error";
                    stack_tags.pop();
                }
                stack_tags.push(tag_names.at(tag_index));
            }
            if (tag == closing_tag)
            {
                stack_tags.pop();
                if (!(stack_tags.empty()) && !stack_tags.top().compare("follower"))
                {
                    xml_error += "         <-------- Error";
                    stack_tags.pop();
                }
                stack_tags.push(tag_names.at(tag_index));
            }
            break;
        case follower:
            if (tag == opening_tag)
            {
                stack_tags.pop();
                if (!(stack_tags.empty()) && !stack_tags.top().compare("followers"))
                {
                    xml_error += "        <-------- Error";
                    stack_tags.pop();
                }
                stack_tags.push(tag_names.at(tag_index));
            }
            break;
        default:
            error_line = true;
            stack_tags.pop();
            break;
        }
    }
}

//check every symbol and name in XML file
void check_symbols_name(char ch)
{
   switch (ch)
   {
    //case for '<'
   case '<':
        stack_symbols.push(ch);
        tagname = "";
        break;
    //case for '>'
    case '>':
        //check if there is an error whether stack is empty or top of stack is not equivalent
        if ((stack_symbols.empty()) || !(stack_symbols.top() == '<'))
        {
            error_line = true;
        }
        //push tagname to stack if tag is open
        if (tag == opening_tag)
        {
            stack_tags.push(tagname);
        }
        //pop tagname from stack and check if there is an error in name
        else if (tag == closing_tag)
        {
            //check if tag is empty so there is an error
            if (stack_tags.empty())
            {
                error_line = true;
            }
            //if tagname is equivalent to top of stack so there is no error
            else if (!tagname.compare(stack_tags.top()))
            {
                stack_tags.pop();
            }
            //if tagname is not equivalent to top of stack so there is error
            else
            {
                stack_tags.push(tagname);
                check_tagname();
                if (tagname.compare(stack_tags.top()))
                {
                    error_line = true;
                }
                stack_tags.pop();
            }
        }
        tagname = "";
        if (!(stack_symbols.empty()))
        {
            stack_symbols.pop();
        }
        break;
    //case for '?'
    case '?':
        if (!(stack_symbols.empty()) && stack_symbols.top() == '?')
        {
            stack_symbols.pop();
            tagname = "";
        }
        else
        {
            stack_symbols.push(ch);
        }
        break;
    //case for '"'
    case '"' :
        if (!(stack_symbols.empty()) && stack_symbols.top() == '"')
        {
            stack_symbols.pop();
            tagname = "";
        }
        else
        {
            stack_symbols.push(ch);
        }
        break;
    //case for '/' to see if it is opening tag or not
    case '/' :
        tag = closing_tag;
        break;
    //ignore whitespaces and spaces
    case ' ' :
        break;
    case '/n' :
        break;
    //add character to tagname if it is not any special character
    default:
        tagname.push_back(ch);
        break;
    }
}

void XMLProject::XML_Form::read_file(String^ str_filename)
{   
    //convert system string to standard string
    System2StdString(str_filename, filename);
    //read file and read it line by line
    ifstream MyReadFile(filename);
    while (getline(MyReadFile, xml))
    {
        tagname = "";
        tag = opening_tag;
        error_line = false;
        //check every character in XML file
        for (auto& ch : xml)
        {
           check_symbols_name(char(ch));
        }

        check_tagname();

        if (!stack_symbols.empty())
        {
            while (!stack_symbols.empty())
            {
                stack_symbols.pop();
            }
            if (tag == opening_tag)
            {
                stack_tags.push(tagname);
            }
            else if (tag == closing_tag)
            {
                if (!tagname.compare(stack_tags.top()))
                {
                    stack_tags.pop();
                }
            }
            tagname = "";
            error_line = true;
        }
        xml_error += "\n";
        xml_error += xml;
#if 0
        xml_error += "        ";
        stack<string> stacks = stack_tags;
        while(!stacks.empty())
        {
            xml_error += stacks.top();
            xml_error += "   ";
            stacks.pop();
        }
#endif
        if (error_line)
        {
            xml_error += " <-------- Error";
        }
    }
    cout << xml_error;
    MyReadFile.close();
}

#endif


//class for xml node represented like a tree
class xml_node {
private:
    string name;
    string value;
    vector<xml_node *> children;
public:
    xml_node(string s)
    {
        this -> name = s;
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


//an enum defining wether tag is an opening or closing tag
typedef enum {
    opening_tag, closing_tag
}tag_Type;

tag_Type tag_type;

stack<xml_node*> xml_parent;
stack<char> symbol;

//convert system string to standard string
void System2StdString(String^ s, string& os) {
    using namespace Runtime::InteropServices;
    const char* chars =
        (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
    os = chars;
    Marshal::FreeHGlobal(IntPtr((void*)chars));
}


void print_XML(xml_node* node , char no_tabs)
{
    cout <<"<" << node->get_name() <<">";
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


xml_node * xml2tree(string xml_filename)
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
                if(!(xml_parent.empty()))
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

unsigned char buffer;
int bitCount = 0;
queue<char> output;

struct Node
{
    char symbol;
    int freq;
    Node* left, * right;

    Node(char symbol = NULL, int freq = 0) {
        left = right = NULL;
        this->symbol = symbol;
        this->freq = freq;
    }
};

struct compare
{
    bool operator()(Node* left, Node* right) {
        return (left->freq > right->freq);
    }
};





void bitWriter(bool bit, ofstream& out) {
    if (bitCount > 7) {
        out << buffer;
        bitCount = 0;
    }
    buffer = buffer << 1;
    if (bit) {
        buffer++;
    }
    bitCount++;
}

void dec2bit(unsigned char symbol, ofstream& out)
{
    unsigned char m = 0;
    unsigned char mask = 128;
    for (int i = 0; i < 8; i++) {
        m = symbol & mask;
        if (m > 0)
            bitWriter(1, out);
        else
            bitWriter(0, out);
        mask = mask >> 1;
    }
}

void bitReader(unsigned int symbol) {
    stack<char> temp;
    for (int i = 0; i < 8; ++i) {
        temp.push(symbol % 2 + '0');
        symbol >>= 1;
    }
    for (int i = 0; i < 8; i++) {
        output.push(temp.top());
        temp.pop();
    }
}

char getBit()
{
    if (!output.size())
        return 0;
    char ret = output.front();
    output.pop();
    return ret;
}

char getByte()
{
    unsigned char ret = 0;
    unsigned char temp = 0;
    for (int i = 0; i < 8; i++) {
        temp = getBit();
        ret = ret << 1;
        if (temp != '0') {
            ret++;
        }
    }
    return ret;
}

void StoreTree(Node* node, ofstream& out)
{
    if (node->left == 0 && node->right == 0)
    {
        bitWriter(1, out);
        dec2bit(node->symbol, out);
    }
    else {
        bitWriter(0, out);
        if (node->left != NULL)
            StoreTree(node->left, out);
        if (node->right != NULL)
            StoreTree(node->right, out);
    }
}

void getCode(char symbol, Node* root, string& code)
{
    if (root->symbol == symbol && code.back() != '#')
        code.push_back('#');

    if (root->left != NULL) {
        code.push_back('0');

        getCode(symbol, root->left, code);
        if (code.back() == '#') {
            return;
        }
        else
            code.pop_back();
    }
    if (root->right != NULL) {
        code.push_back('1');
        getCode(symbol, root->right, code);
        if (code.back() == '#')
            return;
        else code.pop_back();
    }
    return;
}

void Compression(string filename)
{
    char in;
    ifstream input(filename, ios::binary | ios::in);
    int freqTable[256] = { 0 };
    freqTable[1]++;


    while (!input.eof()) {
        input.read(&in, 1);
        freqTable[in]++;
    }

    priority_queue<Node*, vector<Node*>, compare> minHeap; //ascending order
    for (int i = 0; i < 256; i++) {
        if (freqTable[i]) {
            minHeap.push(new Node(i, freqTable[i]));
        }
    }

    while (minHeap.size() != 1) {
        Node* left, * right, * alpha;
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        alpha = new Node;
        alpha->freq = left->freq + right->freq;
        alpha->left = left;
        alpha->right = right;
        minHeap.push(alpha);
    }
    filename.erase(filename.end() - 3, filename.end());
    filename += "mcf";
    ofstream out(filename);
    StoreTree(minHeap.top(), out);
    while (bitCount != 8) {
        buffer = buffer << 1;
        bitCount++;
    }
    out << buffer;
    bitCount = 0;
    out << ' ';
    input.clear();
    input.seekg(0, std::ios::beg);
    char inp;
    string code;
    while (input.get(inp))
    {
        getCode(inp, minHeap.top(), code);
        code.pop_back();
        for (int i = 0; i < code.length(); i++) {
            bitWriter(code[i] -= '0', out);
        }
        code.clear();
    }
    getCode(1, minHeap.top(), code); //TO ADD A PSEUDO EOF
    while (bitCount != 8) {
        buffer = buffer << 1;
        bitCount++;
    }
    out << buffer;

}

Node* treeReader() {
    Node* root = new Node;
    char bit;
    if (output.size() != 0)
        bit = getBit();
    else
        return NULL;
    if (bit == '0') {
        root->left = treeReader();
        root->right = treeReader();
    }
    else if (bit == '1') {
        root->symbol = getByte();
        root->left = root->right = NULL;
    }
    return root;
}

char deCode(Node* root, ifstream& inp) {
    if (root->symbol != NULL) {
        return root->symbol;
    }
    char bit;
    while (output.size() == 0 && inp.get(bit)) {
        bitReader(bit);
    }
    bit = getBit();
    if (bit == '0' && root->left != NULL) {
        return deCode(root->left, inp);
    }
    else if (bit == '1' && root->right != NULL) {
        return deCode(root->right, inp);
    }
}

void Decompression(string filename, string &xml_de) {

    ifstream input(filename, ios::binary | ios::in);
    char sym;


    while (input.get(sym) && sym != ' ') {
        bitReader(sym);
    }
    Node* root = treeReader();
    while (!output.empty())
        output.pop();
    filename.erase(filename.end() - 3, filename.end());
    filename += "txtss";
    ofstream out(filename);
    char temp;
    while (input.get(sym)) {
        bitReader(sym);
        temp = deCode(root, input);
        out << temp;
        xml_de.push_back(temp);
    }
    while (output.size() > 0) {
        temp = deCode(root, input);
        if (temp == 0)
            break;
        out << temp;
        xml_de.push_back(temp);
    }
}


void compression(string filename)
{
    Compression(filename);
}

void XMLProject::XML_Form::compress(String^ str_filename)
{
    string filename;
    //convert system string to standard string
    System2StdString(str_filename, filename);
    string xml_mini;
    xml_node* xml_tree = xml2tree(filename);
    filename.erase(remove(filename.begin(), filename.end(), '.'), filename.end());
    ofstream out(filename + "mini.xml");
    xml_minify(xml_tree, xml_mini);
    out << xml_mini;
    out.close();
    compression(filename + "mini.xml");
}

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
#define MAX_LINES 1000
#define MAX_ERRORS 10


bool isIn(vector<string> arr, string k)
{
    for (int i = 0; i < arr.size(); i++)
        if (arr[i] == k) return true;
    return false;
}

void PrintStack(stack<string> s)
{

    if (s.empty())      // If stack is empty then return
        return;

    string x = s.top();
    s.pop();            // Pop the top element of the stack


    PrintStack(s);      // Recursively call the function PrintStack

    // Print the stack element starting
    // from the bottom
    cout << x << " ";

    // Push the same element onto the stack
    // to preserve the order
    s.push(x);
}

void printVector(vector<string> v)
{
    if (v.size() == 0)  return;

    for (int i = 0; i < v.size(); i++)
        cout << v[i] << "\t";
    cout << endl;
}


/*
this function takes name of file (ex: "books.xml") and array of strings for storing lines (each element in array represent line)
*/
int readXML(string name, string arr[])
{
    string filename;             // stores the name of the file to be opened
    ifstream file;               // ifstream file object is used to access the file

    filename = name;

    file.open(filename);     // Use the open member function of the ifstream file object to open the file
    // If the file fails to open for some reason (e.g. the file doesn't exist),
    // the fail member function of the ifstream file object will return true.
    // If it does, we exit the program with an error message and status.
    if (file.fail())
    {
        cout << "File failed to open." << endl;            // Output an error message for the user
        return 0;
    }


    int lines = 0;      // lines will keep track of the number of lines read in from the file
    string temp;

    // The .eof() member function will return true when we reach the end of the
    while (!file.eof())
    {
        // getline() will read the next line from the file and store it into temp.
        getline(file, temp);

        // ignore comments and empty lines
        if (temp.empty())          continue;
        if (temp.find('?') != string::npos)        continue;

        arr[lines++] = temp;    // store line into arr and increment lines

        // If lines reaches MAX_LINES we cannot read any more lines from the file
        // as we have reached the length of the array.  So we output a message to
        // inform the user, and then use 'break' to stop the loop.
        if (lines == MAX_LINES)
        {
            cout << "Max storage reached" << endl;
            break;
        }
    }


    file.close();   // Close the file as we are now done working with it

    return lines;
}



/*
this function check vadility of xml file
it reports error in cases
    1- if stack top is empty and '<' is comming         ,  push '<' into stack
    2- if the stack top '<'  and '<' is comming         ,  report error
    3- if the stack top is empty   and '>' is comming   ,  report error
    4- if the stack top '>'  and '>' is comming         ,  report error
    5- if the stack isnot empty after the end of xml    ,  report error
*/
bool isValid(string lines[], int noOfLines, string &error)
{
    stack<char> s1;         //  define staack for storing '<' , '>'
    vector<string> s3;      //  define vector for storing tag’s name

    bool flagToStore = false;
    string temp;

    error = "No errors in File";

    for (int i = 0; i < noOfLines; i++)
    {
        temp = "";

        for (int y = 0; y < lines[i].length(); y++)
        {
            // if comming is '<'
            if (lines[i][y] == '<')
            {
                // if stack top is empty, push '<' into stack
                if (s1.empty())
                {
                    s1.push('<');
                    flagToStore = true;
                }
                // report error
                else
                {
                    error = "missing '>' at  line " + to_string(i);
                    return false;
                }
            }

            // at storing tag name
            // if comming is '>'
            else if (lines[i][y] == ' ')
            {
                //temp = "";
                flagToStore = false;
            }
            else if (lines[i][y] == '>')
            {
                //if the stack top is empty, report error
                if (s1.empty())
                {
                    error =  "missing '<' at  line " + to_string(i);
                    return false;
                }
                else
                {
                    s1.pop();                // remove '<' from stack top      

                    // if vector of tags’ names is empty
                    if (s3.empty())
                    {
                        s3.push_back(temp);      // insert tag name into vector s3
                    }
                    else
                    {
                        // if the comming tag name is last tag name in vector of tags’ names
                        if (temp == '/' + s3[s3.size() - 1])
                        {
                            //printVector(s3);
                            s3.pop_back();      // remove this tag name
                        }
                        else
                        {
                            // if comming tag name is already in vector of tags’ names , report error
                            if (isIn(s3, temp))
                            {
                                error = "there is open tag which doesnot have end tag crached at line " + to_string(i + 1);
                                return false;
                            }
                            else if (isIn(s3, temp.substr(1)))
                            {
                                error = "missing close tag after line " + to_string(i);
                                return false;
                            }
                            else
                            {
                                if (temp[0] == '/')
                                {
                                    error = "wrong close tag at line " + to_string(i);
                                    return false;
                                }
                                s3.push_back(temp);
                            }
                        }
                    }

                    temp = "";
                    flagToStore = false;
                }
            }
            else if (flagToStore)
            {
                temp += lines[i][y];
            }
        }
        //printVector(s3);
    }


    if (s3.empty())
    {
        return true;
    }

    return s1.empty();
}


void createXML(string arr[], int noOfLines, string filename)
{
    // create file
    filename.erase(remove(filename.begin(), filename.end(), '.'), filename.end());
    ofstream MyFile(filename + "corrected.xml");

    // Write to the file
    for (int i = 0; i < noOfLines; i++)
    {
        MyFile << arr[i] << endl;
    }

    // Close the file
    MyFile.close();
}




/*
*   this function correctXML one type of error
*   error : missing close tag
*   (there are multiple lines between the line contains open tag and line that should contain close tag)
*/
void correctOneTypeError(string lines[], int noOfLines)
{
    stack<char> s1;         //  define staack for storing '<' , '>'
    vector<string> s3;      //  define vector for storing tag’s name

    bool flagToStore = false;
    string temp;

    for (int i = 0; i < noOfLines; i++)
    {
        temp = "";

        for (int y = 0; y < lines[i].length(); y++)
        {
            // if comming is '<'
            if (lines[i][y] == '<')
            {
                // if stack top is empty, push '<' into stack
                if (s1.empty())
                {
                    s1.push('<');
                    flagToStore = true;
                }
                // report error
                //else
                //{
                    //cout << "missing '>' at  line " << i + 1 << endl;
                    //return false;
                //}
            }

            // at storing tag name
            // if comming is '>'
            else if (lines[i][y] == ' ')
            {
                //temp = "";
                flagToStore = false;
            }
            else if (lines[i][y] == '>')
            {
                //if the stack top is empty, report error
                if (s1.empty())
                {
                    //cout << "missing '<' at  line " << i + 1 << endl;
                    //return false;
                }
                else
                {
                    s1.pop();                // remove '<' from stack top      

                    // if vector of tags’ names is empty
                    if (s3.empty())
                    {
                        s3.push_back(temp);      // insert tag name into vector s3
                    }
                    else
                    {
                        // if the comming tag name is last tag name in vector of tags’ names
                        if (temp == '/' + s3[s3.size() - 1])
                        {
                            //printVector(s3);
                            s3.pop_back();      // remove this tag name
                        }
                        else
                        {
                            // if comming tag name is already in vector of tags’ names , report error
                            if (isIn(s3, temp))
                            {
                                //cout << "there is open tag which doesnot have end tag crached at line " << i + 1 << endl;
                                //return false;
                            }
                            else if (isIn(s3, temp.substr(1)))
                            {
                                //cout << "missing close tag after line " << i << endl;
                                lines[i - 1] = ("</" + s3[s3.size() - 1] + '>');
                                //return false;
                            }
                            else
                            {
                                if (temp[0] == '/')
                                {
                                    //cout << "wrong close tag at line " << i + 1 << endl;
                                    //return false;
                                }
                                s3.push_back(temp);
                            }
                        }
                    }

                    temp = "";
                    flagToStore = false;
                }
            }
            else if (flagToStore)
            {
                temp += lines[i][y];
            }
        }
        //printVector(s3);
    }

}



int helper(string str, string& openTagName, int* index)
{
    int count = 0;
    bool isMissingClosingTag = false;
    bool recordFlag1 = false;

    bool m = false;

    string openTag = "";
    string closeTag = "";
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '<')
        {
            count++;
            recordFlag1 = true;
        }
        else if (str[i] == '>')
        {
            count++;
            recordFlag1 = false;
            m = true;
        }
        else if (recordFlag1)
        {
            if (m == false)
                openTag += str[i];
            if (m == true)
                closeTag += str[i];
        }


        if (i < str.size() - 1)
            if (str[i] == '>' && str[i + 1] != ' ')
                isMissingClosingTag = true;

    }

    openTagName = openTag;

    if (count == 2 && isMissingClosingTag)
        return 1;
    else if (count == 4 && (openTagName != closeTag.substr(1)))
    {
        std::size_t pos = str.find('/');
        if (pos != std::string::npos)   // Check if index position is valid 
        {
            //str = str.substr(0, pos); // Remove all characters after the given position 
            *index = pos;
        }
        return 2;
    }
    else
        return 0;
}


/*
* this function corrects two types of errors
* error : missing close tag (line contains open tag and attribute but doesont contain close tag)
* error : wrong close tag   (line contains open tag and attribute but contain wrong close tag)
*/
void correctTwoTypeErrors(string lines[], int noOfLines)
{
    string opentagName;
    int index;

    for (int i = 0; i < noOfLines; i++)
    {
        opentagName = "";
        switch (helper(lines[i], opentagName, &index))
        {
        case 1:
            lines[i] += ("</" + opentagName + '>');
            break;

        case 2:
            lines[i] = lines[i].substr(0, index - 1);
            lines[i] += ("</" + opentagName + '>');
            break;
        }
    }
}


/*
*   this function corrects xml file
*/
void correctXML(string lines[], int noOfLines, int calls)
{
    for (int i = 0; i < calls; i++)
    {
        // correctXML two types of errors 
        // error : missing close tag in same line
        // error : wrong close tag in same line
        //correctTwoTypeErrors(lines, noOfLines);

        // correctXML one type of error
        correctOneTypeError(lines, noOfLines);          // correctXML error per loop
    }
}



void XMLProject::XML_Form::check_xml(String^ str_filename, String^& xml_error)
{
    string lines[MAX_LINES];
    int noOfLines;
    string filename;
    //convert system string to standard string
    System2StdString(str_filename, filename);

    noOfLines = readXML(filename, lines);

   
    string error;

    cout << "----------------------------------------" << endl;
    cout << "validity : " << isValid(lines, noOfLines, error) << endl;
    cout << "----------------------------------------" << endl;

    

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

    xml_error = gcnew String(xml_corrected.data());

}



void XMLProject::XML_Form::graph(String^ str_filename, String^& information)
{
    string filename;
    System2StdString(str_filename, filename);
    //construction
    users = constructGraph(users, filename);
    string xml_information;
    //trivial test
    cout << users[0]->id << endl;
    cout << users[0]->name << endl;
    cout << users[0]->num_of_posts << endl;
    cout << users[0]->posts[0]->body << endl;
    cout << users[0]->posts[0]->topics[1] << endl;
    cout << users[0]->posts[0]->posterID << endl;
    cout << users[0]->posts[0]->topics[0] << endl;
    cout << users[0]->followersIDs[0] << endl;
    cout << users[0]->followersIDs[1] << endl;
    cout << users[0]->followers[0]->id << endl;
    cout << users[0]->followers[1]->id << endl;
    cout << "most influencer user's id is " << most_influencer(users)->id << endl;
    xml_information = "Most Influencer : ";
    xml_information += "\r\nMost Influencer User's ID is ";
    xml_information += to_string(most_influencer(users)->id);
    xml_information += "\r\n\r\nMost Active : ";
    cout << "most active user's id is " << most_active(users)->id << endl;
    xml_information += "\r\nMost Active User's ID is ";
    xml_information += to_string(most_active(users)->id);
    xml_information += "\r\n\r\nMutual Friends : ";
    if (mutual_followers(users[1], users[2]).size() != 0)
    {
        xml_information += "\r\nThe IDs of Mutual Followers between 2 and 3 is just: ";
        xml_information += to_string(mutual_followers(users[1], users[2])[0]->id);
        xml_information += "\r\n";
    }
    else
    {
        xml_information += "\r\n No Mutual Friends between two users";
    }
    xml_information += "\r\nSuggested Followers :";
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
    cout << "the id of the user that wrote about education is: " << searchForPosts("education", "topic", users)[0]->posterID << endl;
    cout << "trend topic is: " << trend(users) << endl;
    xml_information += "\r\n\r\nTrend Topic is ";
    xml_information += trend(users);
    //visualization
    visualizeGraph(users);

    information = gcnew String(xml_information.data());
}

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
            post_std += "ID for User ";
            post_std += to_string(posts[i]->posterID);
            post_std += "\r\n";
            post_std += "\r\n\r\n";
            post_std += posts[i]->body;
            post_std += "\r\n\r\n\r\n";
        }
    }
    post = gcnew String(post_std.data());
}