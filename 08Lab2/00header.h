int totalProcess = -1;
int processSN = 0;
int cycleI = 0;
std::vector<int> randomVec;
int nextRun = -1;

/////////////////////////////////
class ProcessClass {
public:
	string state;
	int A; int B; int C; int M;
	int cpuBurst; int IOburst; int remainTime; int turnToReayCycleI;
	int quantum;
	int cycleI; int processNum;
	int SN;
	ProcessClass() {
		state = "unstarted";
		A=-1; B=-1; C= -1; M=-1;
		cpuBurst = -1; remainTime = -1; IOburst = -1; cycleI = -1;
		quantum = 2; SN = processSN;
		processSN ++;
	}

	ProcessClass newProcess(ProcessClass iPrcC){
		iPrcC.SN = processSN;
		// nPrc.SN = 777;
		processSN++;

		return iPrcC;
	}		
};
std::vector<ProcessClass> processVec, donePrcVec, originalPrcVec;
std::vector<ProcessClass> blockZeroVec;
//---


class PrcResultClass {
public:
	//int A; int B; int C; int M;	
	int finishTime; int IOtime; int waitTime;
	PrcResultClass(){
		//A=-1; B=-1; C= -1; M=-1; finishTime=-1; 
		IOtime = 0; waitTime = 0;	
	}	
};
std::vector<PrcResultClass> prcResultVec;
////////////////////////////////////
bool sortProcessVecFunByAsn(ProcessClass aP, ProcessClass bP) {
	if(aP.A < bP.A) return true;
	if(aP.A > bP.A) return false;

	if(aP.SN < bP.SN) return true;
	if(aP.SN > bP.SN) return false;

	return false;
}

///////////////////////////////////
void printProcess(string fSt, ProcessClass iPrcC){
	// cout<<fSt<<"A="<<iPrcC.A<<" "<<" B="<<iPrcC.B<<" C="<<iPrcC.C<<" M="<<iPrcC.M
	// <<" SN="<<iPrcC.SN<< endl;
	cout<<fSt<<iPrcC.processNum<<" sta="<<iPrcC.state<<" cB="<<iPrcC.cpuBurst<<" remainT="<<iPrcC.remainTime
	<<" qua="<<iPrcC.quantum<<" ioB="<<iPrcC.IOburst<<" SN="<<iPrcC.SN<<" cy="<<iPrcC.cycleI<<endl;
}
//---
void printProcessVec(string fSt, std::vector<ProcessClass> iVec,string rSt) {
	ProcessClass proC;
	cout<<fSt;
	for(int i = 0; i < iVec.size(); i++) {
		proC = processVec[i];
		printProcess("<------", proC);
	}
	cout<<rSt<<endl;
}

void clearAll() {
	totalProcess = -1; processSN = 0; cycleI = 0;
	randomVec.clear(); nextRun = -1;

	processVec.clear(); donePrcVec.clear();	originalPrcVec.clear();

	prcResultVec.clear();
}




