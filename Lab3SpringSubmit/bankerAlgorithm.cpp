//<--Check if other taks are in safe  or not.
int checkOtherResourceSafe(Task cTask) {
	int returnInt = 1;
	for(int i = 1; i < availableResourceVec.size(); i++) {
		if(i != cTask.taResource) {
			if(	stillNeedUTaskVVec[cTask.taName].resourceVec[i] > availableResourceVec[i]) 	return 0;;			
		}
	}
	return returnInt;
}//-->

//<--Check if the request is safe or not.
int checkSafe(Task cTask) {
	if( (stillNeedUTaskVVec[cTask.taName].resourceVec[cTask.taResource] == cTask.unit
		&& cTask.unit <= availableResourceVec[cTask.taResource])
		|| stillNeedUTaskVVec[cTask.taName].resourceVec[cTask.taResource] == 
		availableResourceVec[cTask.taResource]) {
			if(checkOtherResourceSafe(cTask) ==1) return 1;
	}
	return 0;
}//-->

//<-Check if all resuouce are consumed or not. 
int qAllResourceFull() {
	for(int i = 1; i < maxResourceVec.size(); i++ ) {
		if(maxResourceVec[i] != availableResourceVec[i]) return 0;		
	}
	return 1;
}//->

//<-Subtract requested resource from available and still need resource 
void DoSubtract(Task cTask) {
	hasUTaskVVec[cTask.taName].resourceVec[cTask.taResource] += cTask.unit;
	stillNeedUTaskVVec[cTask.taName].resourceVec[cTask.taResource] -= cTask.unit;

	possesResourceVec[cTask.taResource] += cTask.unit;
	availableResourceVec[cTask.taResource] -= cTask.unit;

	requestedTVecVec[cTask.taName].taskVec.push_back(cTask);
}//->

//<-- Releases resource by release request
void releaseUFromReleased() {
	Task cTask;
	for(int i = 0; i < releaseTVec.size(); i++) {
		cTask = releaseTVec[i];
		hasUTaskVVec[cTask.taName].resourceVec[cTask.taResource] -= cTask.unit;
		stillNeedUTaskVVec[cTask.taName].resourceVec[cTask.taResource] += cTask.unit;

		possesResourceVec[cTask.taResource] -= cTask.unit;
		availableResourceVec[cTask.taResource] += cTask.unit;
	
		requestedTVecVec[cTask.taName].taskVec.clear();			
	}
	releaseTVec.clear();
}//-->

//<--Processing request and check if it is safe
void processRequest(Task cTask) {
	if(qAllResourceFull() == 1 || checkSafe(cTask) == 1) DoSubtract(cTask); 
	else {
		cTask.iTW = iW;
		unSafeTVec.push_back(cTask);
	}
}//-->

//<<-- Erase processed tasks from task vectors
void eraseDoneTaskBa() {
	std::vector<Task> * cTVec;
	Task cTask;
	for(int i = 0; i < removeTVec.size(); i++) {
		cTask = removeTVec[i];
		cTVec = & taskVecVec[cTask.taName].taskVec;
		cTVec->erase(cTVec->begin());
	}
	removeTVec.clear();
}//-->	
///////////////////////////////////////////////////////////
//<-Check if all taske are completed  or not.
int qFinishBanker(std::vector<Task> iVec) {
	Task cTask;
	for(int i = 0; i < iVec.size(); i ++) {
		cTask = iVec[i];
		if(cTask.state != "terminate" && cTask.state != "Done" && cTask.state != "aborted") {
			return 1;}}
	return 0;
}//->

//<--Releasing resources from aborted tasks
void releaseAbortedU(Task iTask) {
	Task cTask;
	for(int i = 0; i < requestedTVecVec[iTask.taName].taskVec.size(); i++) {
		cTask = requestedTVecVec[iTask.taName].taskVec[i];
		hasUTaskVVec[cTask.taName].resourceVec[cTask.taResource] -= cTask.unit;
		stillNeedUTaskVVec[cTask.taName].resourceVec[cTask.taResource] += cTask.unit;

		possesResourceVec[cTask.taResource] -= cTask.unit;
		availableResourceVec[cTask.taResource] += cTask.unit;	
	}
}//-->

