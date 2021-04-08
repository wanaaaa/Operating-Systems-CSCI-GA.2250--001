std::vector<char> readFileFun(char str[]);
void parseData(std::vector<char> );
void parseRanNum();
////////////////////////////////////////////
void parser(char fileName[]) {
	// cout<<" "<<endl;
	// cout<<"in parser fileName="<<fileName<<endl;
	std::vector<char> strVec = readFileFun(fileName);

	parseData(strVec);
	parseRanNum();

	std::sort(processVec.begin(), processVec.end(), sortProcessVecFunByAsn);

	for(int i = 0; i < processVec.size(); i++) {
		processVec[i].processNum = i;
		processVec[i].remainTime = processVec[i].C;
	}

}
//---
void parseRanNum() {
	std::vector<char> stVec;

	if (FILE *fp = fopen("./random-numbers", "r")) {
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp)){
			stVec.insert(stVec.end(), buf, buf + len);
		}

		fclose(fp);
	}

	string tempString = "";
	char tempChar;
	int ranInt;
	for(int i = 0; i < stVec.size(); i++) {
		tempChar = stVec[i];
		if(tempChar == ' ' || tempChar == '\n' || i == stVec.size()-1) {
			if(i == stVec.size() -1) tempString += tempChar;
			ranInt = atoi(tempString.c_str());

			randomVec.push_back(ranInt);
			tempString = "";
		} else {
			tempString += tempChar;
		}			
	}
}
//---
std::vector<char> readFileFun(char fileName[]) {
	std::vector<char> strVec;
	
	if (FILE *fp = fopen(fileName, "r")) {
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp)){
			strVec.insert(strVec.end(), buf, buf + len);
			//cout<<buf<<endl;
		}

		fclose(fp);
	} 

	return strVec;
}
//---
void parseData(std::vector<char> strVec) {
	int numProcess = -1;
	string tempStr = "";

	int nthEle = -1;

	char tempChar;
	ProcessClass nProcess;
	for(int i = 0; i < strVec.size(); i++) {
		
		tempChar = strVec[i];
		if(tempChar == ' ') {
			nthEle = nthEle % 4;

			if(numProcess == -1) {
				numProcess = atoi(tempStr.c_str());
				totalProcess = numProcess;
			}
			
			if(tempStr != "" && numProcess >= 0 ) {
				if(nthEle == 0){
					nProcess.A = atoi(tempStr.c_str());					
				} 
				else if (nthEle == 1) {
					nProcess.B = atoi(tempStr.c_str());
				}
				else if (nthEle == 2) {					
					nProcess.C = atoi(tempStr.c_str());
				} 
				else if (nthEle == 3) {
					numProcess --;
					// cout<<tempStr<<" numProcess="<<numProcess<<" nthEle="<<nthEle<<" totalProcess="<<totalProcess <<endl;
					if(numProcess == 0) numProcess = -777;
					processSN ++;
					nProcess.M = atoi(tempStr.c_str());
					nProcess.SN = processSN;
					processVec.push_back(nProcess);
				}
				nthEle ++;					
			}	

			/////////////////////////
			tempStr = "";
			
		} 
		else {
			tempStr += tempChar;
		}
	}// end of for

	//copy to originalPrcVec
	for(int i = 0; i < processVec.size(); i++) {
		ProcessClass cPrc;
		cPrc = processVec[i];
		originalPrcVec.push_back(cPrc);
	}

}






