# 452-Cryptography-Assignment-1
Spring 2020

– Names and email addresses of all partners.

Michael Rozsypal mrozsypal@csu.fullerton.edu
Ethan Letrong letronge@csu.fullerton.edu
Lily Tran derpyhooves@csu.fullerton.edu
Jin Nguyen jwin@csu.fullerton.edu

– The programming language you use (e.g. C++, Java, Python)

Language used C++

– How to execute your program.

type in make without quotes
then use 
Your program shall be called cipher and shall be executed as:
./cipher <CIPHER NAME> <KEY> <ENC/DEC> <INPUTFILE> <OUTPUT FILE>
where
• CIPHER NAME: Is the name of the cipher. Valid names are:
– PLF: Playfair
– RTS: Row Transposition
– RFC: Railfence
– VIG: Vigenre
– CES: Caesar
– MAC: Monoalphabetic Cipher (graduate students only)
• KEY: the encryption key to use.
1
• ENC/DEC: whether to encrypt or decrypt, respectively.
• INPUT FILE: the file from which to read the input.
• OUTPUT FILE: the file to which the output shall be written.

– Whether you implemented the extra credit.

No extra credit

– Anything special about your submission that we should take note of.

The Playfair cipher may cause a seg fault out of bounds error if run with large amounts of text but if the process
is run multiple times it will produce the correct output

- Individual Contributions

Michael- did the Vigenere Cipher and the cipher.cpp (which involved converting the playfair cipher into a form that could be used by cipher, and helping to debug all other ciphers)

Ethan- wrote the original Playfair Cipher in java and made another version of it in C++ that we did not end up using

Lily- wrote the Row Transposition Cipher and tried to help write the Playfair cipher a bit

Jin- wrote the Caesar Cipher, Railfence Cipher, and wrote a Playfair Cipher that we used for the final submit
