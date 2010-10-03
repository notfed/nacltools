NACL_LIB_DIR=/usr/lib/nacl
NACL_INCLUDE_DIR=/usr/include/nacl
it : crypto-box-keypair crypto-secretbox-key \
     crypto-box crypto-box-open \
     crypto-secretbox crypto-secretbox-open \
     nacl-key-decode nacl-key-encode 
install : it
	./install /usr/local/bin/ crypto-box-keypair crypto-secretbox-key crypto-box crypto-box-open crypto-secretbox crypto-secretbox-open nacl-key-decode nacl-key-encode 
	./install /usr/share/man/man1/ crypto-box-keypair.1 crypto-secretbox-key.1 crypto-box.1 crypto-box-open.1 crypto-secretbox.1 crypto-secretbox-open.1 
test : test-box test-secretbox
test-box : crypto-box crypto-box-open spk pk  
	echo 'testmessage' | ./crypto-box spk sk | ./crypto-box-open pk ssk
test-secretbox : crypto-secretbox crypto-secretbox-open spk pk
	echo 'testmessage' | ./crypto-secretbox sk | ./crypto-secretbox-open sk
longtest-box : crypto-box crypto-box-open spk pk zeros zerocheck
	./zeros | ./crypto-box spk sk | ./crypto-box-open pk ssk | ./zerocheck
longtest-secretbox : crypto-secretbox crypto-secretbox-open spk pk zeros zerocheck
	./zeros | ./crypto-secretbox sk | ./crypto-secretbox-open sk | ./zerocheck
zeros : zeros.o
	./load zeros
zerocheck : load zerocheck.o error.o strerr_die.o buffer_2.o buffer_put.o byte_copy.o byte_copyr.o str_len.o strerr_sys.o error_str.o buffer_write.o buffer_put.o
	./load zerocheck error.o strerr_die.o buffer_2.o buffer_put.o byte_copy.o byte_copyr.o str_len.o strerr_sys.o error_str.o buffer_write.o buffer_0.o buffer_1.o buffer_get.o
test-netstring : test-netstring-read test-netstring-write
	echo -n  'this is a test' | ./test-netstring-write
	echo -n  '&14:This is a test,' | ./test-netstring-read
test-base32 : nacl-key-encode nacl-key-decode enckey
	echo `cat enckey`
	echo `cat enckey | ./nacl-key-decode | ./nacl-key-encode`
test-readchunk : load test-readchunk.o readchunk.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o buffer_put.o error.o byte_copy.o byte_copyr.o str_len.o stralloc_copys.o stralloc_copyb.o stralloc_ready.o alloc.o alloc_re.o buffer_write.o
	./load test-readchunk readchunk.o buffer_0.o buffer_1.o buffer_get.o buffer_put.o error.o byte_copy.o byte_copyr.o str_len.o stralloc_copys.o stralloc_copyb.o stralloc_ready.o alloc.o alloc_re.o buffer_write.o
test-netstring-read : load test-netstring-read.o netstring_read.o strerr_die.o error_str.o strerr_sys.o buffer_put.o stralloc_num.o str_len.o stralloc_ready.o alloc.o alloc_re.o byte_copy.o error.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o scan_ulong.o stralloc_append.o byte_copyr.o buffer_write.o fmt_ulong.o stralloc_copys.o stralloc_copyb.o
	./load test-netstring-read netstring_read.o strerr_die.o error_str.o strerr_sys.o buffer_put.o stralloc_num.o str_len.o stralloc_ready.o alloc.o alloc_re.o byte_copy.o error.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o scan_ulong.o stralloc_append.o byte_copyr.o buffer_write.o fmt_ulong.o stralloc_copys.o stralloc_copyb.o
