#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

void splitByChar(string s, char c, vector<string> &vec)
{
   int i = 0;
   int j;
   j = s.find(c, i);
   int l = s.length();
   while (j != -1)
   {
      vec.push_back(s.substr(i, j - i));
      i = ++j;
      j = s.find(c, i);
   }
   if (i != l)
   {
      vec.push_back(s.substr(i));
   }
   return;
} 
string trimmedLeft(string &s){
    int ind = 0;
    while(ind < s.length()){
        if(s[ind] == ' ') ind++;
        else{
            break;
        }
    }
    return s.substr(ind);
}

int countBlanks(string s){
    int c = 0;
    int ind = 0;
    while(ind < s.length()){
        if(s[ind] == ' '){
            c++;
            ind++;
        }
        else{
            break;
        }
    }
    return c;
}
struct variableWithData{
    string name;
    int indentation;
    int defLine;
    bool isDefined;
}; 

string line;
vector<string> lines;
vector<int> blanks;
int lineIndex = 0;

vector<struct variableWithData> vars;

int getIndexInVars(string name){
    int ind = -1;
    for(int i=0; i<vars.size(); i++){
        if(vars.at(i).name == name){
            ind = i;
        }
    }
    return ind;
}
void izbrisi(int indentation){
    for(int i=0; i<vars.size(); i++){
        if(vars.at(i).indentation > indentation){
            //cout << "brisem: " << vars.at(i).name;
            vars.erase(vars.begin() + i);
        }
    }
}
void pridruzivanje(){
    int indentationOnStart = blanks.at(lineIndex);
    lineIndex++;
    vector <string> splitani;
    splitByChar(lines.at(lineIndex), ' ', splitani);
    struct variableWithData varijabla = {splitani.at(2), indentationOnStart, stoi(splitani.at(1)), true};
    lineIndex++;
    while(blanks.at(lineIndex) > indentationOnStart){
        vector <string> splitani;
        //cout << "splitam:" << lines.at(lineIndex) << endl;
        splitByChar(lines.at(lineIndex), ' ', splitani);
        if(splitani.at(0) == "IDN"){
            int i = getIndexInVars(splitani.at(2));
            //cout << i;
            if(i > -1 && vars.at(i).isDefined){
                cout << splitani.at(1) << " " << vars.at(i).defLine << " " << vars.at(i).name << endl;
            }
            else{
                cout << "err " << splitani.at(1) << " " << splitani.at(2) << endl;
                exit(1);
            }
        }
        lineIndex++;
    }
    int i = getIndexInVars(varijabla.name);
    if(i == -1)
        vars.push_back(varijabla);

    //cout << "pusao sam varijablu: " << vars.at(vars.size()-1).name << vars.at(vars.size()-1).defLine << vars.at(vars.size()-1).indentation << vars.at(vars.size()-1).isDefined;
    return;
}

void petlja(){
    int indentationOnStart = blanks.at(lineIndex);
    lineIndex++;
    lineIndex++;
    vector <string> splitani;
    splitByChar(lines.at(lineIndex), ' ', splitani);
    string nazivI = splitani.at(2);
    struct variableWithData varijabla = {splitani.at(2), blanks.at(lineIndex), stoi(splitani.at(1)), false};
    vars.push_back(varijabla);
    lineIndex+=5;
    splitani.clear();
    splitByChar(lines.at(lineIndex), ' ', splitani);
    if(splitani.at(0) == "OP_PLUS" || splitani.at(0) == "OP_MINUS"){
        //cout << "je";
        lineIndex++;
        lineIndex++;
    }
    splitani.clear();
    splitByChar(lines.at(lineIndex), ' ', splitani);
    if(splitani.at(0) == "IDN"){
        int i = getIndexInVars(splitani.at(2));
        //cout << i;
        if(i > -1 && vars.at(i).isDefined){
            cout << splitani.at(1) << " " << vars.at(i).defLine << " " << vars.at(i).name << endl;
        }
        else{
            cout << "err " << splitani.at(1) << " " << splitani.at(2) << endl;
            exit(1);
        }
    }
    lineIndex+=9;
    splitani.clear();
    splitByChar(lines.at(lineIndex), ' ', splitani);
    if(splitani.at(0) == "OP_PLUS" || splitani.at(0) == "OP_MINUS"){
        //cout << "je";
        lineIndex++;
        lineIndex++;
    }
    splitani.clear();
    splitByChar(lines.at(lineIndex), ' ', splitani);
    if(splitani.at(0) == "IDN"){
        int i = getIndexInVars(splitani.at(2));
        //cout << i;
        if(i > -1 && vars.at(i).isDefined){
            cout << splitani.at(1) << " " << vars.at(i).defLine << " " << vars.at(i).name << endl;
        }
        else{
            cout << "err " << splitani.at(1) << " " << splitani.at(2) << endl;
            exit(1);
        }

    }
    int i = getIndexInVars(nazivI);
    vars.at(i).isDefined = true;
   
    lineIndex++;
    while(blanks.at(lineIndex) > indentationOnStart){
        vector <string> splitani;
        //cout << "splitam:" << lines.at(lineIndex) << endl;
        splitByChar(lines.at(lineIndex), ' ', splitani);
        if(splitani.at(0) == "<naredba_pridruzivanja>"){
            pridruzivanje();
        }
        lineIndex++;
    }
    izbrisi(indentationOnStart);
    
    return;
}



int main(void)
{
   while (getline(cin, line))
   {
    blanks.push_back(countBlanks(line));
    //cout << countBlanks(line);
    lines.push_back(trimmedLeft(line));
    //cout << trimmedLeft(line) << endl;
   }

    while(lineIndex < lines.size()){
        
        if(lines.at(lineIndex) == "<naredba_pridruzivanja>"){
            pridruzivanje();
        }
        if(lines.at(lineIndex) == "<za_petlja>"){
            petlja();
        }
        lineIndex++;
    }
   return 0;
}