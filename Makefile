parse:
	gcc -I /usr/include/libxml2 -L /usr/local/lib -lxml2 -Wall -g  parse.c -o parse
clean:
	rm parse
