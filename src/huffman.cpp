#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <queue>
#include <vector>
#include <bits/stdc++.h>
#include <cstddef>
#include <regex>
#include <cstdlib>
#include <unistd.h>
#include <cstdio>

using namespace std;
using std::cout; using std::endl;
using std::cin; using std::string;
using std::map;

struct Node{
    int occ;
    char chr;
    struct Node* left;
    struct Node* right;

    Node(int val,char x){
        occ = val;
        chr = x;
        left = NULL;
        right = NULL;
    }
};

struct compOCC
{
    bool operator()(const Node* a, const Node* b){
        return a->occ > b->occ;
    }
};

map<char,int> frenqTab(string txtname){
    ifstream file(txtname);
    if(!file.is_open()){
        cout<<"arquivo não encontrado"<<endl;
        exit(0);
    }
    else{
        map<char,int> frenqTab;
        string line;
        char aux;
        while(file.get(aux)){
            frenqTab[aux]++;
        }
        file.close();
        return frenqTab;
    }
}
Node* genTree(priority_queue <Node*,vector<Node*>,compOCC>& priFila ){
    while (priFila.size()>1)
    {
    struct Node* x1= priFila.top();
    priFila.pop();
    struct Node* x2 = priFila.top();
    priFila.pop();
    struct Node* x3 = new Node(x1->occ+x2->occ,'.');
    x3->left=x1;
    x3->right=x2;
    priFila.push(x3);
    }
    return priFila.top();
}
void genDict(Node* tree, map<char,string>& dic,string path){
    if(tree->left == NULL and tree->right==NULL) dic[tree->chr]=path;
    else{
        if(tree->left != NULL) genDict(tree->left,dic,path+"0");
        if(tree->right != NULL) genDict(tree->right,dic,path+"1");
    } 
}
string genByte(unsigned char byte){
    string ret="";
    for(int i=7;i>=0;i--){
        unsigned int comp=byte & (1<<i);
        if(comp){
            ret+="1";
        }else{
            ret+="0";
        }
    }
    return ret;
}
void compactar(string textname,map<char,string> dic,Node* tree){
    string filename(textname+".myz");
    ofstream output_fstream;
    output_fstream.open(filename,std::ios_base::binary);
    if (!output_fstream.is_open()) {
        cerr << "Failed to create " << filename << '\n';
        exit(0);
    } else {
        output_fstream<<dic.size()<<endl;
        for(auto &item :dic) output_fstream<<item.first<<":"<<item.second<<endl;
        ifstream file(textname);
        if(!file.is_open()){
        cout<<"arquivo não encontrado"<<endl;
        exit(0);
        }else{
            char aux;
            string linecod="";
            int j = 7;
            unsigned char mascara,byte =0;
            while(file.get(aux)){
                //cout<<line<<endl;
                linecod+=dic[aux];
                while((int)linecod.size()>0){
                    mascara=1;
                    if(linecod[0]=='1'){
                        mascara = mascara << j;
                        byte = byte | mascara;
                    }
                    linecod.erase(0,1);
                    j--;
                    if(j<0){
                        //cout<<genByte(byte)<<endl;
                        output_fstream<<byte;
                        byte = 0;
                        j=7;
                    }
                }
            }
            if(j!=7) output_fstream<<byte;
            file.close();
            output_fstream.close();
            remove(textname.c_str());
        }
    }   
}
Node* reGenTree(map<char,string> dict){
    struct Node* tree = new Node(0,'.');
    struct Node* aux= tree;
    for(auto &item:dict){
        int tam=(int)item.second.size();
        for(int i=0;i<tam;i++){
            if(item.second[i] == '0'){
                if(aux->left == NULL){
                    aux->left=new Node(0,'.');
                }
                aux=aux->left;
            }else if(item.second[i]=='1'){
                if(aux->right == NULL){
                    aux->right = new Node(0,'.');
                }
                aux=aux->right;
            }
        }
        aux->chr=item.first;
        aux=tree;
    }
    return tree;
}
void compare(string text1name,string text2name){
    ifstream file1(text1name);
    ifstream file2(text2name);
    if(!file1.is_open() or !file2.is_open()){
        cout<<"Um dos arquivos não foi encotrado"<<endl;
        exit(0);
    }else{
        string line1,line2;
        int nline=1;
        bool erro= false;
        while(!file1.eof() or !file2.eof()){
            getline(file1,line1);
            getline(file2,line2);
            if(line1 != line2){
                cout<<"erro na linha "<<nline<<":"<<endl;
                cout<<line1<<endl;
                cout<<endl;
                cout<<line2<<endl;
                erro=true;
            }
            nline++;
        }
        cout<<"numero de linhas"<<nline<<endl;
        if(!file1.eof()){
            cout<<"o arquivo "<<text1name<<" gerou texto a mais";
        }else if(!file2.eof()){
            cout<<"o arquivo "<<text2name<<" gerou texto a mais";
        }else if(!erro){
            cout<<"os textos são iguais"<<endl;
        }
    }
}
void descompactar(string textcompname){
    if(regex_match(textcompname,regex(".*.myz"))){
        ifstream file(textcompname,ios::binary);
        if(!file.is_open()){
            cout<<"arquivo "<< textcompname<<" não encontrado"<<endl;
        }
        else{
            string filename=textcompname;
            int tam=(int)filename.size();
            filename.erase(tam-4,4);
            ofstream output_fstream;
            output_fstream.open(filename);
            if(!output_fstream.is_open()){
                cout<<"arquivo nao criado"<<endl;
            }
            else{
                string line;
                getline(file,line);
                tam=stoi(line);
                //cout<<tam<<endl;
                map<char,string> dict;
                for(int i=0;i<tam;i++){
                    getline(file,line);
                    //cout<<line<<endl;
                    if(line != ""){
                        char c = line[0];
                        line.erase(0,2);
                        dict[c]=line;    
                    }else{
                        char c ='\n';
                        getline(file,line);
                        line.erase(0,1);
                        dict[c]=line;
                    }
                }
                //for(auto &item:dict) cout<<item.first<<":"<<item.second<<endl;
                Node* tree = reGenTree(dict);
                Node* aux = tree;
                char c;
                int i;
                //file.get(c);
                //cout<<(bool)file.get(c)<<endl;
                cout<<(c!='\0')<<endl;
                while (file.get(c))
                {    
                    //sleep(5);
                    //cout<<c<<endl;
                    unsigned char byte = c;
                    //cout<<genByte(byte)<<endl;
                    for(i=7;i>=0;i--){
                        unsigned int comp=byte & (1<<i);
                        //cout<<"comp:"<<comp<<endl;
                        if(comp){
                            aux=aux->right;
                            //cout<<"1:";
                        }else{
                            aux=aux->left;
                            //cout<<"0";
                        }
                        //cout<<aux->chr<<endl;
                        if(!aux->left and !aux->right){
                            output_fstream<<aux->chr;
                            aux=tree;
                            
                        }   
                    }
                    //cout<<byte<<endl;
                }
            }    
        }
        file.close();
        remove(textcompname.c_str());
    }else{
        cout<<"O arquivo tem que ser .myz"<<endl;
    }    
}
void huffman(string textname){
    map<char,int> freq = frenqTab(textname);
    // cout<< "[";
    // for(auto &item : freq){
    //     cout << item.first << ":" <<item.second<<" ";
    // }
    //  cout<<"]"<<endl;

     priority_queue <Node*,vector<Node*>,compOCC>priFila;
    for(auto &item:freq)priFila.push(new Node(item.second,item.first));
    struct Node* huffTree = genTree(priFila);
    map<char,string> dict;
    genDict(huffTree,dict,"");
    // cout<<"Tamanho do alfabeto: "<<dict.size()<<endl;
    // cout<< "[";
    // for(auto &item : dict){
    //     cout << item.first << ":" <<item.second<<" "<<"|"<< freq[item.first]<<endl;
    // }
    // cout<<"]"<<endl;
    compactar(textname,dict,huffTree);    
}
