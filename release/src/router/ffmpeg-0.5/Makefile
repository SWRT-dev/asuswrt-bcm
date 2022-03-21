#
# Main ffmpeg Makefile
# (c) 2000-2004 Fabrice Bellard
#
include config.mak

SRC_DIR = $(SRC_PATH_BARE)

vpath %.texi $(SRC_PATH_BARE)

PROGS-$(CONFIG_FFMPEG)   += ffmpeg
PROGS-$(CONFIG_FFPLAY)   += ffplay
PROGS-$(CONFIG_FFSERVER) += ffserver

PROGS       = $(addsuffix   $(EXESUF), $(PROGS-yes))
PROGS_G     = $(addsuffix _g$(EXESUF), $(PROGS-yes))
PROGS_SRCS  = $(addsuffix .c,          $(PROGS-yes)) cmdutils.c
MANPAGES    = $(addprefix doc/, $(addsuffix .1, $(PROGS-yes)))

BASENAMES   = ffmpeg ffplay ffserver
ALLPROGS    = $(addsuffix   $(EXESUF), $(BASENAMES))
ALLPROGS_G  = $(addsuffix _g$(EXESUF), $(BASENAMES))
ALLMANPAGES = $(addsuffix .1, $(BASENAMES))

FFLIBS-$(CONFIG_AVFILTER) += avfilter
FFLIBS-$(CONFIG_POSTPROC) += postproc
FFLIBS-$(CONFIG_SWSCALE)  += swscale

FFLIBS := avdevice avformat avcodec avutil

include common.mak

FF_LDFLAGS   := $(FFLDFLAGS)
FF_EXTRALIBS := $(FFEXTRALIBS)

S := $(BUILD_SHARED:yes=S)
DEP_LIBS := $(foreach L,$(FFLIBS),lib$(L)/$($(S)LIBPREF)$(L)$($(S)LIBSUF))

ALL_TARGETS-$(CONFIG_VHOOK) += videohook
ALL_TARGETS-$(BUILD_DOC)    += documentation

INSTALL_TARGETS-$(CONFIG_VHOOK) += install-vhook
ifneq ($(PROGS),)
INSTALL_TARGETS-yes             += install-progs
INSTALL_TARGETS-$(BUILD_DOC)    += install-man
endif
INSTALL_PROGS_TARGETS-$(BUILD_SHARED) = install-libs

all: $(DEP_LIBS) $(PROGS) $(ALL_TARGETS-yes)

$(PROGS): %$(EXESUF): %_g$(EXESUF)
	cp -p $< $@
	$(STRIP) $@

.depend: version.h $(PROGS_SRCS)

SUBDIR_VARS := OBJS ASM_OBJS CPP_OBJS FFLIBS CLEANFILES

define RESET
$(1) :=
$(1)-yes :=
endef

define DOSUBDIR
$(foreach V,$(SUBDIR_VARS),$(eval $(call RESET,$(V))))
SUBDIR := $(1)/
include $(1)/Makefile
endef

$(foreach D,$(FFLIBS),$(eval $(call DOSUBDIR,lib$(D))))

ffplay_g$(EXESUF): FF_EXTRALIBS += $(SDL_LIBS)
ffserver_g$(EXESUF): FF_LDFLAGS += $(FFSERVERLDFLAGS)

%_g$(EXESUF): %.o cmdutils.o $(DEP_LIBS)
	$(CC) $(FF_LDFLAGS) -o $@ $< cmdutils.o $(FF_EXTRALIBS)

SVN_ENTRIES = $(SRC_PATH_BARE)/.svn/entries
ifeq ($(wildcard $(SVN_ENTRIES)),$(SVN_ENTRIES))
version.h: $(SVN_ENTRIES)
endif

version.h:
	$(SRC_PATH)/version.sh $(SRC_PATH)

output_example$(EXESUF): output_example.o $(DEP_LIBS)
	$(CC) $(CFLAGS) $(FF_LDFLAGS) -o $@ $< $(FF_EXTRALIBS)

tools/%$(EXESUF): tools/%.c
	$(CC) $(CFLAGS) $(FF_LDFLAGS) -o $@ $< $(FF_EXTRALIBS)

ffplay.o .depend: CFLAGS += $(SDL_CFLAGS)

ffmpeg.o ffplay.o ffserver.o: version.h

VHOOKCFLAGS += $(filter-out -mdynamic-no-pic,$(CFLAGS))

BASEHOOKS = fish null watermark
ALLHOOKS = $(BASEHOOKS) drawtext imlib2 ppm
ALLHOOKS_SRCS = $(addprefix vhook/, $(addsuffix .c, $(ALLHOOKS)))

HOOKS-$(HAVE_FORK)      += ppm
HOOKS-$(HAVE_IMLIB2)    += imlib2
HOOKS-$(HAVE_FREETYPE2) += drawtext

HOOKS = $(addprefix vhook/, $(addsuffix $(SLIBSUF), $(BASEHOOKS) $(HOOKS-yes)))

