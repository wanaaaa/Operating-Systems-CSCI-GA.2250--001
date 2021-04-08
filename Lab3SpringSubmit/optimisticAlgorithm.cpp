//<-Subtracting requested unit from availabe unit after checking deadlock.
void DoSubtract(Task cTask, int nI) {
	numRequested ++;
	//check for deadlock
	if(currentUnitVec[cTask.taResource] >= cTask.unit) {
		currentUnitVec[cTask.taResource] -= cTask.unit;
		removeTVec.push_back(cTask);
		requestedTVecVec[cTask.taName].taskVec.push_back(cTask);
	} else {
		numDenied ++;
		reqDeniedTVec.push_back(cTask);
		reqDeniedTimeVec.push_back(nI);
		outPutInfoFifoVec[cTask.taName].waitTime ++;}}//->

//<-Release resource unit from aborted task
void releaseAbortedU(){
	if(abortedTVec.size() > 0) {
		Task cTask, ccTask;
		for(int i = 0; i < abortedTVec.size(); i++) {
			cTask = abortedTVec[i];
			for(int j = 0; j < requestedTVecVec[cTask.taName].taskVec.size();j++) {
				ccTask = requestedTVecVec[cTask.taName].taskVec[j];
				currentUnitVec[ccTask.taResource] += ccTask.unit;}}}
	abortedTVec.clear();}//->

//<-Release resource unit by releasing request of task
void releasePreReleaseUnit(){
	Task cTask;
	for(int i = 0; i < releaseTVec.size(); i++) {
		cTask = releaseTVec[i];
		currentUnitVec[cTask.taResource] += cTask.unit;
	}
	releaseTVec.clear();}//->

//<-Abort a task which causes deadlock
void doAbort() {
	Task cTask;
	std::sort(reqDeniedTVec.begin(), reqDeniedTVec.end(), sortTVecByTask);
	std::vector<Task> * cTVec;
	for(int i = 0; i < reqDeniedTVec.size()-1; i++) {
		cTask = reqDeniedTVec[i];
		cTVec  = & taskVecVec[cTask.taName].taskVec;
		cTVec->clear();
		abortedTVec.push_back(cTask);
	}}//->

//<-Erase processed task from vector which has tasks
void eraseDoneTask() {
	Task cTask;
	std::vector<Task> * cTVec;
	for(int i = 0; i < removeTVec.size(); i++) {
		cTask = removeTVec[i];
		cTVec = & taskVecVec[cTask.taName].taskVec;
		cTVec->erase(cTVec->begin());}}//<- 
//=====================================================================
//<-Optimistic algorithm begins
void executeOptimistic() {
	int newI;

	//Cycle begins
	while (maxVecLength  > 1) {
		//<--releasing resource unit from previous tasks
		releaseAbortedU();
		releasePreReleaseUnit();//-->

		numDenied = 0;
		numRequested = 0;
		removeTVec.clear();

		setMaxVecLength();
		//Processing tasks in a same cycle begins
		for(int i = 1; i < taskVecVec.size(); i++) {
			//<- check if there is task which is denied from prevois cycle
			if(i == 1 && reqDeniedTimeVec.size() != 0) {
				stopCycle = reqDeniedTimeVec[0]-1;
				reqDeniedTimeVec.clear();
			}//->

			newI = (i + stopCycle) % (taskVecVec.size()-1);
			if (newI == 0) newI = (taskVecVec.size() - 1);

			//The tasks in a cycle are processed.
			if(taskVecVec[newI].taskVec.size() > 0) {
				Task cTask;
				cTask = taskVecVec[newI].taskVec[0];

				//<-Processing release task
				if(cTask.state == "release") {
					releaseTVec.push_back(cTask);
					removeTVec.push_back(cTask);					
					requestedTVecVec[cTask.taName].taskVec.clear();
				}//->
				
				//<-Processing request task
				if(cTask.state == "request") DoSubtract(cTask, newI);//->
				
				//<-Porcessing initiate task				
				if(cTask.state == "initiate"|| cTask.state == "terminate"){					
					removeTVec.push_back(cTask);
					if(cTask.state == "terminate") outPutInfoFifoVec[cTask.taName].timeTaken = iW;					
				}//->

				//<- Processing compute task
				if (cTask.state == "compute") {
					if(cTask.taResource > 1) taskVecVec[newI].taskVec[0].taResource --;
					else removeTVec.push_back(cTask);					
				}//->
			}
		}//end of For		

		//<- Checking for deadlock. If process a task whose reaquest is greater than current 
		//remaning unit of resource, it will be aborted.
		if((numRequested == numDenied && numRequested > 0) && releaseTVec.size() == 0) 
			doAbort();//->

		reqDeniedTVec.clear();
		eraseDoneTask() ;	

		iW ++;
	}//end of while
	clearAll();
}//Optimistic algorithm ends

























