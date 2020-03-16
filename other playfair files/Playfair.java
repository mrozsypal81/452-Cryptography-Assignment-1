// Assignment will take in the user string input and key input and store it into a 5 x 5 matrix.
// Using the Matrix, the program will then encode the string into a jumble,
// The program will also have the ability to decrypt a string if it knows the key.
// Group of 4 for this project
// Ethan Letrong 890390305

//imported libraries needed to take user input
import java.util.Scanner;

//Using a class to make this easier
public class PlayfairCipher
{
	//Private data types
    private char[][] table = new char [5][5];							//The 5 x 5 matrix to store the key and remaining letters
    private String plaintext, ciphertext, key;
	private char[] tempKey;												//Temporary Key used for storage

    Scanner scan = new Scanner (System.in);								//Scanner to take in user input

    // Default constructor will set shift to 0.
	// We will default the plaintext, ciphertext, and key to empty strings
    //
    public PlayfairCipher ()
    {
        plaintext = "";
        ciphertext = "";
        key = "";
    }

    
    // Function will take and store the user input as a key for encryption and decryption
    public void setKey (String k)
    {
        key = k;
    }

    // Function will display the matrix and what's written in it.
    public void viewTable ()
    {
        for (int idx = 0; idx < 5; idx++)								//For the rows
        {
            for (int i = 0; i < 5; i++)									//For the columns
            {
                System.out.print (table[idx][i] + " ");
            }
            System.out.println ();
        }
    }

