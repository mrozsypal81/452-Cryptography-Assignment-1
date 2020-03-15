#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
//#include "stdafx.h"
#include <vector>
#include <stdlib.h>
#include <ctype.h>
#include <algorithm>
#include "CipherInterface.h"

using namespace std;

class PlayfairCipher : public CipherInterface
{
public:
	//universal variables
	string plainText;
	string userKeyStr;
	vector<char> userKey;
	vector<char> userInputStr;
	vector<char> userKeyM;
	vector<char> alphaArray = { 'a','b','c','d','e','f','g','h','i','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z' };

	//list of functions for CaeserCipher
	void startup();
	void keyGrab();
	void encrypt(vector<char>);
	void removeDupe(vector<char>);
	//void removeSpace(char*);
	//bool isSpace(unsigned char);
	//void decrypt();
	//int shiftIndexR(int);
	//int shiftIndexL(int);
	void popMatrix(vector<char>);
	void dupeVector(vector<char>, vector<char>);
	void displayVector(vector<char>);

};


void PlayfairCipher::removeDupe(vector<char> tempV)
{
	
	//Going through the string
	for (int idx = 0; idx < tempV.size()-1; idx++)
	{

		//Now comparing to the rest of the string
		for (int j = idx+1; j < tempV.size(); j++)
		{
			//Assuming that the indexs match
			if (tempV[idx] == tempV[j])
			{
				break;
			}
			//assuming we hit the end of the comparison loop
			if (j == tempV.size() - 1)
			{
				userKey.push_back(tempV[idx]);
			}

		}

	}
	cout << "Removed dupes" << endl;
	displayVector(userKey);

}

//Startup to take in the user's input and store it in userString to be altered later. 
//
void PlayfairCipher::startup()
{
	cout << "Please put in the string you wish to encrypt." << endl;
	cin >> plainText;

	//plainText.erase(std::remove_if(plainText.begin(), plainText.end(), isSpace()), plainText.end());
	//removeSpace(plainText);
	cout << "you entered " << plainText << endl;

	//DEBUG: populating the vector with a string
	cout << "Now populating vector." << endl;
	for (int idx = 0; idx < plainText.size(); idx++)
	{
		//if the char at the array index is not a blank, populate the vector
		userInputStr.push_back(plainText[idx]);
		
	}



	//DEBUG: Display the vector
	displayVector(userInputStr);

}

//Now we have a user string, so we shall take in the key they wish to use.
void PlayfairCipher::keyGrab()
{
	cout << "Please input a unique key." << endl;
	cin >> userKeyStr;

	// DEBUG: Pushing the key into a vector for reference later
	cout << "We are now populating your key." << endl;
	for (int idx = 0; idx < userKeyStr.size(); idx++)
	{
		userKey.push_back(userKeyStr[idx]);
	}

	//DEBUG: To verify what the key is.
	cout << "They key you have selected is ";
	displayVector(userKey);
	cout << endl;
	//removeDupe(userKey);
	//We need to eliminate the extra letters in the user's key
	//First loop will store a letter and check the rest of the vector

	
	cout << "Eliminating duplicate letters. " << endl;

	//We will take the first letter of the vector string and store it in a temp variable
	//We will go through the vector and check for any duplicate letters
	//We will then eliminate those vectors and store it in the new vector
	//profit???

	//Go through the original key
	//compare with the second vector
	//if duplicate, do not copy
	//if unique, append to new vector

	vector<char> trueKey;										//initialize a new vector
	trueKey.push_back(userKey[0]);								//We need the first element there to compare

	// Now we create a for loop to go through the the user's input key and populate another vector
	for (int i = 1; i < userKey.size(); i++)
	{

		//STUPID ASS I/J CASE
		if (trueKey[0] == 'j')
		{
			cout << "Special Case I/J." << endl;
			trueKey[0] = 'i';
		}


		//A 'for' loop to compare the current element "i" in user Key to all elements in trueKey vector
		for (int index = 0; index < trueKey.size(); index++)
		{
			if (userKey[i] == trueKey[index])					//If there is a duplicate, we are gunna exit the loop for now
			{
				break;
			}

			if (index == trueKey.size() - 1)			//If there is no duplicate and we reached the end of the vector
			{
				trueKey.push_back(userKey[i]);			//We push the letter in the index onto the trueKey
			}
		}
	}

	cout << "The vector without duplicates. " << endl;
	displayVector(trueKey);
	userKey.clear();


	for (int odx = 0; odx < trueKey.size(); odx++)
	{
		userKey.push_back(trueKey[odx]);
	}

	cout << "Duplicated the keys, but no duplicates." << endl;
	trueKey.clear();
	displayVector(userKey);
}


