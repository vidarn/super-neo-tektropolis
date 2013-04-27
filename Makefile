OUT=ldgame
OBJS=main.o game.o actor.o level.o obstacle.o player.o common.o
CC=g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lBox2D
INC=
FLG= -g

linux:$(OBJS)
	$(CC) -o $(OUT) $(OBJS) $(LIBS) $(FLG)

%.o:%.cpp %.hpp Makefile common.hpp
	$(CC) $(FLG) $(INC) -c $< -o $@

clean:
	rm `find . -name '*.o'`
	rm $(OUT)
