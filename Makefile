default : it
load :
	echo '#!/bin/sh' > load
	echo 'main="$$1"; shift' >> load
	echo 'exec cc -o "$$main" "$$main".o $${1+"$$@"}' >> load
	chmod +x load
compile :
	echo '#!/bin/sh' > compile
	echo 'exec cc -c $${1+"$$@"}' >> compile
	chmod +x compile
crypto-box : load crypto-box.o alloc.o alloc_re.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o buffer_put.o buffer_write.o byte_copy.o byte_copyr.o crypto_str_box_afternm.o crypto_str_box_beforenm.o devurandom.o env.o error.o error_str.o fmt_uint.o fmt_ulong.o netstring_write.o open_read.o openreadclose.o readchunk.o readclose.o str_len.o str_start.o stralloc_copyb.o stralloc_copys.o stralloc_ready.o strerr_die.o strerr_sys.o surf.o 
	./load crypto-box alloc.o alloc_re.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o buffer_put.o buffer_write.o byte_copy.o byte_copyr.o crypto_str_box_afternm.o crypto_str_box_beforenm.o devurandom.o env.o error.o error_str.o fmt_uint.o fmt_ulong.o netstring_write.o open_read.o openreadclose.o readchunk.o readclose.o str_len.o str_start.o stralloc_copyb.o stralloc_copys.o stralloc_ready.o strerr_die.o strerr_sys.o surf.o -lnacl
crypto-secretbox : load crypto-secretbox.o alloc.o alloc_re.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o buffer_put.o buffer_write.o byte_copy.o byte_copyr.o crypto_str_box_afternm.o crypto_str_box_beforenm.o crypto_str_secretbox.o devurandom.o env.o error.o error_str.o fmt_uint.o fmt_ulong.o netstring_write.o open_read.o openreadclose.o readchunk.o readclose.o str_len.o str_start.o stralloc_copyb.o stralloc_copys.o stralloc_ready.o strerr_die.o strerr_sys.o surf.o
	./load crypto-secretbox alloc.o alloc_re.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o buffer_put.o buffer_write.o byte_copy.o byte_copyr.o crypto_str_box_afternm.o crypto_str_box_beforenm.o crypto_str_secretbox.o devurandom.o env.o error.o error_str.o fmt_uint.o fmt_ulong.o netstring_write.o open_read.o openreadclose.o readchunk.o readclose.o str_len.o str_start.o stralloc_copyb.o stralloc_copys.o stralloc_ready.o strerr_die.o strerr_sys.o surf.o -lnacl
crypto-box-open : load crypto-box-open.o alloc.o alloc_re.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o buffer_put.o buffer_write.o byte_copy.o byte_copyr.o crypto_str_box_beforenm.o crypto_str_box_open_afternm.o devurandom.o env.o error.o error_str.o netstring_read.o open_read.o openreadclose.o readchunk.o readclose.o scan_ulong.o str_len.o str_start.o stralloc_catb.o stralloc_copyb.o stralloc_copys.o stralloc_ready.o strerr_die.o strerr_sys.o surf.o 
	./load crypto-box-open alloc.o alloc_re.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o buffer_put.o buffer_write.o byte_copy.o byte_copyr.o crypto_str_box_beforenm.o crypto_str_box_open_afternm.o devurandom.o env.o error.o error_str.o netstring_read.o open_read.o openreadclose.o readchunk.o readclose.o scan_ulong.o str_len.o str_start.o stralloc_catb.o stralloc_copyb.o stralloc_copys.o stralloc_ready.o strerr_die.o strerr_sys.o surf.o -lnacl
alloc.o : compile alloc.c
	./compile alloc.c
alloc_re.o : compile alloc_re.c
	./compile alloc_re.c
buffer_0.o : compile buffer_0.c
	./compile buffer_0.c
buffer_1.o : compile buffer_1.c
	./compile buffer_1.c
buffer_2.o : compile buffer_2.c
	./compile buffer_2.c
buffer_get.o : compile buffer_get.c
	./compile buffer_get.c
buffer_put.o : compile buffer_put.c
	./compile buffer_put.c
buffer_write.o : compile buffer_write.c
	./compile buffer_write.c
byte_copy.o : compile byte_copy.c
	./compile byte_copy.c
byte_copyr.o : compile byte_copyr.c
	./compile byte_copyr.c
crypto-box.o : compile crypto-box.c
	./compile crypto-box.c
crypto-box-open.o : compile crypto-box-open.c
	./compile crypto-box-open.c
crypto-secretbox.o : compile crypto-secretbox.c
	./compile crypto-secretbox.c
crypto_str_box_afternm.o : compile crypto_str_box_afternm.c
	./compile crypto_str_box_afternm.c
crypto_str_box_beforenm.o : compile crypto_str_box_beforenm.c
	./compile crypto_str_box_beforenm.c
crypto_str_box_open_afternm.o : compile crypto_str_box_open_afternm.c
	./compile crypto_str_box_open_afternm.c
crypto_str_secretbox.o : compile crypto_str_secretbox.c
	./compile crypto_str_secretbox.c
devurandom.o : compile devurandom.c
	./compile devurandom.c
env.o : compile env.c
	./compile env.c
error.o : compile error.c
	./compile error.c
error_str.o : compile error_str.c
	./compile error_str.c
fmt_uint.o : compile fmt_uint.c
	./compile fmt_uint.c
fmt_ulong.o : compile fmt_ulong.c
	./compile fmt_ulong.c
netstring_read.o : compile netstring_read.c
	./compile netstring_read.c
netstring_write.o : compile netstring_write.c
	./compile netstring_write.c
open_read.o : compile open_read.c
	./compile open_read.c
openreadclose.o : compile openreadclose.c
	./compile openreadclose.c
readchunk.o : compile readchunk.c
	./compile readchunk.c
readclose.o : compile readclose.c
	./compile readclose.c
scan_ulong.o : compile scan_ulong.c
	./compile scan_ulong.c
str_len.o : compile str_len.c
	./compile str_len.c
str_start.o : compile str_start.c
	./compile str_start.c
stralloc_catb.o : compile stralloc_catb.c
	./compile stralloc_catb.c
stralloc_copyb.o : compile stralloc_copyb.c
	./compile stralloc_copyb.c
stralloc_copys.o : compile stralloc_copys.c
	./compile stralloc_copys.c
stralloc_ready.o : compile stralloc_ready.c
	./compile stralloc_ready.c
strerr_die.o : compile strerr_die.c
	./compile strerr_die.c
strerr_sys.o : compile strerr_sys.c
	./compile strerr_sys.c
surf.o : compile surf.c
	./compile surf.c
it : crypto-box crypto-box-open crypto-secretbox
clean : 
	rm -f *.o crypto-box crypto-box-open crypto-secretbox
