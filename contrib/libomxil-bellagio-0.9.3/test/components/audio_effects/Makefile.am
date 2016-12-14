check_PROGRAMS = omxvolcontroltest omxaudiomixertest

bellagio_LDADD = -lomxil-bellagio
# M by jwf @{
common_CFLAGS = -I$(top_srcdir)/test/components/common -I$(includedir) -Wno-error=unused-but-set-variable
# M @}

omxvolcontroltest_SOURCES = omxvolcontroltest.c omxvolcontroltest.h
omxvolcontroltest_LDADD = $(bellagio_LDADD) -lpthread 
omxvolcontroltest_CFLAGS = $(common_CFLAGS)

omxaudiomixertest_SOURCES = omxaudiomixertest.c omxaudiomixertest.h
omxaudiomixertest_LDADD = $(bellagio_LDADD) -lpthread
omxaudiomixertest_CFLAGS = $(common_CFLAGS)
