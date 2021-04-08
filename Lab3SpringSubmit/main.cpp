#include <iostream>
#include <string>
#include <sstream>
#include <algorithm> 
#include <fstream> 
#include <vector>
#include <cstdlib>
#include <cmath>
using namespace std;

#include "header.h"
#include "parser.cpp"
#include "optimisticAlgorithm.cpp"
#include "bankerAlgorithm.cpp"

int main(int argc, char *argv[]) {
	//<-Call optimstics algorithm
	//string algorithm = argv[1];
	parser(argv[1]);
	executeOptimistic();
	int infoVecLen = outPutInfoFifoVec.size();//->

	//<-Call banker algorithm
	clearAll();
	parser(argv[1]);
	executeBanker();//->

	//<--Do statistics to get Table and print the tables from processed Tasks
	OutputInfo cInfo, bInfo;
	float percenWaitT;	float percenWaitBT;
	int totalTakenT = 0;	int totalTakenBT = 0;
	int totalWaitT = 0;	int totalWaitBT = 0;

	for(int i = 0; i < bankerErrMessVec.size(); i++ ) 
		cout<<bankerErrMessVec[i]<<endl;
	
	cout<<"             FIFO                         BANKER'S"<<endl;
	for(int i = 1; i < infoVecLen; i++) {
		cInfo = outPutInfoFifoVec[i];
		bInfo = outPutInfoBankVec[i];
		
		cout<<"     Task "<<i; 
		//<-Calculating time taken, the waiting time, and the percentage of time spent waiting for FIFO
			//For FIFO
		if(cInfo.timeTaken != -777) {
			percenWaitT = (float) cInfo.waitTime/ cInfo.timeTaken * 100;
			totalTakenT += cInfo.timeTaken;
			totalWaitT += cInfo.waitTime;
			
			cout.width(6); cout<<std::right<<cInfo.timeTaken;
			cout.width(5); cout<<std::right<<cInfo.waitTime;
			cout.width(5); cout<<std::right<<round(percenWaitT)<<"%";			
		} else cout<<"     aborted     ";
		
		cout<<"        "<<"Task "<<i;
			//For Banker
		if(bInfo.timeTaken != -777) {
			percenWaitBT = (float) bInfo.waitTime/ bInfo.timeTaken * 100;
			totalTakenBT += bInfo.timeTaken;
			totalWaitBT += bInfo.waitTime;
			
			cout.width(6); cout<<std::right<<bInfo.timeTaken;
			cout.width(5); cout<<std::right<<bInfo.waitTime; 
			cout.width(5);cout<<std::right<<round(percenWaitBT)<<"%"<<endl; 			
		} else cout<<"     aborted"<<endl;//->		
	}

	//<-Calculating the total waiting time, and the overall percentage of time spent waiting
	cout<<"     total"; cout.width(7); cout<<std::right<<totalTakenT;
	cout.width(5); cout<<std::right<<totalWaitT;
	cout.width(5); cout<<std::right<<round( (float) totalWaitT/(float)totalTakenT*100)<<"%"
	
	<<"        "<<"total"; cout.width(7); cout<<std::right<<totalTakenBT;
	cout.width(5); cout<<std::right<<totalWaitBT;
	cout.width(5); cout<<std::right<<round( (float) totalWaitBT/(float)totalTakenBT*100)<<"%"<<endl;
	//-> //-->
	
	return 0;
}

