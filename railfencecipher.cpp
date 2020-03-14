#include <iostream>
#include <string>
using namespace std;
string railfenceCipher(string, int, char);

int main()
{
    string input;
    string output;
    char mode;
    int key;

    cout << "Enter input: ";
    getline(cin, input);

    cout << "\nEnter key: ";
    cin >> key;

    cout << "Choose a mode(e/d): ";
    cin >> mode;

    output = railfenceCipher(input, key, mode);

    cout << output << endl;

    return 0;
}

string railfenceCipher(string text, int key, char mode)
{
    string output;
    char **table;
    char empty = ' ';
    int len = round(text.length() / key);
    int counter = 0;

    len++;

    //create table
    table = new char *[key];
    for (int i = 0; i < key; ++i)
    {
        table[i] = new char[len];
    }

    //empty the table
    for (int row = 0; row < key; row++)
    {
        for (int col = 0; col < len; col++)
        {
            table[row][col] = empty;
        }
    }

    //encrypt
    if (mode == 'e')
    {
        //fill table with inputs
        for (int col = 0; col < len; col++)
        {
            for (int row = 0; row < key; row++)
            {
                if (counter < text.length())
                {
                    char temp = text.at(counter);
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
        
        for (int row = 0; row < key; row++)
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

    //decrypt
    if (mode == 'd')
    {
        //fill the table
        for (int row = 0; row < key; row++)
        {
            for (int col = 0; col < len; col++)
            {
                if (counter < text.length())
                {
                    char temp = text.at(counter);
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
            for (int row = 0; row < key; row++)
            {
                if (isalpha(table[row][col]))
                {
                    output += table[row][col];
                }
            }
        }
        return output;
    }
}
