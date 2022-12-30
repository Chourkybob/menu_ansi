
all:
	gcc -o serialCom main.c -lncurses

clean:
	rm serialCom