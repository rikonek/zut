# przyklad uzycia prostego Makefile do ulatwienia i przyspieszenia procesu kompilacji

# Makefile sklada sie z zestawu regul w formie
# cel: zaleznosci
#	polecenia potrzebne do stworzenia cel

# cel - moze byc oczekiwanym plikiem lub stanem
# zaleznosci - moga byc plikiem lub stanem
# polecenia - lista polecen - jedno w kazdej linii. Przed kazdym poleceniem musi byc jeden lub wiecej znakow TAB

# ustawiam kompilator
#cc = gcc
cc = ~/embedded_C/buildroot-build/host/usr/bin/i586-buildroot-linux-uclibc-gcc


# pierwsza regula w pliku Makefile zostanie uruchomiona. Jezeli ma jakies zaleznosci to zostana one spelnione jako pierwsze
all: p3

# zbuduj plik sample_lib.o z pliku sample_lib.c
# komenda gcc zostanie uruchomiona jezeli plik sample_lib.o nie istnieje lub jest starszy niz plik sample_lib.c
p3_lib.o: p3_lib.c
	$(cc) -c -o p3_lib.o p3_lib.c

p3.o: p3.c
	$(cc) -c -o p3.o p3.c

# zbuduj plik p3 wykorzystujac pliki p3.o i sample_lib.o
p3: p3.o p3_lib.o
	$(cc) -o p3 p3.o p3_lib.o

# calosc budujemy poleceniem make

# Zadanie: zmodyfikuj Makefile tak aby mozliwa byla cross compilacja
