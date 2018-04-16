mazeway:mazeway.c
	gcc $^ -o $@

.PHONY:clean
	clean:
		rm -f mazeway
