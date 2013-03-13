CC=gcc
CFLAGS=-Wall -std=c99 -O2 -g -fPIC
PKGCONFIG=pkg-config
LIBS=$(shell $(PKGCONFIG) libnautilus-extension --libs)
INCS=$(shell $(PKGCONFIG) libnautilus-extension --cflags)

ndt: nautilus-extension-mtime.c
	$(CC) ${CFLAGS} -c nautilus-extension-mtime.c -o nautilus-extension-mtime.o ${INCS}
	$(CC) -shared nautilus-extension-mtime.o -o nautilus-extension-mtime.so ${LIBS}

clean:
	rm -f *.o *.so
