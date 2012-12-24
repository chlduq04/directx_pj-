#include "ItemsList.h"
ItemsList::ItemsList(){
	nCount = 0;
	pStart = new Items();
	pEnd = new Items();

	pStart->SetPrev(NULL);
	pStart->SetNext(pEnd);
	pEnd->SetNext(NULL);
	pEnd->SetPrev(pStart);
	pNowNode = pStart;
}

ItemsList::~ItemsList(){
	Items* pNow = pStart->GetNext();
	while(pNow!=pEnd){
		pStart->SetNext(pNow ->GetNext());
		pNow ->GetNext()->SetPrev(pStart);
		delete pNow ;
		pNow  = pStart->GetNext();
	}
	delete pStart;
	delete pEnd;
}

void ItemsList::SetNode(Items* argu){
	if(nCount==0){
		Items* inow;
		inow = argu;
		inow->SetPrev(pStart);
		inow->SetNext(pEnd);
		pStart->SetNext(inow);
		pEnd->SetPrev(inow);
	}
	else{
		Items* inow;
		pListPrev = pStart;
		inow = pStart->GetNext();

		while(inow->GetNext()!=NULL){
			pListPrev = inow;
			inow = inow->GetNext();
		}
		inow = argu;

		inow->SetPrev(pListPrev);
		pListPrev->SetNext(inow);

		inow->SetNext(pEnd);
		pEnd->SetPrev(inow);
		pEnd->SetNext(NULL);
	}
	nCount++;
}

void ItemsList::DelNode(Items* node){
	node->GetPrev()->SetNext(node->GetNext());
	node->GetNext()->SetPrev(node->GetPrev());
	delete node;
	nCount--;
}

Items* ItemsList::SearchNode(){
	Items* pNow;
	pNowNode = pNowNode->GetNext();
	pNow = pNowNode;
	if(pNowNode->GetNext()==pEnd){
		pNowNode = pStart;
	}
	return pNow;
}

