SOURCE=myShell.cpp CmdVar.cpp Cmd.cpp Directory.cpp
OBJS=$(patsubst %.cpp, %.o, $(SOURCE))
CPPFLAGS=-ggdb3 -Wall -Werror -pedantic -std=gnu++98

myShell: $(OBJS)
	g++ $(CPPFLAGS) -o myShell $(OBJS)

%.o: %.cpp CmdVar.h Cmd.h Directory.h
	g++ $(CPPFLAGS) -c $<

clean:
	rm myShell *.o *~
