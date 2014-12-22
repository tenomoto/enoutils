CC = /usr/bin/clang
CPPFLAGS = -DNOVERBOSE -DSWAPENDIAN -I${HOME}/src/libeno
CFLAGS = -O2
LDFLAGS = -L${HOME}/src/libeno -leno
PROGS = slice yyyymmddhh eav

all : $(PROGS)

clean :
	rm $(PROGS) slice.tmp
