#include "RowTransposition.h"
#include <iostream>
#include <cmath>
using namespace std;

bool RowTransposition::setKey(const string& key){
	for (int i = 0; i< key.length(); i++){
		if (!isdigit(key[i]))
			return false;
	}
	secretkey = key;
	return true;  
}

string RowTransposition::encrypt(const string& plaintext){ 
	string ciphertext = "";
	int maxcolumns = secretkey.length();
	int maxrows = ceil(plaintext.length()/(double)maxcolumns);
	int plaintextlength = plaintext.length();
	char matrix[maxrows][maxcolumns];
	int i = 0;
	for (int r = 0; r < maxrows; r++){
		for (int c = 0; c < maxcolumns; c++){
			if (i < plaintextlength){
				matrix[r][c] = plaintext[i];
				i++;
			}
			else {
				matrix[r][c] = 'x';
			}
		}
	}
	for (i = 0; i < maxcolumns; i++){
		for(int r = 0; r < maxrows; r++){
			ciphertext.push_back(matrix[r][secretkey[i]-'1']);
		}
	}
	return ciphertext;
}

string RowTransposition::decrypt(const string& ciphertext){ 
	string plaintext = "";
	int maxcolumns = secretkey.length();
	int maxrows = ciphertext.length()/maxcolumns;
	char matrix[maxrows][maxcolumns];
	int i = 0;
	for (int c = 0; c < maxcolumns; c++){
		for (int r = 0; r < maxrows; r++){
			matrix[r][secretkey[c]-'1'] = ciphertext[i];
			i++;
		}
	}
	for (int r = 0; r < maxrows; r++){
		for (int c = 0; c < maxcolumns; c++){
			plaintext.push_back(matrix[r][c]);
		}
	}
	return plaintext; 
}

