int MachineSize = -1; int PageSize = -1;
int ProcessSize, JobMix, NumReferenceProcess;
string algorithm; //debugStr
int frameSize;
int pageSN = 0; int processSN = 0;

int timeI = 1;

std::vector<int> randomVec;

class Page {
public:
	int pageNum; int processNum; int SN;
	std::vector<int> timeVec;

	Page() {
		pageNum = -1; SN = pageSN; pageSN ++;
	} 
	Page(int pageN, int processN ){
		pageNum = pageN; processNum = processN; 
		SN = pageSN;
		pageSN ++;
	}
};
std::vector<Page> pageVec, frameTableVec;

//---
int qPageSame(Page cPage, Page iPage) {
	if(cPage.pageNum == iPage.pageNum && cPage.processNum == iPage.processNum)
		return 1;
	return 0;
}

struct TimeVecStu {
	std::vector<int> timeVec;
};
//---
class  Process {
public:
	int processNum; int refWord; int numOfRefercences;
	int qFirst; int pageFault; int maxPage;

	std::vector<TimeVecStu> loadedTStu;
	std::vector<TimeVecStu> evictedTStu;

	int SN;
	double A; double B; double C;
	Process(){
		processNum = -1; refWord = -1; numOfRefercences = NumReferenceProcess;
		qFirst = 1; pageFault = 0; maxPage = -1; SN = processSN; 		 
		processSN ++;
		A = -1; B = -1; C = -1;

		for(int i = 0; i <= ProcessSize; i++) {
			TimeVecStu eStu;
			loadedTStu.push_back(eStu);
			evictedTStu.push_back(eStu);
		}
	}	
};
std::vector<Process> processVec;
///////////////
void insertTimePageVec(Page iPage) {
	Page *pPage;
	for(int i = 0; i < pageVec.size(); i++){
		pPage = & pageVec[i];
		if(qPageSame(pageVec[i], iPage)==1) {
			pPage->timeVec.push_back(timeI);
			break;
		} 
	}
}
//---
bool sortFunByTimeVec(Page aPage, Page bPage) {
	return aPage.timeVec.back() < bPage.timeVec.back();
}
///////////////////////////////////////////////////////////////////////////////
string convertDoubleToStr(int numerator, int denominator, int numWith) {
	double numDouble = (double) numerator / (double) denominator ;

	stringstream stream;
	if(numerator % denominator == 0) 
		stream << std::fixed << setprecision(1)<<numDouble;		
	else if(numDouble < 10) 
		stream << setprecision(16)<<numDouble;
	else if (numDouble < 40)
		stream << setprecision(17)<<numDouble;
	else if (numDouble < 100)
		stream << setprecision(16)<<numDouble;
	else if (numDouble < 1000)
		stream << setprecision(16)<<numDouble;
	else if (numDouble < 10000)
		stream << setprecision(17)<<numDouble;

	string numStr = stream.str();

	return numStr;
}

string convertProcessDoubleToStr(int numerator, int denominator, int numWith) {
	double numDouble = (double) numerator / (double) denominator ;

	stringstream stream;
	if(numerator % denominator == 0) 
		stream << std::fixed << setprecision(1)<<numDouble;		
	else if(numDouble < 10) 
		stream << setprecision(16)<<numDouble;
	else if (numDouble < 40)
		stream << setprecision(17)<<numDouble;
	else if (numDouble > 100 & numDouble < 110)
		stream << setprecision(17)<<numDouble;
	else if (numDouble > 490 & numDouble < 500)
		stream << setprecision(17)<<numDouble;
	else if (numDouble < 1000)
		stream << setprecision(16)<<numDouble;
	else if (numDouble > 1100 && numDouble < 1200)
		stream << setprecision(16)<<numDouble;
	else if (numDouble > 1250 && numDouble < 1260)
		stream << setprecision(16)<<numDouble;			
	else if (numDouble < 10000)
		stream << setprecision(17)<<numDouble;

	string numStr = stream.str();

	return numStr;
}