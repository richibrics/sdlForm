make re-run:
	g++ main.cpp forms.cpp -W -o out -l SDL2 -l SDL2_ttf -g -lm
	./out
debug:
	g++ main.cpp forms.cpp -W -o out -l SDL2 -l SDL2_ttf -g -lm
	gdb out
release:
	g++ main.cpp forms.cpp -W -o out -l SDL2 -l SDL2_ttf -lm
run:
	./out
