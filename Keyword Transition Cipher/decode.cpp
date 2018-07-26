#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <string>
#include <stdio.h>
using namespace std;


char originalAlphabet[26] = {'A', 'B', 'C', 'D', 'E','F','G','H','I','J','K','L','M','N','O', 'P','Q','R','S','T','U','V','W','X','Y','Z'};


void detectMoves(string unordered, string ordered, int *moves){
    int length;
    int index=0;
    //cout << "Detect Moves: " << endl;
    //cout << "Unordered: " << unordered << " Length: " << unordered.length() << endl;
    //cout << "Ordered: " << ordered << " Length: " << ordered.length() << endl;
    for(int i=0; i<unordered.length(); i++){
        char u = unordered[i];
        for(int j=0; j<ordered.length(); j++){
            char o = ordered[j];
            if(u==o){
                moves[index++] = j;
                //cout << i << " th changed as " << j << endl;
            }
        }
    }
}

string transformword(string inputword, int *moves){
    int movesize = inputword.length();
    char outputtemp[movesize];
    string outputword;
    //cout << "Word at first: " << inputword << endl;
    for(int i=0; i<movesize; i++){
        char x = inputword[i];
        outputtemp[moves[i]] = x;
        //cout << "moves[i]: " << moves[i] << " x: " << x << endl;
    }
    outputword = string(outputtemp);
    //cout << "Transformed word: " << outputword << endl;
    return outputword;
}

void transformAlphabet(int *moves, string keyword, char substitutedAlphabet[26]){
    char temp[26];
    int keylength = keyword.length();
    bool same = false;
    int index = 0;
    int wordIndex = 0;
    for(int i = 0; i<keylength; i++){
        temp[i] = keyword[i];
        index=i+1;
    }
    wordIndex = index;
    for(int i=0; i<26; i++){
        char x = originalAlphabet[i];
        for(int j = 0; j<keylength; j++){
            char y = keyword[j];
            if(x==y){
                same = true;
                break;
            }
        }
        if(same==true){
            same=false;
            continue;
        }
        temp[index++] = x;
    }
    /*cout << "Untransformed Word Alphabet: " << endl;
    for(int i=0; i<26; i++){
        cout << temp[i] << " ";
    }
    cout << endl;
    */
    int numberOfElements = (int)26/keylength +1;
    string trans[numberOfElements];
    trans[0] = keyword;
    char newst[keylength];
    //cout << "Keylength: " << keylength << endl;
    //cout << "Trans: " << endl;
    for(int i=1; i<numberOfElements; i++){
        for(int j=0; j<keylength; j++){
            if(j>=keylength)
                break;
            if(i*keylength + j >= 26)
                newst[j] = '*';
            else
                newst[j] = temp[i*keylength + j];
            //cout << "j: " << j << " newst[j]: " << newst[j] << endl;
        }
        //cout << newst << endl;
        trans[i] = string(newst);
        if(trans[i][keylength])
            trans[i].resize(keylength);
        //cout << trans[i]  << endl;
        //cout << "Trans Length: " << trans[i].length() << endl;
    }
    for(int i=1; i<numberOfElements; i++){
        string result = transformword(trans[i], moves);
        trans[i] = result;
        //cout << trans[i] << endl;
    }
    int subsIndex = 0;
    string substitutedStr[keylength];
    //cout << "Number of elements: " << numberOfElements << endl;
    for(int i=0; i<keylength; i++){
        //cout << " First Index: " << subsIndex << endl;
        //cout << "i= " << i << endl;
        for(int j=0; j<numberOfElements; j++){
            //cout << "i in j: " << i << endl;
            //cout << "j: "  << j << endl;
            if(trans[j][i]!='*')
                substitutedAlphabet[subsIndex++] = trans[j][i];
            //cout << "Index in j: " << subsIndex << endl;
        }
        //cout << "Last Index: " << subsIndex << endl;
    }
    /*cout << "Transformed Alphabet " << endl;
    for(int i=0; i<26; i++){
        cout << substitutedAlphabet[i] << " ";
    }
    cout << endl;*/
}


void decode(string ciphertext, char substitutedAlphabet[26]){
    int sizeofDecode = ciphertext.length();
    char tmp[sizeofDecode];
    for(int i=0; i<sizeofDecode; i++){
        char x = ciphertext[i];
        for(int j=0; j<26; j++){
            char y = substitutedAlphabet[j];
            if(x==y){
                ciphertext[i] = originalAlphabet[j];
            }
        }
    }
    //cout << "Ciphertext returned: ";
    cout << ciphertext << endl;
}


string orderChars(string word){
    vector<char>wordVector;
    string result;
    char temporary[20];
    for(int i=0; i<word.length(); i++){
        wordVector.push_back(word[i]);
    }
    sort(wordVector.begin(), wordVector.end());
    wordVector.erase(unique(wordVector.begin(), wordVector.end()), wordVector.end());
    for(int i=0; i<wordVector.size(); i++){
        temporary[i] = wordVector[i];
    }
    result =  string(temporary);
    if(result[wordVector.size()])
        result.resize(wordVector.size());
    //cout << "Result after order char: " << result << endl;
    return result;
}

string removeDuplicate(string word){
    vector<char>wordVector;
    char temporary[20];
    string result;
    for(int i=0; i<word.length(); i++){
        if(find(wordVector.begin(), wordVector.end(), word[i])!=wordVector.end())
            continue;
        wordVector.push_back(word[i]);
    }
    for(int i=0; i<wordVector.size(); i++){
        temporary[i]  = wordVector[i];
    }
    result = string(temporary);
    if(result[wordVector.size()])
        result.resize(wordVector.size());
    //cout << "Result after removeDuplicate: " << result << endl;
    return result;
}

int main() {
    int numberOfConversions;
    cin >> numberOfConversions;
    for(int i = 0; i< numberOfConversions; i++){
        string keyword ;
        string orderedkeyword;
        string ciphertext;
        cin >> keyword;
        cin.ignore();
        //cout << "Keyword taken as: " << keyword << endl;
        getline(cin, ciphertext);
        //cout << "Ciphertext taken as: " << ciphertext << endl;
        orderedkeyword = orderChars(keyword);
        keyword =  removeDuplicate(keyword);
        //cout << "Keyword: " << keyword << endl;
        //cout << "Ordered Keyword: " << orderedkeyword << endl;
        int moves[keyword.length()];
        char substitutedAlphabet[26];
        detectMoves(keyword, orderedkeyword, moves);
        //cout << "Keyword: " << keyword << endl;
        //cout << "Ordered Keyword: " << orderedkeyword << endl;
        transformAlphabet(moves, orderedkeyword, substitutedAlphabet);
        decode(ciphertext, substitutedAlphabet);
    }
    return 0;
}
