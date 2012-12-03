#include "MonList.h"

MonList::MonList(){
	count = 0;
	istart = new Monster();
	iend = new Monster();

	istart->setPrev(NULL);
	istart->setNext(iend);
	iend->setNext(NULL);
	iend->setPrev(istart);
	nowNode = istart;
}

MonList::~MonList(){
	Monster* inow = istart->getNext();
	while(istart->getNext()!=iend){
		istart->setNext(inow->getNext());
		inow->getNext()->setPrev(istart);
		delete inow;
		inow = istart->getNext();
	}
	delete istart;
	delete iend;
}

void MonList::setNode(Monster* argu){
	if(count==0){
		Monster* inow;
		inow = argu;
		inow->setPrev(istart);
		inow->setNext(iend);
		istart->setNext(inow);
		iend->setPrev(inow);
	}
	else{
		Monster* inow;
		listPrev = istart;
		inow = istart->getNext();

		while(inow->getNext()!=NULL){
			listPrev = inow;
			inow = inow->getNext();
		}
		inow = argu;

		inow->setPrev(listPrev);
		listPrev->setNext(inow);

		inow->setNext(iend);
		iend->setPrev(inow);
		iend->setNext(NULL);
	}
	count++;
}
void MonList::delNode(int item_number){
	Monster* inow;
	if(!count==0){
		listPrev = istart;
		inow = listPrev->getNext();
		listNext = inow->getNext();
		do{
			if(inow->getNumber()==item_number){
				listPrev->setNext(listNext);
				listNext->setPrev(listPrev);
				inow = NULL;
				count--;
				break;
			}
			else{
				if(listNext==iend){
					break;
				}
				else{
					listPrev = inow;
					inow = listNext;
					listNext = listNext->getNext();
				}
			}
		}while(listNext!=iend);
	}
}

Monster* MonList::searchNode(){
	Monster* inow;
	nowNode = nowNode->getNext();
	inow = nowNode;
	if(nowNode->getNext()==iend){
		nowNode = istart;
	}
	return inow;
}

Monster* MonList::returnNode(){
	return nowNode;
}

int MonList::getCount(){
	return count;
}

Monster* MonList::getStart(){
	return istart;
}

Monster* MonList::getEnd(){
	return iend;
}