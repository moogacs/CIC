#include <iostream>
#include <fstream>
#include <bitset> 	
#include "lcf.h"


using namespace std;

template<class T, size_t N> size_t size(T (&)[N]) { return N; }

int main(){




/*READ FILE AND FILE DETAILS*/
	ifstream inFile("list2.txt",ios::in|ios::binary|ios::ate);
	size_t file_size = 0;
	char* oData = 0;
	lcf test;
	int counter_original = 0, counter_compressed = 0;
	inFile.seekg(0, ios::end);
	file_size = inFile.tellg();
	inFile.seekg(0, ios::beg);

	oData = new char[BLOCK];
	if(file_size < BLOCK){
		int rest = file_size;
		inFile.seekg(0, ios::beg);
		inFile.read(oData,rest);
		oData[rest] = '\0';//fix here
		test.set(oData);
		string compressed = test.compress();
		counter_compressed += compressed.length();
		counter_original   += rest;
	}else{
		for(int i = 0;i < file_size/BLOCK;i++){
			inFile.seekg(i*BLOCK, ios::beg);
			inFile.read(oData,BLOCK);
			oData[BLOCK] = '\0';
			test.set(oData);
			string compressed = test.compress();
			//cout << "\nCompression: "<< BLOCK << " ===> "<< compressed.length() <<" [ " << prec(2) << (float)(compressed.length()/BLOCK) << "% ]" << endl;
			counter_compressed += compressed.length();
			counter_original   += BLOCK;
		}
		int rest = file_size % BLOCK;
		if(rest != 0){
			inFile.seekg(rest, ios::end);
			inFile.read(oData,BLOCK);
			oData[rest] = '\0';//fix here
			test.set(oData);
			string compressed = test.compress();
			counter_compressed += compressed.length();
			counter_original   += rest;
		}
	}

	cout << "\nResults : \nOrgiginal size  : "<< counter_original << " bytes\nCompressed size : "<< counter_compressed <<" bytes"<< endl;

	printf("Compression ration : %.2f%c\n",(float)((float)counter_compressed/(float)counter_original)*100,'%');
	//for(int i = 0; i < compressed.length();i++)cout << " " << (int)((u_char)compressed[i]);

	//	cout << endl;
}
