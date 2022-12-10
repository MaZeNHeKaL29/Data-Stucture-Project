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





#define MAX_LINES 1000

using namespace std;

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

bool isValid(string lines[] , int noOfLines)
{
    stack<char> stack;
    for (int i = 0; i < noOfLines; i++)
    {
        for (int y = 0; y < lines[i].length(); y++)
        {
            if (lines[i][y] == '<')
            {
                if (stack.empty())
                    stack.push('<');
                else
                {
                    cout << "<..........<" << endl;
                    cout << lines[i] << endl;
                    return false;
                }
            }
            else if (lines[i][y] == '/' || lines[i][y] == '>')
            {
                if (stack.empty())
                {
                    cout << "..........<" << endl;
                    cout << lines[i] << endl;
                    return false;
                }
                else if (stack.top() == '>')
                {
                    cout << ">..........>" << endl;
                    cout << lines[i] << endl;
                    return false;
                }
                else
                {
                    stack.pop();
                    break;
                }
            }
        }
    }

 
    return stack.empty();
     
}
int main(void)
{
    string lines[MAX_LINES];
    int noOfLines;

    noOfLines = readXML("books.xml", lines);

   // print read file
    for (int i = 0; i < noOfLines; i++)
        cout << lines[i] << endl;

   
    cout << "validity : " << isValid(lines, noOfLines) << endl;
    
    
        

    return 0;
}