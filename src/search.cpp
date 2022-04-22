#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include "search.hpp"

using namespace std;
using std::cout; using std::endl;
using std::cin; using std::string;

void search(string text,bool p, bool c, string pattern){
    //checando a existencia do arquivo de texto.
    ifstream file(text);
    if(!file.is_open()) {
        cout<< "arquivo não encontrado"<<endl;
        exit(0);
    }
    else{
        //checando a existencia de um arquivo de padrões
        if(p){
            ifstream pat(pattern);
            if(!pat.is_open()){
                cout<<"arquivo de padrões não encontrado"<<endl;
                exit(0);
            }
            pat.close();
        }
        //algoritimo de busca por indexação
    }
    file.close();
}