#include <iostream>
#include <string>
#include <math.h>
#include "caesarcipher.h"

using namespace std;

bool Caesar::setKey(const string& key)
{     
    for (int i = 0; i< key.length(); i++)
    {
	    if (!isdigit(key[i])){
		    return false;
        }
    }
    int keytemp = stoi(key);

    //cout << "key is a number" << key << endl;
    secretkey = keytemp;
    return true;
    
}

string Caesar::encrypt(const string& input)
{
    cout << secretkey << endl;
    string output;
    for (int i = 0; i < input.length(); i++)
        {
            char temp = input.at(i);
            for (int j = 0; j < secretkey; j++)
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

        return output;
    }

string Caesar::decrypt(const string& input)
{
    string output;
    for (int i = 0; i < input.length(); i++)
    {
            char temp = input.at(i);
            for (int j = 0; j < secretkey; j++)
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
   return output;      
}

   
