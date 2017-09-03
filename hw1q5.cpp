#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>
#include <sstream>
using namespace std;
int main(int argc, char const *argv[])
{    
	
	ifstream ifile;
	ifile.open(argv[1]);

	//getline(ifile,total_numb);
	
	string total_numb;
	int numb_words;
	
	getline(ifile,total_numb);

	stringstream ss(total_numb);
	ss>>numb_words;
    
	//numb_words = atoi(total_numb);

	char* input_sentence = new char[numb_words+1];
	//char* reverse_sentence = new char[numb_words];
	
	//getline(ifile, input_sentence);
	ifile.getline(input_sentence,numb_words+1);

	for (int i = 0; i <= numb_words+1; ++i)
	{
		cout<<input_sentence[numb_words+1 - i];
	}
    
     cout<<endl;

     delete[] input_sentence;
     //delete[] total_numb;

	return 0;
}
