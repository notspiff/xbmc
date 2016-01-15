.SUFFIXES : .mm

SRCS = SDLMain.mm

LIB=sdlmain.a

include /home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/Makefile.include
-include $(patsubst %.m,%.P,$(patsubst %.mm,%.P,$(patsubst %.cpp,%.P,$(patsubst %.c,%.P,$(SRCS)))))
