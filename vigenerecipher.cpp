#include <iostream>
#include <string>
#include<math.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
string vigenerecipher(string, string, char);
                        //0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15
vector<char> alphavector{'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p',
                        'q','r','s','t','u','v','w','x','y','z'};
                    //   16  17  18  19  20  21  22  23  24  25

string checkkeysize(string key,string input){

    while(input.size() > key.size()){
        key += key;
        cout << "making key larger ", key;
    }
    return key;
}

int main()
{

    string input;
    string output;
    char mode;
    string key;

    cout << "Enter input: ";
    getline(cin,input);

    //transforms the input to lowercase
    transform(input.begin(),input.end(),input.begin(), ::tolower);

    cout << "\nEnter key: ";
    cin >> key;

    //transforms the key to lowercase
    transform(key.begin(),key.end(),key.begin(), ::tolower);

    cout << "Choose a mode(e/d): ";
    cin >> mode;

    // This makes sure that the key is longer than the input
    key = checkkeysize(key,input);
    output = vigenerecipher(input,key,mode);

    cout << output << endl;


}

int findposition(string k, int startval){

    for(int i = 0; i < alphavector.size();i++){
        if(k.at(startval) == alphavector.at(i)){
            return i;
        }
    }

    cout << "There was no match it was not a letter or some other error";
    return 0;
}

string vigenerecipher(string input, string k, char m)
{

    string output;
    int keyloc = 0;
    int inputloc = 0;

    //encypt
    if (m == 'e')
    {
        for(int i = 0;i<input.size();i++){
            keyloc = findposition(k,i);
            inputloc = findposition(input,i);

            output += (alphavector.at((keyloc + inputloc)%26));
        }

    }

    //decrypt
    if (m == 'd')
    {
        for(int i = 0;i<input.size();i++){
            keyloc = findposition(k,i);
            inputloc = findposition(input,i);
            output += (alphavector.at((inputloc - keyloc +26)%26));
        }
        
    }

    return output;

}