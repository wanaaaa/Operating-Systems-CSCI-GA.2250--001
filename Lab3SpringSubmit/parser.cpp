void readFileFun(char str[]);
void convertToCompute();

//call readFileFun. It passes file name to readFilefun.
void parser(char fileName[]) {
	readFileFun(fileName);
}

//It reads data and random file and parses them.
void readFileFun(char str[]) {
	std::vector<char> stVec;
	int is1stLine = 0;
	
	//<- read each character
	if (FILE *fp = fopen(str, "r")) {
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp))
			stVec.insert(stVec.end(), buf, buf + len);
		fclose(fp);
	}//->

	//<-Parse the charcters into string
	string temString = "";
	char tempChar;
	for(int i = 0; i < stVec.size(); i++) {
		tempChar = stVec[i];
			
		if (is1stLine == 0 ) {
			temString += tempChar;
			if(tempChar == ' ' || tempChar == '\n') {
				initInfo.push_back(atoi(temString.c_str()));
				temString = "";
			}

		} else {
			if (tempChar != '\n' && tempChar != ' ' && tempChar != '\t') temString += tempChar;

			if(tempChar == ' ' || tempChar == '\n') {
				if(temString != " " && temString !="") rawDataVec.push_back(temString);
				temString = "";
			}
		}

		if(stVec[i] == '\n') is1stLine ++;
	}//->

	//<-The first line in input is parsed into vector.
	maxUnitVec.push_back(-1);
	currentUnitVec.push_back(2147483647);
	maxResourceVec.push_back(2147483647);
	possesResourceVec.push_back(2147483647);
	availableResourceVec.push_back(2147483647);
	for (int i = 0; i < initInfo.size(); i++ ) {
		if(i == 0) numTasks = initInfo[i];
		else if(i == 1) numResource = initInfo[i];
		else{
			maxUnitVec.push_back(initInfo[i]);
			currentUnitVec.push_back(initInfo[i]);

			maxResourceVec.push_back(initInfo[i]);
			possesResourceVec.push_back(0);
			availableResourceVec.push_back(initInfo[i]);
		} 
	}//->

	//<-Parse the data string into Task class and saved in vector
	Task nTask;
	for (int i = 0; i < rawDataVec.size(); ++i){
		string cStr = rawDataVec[i];
		if (i % 5 == 0) {
			Task nnTask;
			nTask = nnTask;
			nTask.state = cStr;
		}
		if (i % 5 == 1) nTask.taName = atoi(cStr.c_str());
		if (i % 5 == 2) nTask.delayT = atoi(cStr.c_str());			
		if (i % 5 == 3) nTask.taResource = atoi(cStr.c_str());
		if (i % 5 == 4) {
			nTask.unit = atoi(cStr.c_str());
			taskVec.push_back(nTask);
		}
	}//->

	//delay is converted to computing.
	convertToCompute();

	Task cTask;
	TaskVecStu zeroStu, emptyStu;
	zeroStu.taskVec.push_back(cTask);
	taskVecVec.push_back(zeroStu);
	processedInCycleVec.push_back(-1);

	requestedTVecVec.push_back(emptyStu);

	OutputInfo outPutInfo;
	outPutInfoFifoVec.push_back(outPutInfo);
	outPutInfoBankVec.push_back(outPutInfo);

	//<-Each task Vector is saved into a vector again becuase a cycle has many tasks.
	int currentLength;
	for (int j = 1; j <= numTasks; j++) {
		TaskVecStu tVecStu;
		currentLength = 0;
		for(int i = 0; i < taskVec.size(); i ++) {
			cTask = taskVec[i];

			if(j == cTask.taName) {
				tVecStu.taskVec.push_back(cTask);
				currentLength ++;	
			} 
		}//end of inner for

		if(currentLength > maxVecLength) maxVecLength = currentLength ;
		taskVecVec.push_back(tVecStu);
		processedInCycleVec.push_back(0);

		requestedTVecVec.push_back(emptyStu);

		outPutInfoFifoVec.push_back(outPutInfo);
		outPutInfoBankVec.push_back(outPutInfo);

	}//end of outer for

	for(int i = 1; i < taskVecVec.size(); i++) {
		for(int j = 0; j <taskVecVec[i].taskVec.size(); j++) 
			taskVecVec[i].taskVec[j].serial = j+1;
	}//->
}

//The data has dealy. The request is delayed because of computing.
// So delayed request is converted to "compute state"
void convertToCompute() {
	Task cTask;
	Task *pTask;
	int i = 0;
	while ( i < taskVec.size()) {
		cTask = taskVec[i];
		if(cTask.delayT > 0) {
			Task nTask = cTask;
			nTask.state = "compute";
			nTask.taResource = cTask.delayT;
			taskVec.insert(taskVec.begin()+i, nTask);
			i++;
		}
		i++;
	}
}