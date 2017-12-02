CC=gcc
SRC=login.c
SO=liblogin.so

$(SO): $(SRC)
	$(CC) -fPIC -shared -o $(SO) $(SRC)

clean:
	rm -f $(SO)

