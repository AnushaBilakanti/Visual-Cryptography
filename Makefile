hw2: main.o key_stream.o encrypt.o merge.o decrypt.o 
	gcc -g main.o key_stream.o encrypt.o merge.o decrypt.o -o hw2 -L/home/scf-22/csci551b/openssl/lib -lcrypto -lm

main.o: main.c functions.h
	gcc  -c -g -Wall main.c -I/home/scf-22/csci551b/openssl/include

key_stream.o: key_stream.c functions.h
	gcc  -c -g -Wall key_stream.c -I/home/scf-22/csci551b/openssl/include

encrypt.o: encrypt.c functions.h
	gcc -c -g -Wall encrypt.c -I/home/scf-22/csci551b/openssl/include

merge.o: merge.c functions.h
	gcc -g -c -Wall merge.c -I/home/scf-22/csci551b/openssl/include

decrypt.o: decrypt.c functions.h
	gcc -g -c -Wall decrypt.c -I/home/scf-22/csci551b/openssl/include

clean:
	rm *.o
	rm hw2

