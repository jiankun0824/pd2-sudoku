class Sudoku
{
public:

	Sudoku();
	~Sudoku();
	
	void giveQuestion(); //no input /output 81 digits
	
	void readIn(); // input 81 digits / no output
	
	void solve(); // no input (use the one in 'readIn()')/out put your answer
	
	void changeNum(int a , int b); // no input / no output
	
	void changeRow(int a , int b); // no input / no output
	
	void changeCol(int a , int b); // no input / no output

	void rotate(int n); // no input / no output
	
	void flip(int n); // no input / no output
	
	void transform(); //no input(use the one in 'readIn()') output 81 digits

};