    // Function will create the matrix for encryption and decryption
    private void createTable ()
    {
        // Create a char array for key
        char keyArr[] = new char[key.length()];

        for (int idx = 0; idx < keyArr.length; idx++)
        {
            keyArr[idx] = key.charAt(idx);
        }

        // Create a char array to test for duplicates
        char temp[] = new char[key.length()];
        boolean distinct = true;

        // If there is a duplicate, set its index to ' '
        // If not, add it to the temp array
        for (int idx = 0; idx < keyArr.length; idx++)
        {
            for (int i = 0; i < temp.length; i++)
            {
                if (keyArr[idx] == temp[i])								//Assuming that there is a duplicate
                    distinct = false;
            }
            if (distinct == true)
                temp[idx] = keyArr[idx];								//Assuming that there is no duplicates
            else
                keyArr[idx] = ' ';										//Get rid of that duplicate
        }

        // If there is a ' ' in the array, we get rid of it
        for (int idx = 0; idx < keyArr.length; idx++)
        {
            if (keyArr[idx] == ' ')
            {
                keyArr[idx] = keyArr[idx + 1];								//We shift it to get rid of the ' '
                keyArr[idx + 1] = ' ';
            }
        }


        // Populate the matrix with the key
        int row = 0, col = 0;
		
        for (int idx = 0; idx < keyArr.length; idx++)
        {
            if (row < 5 && col < 5)
            {
                if (keyArr[idx] != ' ')
                {
                    table[row][col] = keyArr[idx];
                    col++;
                }
            }
            if (col >= 5)
            {
                col = 0;
                row++;
            }
        }

        // Fill the matrix
		distinct = false;
        char start = 'a';
        
        for (int idx = 0; idx < 5; idx++)
        {
            for (int i = 0; i < 5; i++)
            {
                // Only add a char if the space is empty
                if (table[idx][i] < 'a' || table[idx][i] > 'z') {
                    
					// Check for duplicates
					int tempCount;
                    boolean dupe = false;
             
                    while (distinct == false) {
                        for (tempCount = 0; tempCount < temp.length; tempCount++) {
                            if (start == temp[tempCount])
                                dupe = true;
                            else if (start == 'i' && temp[tempCount] == 'idx')
                                dupe = true;
                            else if (start == 'idx' && temp[tempCount] == 'i')
                                dupe = true;
                        }
                        if (dupe == true) {
                                start++;
                            dupe = false;
                        }
                        else
                            distinct = true;
                    }
                    // If the character is not a dupe
                    table[idx][i] = start;
                    start++;
                    distinct = false;
                }
            }
        }
    }

    
    // Encrypt the plaintext and return the ciphertext
    public String encrypt (String p)
    {
        plaintext = p;

        // Create an array for plaintext
		int plainCounter = 0;
        char plainArr[] = new char [plaintext.length ()];
		
        for (int idx = 0; idx < plainArr.length; idx++)
        {
            // if 2nd char in a pair is same as the 1st one
            // add the 'x' in between them to simulate concurrent letters
            if (idx % 2 == 1 && plaintext.charAt(plainCounter) == plaintext.charAt(plainCounter-1))
            {
                plainArr[idx] = 'x';
            }
            else {
                plainArr[idx] = plaintext.charAt(plainCounter);
                plainCounter++;
            }
        }

        createTable ();


        // create 2 arrays to hold row and column numbers of each plaintext pair
        int x = 0, y = 1, a = 0, b = 0;
        int[] numCol = new int [plainArr.length];
        int[] numRow = new int [plainArr.length];

        for (; x < plainArr.length; x++)
        {
            for (int idx = 0; idx < 5; idx++) {
                for (int i = 0; i < 5; i++) {
                    if (plainArr[x] == table[idx][i]) {
                        numRow[a] = idx;
                        a++;
                    }
                }
            }
        }
		
        for (; y < plainArr.length;)
        {
            for (int idx = 0; idx < 5; idx++) {
                for (int i = 0; i < 5; i++)
                {
                    if (plainArr[y] == table[idx][i]) {
                        numCol[b] = i;
                        b++;
                    }
                }
            }
            if (y % 2 == 1)
                y -= 1;
            else
                y += 3;
        }

        // Encrypt the plaintext based on the row and column numbers
        char[] cipher = new char[plainArr.length];
        a = 0;
        b = 0;
		
        for (int idx = 0; idx < cipher.length; idx++)
        {
            if (a % 2 == 0) {                                           // if char is 1st in the pair
                if (numRow[a] == numRow[a + 1])                         // if pair is in the same row
                {
                    if (numCol[a] == 4)
                        cipher[idx] = table[numRow[a]][0];                // circle to 1st column
                    else
                        cipher[idx] = table[numRow[a]][numCol[a] + 1];    // shift right
                }
                else  if (numCol[a] == numCol[a + 1])                   // if pair is in the same column
                {
                    if (numRow[a] == 4)
                        cipher[idx] = table[0][numCol[a]];                // circle to 1st row
                    else
                        cipher[idx] = table[numRow[a] + 1][numCol[a]];    // shift down
                }
                else
                    cipher[idx] = table[numRow[a]][numCol[a]];
            }
            if (a % 2 == 1) {                                           // if char is 2nd in the pair
                if (numRow[a] == numRow[a - 1])
                {
                    if (numCol[a] == 4)
                        cipher[idx] = table[numRow[a]][0];
                    else
                        cipher[idx] = table[numRow[a]][numCol[a] + 1];
                }
                else if (numCol[a] == numCol[a - 1])
                {
                    if (numRow[a] == 4)
                        cipher[idx] = table[0][numCol[a]];
                    else
                        cipher[idx] = table[numRow[a] + 1][numCol[a]];
                }
                else
                    cipher[idx] = table[numRow[a]][numCol[a]];
            }
            a++;
        }

        ciphertext = String.valueOf (cipher);
        return ciphertext;													//After decryption, it will return the encrypted ciphertext
    }

 
    // Decrypt the ciphertext and return the plaintext
    public String decrypt (String c)
    {
         ciphertext = c;

        // Create a plaintext array
        char cipherArr[] = new char [ciphertext.length ()];
        for (int idx = 0; idx < cipherArr.length; idx++)
        {
                cipherArr[idx] = ciphertext.charAt(idx);
        }

        createTable ();

        // create 2 arrays to hold row and column numbers of each ciphertext pair
        int x = 0, y = 1, a = 0, b = 0;
        int[] numCol = new int [cipherArr.length];
        int[] numRow = new int [cipherArr.length];

        for (; x < cipherArr.length; x++)
        {
            for (int idx = 0; idx < 5; idx++) {
                for (int i = 0; i < 5; i++) {
                    if (cipherArr[x] == table[idx][i]) {
                        numRow[a] = idx;
                        a++;
                    }
                }
            }
        }
		
        for (; y < cipherArr.length;)
        {
            for (int idx = 0; idx < 5; idx++) {
                for (int i = 0; i < 5; i++)
                {
                    if (cipherArr[y] == table[idx][i]) {
                        numCol[b] = i;
                        b++;
                    }
                }
            }
            if (y % 2 == 1)
                y -= 1;
            else
                y += 3;
        }

        // Decrypt the plaintext based on the row and column numbers
        char[] cipher = new char[cipherArr.length];
        a = 0;
        b = 0;
		
        for (int idx = 0; idx < cipher.length; idx++)
        {
            if (a % 2 == 0) {                                           // if char is 1st in the pair
                if (numRow[a] == numRow[a + 1])                         // if pair is in the same row
                {
                    if (numCol[a] == 0)
                        cipher[idx] = table[numRow[a]][4];                // circle to 4th column
                    else
                        cipher[idx] = table[numRow[a]][numCol[a] - 1];    // shift left
                }
                else  if (numCol[a] == numCol[a + 1])                   // if pair is in the same column
                {
                    if (numRow[a] == 0)
                        cipher[idx] = table[4][numCol[a]];                // circle to 4th row
                    else
                        cipher[idx] = table[numRow[a] - 1][numCol[a]];    // shift upwards
                }
                else
                    cipher[idx] = table[numRow[a]][numCol[a]];
            }
            if (a % 2 == 1) {                                           // if char is 2nd in the pair
                if (numRow[a] == numRow[a - 1])
                {
                    if (numCol[a] == 0)
                        cipher[idx] = table[numRow[a]][4];
                    else
                        cipher[idx] = table[numRow[a]][numCol[a] - 1];
                }
                else if (numCol[a] == numCol[a - 1])
                {
                    if (numRow[a] == 0)
                        cipher[idx] = table[4][numCol[a]];
                    else
                        cipher[idx] = table[numRow[a] - 1][numCol[a]];
                }
                else
                    cipher[idx] = table[numRow[a]][numCol[a]];
            }
            a++;
        }

        plaintext = String.valueOf (cipher);
        return plaintext;													//returns the plaintext which has been decrypted
    }
}
