void convertToRunPrbb(ProcessClass *cPrcC);
//////////////////////////////
void schedulerRRB() {
	//cout<<" "<<endl<<endl;
	nextRun = 0;
	int qAllTerminated = totalProcess;
	cycleI = 0;
	
	// while (cycleI <= 10) {
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
			//printProcess("->", cPrcC);
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
				else if(cPrcC.quantum == 1|| cPrcC.cpuBurst == 1) {
					if(cPrcC.cpuBurst == 1) {
						cPrcC = convertToBlocked(cPrcC);						
						cPrcC.quantum --;
					} else {
						cPrcC.state = "ready";
						cPrcC.turnToReayCycleI = cycleI;
						cPrcC.quantum = 2;
						
						cPrcC.cpuBurst --;
						
					}
				}
				else {
					cPrcC.cpuBurst --;
					cPrcC.remainTime --;					
					cPrcC.quantum --;
				}

			}
			else if(cPrcC.state == "blocked") {
				if(cPrcC.IOburst == 0) {
					cPrcC.state = "ready";
					cPrcC.turnToReayCycleI = cycleI;

					//It's new Ready, not from quantum stop
					cPrcC.cpuBurst = -1;
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
					convertToRunPrbb(& processVec[i]);
				}
			}
		}

		//System
		cycleI++;

	}//end of while
}
////////---
void convertToRunPrbb(ProcessClass *cPrcC) {
	int cBurst;
	if(cPrcC->cpuBurst > 0) {
		cBurst = cPrcC->cpuBurst;
	} else {
		cBurst = 1 + (randomVec[0]) % cPrcC->B;
		randomVec.erase(randomVec.begin());
		cPrcC->quantum = 2;
	}

	cPrcC->state = "running";
	cPrcC->cpuBurst = cBurst;
	cPrcC->remainTime --;
}

