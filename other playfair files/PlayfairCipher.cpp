
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include "PlayfairCipher.h"



using namespace std;

bool PlayfairCipher::setKey(const string& k){
    cout << "setting the key inside the class" << endl;
    string temp = k;
    char *Ckey = &(temp[0]);

    
    strcpy(secretkey,Ckey);
}

// Function to convert the entire string to lowercase letters
void PlayfairCipher::lowerCase(char plain[], int ps)
{
    for (int idx = 0; idx < ps; idx++)
    {
        if (plain[idx] > 64 && plain[idx] < 91)
        {
            plain[idx] += 32;
        }
    }
}


// Function to remove all spaces in a string
// Returns the altered string
int PlayfairCipher::removeSpace(char* plain, int ps)
{
    int count = 0;
    for (int idx = 0; idx < ps; idx++)
    {
        if (plain[idx] != ' ')
        {
            plain[count++] = plain[idx];
        }
        
    }
    plain[count] = '\0';
    return count;
}


// Function to generate the 5x5 key matrix used for later
void PlayfairCipher::generateKeyTable(char key[], int ks, char keyT[5][5])
{
    //Declarations used for future uses
    int idx, i, k, flag = 0, * dicty;

    // a 26 character hashmap 
    // to store count of the alphabet 
    dicty = (int*)calloc(26, sizeof(int));


    for (idx = 0; idx < ks; idx++)
    {
        if (key[idx] != 'j')                    //In the case of J which we do not need
        {
            dicty[key[idx] - 97] = 2;
        }
    }

    dicty['j' - 97] = 1;

    idx = 0;
    i = 0;

    for (k = 0; k < ks; k++)
    {
        if (dicty[key[k] - 97] == 2)
        {
            dicty[key[k] - 97] -= 1;
            keyT[idx][i] = key[k];
            i++;
            if (i == 5)
            {
                idx++;
                i = 0;                          //Reset to simulate the mod attribute
            }
        }
    }

    for (k = 0; k < 26; k++)
    {
        if (dicty[k] == 0)
        {
            keyT[idx][i] = (char)(k + 97);
            i++;
            if (i == 5)
            {
                idx++;
                i = 0;                          //Reset to simulate the mod attribute
            }
        }
    }
}

// Function to search for the characters of agraph 
// in the key and return their position 
void PlayfairCipher::search(char keyT[5][5], char first, char second, int tempArr[])
{
   
    //Cases for "i" and "J" issues. We only care about "I", so "J" becomes an "I" clone
    if (first == 'j')
    {
        first = 'i';
    }
    else if (second == 'j')
    {
        second = 'i';
    }

    //We're assuming that there is no special cases, so we move 
    // onto the rest of the array. 
    for (int idx = 0; idx < 5; idx++)
    {

        for (int i = 0; i < 5; i++)
        {

            if (keyT[idx][i] == first)
            {
                tempArr[0] = idx;
                tempArr[1] = i;
            }
            else if (keyT[idx][i] == second)
            {
                tempArr[2] = idx;
                tempArr[3] = i;
            }
        }
    }
}


// Excessively needed a mod function for the reason that my
// mod operations are not working properly
int PlayfairCipher::modby5(int a)
{
    a %= 5;                                 //Help for index modification by 5
    return a;
}


// Function to make the plain text length to be even 
int PlayfairCipher::prepare(char tempPlain[], int ptrs)
{
    if (ptrs % 2 != 0)
    {
        tempPlain[ptrs++] = 'z';
        tempPlain[ptrs] = '\0';
    }
    return ptrs;
}

