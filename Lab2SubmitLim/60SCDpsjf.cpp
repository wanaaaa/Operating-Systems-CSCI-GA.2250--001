//////////////////////////////////////////
void schedulerPSJD() {
	// cout<<" "<<endl<<endl;
	nextRun = 0;
	int qAllTerminated = totalProcess;
	int tunrnToBlocked = 0;

	// while (cycleI <= 133) {
	while(qAllTerminated) {
		//cout<<"===>cycleI = "<<cycleI<<endl;
		blockZeroVec.clear();

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
						//cPrcC.quantum = -777;
						cPrcC.turnToReayCycleI = cycleI;
					}
				}
			}
			else if(cPrcC.state == "running") {
				if(cPrcC.remainTime == 0) {
					// cout<<"terminated%%%%%%%%%%%%%%%%%%%"<<endl;
					cPrcC.state = "terminated";
					qAllTerminated --;
				}
				else if(cPrcC.cpuBurst == 1) {
					cPrcC = convertToBlocked(cPrcC);
					tunrnToBlocked = 1;

					//cout<<" convertToBlocked ==========="<<endl;
				} 
				else {
					cPrcC.cpuBurst --;
					cPrcC.remainTime --;					
				}
			}
			else if(cPrcC.state == "blocked") {
				if(cPrcC.IOburst == 0) {
					blockZeroVec.push_back(cPrcC);

				} 

				cPrcC.IOburst --;					
			}
			
			//System
			processVec.push_back(cPrcC);
		}//end of for
		//////////////////////////////////////////

		if((blockZeroVec.size() == 0 || tunrnToBlocked == 1) && processVec.size() > 1) {
			if(isThereRun() == 0) {
				nextRun = getNextRunSJF();
				// cout<<"aaaaaaaaaaaaaaaa nextRun ="<<nextRun<<endl;
				ProcessClass cPrcC;
				for(int i = 0; i < processVec.size(); i++) {
					cPrcC = processVec[i];
					if((cPrcC.state == "ready" || cPrcC.state == "blocked") 
						&& cPrcC.processNum == nextRun) {
						if(cPrcC.quantum == -777) {
							processVec[i].state = "running";
							processVec[i].quantum = 111;
						} else {

							convertToRunP(& processVec[i]);
							
						}
					}
					if(cPrcC.state == "blocked" && cPrcC.IOburst == -1 && cPrcC.processNum != nextRun) {
						//cout<<"11111111111111111"<<endl;
						processVec[i].state = "ready";
						processVec[i].turnToReayCycleI = cycleI;
					}
				}//end of for

			}
			tunrnToBlocked = 0;			
		} // end of if
		else {
			// printProcessVec("", processVec, "");
			int BlockZeroProcessNum;
			if(blockZeroVec.size() > 1) {
				 BlockZeroProcessNum = nextRunFromBlockZeros();
				//cout<<"444444444444444 nextRun="<<test<<endl;
			} else {
				BlockZeroProcessNum = blockZeroVec[0].processNum;

			}

			

			if(processVec[BlockZeroProcessNum].state == "terminated") {
				nextRun = getNextRunSJF();
			} else {
				//cout<<"1~~~~~~~~~~` BlockZeroProcessNum="<<BlockZeroProcessNum<<endl;
				nextRun = getNextRunPSJF(BlockZeroProcessNum);
				//cout<<"2~~~~~~~~~~~~~~~~~~~~ nextRun="<<nextRun<<endl;
				
			}
			
			//came from preempted....
			if(processVec[nextRun].state == "running") {

			}
			else if( processVec[nextRun].state == "ready" && processVec[nextRun].quantum == -777) {
				processVec[nextRun].state = "running";
				processVec[nextRun].quantum = 111;
			} else {
				//cout<<"2222222222"<<endl;
				convertToRunP(& processVec[nextRun]);				
			}

			TurnBlockToReady();
			preemptRunToReady();

			blockZeroVec.clear();
		}


		//System
		cycleI++;
		//cout<<""<<endl;

	}//end of while
}
///////////////////////////////////////////

