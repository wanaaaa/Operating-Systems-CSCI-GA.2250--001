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

#include "0header.h"
#include "0parser.cpp"
#include "0pager2.cpp"
#include "0pager.cpp"

int main(int argc, char *argv[]) {
	string Mstr = argv[1];
	string Pstr = argv[2];
	string Sstr = argv[3];
	string Jstr = argv[4];
	string Nstr = argv[5];
	algorithm = argv[6];
	//debugStr = argv[7];

	MachineSize = atoi(Mstr.c_str());
	PageSize = atoi(Pstr.c_str());
	ProcessSize = atoi(Sstr.c_str());
	JobMix = atoi(Jstr.c_str());
	NumReferenceProcess = atoi(Nstr.c_str());

	parser();
	initializeNums();
	pager();

	Process cProcess;
	int residencyInt , processTotalResidency ,processEvictNum ;
	double processAverResidency;
	int totalFault = 0;
	int totalResidency = 0;
	int totalEvitNum = 0;

	for(int i = 0; i < processVec.size();i++) {//process
		cProcess = processVec[i];
		cout<<"Process "<<cProcess.processNum<<" had "<<cProcess.pageFault<<" faults";
		processTotalResidency = 0;
		processEvictNum = 0;
		processAverResidency = 0;

		totalFault += cProcess.pageFault;
		
		TimeVecStu lStu, eStu;
		for(int j= 0; j <= cProcess.maxPage; j++) {//page
			lStu = cProcess.loadedTStu[j];
			eStu = cProcess.evictedTStu[j];

			///////////////
			for(int k = 0; k < eStu.timeVec.size(); k ++) {
				residencyInt = eStu.timeVec[k] - lStu.timeVec[k];
				processTotalResidency += residencyInt;
				processEvictNum ++;
				
				totalResidency += residencyInt;
				totalEvitNum ++;
			}
		}

		processAverResidency = (double) processTotalResidency / (double) processEvictNum;

		if(processEvictNum == 0) {
			cout<<".\n     With no evictions, the average residence is undefined."<<endl;
		} else {
			cout<<" and "<<convertProcessDoubleToStr(processTotalResidency, processEvictNum, -1) 
			<<" average residency."<<endl;
		}
	}//end of for

	cout<<" "<<endl;
	double averResidency;

	if(totalEvitNum > 0)
		averResidency = (double) totalResidency / (double) totalEvitNum;

	cout<<"The total number of faults is "<<totalFault;

	if(totalEvitNum > 0) {
		cout<<" and the overall average residency is ";
		cout<<convertDoubleToStr(totalResidency, totalEvitNum, -1)<<"."<<endl;
	} else {
		cout<<".\n     With no evictions, the overall average residence is undefined."<<endl;
	}

	return 0;
}
