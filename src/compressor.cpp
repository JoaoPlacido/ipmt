#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "compressor.hpp"

using namespace std;
using std::cout; using std::endl;
using std::cin; using std::string;

void compressor(string text){
    //checando  a existencia do arquivo de texto
    ifstream file(text);
    if(!file.is_open()) {
        cout<< "arquivo não encontrado"<<endl;
        exit(0);
    }
    else{
        //algoritmo de compreensão
    }
}