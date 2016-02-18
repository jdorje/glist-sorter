all:
	gcc -std=c99 -g main.c sorted-list.c -o sl 
# also should have "a library called libsla"

doc:
	texi2pdf readme.tex

clean:
	rm main.o sorted-list.o sl libsla