void PlayfairCipher::popMatrix(vector<char> tempV2)
{
	cout << "We are now working on popMatrix " << endl;
	//First, we take the user key and put it into the matrix
	//Then we go through the alphabet and eliminate duplicate letters
	//Then we populate the rest of the matrix
	//display the key for user to enjoy

	//Populating the vector with the user's key
	cout << "We are populating the matrix with your key." << endl;
	for (int idx = 0; idx < tempV2.size(); idx++)
	{
		userKeyM.push_back(tempV2[idx]);
	}
	displayVector(userKeyM);
	tempV2.clear();

	//First loop goes through all of the elements of alphabet
	cout << "Now we are running the population loop for the matrix" << endl;

	vector<char> tempVectorAlpha; // initializes a blank matrix to store the new vector without matches

	for (int i = 0; i < userKeyM.size(); i++)
	{
		tempVectorAlpha.push_back(userKeyM[i]);
	}
						//Something to compare with

	for (int i = 0; i < alphaArray.size(); i++)
	{
		//second for loop to go through all elements of the key vector
		//If there is a match, skip that key
		//if there are no matches, append to the Key Matrix
		for (int index = 0; index < userKeyM.size(); index++)
		{
			//cout << "Currently on '" << alphaArray[i] << "' right now." << endl;
			//Assuming that there is a match
			if (alphaArray[i] == userKeyM[index])
			{
				cout << "Found a match. It is " << alphaArray[i] << endl;
				cout << "We are eliminating " << alphaArray[i] << endl;
				//i++;
				break;
			}

			//Assuming that it went through the entire matrix and didn't find a match
			//but also if the current character is either I or J
			if (index == userKeyM.size() - 1 && (alphaArray[i] == 'i'))
			{
				cout << "Did not find a match. Sepcial Case 'I/J'. Populating the key matrix." << endl;
				tempVectorAlpha.push_back('i');
				break;
			}

			if (index == userKeyM.size() - 1)
			{
				cout << "Did not find a match. Populating the key matrix with " << alphaArray[i] << " ." << endl;
				tempVectorAlpha.push_back(alphaArray[i]);
			}
		}

	}
	userKeyM.clear();

	//Here we take the temporary sliced up alphabet and we populate that into the key matrix
	cout << "Now putting the altered alphabet into the matrix " << endl;
	for (int fidx = 0; fidx < tempVectorAlpha.size(); fidx++)
	{
		userKeyM.push_back(tempVectorAlpha[fidx]);

	}


	//DEBUG: Display the contents of the user key
	cout << "Displaying the user's key matrix after population. " << endl;
	cout << "The key matrix size is: " << userKeyM.size() << endl;
	displayVector(userKeyM);

}


//we will now encrypt the userKey using playfair cipher
//time for math and a 5 x 5 matrix
void PlayfairCipher::encrypt(vector<char> userInputString)
{
	cout << "We are not encrypting your string. " << endl;
	cout << "First we must change the string you implimented into somehting that we can use." << endl;

	vector<char> usableString;
	//for loop to go through the string and add in x for every dupe
	// to do this, we are gunna compare every concurrent pair of letters
	for (int idx = 1; idx < userInputString.size(); idx++)
	{
		if (userInputString[idx-1] == userInputString[idx]&& idx != userInputString.size()-1)
		{
			usableString.push_back(userInputString[idx - 1]);
			usableString.push_back('x');
		}
		if (idx == userInputString.size() - 1)
		{
			usableString.push_back(userInputString[idx]);
		}
		else
		{
			usableString.push_back(userInputString[idx - 1]);
		}

	}
	cout << "The new string is: " << endl;
	displayVector(usableString);




}

void PlayfairCipher::dupeVector(vector<char> originalVector, vector<char> cloneVector)
{

}

//DEBUG: Function takes a vector and prints out all of the individual elements
void PlayfairCipher::displayVector(vector<char> tempVector)
{
	for (int i = 0; i < tempVector.size() - 1; i++)
	{
		cout << tempVector[i] << ',';
	}
	cout << tempVector[tempVector.size() - 1];
	//For formatting
	cout << endl;
}
