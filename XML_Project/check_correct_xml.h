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

#define MAX_LINES 1000
#define MAX_ERRORS 10

bool isIn(vector<string> arr, string k);

void PrintStack(stack<string> s);

void printVector(vector<string> v);

/*
this function takes name of file (ex: "books.xml") and array of strings for storing lines (each element in array represent line)
*/
int readXML(string name, string arr[]);

/*
this function check vadility of xml file
it reports error in cases
    1- if stack top is empty and '<' is comming         ,  push '<' into stack
    2- if the stack top '<'  and '<' is comming         ,  report error
    3- if the stack top is empty   and '>' is comming   ,  report error
    4- if the stack top '>'  and '>' is comming         ,  report error
    5- if the stack isnot empty after the end of xml    ,  report error
*/
bool isValid(string lines[], int noOfLines, string& error);

void createXML(string arr[], int noOfLines, string filename);

/*
*   this function correctXML one type of error
*   error : missing close tag
*   (there are multiple lines between the line contains open tag and line that should contain close tag)
*/
void correctOneTypeError(string lines[], int noOfLines);

int helper(string str, string& openTagName, int* index);

/*
* this function corrects two types of errors
* error : missing close tag (line contains open tag and attribute but doesont contain close tag)
* error : wrong close tag   (line contains open tag and attribute but contain wrong close tag)
*/
void correctTwoTypeErrors(string lines[], int noOfLines);

/*
*   this function corrects xml file
*/
void correctXML(string lines[], int noOfLines, int calls);