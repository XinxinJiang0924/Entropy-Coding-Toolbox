#ifndef HUFFMAN_H
#define HUFFMAN_H

#include<iostream>
#include<queue>
#include<fstream>
#include<unordered_map>
using namespace std;

// A Huffman tree node
struct MinHeapNode {
	// character
	char data;
	// Frequency of the character
	unsigned freq;
	// Left and right child
	MinHeapNode *left, *right;
	MinHeapNode(char data, unsigned freq){
		left = right = NULL;
		this->data = data;
		this->freq = freq;
	}
};

// For comparison of two heap nodes (needed in min heap)
struct compare {
	bool operator()(MinHeapNode* l, MinHeapNode* r){
		return (l->freq > r->freq);
	}
};

class Huffman{
	private:
	int size;
	unordered_map<char, int> frequency;
	unordered_map<char, string> huff;
	//the size of the original file
	double origin_size;
	//the size of the compressed file
	double compressed_size;
	

	public:
	// The main function that builds a Huffman Tree and print codes by traversing the built Huffman Tree
	Huffman(string infilename, string outfilename, string binfilename){
		struct MinHeapNode *left, *right, *top;

		// Create a min heap & inserts all characters of data
		priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;
		preprocess(infilename);
		for(unordered_map<char, int> ::iterator iter = frequency.begin(); iter != frequency.end(); iter++){
			minHeap.push(new MinHeapNode(iter->first, iter->second));
        }

		// Iterate while size of heap doesn't become 1
		while (minHeap.size() != 1) {

			// Extract the two minimum freq items from min heap
			left = minHeap.top();
			minHeap.pop();

			right = minHeap.top();
			minHeap.pop();

			top = new MinHeapNode('$', left->freq + right->freq);

			top->left = left;
			top->right = right;

			minHeap.push(top);
		}

		// Print Huffman codes using
		// the Huffman tree built above
		printCodes(minHeap.top(), "");
		compress(infilename, outfilename);
		transfer(outfilename, binfilename);
	}

	//read the file and count the frequency
	void preprocess(string filename){
    	ifstream file(filename);
    	if (file.is_open()) {
       		char c;
        	while (file.get(c)) {
				origin_size++;
            	if (frequency.find(c) != frequency.end()) {
                	frequency[c]++;
            	} else {
                	frequency[c] = 1;
            	}
        	}
    	} else {
        	cout << "Unable to open file." << endl;
    	}
	};

	//write the compressed file and count the compression rate
	void compress(string infilename, string outfilename){
		ofstream outfile(outfilename);
		ifstream infile(infilename);
    	if (infile.is_open()) {
       		char c;
        	while (infile.get(c)) {
            	outfile<<huff[c];
    	} }else {
        	cout << "Unable to open file." << endl;
    	}
	}

	//transfer the 10 sequence into binary file(take each number as a bit)
	void transfer(string infilename, string outfilename){
		ofstream outfile(outfilename, ios::binary);
		ifstream infile(infilename);
    	if (infile.is_open()) {
       		char c;
			char byte;
			int bit_count = 0;
        	while (infile.get(c)) {
				int bit = c - '0';
				byte |= (bit << bit_count);
            	bit_count++;
				//write 8 bits tegether as a character
            	if (bit_count == 8) {
					compressed_size++;
                	outfile.write(&byte, sizeof(byte));
                	byte = 0;
               	 	bit_count = 0;
            	}
        	}
			//if reamain some bits, write them tegether as a character
			if (bit_count > 0) {
				compressed_size++;
            	byte <<= (8 - bit_count);
            	outfile.write(&byte, sizeof(byte));
        }
    	} else {
        	cout << "Unable to open file." << endl;
    	}
		cout<<"bytes the origin file contains is : "<<origin_size<<endl;
		cout<<"bytes the compressed file contains is : "<<compressed_size<<endl;
		cout<<"the compression ratio is : "<<compressed_size/origin_size<<endl;
	}

	// Prints huffman codes from the root of Huffman Tree.
	void printCodes(MinHeapNode* root, string str){
		if (!root)
			return;
		if (root->data != '$')
			/* cout << root->data << ": " << str << "\n"; */
			huff[root->data] = str;
		printCodes(root->left, str + "0");
		printCodes(root->right, str + "1");
	}
};

#endif 