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


void bitWriter(bool bit, ofstream& out);


void dec2bit(unsigned char symbol, ofstream& out);


void bitReader(unsigned int symbol);

char getBit();

char getByte();

void StoreTree(Node* node, ofstream& out);

void getCode(char symbol, Node* root, string& code);

void Compression(string filename);

Node* treeReader();

char deCode(Node* root, ifstream& inp);

void Decompression(string filename, string& xml_de);

void compression(string filename);
