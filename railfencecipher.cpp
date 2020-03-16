#include <iostream>
#include <string>
#include "railfencecipher.h"
using namespace std;


bool Railfence :: setKey(const string& key)
{     
    for (int i = 0; i< key.length(); i++)
    {
        if (!isdigit(key[i])){
		  return false;
        }
    }

    int tempkey = stoi(key);
    secretkey = tempkey;
    return true;

}

string Railfence :: encrypt(const string& plaintext)
{
    string output;
    int len = round(plaintext.length() / secretkey);
    int counter = 0;
    char empty = ' ';
    len++;

     //create table
    char **table = new char *[secretkey];
    for (int i = 0; i < secretkey; ++i)
    {
        table[i] = new char[len];
    }

    //empty the table
    for (int row = 0; row < secretkey; row++)
    {
        for (int col = 0; col < len; col++)
        {
            table[row][col] = empty;
        }
    }

    //encrypt
    //fill table with inputs
    for (int col = 0; col < len; col++)
    {
        for (int row = 0; row < secretkey; row++)
        {
            if (counter < plaintext.length())
            {
                char temp = plaintext.at(counter);
                if (isalpha(temp))
                {
                    table[row][col] = temp;
                    counter++;
                }
                else
                {
                    counter++;
                    row--;
                }
            }
        }
    }

        //generate cipher text
        
        for (int row = 0; row < secretkey; row++)
        {
            for (int col = 0; col < len; col++)
            {
                cout << table[row][col];
                if (isalpha(table[row][col]))
                {
                    output += table[row][col];
                }
            }
            cout << endl;
        }

        return output;
}
string Railfence :: decrypt(const string& ciphertext)
{
    string output;
    string ciphertextcp = ciphertext;
    int len = round(ciphertext.length() / secretkey);
    int counter = 0;
    len++;
    char empty = ' ';
    int *lettersPerRowArr;
    lettersPerRowArr = new int[secretkey];
    int lettersPerRow = floor(ciphertext.length()/secretkey);
    int leftover = ciphertext.length() % secretkey;

    //remove all blank space from input
    for(int i = 0; i < ciphertextcp.length();i++)
    {
        if(ciphertextcp.at(i)==' ')
        {
            ciphertextcp.erase(i,1);
            i--;
        }
    }

    for(int i = 0;i < secretkey; i++)
    {
        if(leftover != 0)
        {
            lettersPerRowArr[i] = lettersPerRow+1;
            leftover--;
        }
        else
        {
            lettersPerRowArr[i] = lettersPerRow;
        }
        cout << lettersPerRowArr[i] << endl;
        
    }
     //create table
    char **table = new char *[secretkey];
    for (int i = 0; i < secretkey; ++i)
    {
        table[i] = new char[len];
    }

    //empty the table
    for (int row = 0; row < secretkey; row++)
    {
        for (int col = 0; col < len; col++)
        {
            table[row][col] = empty;
        }
    }

    //fill the table
        for (int row = 0; row < secretkey; row++)
        {
            for (int col = 0; col < lettersPerRowArr[row]; col++)
            {
                if (counter < ciphertext.length())
                {
                    char temp = ciphertext.at(counter);
                    if (isalpha(temp))
                    {
                        table[row][col] = temp;
                        cout << table[row][col];
                        counter++;
                    }
                    else
                    {
                        counter++;
                        col--;
                    }
                }
            }
            cout << endl;
        }
        //generate plaintext
        for (int col = 0; col < len; col++)
        {
            for (int row = 0; row < secretkey; row++)
            {
                if (isalpha(table[row][col]))
                {
                    output += table[row][col];
                }
            }
        }

        return output;
}

