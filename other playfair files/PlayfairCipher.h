#ifndef PLAYFAIRCIPHER_H
#define PLAYFAIRCIPHER_H
#include "CipherInterface.h"

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

        virtual int prepare(char tempPlain[], int ptrs);

        virtual int modby5(int a);

        virtual void search(char keyT[5][5], char first, char second, int tempArr[]);

        virtual void generateKeyTable(char key[], int ks, char keyT[5][5]);

        virtual int removeSpace(char* plain, int ps);

        virtual void lowerCase(char plain[], int ps);
		
		/* The protected members */
	protected:
        char keyT[5][5];
        char secretkey[];


};

#endif

