AM_CFLAGS = $(LWBASE_CFLAGS) -Wno-deprecated-declarations
AM_CPPFLAGS = $(LWBASE_CPPFLAGS) -I$(top_srcdir)/include
AM_LDFLAGS = $(LWBASE_LDFLAGS)

lib_LTLIBRARIES = liblwbase_nothr.la liblwbase.la

liblwbase_nothr_la_SOURCES = \
	error-conv.c \
	errno.c \
	ntstatus.c \
	dscache.c \
	rpcstatus.c \
        rtllog.c \
        rtlmemory.c \
        rtlstring.c \
        rtlstring_cstring.c \
        rtlstring_wc16string.c \
        rtlstring_unicode.c \
        rtlstring_ansi.c \
        rbtree.c \
        hash.c \
        security-sid.c \
        security-sddlmapping.c \
        security-sddl.c \
        security-acl.c \
        security-sd.c \
        security-privileges.c \
	wc16str.c \
	wc16printf.c

liblwbase_nothr_la_LIBADD = \
        @DS_FRAMEWORK_LDFLAGS@ \
        @LIBUUID_LIBS@ \
	@LIB_ICONV@

liblwbase_la_SOURCES = \
	atomic.c \
    security-token.c \
    security-sd-inherit.c \
	threadpool-common.c \
	mapsecurity.c \
	svcm.c

liblwbase_la_LIBADD = \
    @LIB_PTHREAD@ \
	@LIB_DL@ \
	@LIB_RT@ \
    liblwbase_nothr.la

if USE_EPOLL
liblwbase_la_SOURCES += threadpool-epoll.c
endif

if USE_KQUEUE
liblwbase_la_SOURCES += threadpool-kqueue.c
endif

if USE_POLL
liblwbase_la_SOURCES += threadpool-poll.c
endif

if USE_SELECT
liblwbase_la_SOURCES += threadpool-select.c
endif
