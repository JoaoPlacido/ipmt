#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <getopt.h>
#include "indexer.hpp"
#include "search.hpp"
#include "compressor.hpp"
#define no_argument 0
#define required_argument 1 
#define optional_argument 2

using namespace std;
using std::cout; using std::endl;
using std::cin; using std::string;
using std::vector;

int main(int argc,char *argv[]){
    string mode = argv[1];
    if(mode == "index") indexer(argv[2]) ;
    else if(mode =="search") cout<< "modo de busca"<<endl;
    else if(mode =="zip") cout << "modo de compressão"<<endl;
    else cout<<"modo não reconhecido"<< endl;
}