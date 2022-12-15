#ifndef COMPRESSDECOMPRESS_H_INCLUDED
#define COMPRESSDECOMPRESS_H_INCLUDED
#include <iostream>
#include <functional>
#include <queue>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
struct Node
{
	char symbol;
	int freq;
	Node *left, *right;

	Node(char symbol = NULL, int freq = 0) {
		left = right = NULL;
		this->symbol = symbol;
		this->freq = freq;
	}
};

struct compare
{
    bool operator()(Node* left, Node* right);
};
void bitWriter(bool bit, ofstream &out);
void dec2bit(unsigned char symbol, ofstream &out);
void bitReader(unsigned int symbol);
char getBit();
char getByte();
void StoreTree(Node* node,ofstream &out);
void getCode(char symbol, Node *root, string &code);
void Compression(string filename);
Node* treeReader();
char deCode(Node* root,ifstream &inp);
void Decompression(string filename);


#endif // COMPRESSDECOMPRESS_H_INCLUDED
