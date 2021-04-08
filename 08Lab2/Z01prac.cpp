#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm> 

#include <fstream> 
#include <vector>
#include <cstdlib>
#include <list>
#include <queue>
#include <map>
#include <cmath>

using namespace std;

class TestC{
public:
	int a;
	int b;
	TestC(){
		a = -1;
		b= -1;
	}	
	
};

int main(int argc, char *argv[]) {
	TestC oneC;
	oneC.a = 777;
	TestC twoC;

	twoC.a = oneC.a;
	oneC.a = 11;

	cout<<" twoC.a = "<<twoC.a<<endl; 

	return 0;
}