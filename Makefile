all:	cipher

cipher:	cipher.o  RowTransposition.o vigenerecipher.o caesarcipher.o railfencecipher.o
	g++ cipher.o  RowTransposition.o vigenerecipher.o caesarcipher.o railfencecipher.o -o cipher

cipher.o:	cipher.cpp
	g++ -g -c cipher.cpp 

#Playfair.o:	Playfair.h CipherInterface.h
#	g++ -g -c Playfair.h

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
