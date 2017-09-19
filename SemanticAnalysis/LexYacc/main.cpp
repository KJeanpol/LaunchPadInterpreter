#include "y.tab.c"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
main(){
	if(yyparse()==0)
	printf("\nAnalisis Sintactico concluido sin errores\n");
}

int main (){
    string fileIN;
    string result;
	ifstream infile;
	infile.open ("test.txt");
    while(!infile.eof()) {
	    getline(infile,fileIN); 
	    result = result + fileIN;
	}
    cout<< result;
	infile.close();

	return 0;
}
