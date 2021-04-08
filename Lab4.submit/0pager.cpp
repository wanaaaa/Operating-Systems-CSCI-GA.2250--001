
void pager() {
	cout<<"The machine size is "<<MachineSize<<"."<<endl;
	cout<<"The page size is "<<PageSize<<"." <<endl;
	cout<<"The process size is "<<ProcessSize<<"." <<endl;
	cout<<"The job mix number is "<<JobMix<<"." <<endl;
	cout<<"The number of references per process is "<<NumReferenceProcess<<"." <<endl;
	cout<<"The replacement algorithm is "<<algorithm<<"." <<endl;
	cout<<"The level of debugging output is "<<0<<endl<<endl;

	int pageNum, ranNum;	
	int refWord = 0;

	int numOfProcess = processVec.size();
	int quantum, outerI;
	double y;
	while(timeI <= NumReferenceProcess*numOfProcess){
		Process cProcess;
		Process *pProcess;

		outerI = 0;
		while(outerI < processVec.size() ){
 
 			cProcess = processVec[outerI];
			pProcess = & processVec[outerI];

			quantum = 1;
			while(quantum <= 3 && pProcess->numOfRefercences) {

				pProcess->numOfRefercences --;

				if(pProcess->qFirst == 1) {
					refWord = (111*pProcess->processNum) % ProcessSize;
					pProcess->refWord = refWord;
					pProcess->qFirst = 0;
				} else {
					if(std::abs(pProcess->refWord) > ProcessSize) {
						pProcess->refWord = pProcess->refWord + ProcessSize;
					}
					refWord = (pProcess->refWord + ProcessSize) % ProcessSize ;
				}

				int pageNum = refWord / PageSize;

				if(pageNum > pProcess->maxPage) {
					pProcess->maxPage = pageNum;
				}

				Page cPage(pageNum, cProcess.processNum);
				int hitFrameInt = hitFrame(cPage, "algo");
				if(hitFrameInt >= 0) {} 
				else {
					int frameUsedEvicted= addPageToFrame(cPage);

					if(frameUsedEvicted >= 0) 
						processVec[cPage.processNum -1].pageFault ++;						
				}

				ranNum = randomVec[0];
				randomVec.erase(randomVec.begin());

				y = ranNum/(2147483647 + 1.0);

				if(y < pProcess->A) pProcess->refWord ++;
				else if (y <(pProcess->A+pProcess->B)) pProcess->refWord -= 5;
				else if(y <(pProcess->A + pProcess->B + pProcess->C)) 
					pProcess->refWord += 4;
				else if ( y >= (pProcess->A + pProcess->B + pProcess->C)) {
					pProcess->refWord = randomVec[0];
					randomVec.erase(randomVec.begin());
				}	
				////////////////////////////
				timeI++;
				quantum++;
			}//end of inner while	
				//cout<<" "<<endl;				
			outerI ++;
		}//end of outer while
	}//end of time while	
}












