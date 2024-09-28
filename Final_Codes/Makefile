CC = gcc
CFLAGS = -Wall -Wextra -std=c11
LDFLAGS = -lallegro -lallegro_font -lallegro_ttf -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_primitives
SRCS = main.c game.c menu_scene.c bullet.c enemy.c player.c game_scene.c loading_scene.c map.c setting_scene.c UI.c utility.c weapon.c
OBJS = $(SRCS:.c=.o)
TARGET = game

all: $(TARGET)

$(TARGET): $(OBJS)
    $(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJS) $(TARGET)