mazeway:mazeway.c
	gcc -g -o $@ $^

.PHONY:clean
	clean:
		rm -f mazeway
