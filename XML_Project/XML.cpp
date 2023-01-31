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


//GUI Function for compression
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