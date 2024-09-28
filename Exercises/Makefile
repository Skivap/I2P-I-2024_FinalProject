.PHONY: clean

CC=gcc
SRC=Src
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	CCFLAGS=$$(pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_image-5 allegro_primitives-5 allegro_acodec-5 --libs --cflags)
	INCLUDE=/usr/include/allegro5
endif
ifeq ($(UNAME_S), Darwin)
	CCFLAGS=$$(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_image-5 allegro_primitives-5 allegro_acodec-5 --libs --cflags)
	INCLUDE=/opt/homebrew/Cellar/allegro/5.2.9.0/include
endif
#REVISE INCLUDE path if you have installed different version or install path.

DBG = -g -fsanitize=address
WARNINGS = -Wall -Wextra # add `$(WARNINGS)`  compile flag in line 26 and 29 if you want additional compile check warnings
target = 01_Create_Window.out 01_Create_Window_Answer.out 02_Image_and_Text.out 02_Image_and_Text_Answer.out 03_Event_Loop.out 03_Event_Loop_Answer.out 04_Keyboard.out 04_Keyboard_Answer.out 05_Mouse.out 05_Mouse_Answer.out

all: $(target)

%.out: %.c
	$(CC) -lm -I$(INCLUDE) $(CCFLAGS) $(DBG) $< -o $@

clean:
	rm $(target)