// Function for performing the encryption 
// Takes in a string
string PlayfairCipher::encrypt(const string& plaintext)
{   cout << "inside encrypt" << endl;
    string temp = plaintext;
    cout << temp << endl;
    char *tempStr = &(temp[0]);
        char ks,ps;

    // Key to be used
    ks = strlen(secretkey);
    ks = removeSpace(secretkey, ks);
    lowerCase(secretkey, ks);

    // Plaintext  to be used
    ps = strlen(tempStr);
    lowerCase(tempStr, ps);
    ps = removeSpace(tempStr, ps);

    ps = prepare(tempStr, ps);

    generateKeyTable(secretkey, ks, keyT);
    int idx, tempArr[4];

    for (idx = 0; idx < ps; idx += 2)
    {

        search(keyT, tempStr[idx], tempStr[idx + 1], tempArr);

        if (tempArr[0] == tempArr[2])
        {
            tempStr[idx] = keyT[tempArr[0]][modby5(tempArr[1] + 1)];
            tempStr[idx + 1] = keyT[tempArr[0]][modby5(tempArr[3] + 1)];
        }
        else if (tempArr[1] == tempArr[3])
        {
            tempStr[idx] = keyT[modby5(tempArr[0] + 1)][tempArr[1]];
            tempStr[idx + 1] = keyT[modby5(tempArr[2] + 1)][tempArr[1]];
        }
        else
        {
            tempStr[idx] = keyT[tempArr[0]][tempArr[3]];
            tempStr[idx + 1] = keyT[tempArr[2]][tempArr[1]];
        }
    }
    string final(tempStr);
    cout << final << endl;
    return final; 
}


// Function to decrypt 
//Takes in a string, matrix, and integer
string PlayfairCipher::decrypt(const string& ciphertext)
{
    string temp = ciphertext;
    cout << temp << endl;
    char *tempStr = &(temp[0]);
        char ks,ps;

    //This is to take in the Key 
    ks = strlen(secretkey);
    ks = removeSpace(secretkey, ks);
    lowerCase(secretkey, ks);

    //This is to take in ciphertext 
    ps = strlen(tempStr);
    lowerCase(tempStr, ps);
    ps = removeSpace(tempStr, ps);

    generateKeyTable(secretkey, ks, keyT);
    int idx, tempArr[4];
    for (idx = 0; idx < ps; idx += 2) 
    {
        search(keyT, tempStr[idx], tempStr[idx + 1], tempArr);
        if (tempArr[0] == tempArr[2]) 
        {
            tempStr[idx] = keyT[tempArr[0]][modby5(tempArr[1] - 1)];
            tempStr[idx + 1] = keyT[tempArr[0]][modby5(tempArr[3] - 1)];
        }
        else if (tempArr[1] == tempArr[3]) 
        {
            tempStr[idx] = keyT[modby5(tempArr[0] - 1)][tempArr[1]];
            tempStr[idx + 1] = keyT[modby5(tempArr[2] - 1)][tempArr[1]];
        }
        else 
        {
            tempStr[idx] = keyT[tempArr[0]][tempArr[3]];
            tempStr[idx + 1] = keyT[tempArr[2]][tempArr[1]];
        }
    }
    string final(tempStr);
    cout << final << endl;
    return final;
}


/*
Use this format for when you need to call it in the CPP format

//You are gunna need a random variable for the outcome
//use tempOutput for now
string tempInput;

char plainText[SIZE], key[SIZE];


        //Let's get a key here
        cout << "Please enter a key for us to use." << endl;
        cin >> key;
        cout << "The key you entered is: " << key << endl;

        cout << "Do you want to Encrypt or Decrypt? (ENC or DEC): ";
        cin >> tempInput;

        if (tempInput == "ENC")
        {
            //Now let's take a string to be used
            cout << "Please enter a string you want us to work on." << endl;
            cin >> plainText;
            cout << "The plaintext you wish to encrypt is: " << plainText << endl;

            //Now running that shit.
            encryptByPlayfairCipher(plainText, key);
            cout << "Cipher text is: " << plainText << endl;
        }
        if (tempInput == "DEC")
        {
            cout << "Please enter a Ciphertext you want us to work on." << endl;
            cin >> plainText;
            cout << "The Ciphertext you wish to encrypt is: " << plainText << endl;

            decryptByPlayfairCipher(plainText, key);
            cout << "Plaintext text is: " << plainText << endl;
        }



*/