VHOOKCFLAGS-$(HAVE_IMLIB2) += `imlib2-config --cflags`
LIBS_imlib2$(SLIBSUF)       = `imlib2-config --libs`

VHOOKCFLAGS-$(HAVE_FREETYPE2) += `freetype-config --cflags`
LIBS_drawtext$(SLIBSUF)        = `freetype-config --libs`

VHOOKCFLAGS += $(VHOOKCFLAGS-yes)

vhook/%.o: CFLAGS:=$(VHOOKCFLAGS)

# vhooks compile fine without libav*, but need them nonetheless.
videohook: $(DEP_LIBS) $(HOOKS)

vhook/%$(SLIBSUF): vhook/%.o
	$(CC) $(LDFLAGS) -o $@ $(VHOOKSHFLAGS) $< $(VHOOKLIBS) $(LIBS_$(@F))

.vhookdep: $(ALLHOOKS_SRCS) version.h
	$(VHOOK_DEPEND_CMD) > $@

depend dep: .vhookdep

documentation: $(addprefix doc/, ffmpeg-doc.html faq.html ffserver-doc.html \
                                 ffplay-doc.html general.html hooks.html \
                                 $(ALLMANPAGES))

doc/%.html: doc/%.texi
	texi2html -monolithic -number $<
	mv $(@F) $@

doc/%.pod: doc/%-doc.texi
	doc/texi2pod.pl $< $@

doc/%.1: doc/%.pod
	pod2man --section=1 --center=" " --release=" " $< > $@

install: $(INSTALL_TARGETS-yes)

install-progs: $(PROGS) $(INSTALL_PROGS_TARGETS-yes)
	install -d "$(BINDIR)"
	install -c -m 755 $(PROGS) "$(BINDIR)"

install-man: $(MANPAGES)
	install -d "$(MANDIR)/man1"
	install -m 644 $(MANPAGES) "$(MANDIR)/man1"

install-vhook: videohook
	install -d "$(SHLIBDIR)/vhook"
	install -m 755 $(HOOKS) "$(SHLIBDIR)/vhook"

uninstall: uninstall-progs uninstall-man uninstall-vhook

uninstall-progs:
	rm -f $(addprefix "$(BINDIR)/", $(ALLPROGS))

uninstall-man:
	rm -f $(addprefix "$(MANDIR)/man1/",$(ALLMANPAGES))

uninstall-vhook:
	rm -f $(addprefix "$(SHLIBDIR)/",$(ALLHOOKS_SRCS:.c=$(SLIBSUF)))
	-rmdir "$(SHLIBDIR)/vhook/"

