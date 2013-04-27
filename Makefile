OUT=ldgame
OBJS=main.o game.o actor.o
CC=g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lBox2D
INC=

linux:$(OBJS)
	$(CC) -o $(OUT) $(OBJS) $(LIBS) $(FLG)

%.o:%.cpp %.hpp Makefile
	$(CC) $(FLG) $(INC) -c $< -o $@

clean:
	rm `find . -name '*o'`
	rm $(OUT)
