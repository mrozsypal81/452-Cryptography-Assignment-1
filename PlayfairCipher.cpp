#include <iostream>
#include<string>
#include<math.h>
#include<sstream>
#include"PlayfairCipher.h"
using namespace std;

bool PlayfairCipher::setKey(const string& orikey)
{
  cout << "inside setkey" << endl;
  string key = orikey;
  for (int i = 0; i< key.length(); i++){
	  if (isdigit(key[i])){
		  return false;
    }
  }
  //remove duplicate from key
  string nodupekey;
  int index = 0;    
     
   // Traverse through all characters 
   for (int i=0; i<key.length(); i++) { 
      int j;
     // Check if key.at(i) is present before it      
     for ( j=0; j<i; j++)
     {  
        if (key.at(i) == key.at(j))
           break; 
     }
     // If not present, then add it to 
     // result. 
     if (j == i){ 
        nodupekey += key.at(i); 
     }
   } 

    //build matrix and coordinate array
    //coordinate[25];
    matrix = new char*[5];
    for(int i = 0; i < 5;i++)
    {
      matrix[i] = new char[5];
    }

    index = 0;
    //insert key into matrix
    for(int row = 0; row < 5; row++)
    {
      for(int col = 0; col < 5; col++)
      {
        if(index < nodupekey.length())
        {
          if(nodupekey.at(index) ==  'i')
          {
            nodupekey.at(index) = 'j';
          }
          matrix[row][col] = nodupekey.at(index);
          index++;
        }
      }
    }

    //fill the rest of the matrix
    char letter = 'a';
    index = 0;
    for(int row = 0; row < 5; row++)
    {
      
      for(int col = 0; col < 5; col++)
      {
        //replace i with j
        if(letter == 'i')
        {
          letter = 'j';
        }
        //if letter is already in matrix
        if(matrix[row][col] == letter)
        {
          stringstream ss1, ss2;
          string temp_x, temp_y;
          ss1<<row;
          ss2<<col;
          temp_x = ss1.str();
          temp_y = ss2.str();

          coordinate[index++]=temp_x+temp_y;

          row=0;
          col=0;
          letter++;
          if(matrix[row][col] == letter)
          {
            stringstream ss1, ss2;
            string temp_x, temp_y;
            ss1<<row;
            ss2<<col;
            temp_x = ss1.str();
            temp_y = ss2.str();

            coordinate[index++]=temp_x+temp_y;


            row=0;
            col=0;
            letter++;
          }
        }
        if (!isalpha(matrix[row][col]) )
        {
          stringstream ss1, ss2;
          string temp_x, temp_y;
          ss1<<row;
          ss2<<col;
          temp_x = ss1.str();
          temp_y = ss2.str();

          coordinate[index++]=temp_x+temp_y;

          matrix[row][col] = letter;
          row =0;
          col =0;
          letter++;
          if(matrix[row][col] == letter)
          {
            stringstream ss1, ss2;
            string temp_x, temp_y;
            ss1<<row;
            ss2<<col;
            temp_x = ss1.str();
            temp_y = ss2.str();

            coordinate[index++]=temp_x+temp_y;

            row=0;
            col=0;
            letter++;
          }
        }
      }
    }


  for(int i = 0; i < 25;i++)
    {
      cout <<coordinate[i] << " ";
    }
    cout<< endl;

    //print matrix
    for(int row = 0; row < 5 ; row++)
    {
      for(int col =0; col < 5; col++)
      {
        cout<< matrix[row][col];
      }
      cout << endl;
    }

    cout<<endl;

    //cout << "At end of setkey" << endl;

    return true;
  }

  ///////////////////////////////////////////////////////////////
  string PlayfairCipher::encrypt(const string& plaintext)
  {
    //cout << "starting encrypt" << endl;
    string input = plaintext;
    string output;
    int index = 0;
    while(index < input.length())
    {
      //cout << "001" << endl;
      //break input into letters pair
      char letter1, letter2,x,y;
      int x1,x2,y1,y2,letter1Index,letter2Index;
      string letter1Coordinate, letter2Coordinate;
      letter1 = input.at(index++);
      if(index != input.length())
      {
        letter2 = input.at(index++);
      }
      else
      {
        letter2 = 'x';
      }
    
      //cout << "002" << endl;
      //if letter = i change it to j
      if(letter1 =='i')
      {
       letter1 = 'j';
      }
      if(letter2 == 'i')
      {
       letter2 ='j';
      }

      //cout << "003" << endl;
      //check for same consecutive letters
      if(letter1 == letter2)
      {
        letter2 = 'x';
        index--;
      }

      cout<< letter1<< "\t" <<letter2<<endl;
      //cout << "004" << endl;
      //convert letter into indexes
      letter1Index = (int)letter1 - 97;
      letter2Index = (int)letter2 - 97;

      if(letter1Index > 8)
      {
        letter1Index--;
      }
      if(letter2Index > 8)
      {
        letter2Index--;
      }
      cout << letter1Index << "\t" << letter2Index << endl;
      //cout << "005" << endl;
      //get coordinate pair from array
      letter1Coordinate = coordinate[letter1Index];
      letter2Coordinate = coordinate[letter2Index];

      cout << letter1Coordinate << "\t" << letter2Coordinate << endl;
      //break coordinate pair into x,y
    
      x = letter1Coordinate.at(0);
      y = letter1Coordinate.at(1);

      x1 = (int)x-48;
      y1 = (int)y-48;

      x = letter2Coordinate.at(0);
      y = letter2Coordinate.at(1);

      x2 = (int)x-48;
      y2 = (int)y-48;

      cout << x1 << "," << y1 << "\t" << x2 << "," << y2 << endl;  

      //cout << "006" << endl;
      //////////////////////////////////////////////////////////////////
      //encrypt
      //check if letter pair is on the same row
      if(x1 == x2)
      {
        y1+=1;
        y2+=1;
        if(y1 > 4)
        {
          y1 =0;
        }
        if(y2 > 4)
        {
          y2 =0;
        }
        output += matrix[x1][y1];
        output += matrix[x2][y2];
      }

      //check if letter pair  is on the same col
      else if(y1 == y2)
      {
        //cout << "007" << endl;
        x1+=1;
        x2+=1;

        if(x1 > 4)
        {
          x1 = 0;
        }
        if(x2 > 4)
        {
          x2 = 0;
        }
        output += matrix[x1][y1];
        output += matrix[x2][y2];
      }
      else
      {
        output += matrix[x1][y2];
        output += matrix[x2][y1];
      }
      }
      //cout << "008" << endl;
    return output;
  }

  string PlayfairCipher::decrypt(const string& plaintext)
  {
    string input = plaintext;
    string output;
    int index = 0;
    while(index < input.length())
    {
      //break input into letters pair
      char letter1, letter2,x,y;
      int x1,x2,y1,y2,letter1Index,letter2Index;
      string letter1Coordinate, letter2Coordinate;
      letter1 = input.at(index++);
      if(index != input.length())
      {
        letter2 = input.at(index++);
      }
      else
      {
        letter2 = 'x';
      }
    

      //if letter = i change it to j
      if(letter1 =='i')
      {
        letter1 = 'j';
      }
      if(letter2 == 'i')
      {
        letter2 ='j';
      }

      
      //check for same consecutive letters
      if(letter1 == letter2)
      {
        letter2 = 'x';
        index--;
      }

      //cout<< letter1<< "\t" <<letter2<<endl;

      //convert letter into indexes
      letter1Index = (int)letter1 - 97;
      letter2Index = (int)letter2 - 97;

      if(letter1Index > 8)
      {
        letter1Index--;
      }
      if(letter2Index > 8)
      {
        letter2Index--;
      }
      //cout << letter1Index << "\t" << letter2Index << endl;
      
      //get coordinate pair from array
      letter1Coordinate = coordinate[letter1Index];
      letter2Coordinate = coordinate[letter2Index];

      //cout << letter1Coordinate << "\t" << letter2Coordinate << endl;
      //break coordinate pair into x,y
      
      x = letter1Coordinate.at(0);
      y = letter1Coordinate.at(1);

      x1 = (int)x-48;
      y1 = (int)y-48;

      x = letter2Coordinate.at(0);
      y = letter2Coordinate.at(1);

      x2 = (int)x-48;
      y2 = (int)y-48;

      //cout << x1 << "," << y1 << "\t" << x2 << "," << y2 << endl;  

      /////////////////////////////////////////////////////////////////
      //decrypt
      
        //check if letter pair is on the same row
      if(x1 == x2)
      {
        y1-=1;
        y2-=1;
        if(y1 < 0)
        {
          y1 =4;
        }
        if(y2 < 0)
        {
          y2 =4;
        }
        output += matrix[x1][y1];
        output += matrix[x2][y2];
      }

      //check if letter pair  is on the same col
      else if(y1 == y2)
      {
        x1-=1;
        x2-=1;

        if(x1 < 0)
        {
          x1 = 4;
        }
        if(x2 < 0)
        {
          x2 = 4;
        }
        output += matrix[x1][y1];
        output += matrix[x2][y2];
      }
      else
      {
        output += matrix[x1][y2];
        output += matrix[x2][y1];
      }
      
    } 
    return output;
  }
