int getNextRunUnipro(int qProcessTerminated);
//---
void schedulerUnipro() {
	//cout<<" "<<endl<<endl;
	nextRun = 0;
	int qAllTerminated = totalProcess;
	int qProcessTerminated;

	// while (cycleI <= 97) {
	while(qAllTerminated) {
		// cout<<"===>cycleI = "<<cycleI<<endl;
		qProcessTerminated = 0;

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
						//cout<<" cPrcC.A ="<<cPrcC.A<<endl;
						cPrcC.state = "ready";
						cPrcC.turnToReayCycleI = cycleI;
					}
				}
			}
			else if(cPrcC.state == "running") {
				if(cPrcC.remainTime == 0) {
					cPrcC.state = "terminated";
					qAllTerminated --;
					qProcessTerminated = 1;
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
			nextRun = getNextRunUnipro(qProcessTerminated);
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
		// cout<<""<<endl;

	}//end of while
}
//////////
int getNextRunUnipro(int qPterminated) {
	int returnInt = nextRun;
	if(qPterminated == 1) returnInt ++;
	return returnInt;
}