test-netstring-write : load test-netstring-write.o netstring_write.o buffer_put.o stralloc_num.o str_len.o stralloc_ready.o alloc.o alloc_re.o byte_copy.o error.o buffer_0.o buffer_1.o buffer_get.o scan_ulong.o stralloc_append.o byte_copyr.o buffer_write.o fmt_ulong.o fmt_uint.o
	./load test-netstring-write netstring_write.o buffer_put.o stralloc_num.o str_len.o stralloc_ready.o alloc.o alloc_re.o byte_copy.o error.o buffer_0.o buffer_1.o buffer_get.o scan_ulong.o stralloc_append.o byte_copyr.o buffer_write.o fmt_ulong.o fmt_uint.o
spk : nacl-key-decode
	echo -n 8mo307mdoobba2e4dpr22soh6nltoeekaj82pv75ovvncjfio91 | ./nacl-key-decode > spk
	echo -n qljm1vqkk4rcnbf1brmbajss0jfto7v4mj6aogj1hlo15js4lrf | ./nacl-key-decode > ssk
pk : crypto-box-keypair
	rm -f pk sk
	./crypto-box-keypair pk sk
enckey : pk nacl-key-encode
	cat pk | ./nacl-key-encode > enckey
crypto-secretbox-key : load crypto-secretbox-key.o buffer_2.o buffer_put.o byte_copy.o str_len.o error.o buffer_write.o open_excl.o error_str.o strerr_die.o strerr_sys.o $(NACL_LIB_DIR)/randombytes.o
	./load crypto-secretbox-key buffer_2.o buffer_put.o byte_copy.o str_len.o error.o buffer_write.o open_excl.o error_str.o strerr_die.o strerr_sys.o $(NACL_LIB_DIR)/randombytes.o
crypto-box-keypair : load crypto-box-keypair.o buffer_2.o buffer_put.o byte_copy.o str_len.o error.o buffer_write.o open_excl.o error_str.o strerr_die.o strerr_sys.o $(NACL_LIB_DIR)/libnacl.a $(NACL_LIB_DIR)/randombytes.o
	./load crypto-box-keypair buffer_2.o buffer_put.o byte_copy.o str_len.o error.o buffer_write.o open_excl.o error_str.o strerr_die.o strerr_sys.o $(NACL_LIB_DIR)/libnacl.a $(NACL_LIB_DIR)/randombytes.o
crypto-box : load crypto-box.o stralloc_copyb.o stralloc_cats.o stralloc_ready.o crypto_str_box_beforenm.o crypto_str_box_afternm.o byte_copy.o str_len.o stralloc_catb.o alloc.o alloc_re.o error.o buffer_put.o buffer_0.o buffer_1.o buffer_write.o buffer_puthex.o buffer_2.o readclose.o openreadclose.o open_read.o strerr_die.o error_str.o strerr_sys.o readchunk.o netstring_write.o fmt_uint.o fmt_ulong.o buffer_get.o byte_copyr.o stralloc_copys.o surf.o env.o str_start.o $(NACL_LIB_DIR)/libnacl.a $(NACL_LIB_DIR)/randombytes.o 
	./load crypto-box stralloc_copyb.o stralloc_cats.o stralloc_ready.o crypto_str_box_beforenm.o crypto_str_box_afternm.o byte_copy.o str_len.o stralloc_catb.o alloc.o alloc_re.o error.o buffer_put.o buffer_0.o buffer_1.o buffer_write.o buffer_puthex.o buffer_2.o readclose.o openreadclose.o open_read.o stralloc_copys.o strerr_die.o error_str.o strerr_sys.o readchunk.o netstring_write.o fmt_uint.o fmt_ulong.o buffer_get.o byte_copyr.o surf.o env.o str_start.o $(NACL_LIB_DIR)/libnacl.a $(NACL_LIB_DIR)/randombytes.o 
