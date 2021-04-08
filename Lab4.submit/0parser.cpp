void parser() {
	std::vector<char> stVec;

	if (FILE *fp = fopen("./random-numbers", "r")) {
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp))
			stVec.insert(stVec.end(), buf, buf + len);

		fclose(fp);
	}

	string tempString = "";
	char tempChar;
	int ranInt;
	for(int i = 0; i < stVec.size(); i++) {
		tempChar = stVec[i];
		if(tempChar == ' ' || tempChar == '\n') {
			ranInt = atoi(tempString.c_str());
			randomVec.push_back(ranInt);
			tempString = "";
		} else {
			tempString += tempChar;
		}			
	}
}

void initializeNums(){
	frameSize = MachineSize / PageSize;
	for(int i= 0; i < frameSize; i++) {
		Page nPage(-1, -1);
		frameTableVec.push_back(nPage);
	}

	if(JobMix == 1 || JobMix == 2 || JobMix == 3) {
		int endI;
		if (JobMix == 1) endI = 1;
		else endI = 4;

		for (int i = 1; i <= endI; i++) {
			Process nProcess;
			nProcess.processNum = i;

			if( JobMix == 3) nProcess.A = 0;
			else nProcess.A = 1;
			nProcess.B = 0;
			nProcess.C = 0;
			processVec.push_back(nProcess);	
		}
	} 

	if (JobMix == 4) {
		for(int i = 1; i <= 4; i++) {
			Process nProcess;
			nProcess.processNum = i;
			if (i == 1) {
				nProcess.A = 0.75; nProcess.B = 0.25; nProcess.C = 0;
			} else if( i == 2) {
				nProcess.A = 0.75; nProcess.B = 0.0; nProcess.C = 0.25;				
			} else if(i == 3) {
				nProcess.A = 0.75; nProcess.B = 0.125; nProcess.C = 0.125;								
			} else if ( i == 4){
				nProcess.A = 0.5; nProcess.B = 0.125; nProcess.C = 0.125;												
			}
			processVec.push_back(nProcess);
		}
	}
}











