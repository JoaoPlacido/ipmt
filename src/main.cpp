#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <getopt.h>
#include "indexer.hpp"
#include "search.hpp"
#include "compressor.hpp"
#include "huffman.hpp"

#define no_argument 0
#define required_argument 1 
#define optional_argument 2

using namespace std;
using std::cout; using std::endl;
using std::cin; using std::string;
using std::vector;
void indexMode(int argc, char* argv[]){
    if(argc > 2) indexer(argv[2]);
    else cout<<"Falta argumentos"<<endl;
}
int main(int argc,char *argv[]){
    cout<<argc<<endl;
    if(argc>1){
        string mode = argv[1];
        if(mode == "index") indexMode(argc,argv) ;
        else if(mode =="search") cout<< "modo de busca"<<endl;
        else if(mode =="zip") huffman(argv[2]);
        else if(mode =="unzip") descompactar(argv[2]);
        else if(mode =="compare") compare(argv[2],argv[3]);
        else cout<<"modo não reconhecido"<< endl;
    }
    
}