#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include<iostream>
#include<unordered_map>
#include<fstream>
using namespace std;

// A struct for character
struct Char{
	// character
	char character;
	// Probability of the character
	double prob;
	//start and end mapped to the number line
	double start, end;
};

class Arithmetic{
	private:
	char *data;
	double *prob;
	int size;
	string *input;
	unordered_map<char, Char> map;
	//the size of the original file
	double origin_size;
	//the size of the compressed file
	double compressed_size;
	unordered_map<char, double> frequency;

	public:
	// The main function that encode the string
	Arithmetic(string infilename, string outfilename, string binfilename){
		preprocess(infilename);
		//calculate the probability of each character
		for(unordered_map<char, double> ::iterator iter = frequency.begin(); iter != frequency.end(); iter++){
			iter->second /= origin_size;
        }
		//calculate the range for each character
		double start = 0;
		for(unordered_map<char, double> ::iterator iter = frequency.begin(); iter != frequency.end(); iter++){
			map[iter->first].character = iter->first;
			map[iter->first].prob = iter->second;
			map[iter->first].start = start;
			map[iter->first].end = start + iter->second;
			start += iter->second;
        }
		//calculate the floating point for input
		double low_v=0.0, high_v=1.0, diff= 1.0;
		ifstream infile(infilename);
    	if (infile.is_open()) {
       		char c;
        	while (infile.get(c)) {
            	high_v= low_v+ diff* map[c].end;
				low_v= low_v+ diff* map[c].start;
				diff= high_v- low_v;
    		} 
		}else {
        	cout << "Unable to open file." << endl;
    	}
		infile.close();
		/* cout<<input<<" "<<low_v<<"-"<<high_v<<endl; */
		//binary search and write the sequence into file
		ofstream outfile(outfilename);
		double low = 0;
		double high = 1;
		double mid = (low + high) / 2;
		while(!(mid<= high_v && mid >= low_v)){
			if(mid > high_v){
				outfile<<"0";
				high = mid;
				mid = (low + high) / 2;
			}
			else if(mid < low_v){
				outfile<<"1";
				low = mid;
				mid = (low + high) / 2;
			}
		}
		outfile.close();
		//transfer the 10 sequence into binary file
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
};

#endif 