std::vector<char> readFileFun(char str[]);
void parseData(std::vector<char> );
void parseRanNum();
////////////////////////////////////////////
void parser(char fileName[]) {
	//cout<<"in parser fileName="<<fileName<<endl;
	std::vector<char> strVec = readFileFun(fileName);

	parseData(strVec);
	parseRanNum();

	std::sort(processVec.begin(), processVec.end(), sortProcessVecFunByAsn);
	
	//PrcVecClass prcVC;

	for(int i = 0; i < processVec.size(); i++) {
		//processSN++;
		//processVec[i].SN = processSN;
		processVec[i].processNum = i;
		processVec[i].remainTime = processVec[i].C;
		//prcVC.prcVec.push_back(processVec[i]);
	}
	
	// prcVC.prcVec = processVec;
	// prcVecCVec.push_back(prcVC);

}
//---
void parseRanNum() {
	std::vector<char> stVec;

	if (FILE *fp = fopen("./random-numbers", "r")) {
		char buf[1024];
		while (size_t len = fread(buf, 1, sizeof(buf), fp)){
			//cout<<"reading "<< buf <<endl;
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
		//cout<<"--->./ opend"<<endl;
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
	int qParenOpen = -1;
	int pParenClose = -1;
	string tempStr = "";

	int nthEle = -1;

	char tempChar;
	ProcessClass nProcess;
	for(int i = 0; i < strVec.size(); i++) {
		// nthEle = nthEle % 4;
		tempChar = strVec[i];
		if(tempChar == ' ' || tempChar == ')') {
			nthEle = nthEle % 4;

			if(numProcess == -1) {
				numProcess = atoi(tempStr.c_str());
				totalProcess = numProcess;
			}
			// cout<<tempStr<<" numProcess="<<numProcess<<endl;
			if(tempStr != "" && numProcess >= 0 && nthEle >= 0) {
				cout<<tempStr<<" numProcess="<<numProcess<<" nthEle="<<nthEle <<endl;
				if(nthEle == 0) nProcess.A = atoi(tempStr.c_str());
				else if (nthEle == 1) nProcess.B = atoi(tempStr.c_str());
				else if (nthEle == 2) nProcess.C = atoi(tempStr.c_str());
				else {
					processSN ++;
					nProcess.M = atoi(tempStr.c_str());
					nProcess.SN = processSN;
					processVec.push_back(nProcess);
					//nProcess.A = -1; nProcess.B = -1; nProcess.C = -1; nProcess.M = -1;
				}
				//cout<<tempStr<< " nthEle="<<nthEle << " numPro="<<numProcess <<endl;
			}	

			/////////////////////////
			if(tempChar == ')' && numProcess == 0) numProcess = -777;
			tempStr = "";
			if(qParenOpen == 1) nthEle ++;
			
		} 
		else if( tempChar == '(') {

			qParenOpen = 1;
			nthEle = 0;
			numProcess --;
			//cout<<"process start"<<endl;
		} 
		else {
			tempStr += tempChar;
		}
	}


}






