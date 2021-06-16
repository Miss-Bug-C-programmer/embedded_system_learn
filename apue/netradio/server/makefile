
LDFLAGS+=-pthread
CFLAGS+=-I/home/emb0105/teacher/emb20210322/apue/netradio/proto
SRC=main.c medialib.c thrChnList.c

server:$(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LDFLAGS)

