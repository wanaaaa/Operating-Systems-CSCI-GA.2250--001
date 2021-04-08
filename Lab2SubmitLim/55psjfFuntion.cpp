int nextRunFromBlockZeros() {
	int minRemainT = 2147483647;
	int processNum;
	ProcessClass bC, pC;
	for(int i = 0; i < blockZeroVec.size(); i++) {
		bC = blockZeroVec[i];
		pC = processVec[bC.processNum];
		if (pC.remainTime < minRemainT) {
			minRemainT = pC.remainTime;
			processNum = pC.processNum;
		}
	}
	return processNum;
}
//
void preemptRunToReady(){
	ProcessClass cPrcC;
	for(int i = 0; i < processVec.size(); i++) {
		cPrcC = processVec[i];
		if(cPrcC.state == "running" && cPrcC.processNum != nextRun) {
			processVec[i].state = "ready";
			processVec[i].quantum = -777;
			processVec[i].turnToReayCycleI = cycleI;
		}

	}
}
////
void TurnBlockToReady() {
	ProcessClass cPrcC;
	for(int i = 0; i < processVec.size(); i++) {
		cPrcC = processVec[i];
		if(cPrcC.state == "blocked" && cPrcC.IOburst == -1) {
			processVec[i].state = "ready";
		}
	}

}
//
int getNextRunPSJF(int bNum) {
	int minRemainT = 2147483647;
	int processNum = bNum;	
	ProcessClass cPrcC;


	for(int i = bNum; i >= 0; i--) {
		cPrcC = processVec[i];
		if(cPrcC.state == "running" && (cPrcC.remainTime < processVec[bNum].remainTime)) return i;
	}

	//unstarted first
	for(int i = bNum; i < processVec.size(); i++) {
		// cout<<"~~~~~~~ cycleI"<<cycleI<<endl;
		cPrcC = processVec[i];
		if(cPrcC.state == "ready" && cPrcC.A == cycleI) {
			return i;
		}
	}

	return bNum;
}
///////////////////////////////////////////
int getNextRunSJF() {
	// printProcessVec("", processVec, "");
	int minRemainT = 2147483647;
	int processNum;
	ProcessClass cPrcC;
	// cout<<"in getNextRunSJF nextRun="<<nextRun<<endl;
	for(int i = 0; i < processVec.size(); i++) {
		cPrcC = processVec[i];

		if(cPrcC.processNum != nextRun && (cPrcC.state == "ready" ||(cPrcC.state == "blocked" && cPrcC.IOburst < 0 ))) {
			if(cPrcC.state == "ready" && cPrcC.quantum == -777) cPrcC.remainTime ++;
			//cout<<"minRemainT="<<minRemainT <<" cPrcC.remainTime="<<cPrcC.remainTime<< " processNum="<<cPrcC.processNum <<endl;
			if( cPrcC.remainTime < minRemainT) {
				minRemainT = cPrcC.remainTime;
				processNum = cPrcC.processNum;
				
			}
		}
	}
	return processNum;
}






