all:	cipher

cipher:	cipher.o  PlayfairCipher.o RowTransposition.o vigenerecipher.o caesarcipher.o railfencecipher.o 
	g++ cipher.o  PlayfairCipher.o RowTransposition.o vigenerecipher.o caesarcipher.o railfencecipher.o  -o cipher

cipher.o:	cipher.cpp
	g++ -g -c cipher.cpp 

PlayfairCipher.o:	PlayfairCipher.cpp PlayfairCipher.h CipherInterface.h
	g++ -g -c PlayfairCipher.cpp

RowTransposition.o:	RowTransposition.cpp RowTransposition.h CipherInterface.h
	g++ -g -c RowTransposition.cpp
	
Vigenerecipher.o: vigenerecipher.cpp vigenerecipher.h CipherInterface.h
	g++ -g -c vigenerecipher.cpp
	
Caesarcipher.o: caesarcipher.cpp caesarcipher.h CipherInterface.h
	g++ -g -c caesarcipher.cpp
	
Railfencecipher.o: railfencecipher.cpp railfencecipher.h CipherInterface.h
	g++ -g -c railfencecipher.cpp


clean:
	rm -rf *.o cipher
