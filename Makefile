Sudoku:Sudoku.o giveQuestion.o solve.o transform.o
	g++ -o Sudoku Sudoku.o giveQuestion.o solve.o transform.o

Sudoku.o:Sudoku.cpp Sudoku.h
	g++ -c Sudoku.cpp

giveQuestion.o:giveQuestion.cpp Sudoku.h
	g++ -c giveQuestion.cpp

solve.o:solve.cpp Sudoku.h
	g++ -c solve.cpp

transform.o:transform.cpp Sudoku.h
	g++ -c transform.cpp

clean:
	rm main*.o
