#ifndef _CHECKAI_H_
#define _CHECKAI_H_
#include <process.h>
#include "Pattern.h"
#include "Settings.h"
class Checkai{
private:
	Pattern*	pCheckResult[MOVE_PATTERN_COUNT][ACTION_PATTERN_COUNT];
	BOOL		g_bChange;
	Pattern*	l_pRandPattern;
public:
	Checkai();
	~Checkai();
	Pattern* DoAction(int type,float time);
	VOID mixPattern();
	inline VOID StartPattern(int move,int type,float time){pCheckResult[move][type]->StartPlay(time);};
	inline VOID EndPattern(int move,int type,float time){pCheckResult[move][type]->EndPlay(time);};
	inline BOOL IsPlay(int move,int type,float time){return pCheckResult[move][type]->IsPlay(time);};
	inline VOID DuringPlay(int move,int type,float time){pCheckResult[move][type]->DuringPlay(time);};
	inline VOID NotDuringPlay(int move,int type){pCheckResult[move][type]->NotDuringPlay();}
	inline INT GetType(int type){return pCheckResult[type][type]->GetType();};
	/*inline void start(){
	_beginthreadex(NULL,0,ChangePattern,this,0,NULL);
	};
	*/
	//inline static UINT WINAPI ChangePattern(LPVOID p){
	//	for(int i=0;i<MOVE_PATTERN_COUNT;i++){
	//		for(int j=0;j<ACTION_PATTERN_COUNT;j++){
	//			Pattern* l_pCheck;
	//			for(int k=j+1;k<ACTION_PATTERN_COUNT;k++){
	//				if(pCheckResult[i][j]->GetRate() < pCheckResult[i][k]->GetRate()){
	//					l_pCheck = pCheckResult[i][j];
	//					pCheckResult[i][j] = pCheckResult[i][k];
	//					pCheckResult[i][k] = l_pCheck;
	//				}
	//			}
	//		}
	//		for(int j=0;j<ACTION_PATTERN_COUNT;j++){
	//			pCheckResult[i][j]->ResetRate();
	//		}
	//	}
	//	g_bChange = TRUE;
	//	_endthreadex(0);
	//	return 0;
	//};
	inline VOID SetChange(BOOL argu){g_bChange = argu;};
	inline BOOL NowChange(){return g_bChange;}
	inline VOID StartSorting(){
		for(int i=0;i<MOVE_PATTERN_COUNT;i++){
			for(int j=0;j<ACTION_PATTERN_COUNT;j++){
				Pattern* l_pCheck;
				for(int k=j+1;k<ACTION_PATTERN_COUNT;k++){
					if(pCheckResult[i][j]->GetRate() < pCheckResult[i][k]->GetRate()){
						l_pCheck = pCheckResult[i][j];
						pCheckResult[i][j] = pCheckResult[i][k];
						pCheckResult[i][k] = l_pCheck;
					}
				}
			}
			for(int j=0;j<ACTION_PATTERN_COUNT;j++){
				pCheckResult[i][j]->ResetRate();
			}
			delete pCheckResult[i][MOVE_PATTERN_COUNT-1];
			pCheckResult[i][MOVE_PATTERN_COUNT-1] = new Pattern(l_pRandPattern,2);
		}

		//for(int k=0;k<MOVE_PATTERN_COUNT;k++){
		//	QSort(pCheckResult[k],0,ACTION_PATTERN_COUNT-1);
		//}
	};
	inline VOID QSort(Pattern* pattern[], INT left, INT right){
		INT i;
		INT j;
		Pattern* temp;
		Pattern* pivot;
		if(left<right){
			i = left;
			j= right;
			pivot = pattern[left];
			while(i<j){
				while(pattern[i]->GetRate()>pivot->GetRate()){j--;}
				while(i<j&&pattern[i]->GetRate()<=pivot->GetRate()){i++;}
				temp = pattern[i];
				pattern[i] = pattern[j];
				pattern[j] = temp;
			}
			pattern[left] = pattern[i];
			pattern[i] = pivot;
			QSort(pattern,left,i-1);
			QSort(pattern,i+1,right);
		}
	};
};
#endif