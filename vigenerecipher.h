#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <bits/stdc++.h>
#include "CipherInterface.h"

using namespace std;

/**
 * This class implements the Vigenere cipher.
 * The class extends the abstract class 
 * CipherInterface.
 */

class Vigenere: public CipherInterface
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

        //makes the key as big or larger than the input
        virtual string checkkeysize(const string& input);

        //determines the position of the passed in value in the
        // alphavector or alphabet
        virtual int findposition(string input,int startval);
		
		/* The protected members */
	protected:
		string secretkey;

};

#endif
