CXXFLAGS+=-fPIC

SRCS=AddonCallbacksPlayer.cpp \
     PlayerCB_AddonPlayList.cpp \
     PlayerCB_AddonPlayer.cpp \
     PlayerCB_InfoTagMusic.cpp \
     PlayerCB_InfoTagVideo.cpp \

LIB=addon-callbacks-player.a

include /home/alwin/Mupel/build/kodi-AlwinEsch/kodi-linux-x86_64/Makefile.include
-include $(patsubst %.cpp,%.P,$(patsubst %.c,%.P,$(SRCS)))