//<--Check if a requests exceeds its claim
int chkRequestErr(Task cTask) {
	int returnInt = 1;
	if(hasUTaskVVec[cTask.taName].resourceVec[cTask.taResource] + cTask.unit
	 > claimUVVec[cTask.taName].resourceVec[cTask.taResource]) {
	 	returnInt = 0;
	 	taskVecVec[cTask.taName].taskVec[0].state = "aborted";

		std::stringstream errSS;
		errSS <<"During cycle "<<iW<<"-"<<iW+1<<" of Banker's algorithms\n   Task "
		<<cTask.taName<<"'s request exceeds its claim; aborted; "<<cTask.unit
		<<" units available next cycle \n";
		string errMessStr;
		
		errMessStr = errSS.str();
		bankerErrMessVec.push_back(errMessStr);
	}
	return returnInt;
}//-->

//<--Check if a initial claim exceeds maximum resources
int setUVVec(Task cTask) {
	int returnInt = 1;
	if(cTask.unit > maxResourceVec[cTask.taResource] ) {
		std::stringstream errSS;
		errSS<<"Banker aborts task "<<cTask.taName<<" before run begins: \n"
		<<"   claim for resourse "<<cTask.taResource<<" ("<<cTask.unit<<")"
		<<" exceeds number of units present ("<<initInfo[cTask.taResource+1]<<")";

		string errMessStr = errSS.str();
		bankerErrMessVec.push_back(errMessStr);

		taskVecVec[cTask.taName].taskVec[0].state = "aborted";
		returnInt = 0;
	} else {
		claimUVVec[cTask.taName].resourceVec[cTask.taResource] = cTask.unit;
		stillNeedUTaskVVec[cTask.taName].resourceVec[cTask.taResource] = cTask.unit;
		hasUTaskVVec[cTask.taName].resourceVec[cTask.taResource] = 0;		
	}
	return returnInt;
}//-->

//<<-initilize vector which has task vectors
void initiateUtaskVVec() {
	for(int i = 0; i < taskVecVec.size(); i++) {
		for(int j = 0; j <= initInfo[1]; j++) {
			ResourceUStu nStu;
			nStu.resourceVec.push_back(2147483647);

			hasUTaskVVec.push_back(nStu);
			stillNeedUTaskVVec.push_back(nStu);
			claimUVVec.push_back(nStu);			
		}}}
//-->

//<--main banker algorithm begins
void executeBanker() {
	int qEraseRemoveTVec;
	initiateUtaskVVec();

	int keepWhile = 1;
	std::vector<Task> finishedVec;

	//Cycle begins
	while (keepWhile) {
		//<--releasing resource unit from previous tasks
		releaseUFromReleased();//-->

		finishedVec.clear();

		Task cTask;
		//Processing tasks in a same cycle begins
		for(int i = 0; i < taskVecVec.size()-1; i++) {
			qEraseRemoveTVec = 1;
			
			//<-Check taske for safty
			if(unSafeTVec.size() > 0 && unSafeTVec[0].iTW < iW) {				
				cTask =unSafeTVec[0];
				unSafeTVec.erase(unSafeTVec.begin());				
				newI = cTask.taName; 
				qEraseRemoveTVec = 0;

				outPutInfoBankVec[cTask.taName].waitTime ++;
			} else cTask = taskVecVec[newI].taskVec[0];	//->
			
			//<-Processing initiate task
			if(cTask.state == "initiate") qEraseRemoveTVec = setUVVec(cTask);//->
			
			//<-Porcessing request task			 
			if (cTask.state == "request") {
				if(chkRequestErr(cTask) == 0) {
					qEraseRemoveTVec = 0;
					releaseAbortedU(cTask);
				} else processRequest(cTask);
			}//->

			//<- Processing compute task which causes delay											
			if (cTask.state == "compute") {
				if(cTask.taResource  > 1) {
					taskVecVec[cTask.taName].taskVec[0].taResource --;
					qEraseRemoveTVec = 0;
				} 
			}//->
			
			//<-Processing release task
			if (cTask.state == "release") releaseTVec.push_back(cTask);//->

			//<-Porcessing terminate state
			if (cTask.state == "terminate") {
				outPutInfoBankVec[cTask.taName].timeTaken = iW;
				taskVecVec[newI].taskVec[0].state = "Done" ;
			}//->
            
            finishedVec.push_back(cTask);

			if(qEraseRemoveTVec == 1 && cTask.state != "terminate" 
				&& cTask.state != "Done" && cTask.state != "aborted") removeTVec.push_back(cTask);						

			oneClickNewI();
		}//end of For		

		keepWhile = qFinishBanker(finishedVec);
		eraseDoneTaskBa() ;	
		iW ++;
	}//end of while
}//Banker algorithm ends-->