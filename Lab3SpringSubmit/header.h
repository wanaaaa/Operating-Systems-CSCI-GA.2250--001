//<--There are all necessary variables to run
std::vector<string> bankerErrMessVec;
std::vector<int> initInfo ;
std::vector<int> maxUnitVec, currentUnitVec, maxResourceVec, 
	possesResourceVec, availableResourceVec, processedInCycleVec;
std::vector<string> rawDataVec;
std::vector<int> reqDeniedTimeVec;

int numTasks, numResource;
int maxVecLength = -1;
int taskSerial = 0;
int iW = 0; 
int newI = 1;
int	numDenied, numRequested;
int stopCycle = 0;
int wasInitiate = 0;
//-->

//<- This Task class has the informaion of each task. The class has task name, state,
//arriving time, resource number, resource amount, and so on.
class Task{
public:
	int taName, delayT ,taResource, unit, serial, iTW, safe, selfRemainU;
	string state;
	
	Task() {
		taName = -1; delayT = -1 ;taResource = -1; unit = -1;
		iTW = -1; safe = 1; selfRemainU = 2147483647;
		serial = taskSerial;
		taskSerial += 1;
		state = "nothing";
	}
	~Task() {}	
};//->

//<-The tasks were saved in various vector.
std::vector<Task> taskVec, removeTVec, releaseTVec, reqDeniedTVec, abortedTVec
	, unSafeTVec;
//->

//The taskVec is saved in struct. 
struct TaskVecStu {
	std::vector<Task> taskVec;
};

//The tasks in same cycle is in one taskVec, so tasks in differnet cycle were different taskVec.
//All the taskVecs are saved in taskVecVec which is a vector with many task vectors
// It makes it to access to a specific cycle like a task <- tasdVecVec[cycle][task name]
std::vector<TaskVecStu> taskVecVec, requestedTVecVec;

//<--Each resource unit is saved in resourceVec. Every task has plural or single resource.
//Each resourceVec is saved in various vectors which need for resources are currently taken, clalimed and more needed.
struct ResourceUStu{
	std::vector<int> resourceVec;	
};
std::vector<ResourceUStu> hasUTaskVVec, stillNeedUTaskVVec, claimUVVec;//-->

//<--The OutputInfo class is the information of processed task for statistics.
//The information class is in outputInfoFifo and outputInfoBank Vectors.
class OutputInfo {
public:
	int timeTaken, waitTime, percenWait, totalTime, totalWaitTime, totalPercenWaitTime;
	OutputInfo() {
		timeTaken=-777, waitTime= 0, percenWait=-777, totalTime=-777
		, totalWaitTime=-777, totalPercenWaitTime=-777;
	} 	
};
std::vector<OutputInfo> outPutInfoFifoVec, outPutInfoBankVec;//-->

//set taskVecVec length
void setMaxVecLength() {
	maxVecLength = -1;
	std::vector<Task> cTVec;
	int cLen;
	for(int i = 1; i < taskVecVec.size(); i++) {
		cTVec = taskVecVec[i].taskVec;
		cLen = cTVec.size();
		if( cLen > maxVecLength){
			maxVecLength = cTVec.size();\
		}
	}
}
//It is for sorting taskVec by arrival time.
bool sortTVecByTask(Task tA, Task tB) {
	return tA.taName < tB.taName;
}

//After finish optimistic algorithm, it set all vectors and variables to set initial value before
// the banker algorithm begin. 
void clearAll() {
	initInfo.clear(); maxUnitVec.clear(); currentUnitVec.clear(); 
	rawDataVec.clear(); reqDeniedTimeVec.clear();
	maxResourceVec.clear(); possesResourceVec.clear(), availableResourceVec.clear();
	
	numTasks = -1; numResource = -1; maxVecLength = -1; taskSerial = 0;
	iW = 0; newI = 1; numDenied = -1; numRequested = -1; stopCycle = 0;

	taskVec.clear(); removeTVec.clear(); releaseTVec.clear();
	reqDeniedTVec.clear(); abortedTVec.clear();

	taskVecVec.clear(), requestedTVecVec.clear();

	outPutInfoBankVec.clear();
}

//It incresae newI by one. When the algorithm is in unsafe mode, newI indicated to check next tasks.
void oneClickNewI() {
	newI++;
	newI = newI % (taskVecVec.size()-1);
	if (newI == 0) newI = taskVecVec.size() -1;
}












