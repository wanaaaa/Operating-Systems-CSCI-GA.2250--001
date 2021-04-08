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
#include <limits.h>

using namespace std;

#include "00header.h"
#include "05parser.cpp"
#include "30SCDfcfs.cpp"
#include "40SCDrrb.cpp"
#include "50SCDunipro.cpp"
#include "55psjfFuntion.cpp"
#include "60SCDpsjf.cpp"

void postStatistics(string algo, int verboseOn);

int main(int argc, char *argv[]) {
	int verboseOn = 0;
	int text = INT_MAX;
	if(argc > 2) verboseOn = 1;
	
	// if(argc == 2) parser(argv[1]); else if(argc > 2) parser(argv[2]);
	// schedulerFCFS();
	// postStatistics("First Come First Served", verboseOn);
	// printf("\n\n");
	// clearAll();
	
	// if(argc == 2) parser(argv[1]); else if(argc > 2) parser(argv[2]);
	// schedulerRRB();
	// postStatistics("Round Robbin", verboseOn);
	// printf("\n\n");
	// clearAll();

	// if(argc == 2) parser(argv[1]); else if(argc > 2) parser(argv[2]);
	// schedulerUnipro();
	// postStatistics("Uniprocessor", verboseOn);
	// printf("\n\n");
	// clearAll();

	if(argc == 2) parser(argv[1]); else if(argc > 2) parser(argv[2]);
	if(processVec.size() == 1) schedulerFCFS();
	else schedulerPSJD();
	postStatistics("shortest Job First", verboseOn);

	return 0;
}

void postStatistics(string algo, int verboseOn) {
	int cpuRunT = 0;
	int blockedT = 0;
	int blockedCycle = 0;


	printf("The original input was: %d  ", totalProcess );
	ProcessClass cPrc;
	for (int i = 0; i < originalPrcVec.size(); ++i) {
		cPrc = originalPrcVec[i]; 
		printf("%d %d %d %d  ", cPrc.A, cPrc.B, cPrc.C, cPrc.M );	
	}
	printf("\n");
	
	std::sort(originalPrcVec.begin(), originalPrcVec.end(), sortProcessVecFunByAsn);
	printf("The (sorted) input is:  %d  ", totalProcess );
	for (int i = 0; i < originalPrcVec.size(); ++i) {
		cPrc = originalPrcVec[i]; 
		printf("%d %d %d %d  ", cPrc.A, cPrc.B, cPrc.C, cPrc.M );	

		PrcResultClass prcResC;
		prcResultVec.push_back(prcResC);
	}
	printf("\n");


	int outCycle = 0;
	//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
	if(verboseOn) {
		printf("\nThis detailed printout gives the state and remaining burst for each process\n\n");
		printf("Before cycle %4d: ", outCycle);
	}
	

	int cPrcTime = -1;
	for(int i = 0; i < donePrcVec.size(); i++) {
		ProcessClass cPrc = donePrcVec[i];
		PrcResultClass * pPrcResC = & prcResultVec[cPrc.processNum];
		if(cPrc.cycleI > outCycle) {
			outCycle = cPrc.cycleI;			
			
			//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
			if(verboseOn) printf(".\nBefore cycle %4d: ", outCycle);
			
			if(blockedT > 0) {
				blockedCycle ++;
				blockedT = 0;
			}
			
		} 

		if(cPrc.state == "unstarted" || cPrc.state == "ready" || cPrc.state == "terminated") {
			cPrcTime = 0;
			if(cPrc.state == "ready") pPrcResC->waitTime ++;
		}
		if(cPrc.state == "running") {
			cPrcTime = cPrc.cpuBurst;
			if(cPrc.remainTime == 0) {
				pPrcResC->finishTime = cPrc.cycleI;
			}

			cpuRunT ++;
		}
		if(cPrc.state == "blocked") {
			cPrcTime = cPrc.IOburst + 1;
			pPrcResC->IOtime ++;
			blockedT ++;
		}
		//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
		if(verboseOn) printf("%11s %2d", cPrc.state.c_str(), cPrcTime );
		
	}
	if(verboseOn) printf(".");

	if(blockedT > 0) blockedCycle ++;

	printf("\nThe scheduling algorithm used was %s\n\n", algo.c_str() );

	PrcResultClass prcResC;
	int turnAroundT;
	float aveTurnAroundT = 0;
	float aveWaitT = 0;
	for(int i = 0; i < prcResultVec.size(); i++) {
		prcResC = prcResultVec[i];
		turnAroundT = prcResC.finishTime - donePrcVec[i].A;
		aveTurnAroundT += (float) turnAroundT;
		aveWaitT  += (float) prcResC.waitTime;

		///////////////////////////////////////////////////
		printf("Process %d:\n    (A,B,C,IO) = (%d,%d,%d,%d) \n", i, originalPrcVec[i].A, 
			originalPrcVec[i].B, originalPrcVec[i].C, originalPrcVec[i].M);
		printf("    Finishing time: %d \n", prcResC.finishTime );
		printf("    Turnsround time: %d \n", turnAroundT );
		printf("    I/O time: %d \n", prcResC.IOtime );
		printf("    Waiting time: %d \n\n", prcResC.waitTime );

	}
	
	///////////////////////////////////////////////////////////////////
	float cpuUtilization = (float) cpuRunT / (float) outCycle;
	float ioUtilization = (float) blockedCycle / (float) outCycle;
	//float test = (float) totalProcess * 100.0
	float throughPut = (float) totalProcess  / ((float) outCycle)  * 100;
	aveTurnAroundT = aveTurnAroundT / (float) totalProcess;
	aveWaitT = aveWaitT / (float) totalProcess;

	printf("Summary Data \n");
	printf("    Finishing time: %d \n", outCycle);
	printf("    CPU Utilization: %f \n", cpuUtilization);
	printf("    I/O Utilization: %f \n", ioUtilization);
	printf("    Throughput: %f processes per hundred cycles \n", throughPut);
	printf("    Average turnaround time: %.6f \n", aveTurnAroundT);
	printf("    Average waiting time: %.6f \n", aveWaitT);

}







































