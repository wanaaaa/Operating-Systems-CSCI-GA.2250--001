ProcessClass convertToRun(ProcessClass cPrcC) ;
void convertToRunP(ProcessClass *cPrcC) ;
ProcessClass convertToBlocked(ProcessClass iPrcC) ;
int getNextRun();
int isThereRun();
//////////////////////////////////////////
void schedulerFCFS() {
	//cout<<" "<<endl<<endl;
	nextRun = 0;
	int qAllTerminated = totalProcess;

	// while (cycleI <= 16) {
	while(qAllTerminated) {
		// cout<<"===>cycleI = "<<cycleI<<endl;

		for(int inI = 0; inI < totalProcess; inI ++) {		
			ProcessClass cPrcC;
			cPrcC = processVec[0];
			cPrcC.SN = processSN;
			processVec.erase(processVec.begin());				

			cPrcC.cycleI = cycleI;			
			donePrcVec.push_back(cPrcC);
			///////////////
			// printProcess("->", cPrcC);
			///////////////
			if(cPrcC.state == "unstarted") {
				if(cPrcC.processNum == nextRun) {
					cPrcC = convertToRun(cPrcC);
				}
				else {
					if(cycleI >= cPrcC.A ) {
						cPrcC.state = "ready";
						cPrcC.turnToReayCycleI = cycleI;
					}
				}
			}
			else if(cPrcC.state == "running") {
				if(cPrcC.remainTime == 0) {
					cPrcC.state = "terminated";
					qAllTerminated --;
				}
				else if(cPrcC.cpuBurst == 1) {
					cPrcC = convertToBlocked(cPrcC);

				} 
				else {
					cPrcC.cpuBurst --;
					cPrcC.remainTime --;					
				}
			}
			else if(cPrcC.state == "blocked") {
				if(cPrcC.IOburst == 0) {
					cPrcC.state = "ready";
					cPrcC.turnToReayCycleI = cycleI;
				} else {
					cPrcC.IOburst --;					
				}
			}
			
			//System
			processVec.push_back(cPrcC);
		}//end of for
		//////////////////////////////////////////

		if(isThereRun() == 0) {
			nextRun = getNextRun();
			ProcessClass cPrcC;
			for(int i = 0; i < processVec.size(); i++) {
				cPrcC = processVec[i];
				if(cPrcC.state == "ready" && cPrcC.processNum == nextRun) {
					convertToRunP(& processVec[i]);
				}
			}
		}

		//System
		cycleI++;
		//cout<<""<<endl;

	}//end of while
}
///////////////////////////////////////////
int isThereRun() {
	int returnInt = 0;
	ProcessClass cPrcC;
	for(int i = 0; i < processVec.size(); i++) {
		cPrcC = processVec[i];
		if(cPrcC.state == "running") returnInt = 1;
	}
	return returnInt;
}
//--
int getNextRun() {
	int turneCycle = 2147483647;
	int processNum;
	ProcessClass cPrcC;
	for(int i = 0; i < processVec.size(); i++) {
		cPrcC = processVec[i];
		//printProcess("===>", cPrcC);
		if(cPrcC.state == "ready" && cPrcC.turnToReayCycleI < turneCycle) {
			turneCycle = cPrcC.turnToReayCycleI;
			processNum = cPrcC.processNum;
		}
	}
	return processNum;
}
//---

ProcessClass convertToBlocked(ProcessClass iPrcC) {
	iPrcC = iPrcC.newProcess(iPrcC);
	iPrcC.state = "blocked";
	iPrcC.IOburst = 1+ (randomVec[0] % iPrcC.M) -1;
	//cout<<"##### IOburst="<<iPrcC.IOburst<<" ran="<<randomVec[0]<<endl;
	randomVec.erase(randomVec.begin());

	return iPrcC;
}
//---
ProcessClass convertToRun(ProcessClass cPrcC) {

	int cBurst = 1 + (randomVec[0]) % cPrcC.B;
	//cout<<"@@@@@ cpuBurst ="<<cBurst<<" ran="<<randomVec[0] <<endl;
	randomVec.erase(randomVec.begin());

	
	cPrcC.state = "running";
	cPrcC.cpuBurst = cBurst;
	cPrcC.remainTime --;

	return cPrcC;
}
//---
void convertToRunP(ProcessClass *cPrcC) {

	//cout<<"@@@@@ cpuBurst PPP"<<" ran="<<randomVec[0] <<endl;

	int cBurst = 1 + (randomVec[0]) % cPrcC->B;
	randomVec.erase(randomVec.begin());

	cPrcC->state = "running";
	cPrcC->cpuBurst = cBurst;
	cPrcC->remainTime --;
}
/////////////////////////////////////////////