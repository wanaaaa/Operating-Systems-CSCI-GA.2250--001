int hitFrame(Page iPage, string algo) {
	Page cPage(-1, -1);
	for(int i = 0; i < frameTableVec.size(); i++) {
		cPage = frameTableVec[i];
		if(qPageSame(cPage, iPage) == 1) {
			insertTimePageVec(iPage);
			return i;
		}
	}
	return -1;
}

int addPageToFrame(Page iPage) {
	int returnInt = -1;
	int qFound = 0;
	Page cPage(-1, -1);
	iPage.timeVec.push_back(timeI);
	
	for(int i = frameTableVec.size()-1; i >= 0; i--) {
		cPage = frameTableVec[i];		
		if(cPage.pageNum == -1) {
			qFound = 1;

			frameTableVec[i] = iPage;
			pageVec.push_back(iPage);

			TimeVecStu *nStu;
			nStu = & processVec[iPage.processNum-1].loadedTStu[iPage.pageNum];
			nStu->timeVec.push_back(timeI);

			returnInt = i;
			break;
		}
	}

	if(qFound == 0 && pageVec.size() > 0) {
		Page rPage;
		if(algorithm == "fifo") {
			rPage = pageVec.front();
			pageVec.erase(pageVec.begin());
		} else if (algorithm == "lru") {
			std::sort(pageVec.begin(), pageVec.end(), sortFunByTimeVec);
			rPage = pageVec.front();
			pageVec.erase(pageVec.begin());
		} else if(algorithm == "random") {
			int ranNum = randomVec[0];
			int frameIndex = ranNum % frameTableVec.size();
			randomVec.erase(randomVec.begin());
			rPage = frameTableVec[frameIndex];
		}

		Page cPage;
		for(int i = 0; i < frameTableVec.size(); i++) {
			cPage = frameTableVec[i];
			if(qPageSame(rPage, cPage) == 1) {
				pageVec.push_back(iPage);
				frameTableVec[i] = iPage;

				TimeVecStu *nStu;
				nStu = & processVec[iPage.processNum-1].loadedTStu[iPage.pageNum];
				nStu->timeVec.push_back(timeI);

				TimeVecStu *rStu;
				rStu = & processVec[rPage.processNum-1].evictedTStu[rPage.pageNum];
				rStu->timeVec.push_back(timeI);
				
				returnInt = i;
				break;				
			}
		}
	}

	return returnInt;
}


