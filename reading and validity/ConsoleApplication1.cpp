#include <iostream>
using namespace std;

#include <iostream>
#include <fstream>
#include <string>
#include <stack>

class follower
{
	private:
		string id;
	public:
		void setID(string id) { this->id = id; }
		string getID() { return id; }
};

class post
{
	private:
		string topics[10];
		int currentNoOfTopics;
	public:
		post()
		{
			currentNoOfTopics = 0;
		}
		void setTopic(string t)   { topics[currentNoOfTopics++]; }
		string getTopic(int index){ return topics[index]; }
};

class user
{
	private:
		string id;
		string name;
		follower followers[10];
		post posts[10];
};



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




#define MAX_LINES 1000

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
bool isValid(string lines[] , int noOfLines)
{
    stack<char> s1;
    stack<string> s2;
    bool flagToStore = false;
    string temp;

    for (int i = 0; i < noOfLines; i++)
    {
        temp = "";
        for (int y = 0; y < lines[i].length(); y++)
        {
            if (lines[i][y] == '<')          // if comming is '<'
            {
                if (s1.empty())              //if stack top is empty, push '<' into stack
                {
                    s1.push('<');
                    flagToStore = true;
                }
                else                        //if the stack top '<', report error
                {
                    cout << "problem in line " << i << endl;
                    cout << "<..........<" << endl;
                    cout << lines[i] << endl;
                    return false;
                }
            }
            else if (lines[i][y] == '>')   // if comming is '>'
            {
                if (s1.empty())             //if the stack top is empty, report error
                {
                    cout << "problem in line " << i << endl;
                    cout << "letter " << lines[i][y] << endl;
                    cout << "..........<" << endl;
                    cout << lines[i] << endl;
                    return false;
                }
                else
                {
                    s1.pop();
                    s2.push(temp);
                    temp = "";
                    flagToStore = false;
                }
            }
            else if(flagToStore)
            {
                temp += lines[i][y];
            }
        }


        PrintStack(s2); cout << endl;
    }

 
    return s1.empty(); 
}




int main(void)
{
    string lines[MAX_LINES];
    int noOfLines;

    noOfLines = readXML("books.xml", lines);

   // print read file
    for (int i = 0; i < noOfLines; i++)
        cout << lines[i] << endl;

    cout << "----------------------------------------" << endl;
    cout << "validity : " << isValid(lines, noOfLines) << endl;
    
    
   
    return 0;
}