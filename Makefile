debug:
	gcc -Wall -Wextra -o rabarber main.c

release:
	gcc -Wall -Wextra -O2 -o rabarber main.c

run:
	./rabarber $(FILE)
