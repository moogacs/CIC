#include <iostream>
#include <fstream>
#include <cstring>
#include <cstddef> 
#include <vector>
#include <string>
#include <bitset>
#include <iomanip>
#include "lcf.h"

using namespace std;



string lcf::compress(){

u_char indxata[BLOCK][BLOCK] = {0},
    Boxes[BLOCK][BLOCK/2] = {0},
    LookBoxe[BLOCK] = {0},
    stop[BLOCK] = {0},
    last[BLOCK] = {0};

string ret = "";

vector< u_char > header_B;
vector< string > header_C;

int block_size = strlen(oData);
cout << "the freaking size is " << block_size << endl;
for(int i = 0;i < BLOCK;i++){
  stop[i] = 0;
  last[i] = 0;
  LookBoxe[i] = 0;
}

/*COPYING INTO ARRAYS*/
    for(size_t i = 0; i < 256 & i < block_size; i++){
      int chr = static_cast < int > (oData[i]);
      int pos = stop[chr];

      if(pos != 0) indxata[chr][pos] = (i - last[chr]);
      else indxata[chr][pos] = i;
      last[chr] = i;
      stop[chr]++;
    }


/*COMPUTATIONS*/
    for(size_t i = 0; i < BLOCK; i++){
      if(stop[i] == 0) continue;
      bool compressed = false;
      string headerc = "";
      for(size_t j = 0; j < stop[i]; j++){
        if(j+1 < stop[i] && indxata[i][j] <= 16 && indxata[i][j+1] <= 16){
          Boxes[i][LookBoxe[i]++] = indxata[i][j] << 4 | indxata[i][j+1];
          compressed = true;
          headerc += "1";
          j++;
        }else{
          Boxes[i][LookBoxe[i]++] = indxata[i][j];
          headerc += "0";
        }
      }
      if(compressed){
        header_B.push_back(LookBoxe[i]);
        if(headerc.length() % 8 != 0) for(int h = 0;h < (headerc.length() % 8);h++)headerc += "0";
        header_C.push_back(headerc);
      }else{
          header_B.push_back((u_char)((int)LookBoxe[i]+128));
          header_C.push_back("");
      }
    }


for(int i = 0;i < BLOCK;i++){
  if(stop[i] != 0){
    cout << ""<<i <<" ==> "<<(int)stop[i]<<" :: ";
  for(int j = 0;j < LookBoxe[i];j++)cout << (int)Boxes[i][j] <<" " ;
  cout << endl << endl;
  }
}

    for(int i = 0;i < header_B.size();i++)
      cout << i << " :: "<< (int)header_B[i] << endl;cout<< endl << endl;
    for(int i = 0;i < header_C.size();i++)
      cout << i << " :: "<< header_C[i] << endl;
    //cout << "header_C[2] size is "<< header_C[2].length() << endl;cout<< endl<<endl;

int k = 0;
    for(size_t i = 0;i < 256; i++){
      if(stop[i] == 0)continue;//means char is not in file
      cout << "dude we found this ==> " << (int)stop[i] << endl;
      ret += (u_char)(i);
      ret += (u_char)header_B[k];
      if((int)header_B[k] <= 128 && (int)header_B[k] > 0){
        for(size_t j = 0; j < (header_C[k].length())/8; j++)
           ret += (u_char)bitset<8>(header_C[k].substr(j*8,j*8+8)).to_ulong();

        int m = (int)(header_B[k]);
        for(size_t j = 0; j < m; j++)ret += (u_char)Boxes[i][j];
      }else{
        int m = (int)(header_B[k]) - 128;
        
        for(size_t j = 0; j < m; j++)ret += (u_char)Boxes[i][j];
      }
      k++;
    }
    
  return ((char)(ret.length()))+ret;
}


bool lcf::print(){
    cout << oData << endl;
    return strlen(oData);
}

void lcf::set(char* Data){oData = Data;}