crypto-box-open : load crypto-box-open.o stralloc_copyb.o stralloc_cats.o stralloc_ready.o crypto_str_box_beforenm.o crypto_str_box_open_afternm.o byte_copy.o str_len.o stralloc_catb.o alloc.o alloc_re.o error.o buffer_put.o buffer_1.o buffer_0.o buffer_write.o buffer_puthex.o buffer_2.o readclose.o openreadclose.o open_read.o stralloc_copys.o error_str.o readchunk.o netstring_read.o strerr_die.o strerr_sys.o fmt_uint.o fmt_ulong.o buffer_get.o scan_ulong.o byte_copyr.o env.o str_start.o $(NACL_LIB_DIR)/libnacl.a 
	./load crypto-box-open stralloc_copyb.o stralloc_cats.o stralloc_ready.o crypto_str_box_beforenm.o crypto_str_box_open_afternm.o byte_copy.o str_len.o stralloc_catb.o alloc.o alloc_re.o error.o buffer_put.o buffer_1.o buffer_0.o buffer_write.o buffer_puthex.o buffer_2.o readclose.o openreadclose.o open_read.o stralloc_copys.o strerr_die.o error_str.o strerr_sys.o readchunk.o netstring_read.o fmt_uint.o fmt_ulong.o buffer_get.o scan_ulong.o byte_copyr.o env.o str_start.o $(NACL_LIB_DIR)/libnacl.a
crypto-secretbox-open : load crypto-secretbox-open.o stralloc_copyb.o stralloc_cats.o stralloc_ready.o byte_copy.o byte_copyr.o str_len.o stralloc_catb.o stralloc_copys.o alloc.o alloc_re.o error.o buffer_put.o buffer_1.o buffer_0.o buffer_write.o buffer_puthex.o buffer_2.o readclose.o openreadclose.o open_read.o error_str.o readchunk.o netstring_read.o strerr_die.o strerr_sys.o fmt_uint.o fmt_ulong.o buffer_get.o scan_ulong.o crypto_str_secretbox_open.o $(NACL_LIB_DIR)/libnacl.a 
	./load crypto-secretbox-open stralloc_copyb.o stralloc_cats.o stralloc_ready.o stralloc_catb.o stralloc_copys.o byte_copy.o str_len.o alloc.o alloc_re.o error.o error_str.o buffer_0.o buffer_1.o buffer_2.o buffer_get.o buffer_put.o buffer_write.o buffer_puthex.o readclose.o openreadclose.o open_read.o strerr_die.o strerr_sys.o readchunk.o netstring_read.o fmt_uint.o fmt_ulong.o scan_ulong.o byte_copyr.o crypto_str_secretbox_open.o $(NACL_LIB_DIR)/libnacl.a
crypto-secretbox : load crypto-secretbox.o stralloc_copyb.o stralloc_cats.o stralloc_ready.o stralloc_catb.o stralloc_copys.o byte_copy.o byte_copyr.o str_len.o alloc.o alloc_re.o error.o error_str.o buffer_0.o buffer_1.o buffer_2.o buffer_put.o buffer_get.o buffer_write.o buffer_puthex.o readclose.o openreadclose.o open_read.o strerr_die.o strerr_sys.o readchunk.o netstring_write.o fmt_uint.o fmt_ulong.o crypto_str_secretbox.o surf.o $(NACL_LIB_DIR)/libnacl.a $(NACL_LIB_DIR)/randombytes.o 
	./load crypto-secretbox stralloc_copyb.o stralloc_cats.o stralloc_ready.o crypto_str_secretbox.o byte_copy.o str_len.o stralloc_catb.o alloc.o alloc_re.o error.o buffer_put.o buffer_0.o buffer_1.o buffer_write.o buffer_puthex.o buffer_2.o readclose.o openreadclose.o open_read.o stralloc_copys.o strerr_die.o error_str.o strerr_sys.o readchunk.o netstring_write.o fmt_uint.o fmt_ulong.o buffer_get.o byte_copyr.o surf.o $(NACL_LIB_DIR)/libnacl.a $(NACL_LIB_DIR)/randombytes.o 
test-readchunk.o : compile test-readchunk.c
	./compile test-readchunk.c
