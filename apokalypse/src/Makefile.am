
SUBDIRS = libcpputil

bin_PROGRAMS = apokalypse

apokalypse_DEPENDENCIES = $(top_srcdir)/src/libcpputil/libcpputil.a

apokalypse_LDADD = $(top_srcdir)/src/libcpputil/libcpputil.a $(IMAGE_LIBS) $(TTF_LIBS) $(SOUND_LIBS)

apokalypse_SOURCES =       \
	main.cpp \
	cacheable.h cacheable.cpp \
	logging.h logging.cpp \
	resourcecache.h \
	status.h status.cpp \
	TextString.h \
	apokalypseapp.h apokalypseapp.cpp \
	screen.h screen.cpp \
	sdl_utils.h sdl_utils.cpp \
	intro.h intro.cpp \
	font.h font.cpp \
	menuscreen.h menuscreen.cpp \
	sdl_window.h sdl_window.cpp \
	sdl_button.h sdl_button.cpp \
	sdl_panel.h sdl_panel.cpp \
	sdl_lineedit.h sdl_lineedit.cpp \
	sdl_label.h sdl_label.cpp






