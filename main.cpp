#include <iostream>
#include <string>
#include "compressDecompress.h"
using namespace std;

int main()
{
   	string input;
    	getline(cin, input, ' ');
	while (input != "exit") {
		if (input == "compress") {
			getline(cin, input);
			Compression(input);
			cout << "Compressed successfully." << endl;
		}

		else if (input == "decompress") {
			getline(cin, input);
			Decompression(input);
			cout << "Decompressed Successfully" << endl;
		}
		getline(cin, input, ' ');
	}
    return 0;
}
