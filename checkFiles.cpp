#include "bits/stdc++.h"
using namespace std;
vector<string>WordReader(string line);
vector<vector<string>> separatWords(string file);
void wordsComparison(string firstFile,string secondFile);
void occuranceWord(string file,int pos);
vector<char>charReader(string line);
void charComparison(string FirstFile,string SecondFile);
int main() {
    string firstFile,secondFile;
    cout<<"write the name of first file: "<<endl;
    cin>>firstFile;
    cout<<"write the name of second file: "<<endl;
    cin>>secondFile;
    firstFile+=".txt";
    secondFile+=".txt";
    fstream myfirstFile,mysecondFile;
    //check if files is exist
    myfirstFile.open(firstFile,ios::in);
    mysecondFile.open(secondFile,ios::in);
    if(!myfirstFile.is_open()||!mysecondFile.is_open()){
        cout<<"file is not exist"<<endl;
        return 0;
    }else{
        cout<<"file is exist"<<endl;
        cout << "1-word by word comprison" << endl << "2-char by char comparison" << endl;
        int answer;
        cin >> answer;
        if (answer == 1) {
            wordsComparison(firstFile, secondFile);
        } else if (answer == 2) {
            charComparison(firstFile, secondFile);
        }
    }
    return 0;
}
vector<string>WordReader(string line) {
    vector<string> words;
    string word{};
    int i = 0;
    while (i < line.size()) {
        while (!isspace(line[i])&& isalpha(line[i])&&i<line.size()) {
            word.push_back(line[i]);
            i++;
        }
        if (word.size() > 0) {
            words.push_back(word);
        }
        word.clear();
        i++;

    }
    return words;
}
vector<vector<string>> separatWords(string file){
    fstream myFile;
    myFile.open(file,ios_base::in);
    vector<vector<string>>Lines;
    string currentLine{};
    while(getline(myFile,currentLine)){
        Lines.push_back(WordReader(currentLine));
    }
    myFile.close();
    return Lines;


}
vector<vector<char>> separatChar(string file){
    fstream myFile;
    myFile.open(file,ios_base::in);
    vector<vector<char>>Lines;
    string currentLine{};
    while(getline(myFile,currentLine)){
        Lines.push_back(charReader(currentLine));
    }
    myFile.close();
    return Lines;

}
void occuranceWord(string fileName,int pos){
    fstream myfile;
    myfile.open(fileName,ios_base::in);
    string line;
    int i=0;
    while(i<pos) {
        getline(myfile,line);
        i++;
    }
    cout<<line<<endl;
}
void wordsComparison(string firstFile,string secondFile){
    fstream myfirstFile,mysecondFile;
    myfirstFile.open(firstFile,ios_base::in);
    mysecondFile.open(secondFile,ios_base::in);
    vector<vector<string>>Fwords= separatWords(firstFile);
    vector<vector<string>>Swords= separatWords(secondFile);
    bool identical{true};
    int pos;
    for(int i=0;i<Fwords.size();i++) {
        for (int j = 0; j < Fwords[i].size(); j++) {
            if (Fwords[i][j] != Swords[i][j]) {
                pos=i+1;
                cout<<"the first different word is in line: "<<pos<<endl;
                cout << Fwords[i][j]<<endl;
                myfirstFile.close();
                mysecondFile.close();
                occuranceWord(firstFile,pos);
                occuranceWord(secondFile,pos);
                identical= false;
                break;
            }else if(j==Fwords[i].size()-1&&Fwords[i].size()<Swords[i].size()){
                pos=i+1;
                cout<<"the first different word is in line: "<<pos<<endl;

                cout << Swords[i][j+1]<<endl;
                myfirstFile.close();
                mysecondFile.close();
                occuranceWord(firstFile,pos);
                occuranceWord(secondFile,pos);
                identical= false;
            }
        }
    }
    if(identical){
        cout<<"identical"<<endl;
    }
}
vector<char>charReader(string line){
    vector<char>chars{};
    int i = 0;
    while (i<line.size()){
            chars.push_back(line[i]);
            i++;
        }
    return chars;
}
void charComparison(string FirstFile,string SecondFile){
    fstream myfirstFile,mysecondFile;
    myfirstFile.open(FirstFile,ios_base::in);
    mysecondFile.open(SecondFile,ios_base::in);

    vector<vector<char>>Fchar= separatChar(FirstFile);
    vector<vector<char>>Schar= separatChar(SecondFile);
    vector<char>different;
    bool identical= true;
    for(int i=0;i<Fchar.size();i++) {
        for (int j = 0; j < Fchar[i].size(); j++) {
            if (Fchar[i][j] != Schar[i][j]) {
                different.push_back(Fchar[i][j]);
                identical= false;

            } if(j==Fchar[i].size()-1&&Fchar[i].size()<Schar[i].size()){
                for(int k=j+1;k<Schar[i].size();k++){
                    different.push_back(Schar[i][k]);
                }
                identical= false;
            }
        }
        if(!identical){
            cout<<"the different characters in line "<<i+1<<" size is "<<different.size()<<endl;
            for(auto l:different){
                cout<<l<<",";
            }
            mysecondFile.close();
            myfirstFile.close();
            break;
        }
    }
    if(identical){
        cout<<"identical"<<endl;
    }
}