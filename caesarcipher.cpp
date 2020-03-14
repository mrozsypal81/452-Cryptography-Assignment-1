#include <iostream>
#include <string>
#include<math.h>
using namespace std;
string caesarCipher(string, int, char);

int main()
{

    string input;
    string output;
    char mode;
    int key;

    cout << "Enter input: ";
    getline(cin,input);

    cout << "\nEnter key: ";
    cin >> key;

    cout << "Choose a mode(e/d): ";
    cin >> mode;

    output = caesarCipher(input,key, mode);

    cout << output << endl;


}

string caesarCipher(string t, int k, char m)
{

    string output;

    //encypt
    if (m == 'e')
    {
        for (int i = 0; i < t.length(); i++)
        {
            char temp = t.at(i);
            for (int j = 0; j < k; j++)
            {
                if(isalpha(temp))
                {
                    if (temp == 'z')
                    {
                        temp = 'a';
                    }
                    else
                    {
                        temp++;
                    }
                }
            }
            if(isalpha(temp))
            {
                output += temp;
            }
            
        }
    }

    //decrypt
    if (m == 'd')
    {
        for (int i = 0; i < t.length(); i++)
        {
            char temp = t.at(i);
            for (int j = 0; j < k; j++)
            {
                if(isalpha(temp))
                {
                    if (temp == 'a')
                    {
                        temp = 'z';
                    }
                    else
                    {
                        temp--;
                    }
                }
            }
            if(isalpha(temp))
            {
                output += temp;
            }
            
        }
        
    }

    return output;

}