#include <iostream>
#include <string>
#include<math.h>
#include <vector>
#include <bits/stdc++.h>
#include "vigenerecipher.h"
using namespace std;


string Vigenere::checkkeysize(const string& input){

    while(input.size() > secretkey.size()){
        secretkey += secretkey;
        //cout << "making key larger ", secretkey;
    }
    return secretkey;
}


int Vigenere::findposition(string k,int startval){
                        //0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
vector<char> alphavector{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p',
                        'q','r','s','t','u','v','w','x','y','z'};
                    //   16  17  18  19  20  21  22  23  24  25
    for(int i = 0; i < alphavector.size();i++){
        if(k.at(startval) == alphavector.at(i)){
            //cout << "found a match" << endl;
            return i;
        }
    }

    cout << "There was no match it was not a letter or some other error";
    return 0;
}

string Vigenere::encrypt(const string& input)
{
                            //0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
    vector<char> alphavector{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p',
                        'q','r','s','t','u','v','w','x','y','z'};
                    //   16  17  18  19  20  21  22  23  24  25
    string inputtemp = input;
    transform(inputtemp.begin(),inputtemp.end(),inputtemp.begin(), ::tolower);
    string output;
    int keyloc = 0;
    int inputloc = 0;
    secretkey = checkkeysize(inputtemp);
    //encypt
        for(int i = 0;i<input.size();i++){
            keyloc = findposition(secretkey,i);
            inputloc = findposition(inputtemp,i);

            //cout << "adding to the output" << endl;
            output += (alphavector.at((keyloc + inputloc)%26));
        }

        return output;

}
string Vigenere::decrypt(const string& input)
{
                                //0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
    vector<char> alphavector{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p',
                        'q','r','s','t','u','v','w','x','y','z'};
                    //   16  17  18  19  20  21  22  23  24  25
    string inputtemp = input;
    transform(inputtemp.begin(),inputtemp.end(),inputtemp.begin(), ::tolower);
    string output;
    int keyloc = 0;
    int inputloc = 0;
    secretkey = checkkeysize(inputtemp);
    //decrypt
        for(int i = 0;i<input.size();i++){
            keyloc = findposition(secretkey,i);
            inputloc = findposition(inputtemp,i);
            //cout << "adding to the output" << endl;
            output += (alphavector.at((inputloc - keyloc +26)%26));
        }
        

    return output;

}

bool Vigenere::setKey(const string& key){
    for (int i = 0; i< key.length(); i++)
    {
        if (isdigit(key[i])){
		  return false;
        }
    }
    secretkey = key;
    //cout << "setting key" << endl;
        //transforms the key to lowercase
    transform(secretkey.begin(),secretkey.end(),secretkey.begin(), ::tolower);
	return true;  
}