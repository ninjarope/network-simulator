out.o: user_interface.o
			sudo g++ user_interface.o -o out -lsfml-graphics -lsfml-window -lsfml-system
user_interface.o: user_interface.c
									sudo g++ -c user_interface.c
clean:
			sudo rm user_interface.o out
