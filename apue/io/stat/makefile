# 链接库
LDFLAGS+=-lcrypt
CFLAGS+=-D_XOPEN_SOURCE

# 目标:依赖
login:login.c
	# 规则 缩进tab gcc -o login login.c -lcrypt
	gcc -o $@ $^ $(LDFLAGS) $(CFLAGS)

test:
	echo "hello world"
