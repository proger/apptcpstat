CC = clang
CFLAGS = -g -Wno-format -Isrc
LDFLAGS = -lssh2

test: test.o src/tcpinfo.o src/dumps.o src/carbonplain.c

src/dumps.c: src/tcpinfo.h
	python src/dumpstruct.py $< 'struct tcp_info' > $@

clean:
	rm -f src/*.o *.o src/dumps.c
