CC := clang
CFLAGS := -O2 -Wall -target bpf
OBJ := trace.o
DEV := eth0

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

all: $(OBJ)

clean:
	rm *.o
	sudo tc qdisc delete dev $(DEV) clsact

install: $(CLEAN)
	sudo tc qdisc add dev $(DEV) clsact
# sudo tc filter add dev $(DEV) ingress bpf da obj $(OBJ) sec ingress