zeros.o : zeros.c 
	./compile zeros.c
zerocheck.o : compile zerocheck.c 
	./compile zerocheck.c
crypto-secretbox.o : compile crypto-secretbox.c
	./compile crypto-secretbox.c -I$(NACL_INCLUDE_DIR)
crypto-secretbox-open.o : compile crypto-secretbox-open.c
	./compile crypto-secretbox-open.c -I$(NACL_INCLUDE_DIR)
crypto-box.o : compile crypto-box.c
	./compile crypto-box.c -I$(NACL_INCLUDE_DIR)
crypto-box-open.o : compile crypto-box-open.c
	./compile crypto-box-open.c -I$(NACL_INCLUDE_DIR)
crypto_str_secretbox.o : compile crypto_str_secretbox.c
	./compile crypto_str_secretbox.c -I$(NACL_INCLUDE_DIR)
crypto_str_secretbox_open.o : compile crypto_str_secretbox_open.c
	./compile crypto_str_secretbox_open.c -I$(NACL_INCLUDE_DIR)
crypto_str_box.o : compile crypto_str_box.c
	./compile crypto_str_box.c -I$(NACL_INCLUDE_DIR)
crypto_str_box_open.o : compile crypto_str_box_open.c
	./compile crypto_str_box_open.c -I$(NACL_INCLUDE_DIR)
crypto_str_box_beforenm.o : compile crypto_str_box_beforenm.c
	./compile crypto_str_box_beforenm.c -I$(NACL_INCLUDE_DIR)
crypto_str_box_afternm.o : compile crypto_str_box_afternm.c
	./compile crypto_str_box_afternm.c -I$(NACL_INCLUDE_DIR)
crypto_str_box_open_afternm.o : compile crypto_str_box_open_afternm.c
	./compile crypto_str_box_open_afternm.c -I$(NACL_INCLUDE_DIR)
nacl-key-encode : load nacl-key-encode.o base32_encode.o strerr_die.o strerr_sys.o buffer_2.o buffer_put.o buffer_write.o str_len.o byte_copy.o error.o error_str.o
	./load nacl-key-encode base32_encode.o strerr_die.o strerr_sys.o buffer_2.o buffer_put.o buffer_write.o str_len.o byte_copy.o error.o error_str.o
nacl-key-encode.o : compile nacl-key-encode.c
	./compile nacl-key-encode.c
nacl-key-decode : load nacl-key-decode.o base32_decode.o strerr_die.o strerr_sys.o buffer_2.o buffer_put.o buffer_write.o str_len.o byte_copy.o error.o error_str.o
	./load nacl-key-decode base32_decode.o strerr_die.o strerr_sys.o buffer_2.o buffer_put.o buffer_write.o str_len.o byte_copy.o error.o error_str.o
nacl-key-decode.o : compile nacl-key-decode.c
	./compile nacl-key-decode.c
crypto-secretbox-key.o : compile crypto-secretbox-key.c
	./compile crypto-secretbox-key.c -I$(NACL_INCLUDE_DIR)
crypto-box-keypair.o : compile crypto-box-keypair.c
	./compile crypto-box-keypair.c -I$(NACL_INCLUDE_DIR)
test-netstring-write.o : compile test-netstring-write.c
	./compile test-netstring-write.c 
buffer_0.o : compile buffer_0.c
	./compile buffer_0.c
buffer_1.o : compile buffer_1.c
	./compile buffer_1.c
buffer_2.o : compile buffer_2.c
	./compile buffer_2.c
buffer_6.o : compile buffer_6.c
	./compile buffer_6.c
buffer_7.o : compile buffer_7.c
	./compile buffer_7.c
buffer_put.o : compile buffer_put.c
	./compile buffer_put.c
buffer_get.o : compile buffer_get.c
	./compile buffer_get.c
buffer_write.o : compile buffer_write.c
	./compile buffer_write.c