clean::
	rm -f gmon.out TAGS $(ALLPROGS) $(ALLPROGS_G) \
	   output_example$(EXESUF)
	rm -f doc/*.html doc/*.pod doc/*.1
	rm -rf tests/vsynth1 tests/vsynth2 tests/data tests/asynth1.sw tests/*~
	rm -f $(addprefix tests/,$(addsuffix $(EXESUF),audiogen videogen rotozoom seek_test tiny_psnr))
	rm -f $(addprefix tools/,$(addsuffix $(EXESUF),cws2fws pktdumper qt-faststart trasher))
	rm -f vhook/*.o vhook/*~ vhook/*.so vhook/*.dylib vhook/*.dll

distclean::
	rm -f .vhookdep version.h config.* *.pc

# regression tests

fulltest test: codectest libavtest seektest

FFMPEG_REFFILE   = $(SRC_PATH)/tests/ffmpeg.regression.ref
FFSERVER_REFFILE = $(SRC_PATH)/tests/ffserver.regression.ref
LIBAV_REFFILE    = $(SRC_PATH)/tests/libav.regression.ref
ROTOZOOM_REFFILE = $(SRC_PATH)/tests/rotozoom.regression.ref
SEEK_REFFILE     = $(SRC_PATH)/tests/seek.regression.ref

CODEC_TESTS = $(addprefix regtest-,             \
        mpeg                                    \
        mpeg2                                   \
        mpeg2thread                             \
        msmpeg4v2                               \
        msmpeg4                                 \
        wmv1                                    \
        wmv2                                    \
        h261                                    \
        h263                                    \
        h263p                                   \
        mpeg4                                   \
        huffyuv                                 \
        rc                                      \
        mpeg4adv                                \
        mpeg4thread                             \
        error                                   \
        mpeg4nr                                 \
        mpeg1b                                  \
        mjpeg                                   \
        ljpeg                                   \
        jpegls                                  \
        rv10                                    \
        rv20                                    \
        asv1                                    \
        asv2                                    \
        flv                                     \
        ffv1                                    \
        snow                                    \
        snowll                                  \
        dv                                      \
        dv50                                    \
        svq1                                    \
        flashsv                                 \
        mp2                                     \
        ac3                                     \
        g726                                    \
        adpcm_ima_wav                           \
        adpcm_ima_qt                            \
        adpcm_ms                                \
        adpcm_yam                               \
        adpcm_swf                               \
        flac                                    \
        wma                                     \
    )

LAVF_TESTS = $(addprefix regtest-,              \
        avi                                     \
        asf                                     \
        rm                                      \
        mpg                                     \
        ts                                      \
        swf                                     \
        ffm                                     \
        flv_fmt                                 \
        mov                                     \
        dv_fmt                                  \
        gxf                                     \
        nut                                     \
        mkv                                     \
        pbmpipe                                 \
        pgmpipe                                 \
        ppmpipe                                 \
        gif                                     \
        yuv4mpeg                                \
        pgm                                     \
        ppm                                     \
        bmp                                     \
        tga                                     \
        tiff                                    \
        sgi                                     \
        jpg                                     \
        wav                                     \
        alaw                                    \
        mulaw                                   \
        au                                      \
        mmf                                     \
        aiff                                    \
        voc                                     \
        ogg                                     \
        pixfmt                                  \
    )

REGFILES = $(addprefix tests/data/,$(addsuffix .$(1),$(2:regtest-%=%)))

CODEC_ROTOZOOM = $(call REGFILES,rotozoom.regression,$(CODEC_TESTS))
CODEC_VSYNTH   = $(call REGFILES,vsynth.regression,$(CODEC_TESTS))

LAVF_REGFILES = $(call REGFILES,lavf.regression,$(LAVF_TESTS))

LAVF_REG     = tests/data/lavf.regression
ROTOZOOM_REG = tests/data/rotozoom.regression
VSYNTH_REG   = tests/data/vsynth.regression

codectest: $(VSYNTH_REG) $(ROTOZOOM_REG)
	diff -u -w $(FFMPEG_REFFILE)   $(VSYNTH_REG)
	diff -u -w $(ROTOZOOM_REFFILE) $(ROTOZOOM_REG)

libavtest: $(LAVF_REG)
	diff -u -w $(LIBAV_REFFILE) $(LAVF_REG)

$(VSYNTH_REG) $(ROTOZOOM_REG) $(LAVF_REG):
	cat $^ > $@

$(LAVF_REG):     $(LAVF_REGFILES)
$(ROTOZOOM_REG): $(CODEC_ROTOZOOM)
$(VSYNTH_REG):   $(CODEC_VSYNTH)

$(CODEC_VSYNTH) $(CODEC_ROTOZOOM): $(CODEC_TESTS)

$(LAVF_REGFILES): $(LAVF_TESTS)

$(CODEC_TESTS) $(LAVF_TESTS): regtest-ref

regtest-ref: ffmpeg$(EXESUF) tests/vsynth1/00.pgm tests/vsynth2/00.pgm tests/asynth1.sw

$(CODEC_TESTS) regtest-ref: tests/tiny_psnr$(EXESUF)
	$(SRC_PATH)/tests/regression.sh $@ vsynth   tests/vsynth1 a
	$(SRC_PATH)/tests/regression.sh $@ rotozoom tests/vsynth2 a

$(LAVF_TESTS):
	$(SRC_PATH)/tests/regression.sh $@ lavf tests/vsynth1 b

seektest: codectest libavtest tests/seek_test$(EXESUF)
	$(SRC_PATH)/tests/seek_test.sh $(SEEK_REFFILE)

test-server: ffserver$(EXESUF) tests/vsynth1/00.pgm tests/asynth1.sw
	@echo
	@echo "Unfortunately ffserver is broken and therefore its regression"
	@echo "test fails randomly. Treat the results accordingly."
	@echo
	$(SRC_PATH)/tests/server-regression.sh $(FFSERVER_REFFILE) $(SRC_PATH)/tests/test.conf

ifeq ($(CONFIG_SWSCALE),yes)
test-server codectest $(CODEC_TESTS) libavtest: swscale_error
swscale_error:
	@echo
	@echo "This regression test is incompatible with --enable-swscale."
	@echo
	@exit 1
endif

tests/vsynth1/00.pgm: tests/videogen$(EXESUF)
	mkdir -p tests/vsynth1
	$(BUILD_ROOT)/$< 'tests/vsynth1/'

tests/vsynth2/00.pgm: tests/rotozoom$(EXESUF)
	mkdir -p tests/vsynth2
	$(BUILD_ROOT)/$< 'tests/vsynth2/' $(SRC_PATH)/tests/lena.pnm

tests/asynth1.sw: tests/audiogen$(EXESUF)
	$(BUILD_ROOT)/$< $@

%$(EXESUF): %.c
	$(CC) $(FF_LDFLAGS) $(CFLAGS) -o $@ $<

tests/seek_test$(EXESUF): tests/seek_test.c $(DEP_LIBS)
	$(CC) $(FF_LDFLAGS) $(CFLAGS) -o $@ $< $(FF_EXTRALIBS)


.PHONY: lib videohook documentation TAGS
.PHONY: codectest libavtest seektest test-server fulltest test
.PHONY: $(CODEC_TESTS) $(LAVF_TESTS) regtest-ref swscale-error

-include .vhookdep
