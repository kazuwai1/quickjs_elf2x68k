# ------------------------------------------------------------------------------
# QuickJS Makefile for X68000 (elf2x68k + newlib) - Atomic Linked Version
# ------------------------------------------------------------------------------

CROSS_COMPILE ?= m68k-xelf-

# ターゲット（X68k）用コンパイラ設定
CC       = $(CROSS_COMPILE)gcc
AR       = $(CROSS_COMPILE)ar

# ホスト（PC）用コンパイラ設定
HOST_CC  = gcc

# カレントディレクトリの絶対パスを取得（qjsc内部へ渡すため）
PWD      = $(shell pwd)

# ターゲット（X68k）用の共通フラグ
CFLAGS  = -Wall -Os -m68000 -fomit-frame-pointer
CFLAGS += -DCONFIG_VERSION=\"2026-06-04_x68k_r1\"
CFLAGS += -DCONFIG_SINGLE_TASK -DEMSCRIPTEN -D_GNU_SOURCE -DCONFIG_BIGNUM
CFLAGS += -include quickjs_x68k_stub.h
CFLAGS += -Wno-format -Wno-incompatible-pointer-types
CFLAGS += -Wno-unused-variable -Wno-unused-but-set-variable
CFLAGS += -I.

LDFLAGS = -lm

# ホスト（PC）用 qjsc のビルドフラグ
HOST_CFLAGS  = -Wall -O2 -D_GNU_SOURCE -DCONFIG_BIGNUM
HOST_CFLAGS += -DCONFIG_VERSION=\"2026-06-04_x68k_r1\"
HOST_CFLAGS += -DCONFIG_CC=\"$(CROSS_COMPILE)gcc\"
# ★ここが重要：qjsc内部で呼び出すm68k-xelf-gccに対し、
#   カレントディレクトリにある「m68000用libquickjs.a」を強制的に見に行かせます。
HOST_CFLAGS += -DCONFIG_LDFLAGS=\"-L$(PWD)\ -lquickjs\"
HOST_CFLAGS += -DCONFIG_PREFIX=\"/usr/local\"

# 出力ファイル名 (qjsはX68k用、qjscはホスト用、およびX68k用静的ライブラリ)
TARGET_X68  = qjs.x
TARGET_HOST = qjsc
LIB_TARGET  = libquickjs.a

# 静的ライブラリを構成する共通オブジェクト（X68kターゲット用 = mc68000用）
LIB_OBJS = quickjs.o libregexp.o libunicode.o cutils.o quickjs-libc.o repl.o dtoa.o quickjs_x68k_atomic.o

# ホスト（PC）用 qjsc をビルドするためのオブジェクト群
HOST_OBJS = qjsc.host.o quickjs.host.o libregexp.host.o libunicode.host.o cutils.host.o quickjs-libc.host.o repl.host.o dtoa.host.o

.PHONY: all clean prepare

# 1. すべてのターゲットとライブラリを生成
all: prepare $(LIB_TARGET) $(TARGET_X68) $(TARGET_HOST)

prepare:
	@touch dlfcn.h
	@mkdir -p sys
	@touch sys/termios.h
	@touch sys/ioctl.h

# 2. repl.c の自動生成
repl.c:
	@echo "#include <stdint.h>" > repl.c
	@echo "const unsigned char qjsc_repl[] = {0};" >> repl.c
	@echo "const uint32_t qjsc_repl_size = 0;" >> repl.c

# 3. ターゲット（X68k）用静的ライブラリ (libquickjs.a) のビルド
$(LIB_TARGET): $(LIB_OBJS)
	@echo "Creating X68k static library $@..."
	$(AR) rcs $@ $(LIB_OBJS)

# 4. X68k用 qjs.x の直接ビルド
$(TARGET_X68): qjs.o $(LIB_TARGET)
	@echo "Building qjs.x..."
	$(CC) $(CFLAGS) -o $@ qjs.o $(LIB_TARGET) $(LDFLAGS)

# 5. ホスト（PC）用 qjsc のビルド
$(TARGET_HOST): $(HOST_OBJS)
	@echo "Building host qjsc..."
	$(HOST_CC) $(HOST_CFLAGS) -o $@ $(HOST_OBJS) -lm

# 6. ターゲット（X68k）用オブジェクトのコンパイルルール
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

quickjs.o: quickjs.c quickjs.h cutils.h libregexp.h libunicode.h dtoa.h
quickjs-libc.o: quickjs-libc.c quickjs.h cutils.h
dtoa.o: dtoa.c dtoa.h cutils.h
qjs.o: qjs.c quickjs.h cutils.h
quickjs_x68k_atomic.o: quickjs_x68k_atomic.c

# 7. ホスト（PC）用オブジェクトのコンパイルルール (.host.o)
%.host.o: %.c
	$(HOST_CC) $(HOST_CFLAGS) -c -o $@ $<

qjsc.host.o: qjsc.c quickjs.h cutils.h
quickjs.host.o: quickjs.c quickjs.h cutils.h libregexp.h libunicode.h dtoa.h
quickjs-libc.host.o: quickjs-libc.c quickjs.h cutils.h
dtoa.host.o: dtoa.c dtoa.h cutils.h
libregexp.host.o: libregexp.c libregexp.h
libunicode.host.o: libunicode.c libunicode.h
cutils.host.o: cutils.c cutils.h
repl.host.o: repl.c

# 8. クリーンアップ
clean:
	rm -f *.o dlfcn.h repl.c $(LIB_TARGET) $(TARGET_X68) $(TARGET_HOST)
	rm -rf sys
	