buffer_puthex.o : compile buffer_puthex.c
	./compile buffer_puthex.c
stralloc_random.o : compile stralloc_random.c
	./compile stralloc_random.c -I$(NACL_INCLUDE_DIR)
stralloc_copyb.o : compile stralloc_copyb.c
	./compile stralloc_copyb.c
stralloc_copy.o : compile stralloc_copy.c
	./compile stralloc_copy.c
stralloc_copys.o : compile stralloc_copys.c
	./compile stralloc_copys.c
stralloc_ready.o : compile stralloc_ready.c
	./compile stralloc_ready.c
stralloc_cat.o : compile stralloc_cat.c
	./compile stralloc_cat.c
stralloc_cats.o : compile stralloc_cats.c
	./compile stralloc_cats.c
stralloc_catb.o : compile stralloc_catb.c
	./compile stralloc_catb.c
stralloc_num.o : compile stralloc_num.c
	./compile stralloc_num.c
stralloc_append.o : stralloc_append.c
	./compile stralloc_append.c
pathexec_env.o : compile pathexec_env.c
	./compile pathexec_env.c
pathexec_run.o : compile pathexec_run.c
	./compile pathexec_run.c
byte_copy.o : compile byte_copy.c
	./compile byte_copy.c
byte_copyr.o : compile byte_copyr.c
	./compile byte_copyr.c
byte_diff.o : compile byte_diff.c
	./compile byte_diff.c
str_start.o : compile str_start.c
	./compile str_start.c
str_len.o : compile str_len.c
	./compile str_len.c
str_chr.o : compile str_chr.c
	./compile str_chr.c
error.o : compile error.c
	./compile error.c
alloc.o : compile alloc.c
	./compile alloc.c
alloc_re.o : compile alloc_re.c
	./compile alloc_re.c
env.o : compile env.c
	./compile env.c
fmt_ulong.o : compile fmt_ulong.c
	./compile fmt_ulong.c
fmt_uint.o : compile fmt_uint.c
	./compile fmt_uint.c
netstring_read.o : compile netstring_read.c
	./compile netstring_read.c
netstring_write.o : compile netstring_write.c
	./compile netstring_write.c
open_excl.o : compile open_excl.c
	./compile open_excl.c
open_read.o : compile open_read.c
	./compile open_read.c
error_str.o : compile error_str.c
	./compile error_str.c
strerr_die.o : compile strerr_die.c
	./compile strerr_die.c
strerr_sys.o : compile strerr_sys.c
	./compile strerr_sys.c
openreadclose.o : compile openreadclose.c
	./compile openreadclose.c
readclose.o : compile readclose.c
	./compile readclose.c
readchunk.o : compile readchunk.c
	./compile readchunk.c
base32_decode.o : compile base32_decode.c
	./compile base32_decode.c
base32_encode.o : compile base32_encode.c
	./compile base32_encode.c
scan_ulong.o : compile scan_ulong.c
	./compile scan_ulong.c
taia_now.o : taia_now.c
	./compile taia_now.c
taia_add.o : taia_add.c
	./compile taia_add.c
taia_sub.o : taia_sub.c
	./compile taia_sub.c
taia_less.o : taia_less.c
	./compile taia_less.c
taia_approx.o : taia_approx.c
	./compile taia_approx.c
taia_frac.o : taia_frac.c
	./compile taia_frac.c
fd_copy.o : fd_copy.c
	./compile fd_copy.c
fd_move.o : fd_move.c
	./compile fd_move.c
surf.o : surf.c
	./compile surf.c -I$(NACL_INCLUDE_DIR)
clean :
	rm -f crypto-box-keypair crypto-secretbox-key sk pk test-netstring-read test-netstring-write nacl-key-encode nacl-key-decode enckey sk pk spk ssk crypto-box crypto-box-open crypto-secretbox crypto-secretbox-open zeros test-readchunk zerocheck *.o 
