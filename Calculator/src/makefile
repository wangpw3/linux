src = /home/wang/linux/jjcc/src
include = /home/wang/linux/jjcc/include
main:main.c libjjcc.a
	gcc $< -o $@ -ljjcc -L./ -I$(include)
libjjcc.a:jia.o jian.o cheng.o chu.o
	ar -rc $@ $^
%.o:%.c
	gcc -c $< -o $@ -I$(include)
clear:
	rm main *.o *.a
