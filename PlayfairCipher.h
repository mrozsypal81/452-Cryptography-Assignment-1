#ifndef PLAYFAIRCIPHER_H
#define PLAYFAIRCIPHER_H
#include "CipherInterface.h"
#include <iostream>
#include<string>
#include<math.h>
#include<sstream>

using namespace std;

/**
 * This class implements the PlayFair cipher.
 * The class extends the abstract class 
 * CipherInterface.
 */

class PlayfairCipher: public CipherInterface
{
	/** The public members **/
	public:

		/**
		 * Sets the key to use
		 * @param key - the key to use
		 * @return - True if the key is valid and False otherwise
		 */
		virtual bool setKey(const string& key);

		/**	
		 * Encrypts a plaintext string
		 * @param plaintext - the plaintext string
		 * @return - the encrypted ciphertext string
		 */
		virtual string encrypt(const string& plaintext);

		/**
		 * Decrypts a string of ciphertext
		 * @param ciphertext - the ciphertext
		 * @return - the plaintext
		 */
		virtual string decrypt(const string& ciphertext);

		
		/* The protected members */
	protected:
        string secretKey;
		char** matrix;
		string coordinate[25];


};

#endif

