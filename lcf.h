#include <string>
#include <iostream>
#include <vector>

#define u_int unsigned int
#define u_char unsigned char
#define BLOCK 256

#ifndef __LCF_H_INCLUDED__
#define __LCF_H_INCLUDED__


using namespace std;

class lcf{
private:
	char* oData;
public:
	lcf(){}
	lcf(char* Data){oData = Data;}
	bool print();
	void set(char*);
	
	vector< char > bits_to_char(string);
	string compress();
	string decompress();
};
	
#endif 
