#include "ItemsList.h"
ItemsList::ItemsList(){
	count = 0;
	istart = new Items();
	iend = new Items();

	istart->setPrev(NULL);
	istart->setNext(iend);
	iend->setNext(NULL);
	iend->setPrev(istart);
	nowNode = istart;
}

ItemsList::~ItemsList(){
	Items* inow = istart->getNext();
	while(istart->getNext()!=iend){
		istart->setNext(inow->getNext());
		inow->getNext()->setPrev(istart);
		delete inow;
		inow = istart->getNext();
	}
	delete istart;
	delete iend;
}

void ItemsList::setNode(Items* argu){
	if(count==0){
		Items* inow;
		inow = argu;
		inow->setPrev(istart);
		inow->setNext(iend);
		istart->setNext(inow);
		iend->setPrev(inow);
	}
	else{
		Items* inow;
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

void ItemsList::delNode(int item_number){
	Items* inow;
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

Items* ItemsList::searchNode(){
	Items* inow;
	nowNode = nowNode->getNext();
	inow = nowNode;
	if(nowNode->getNext()==iend){
		nowNode = istart;
	}
	return inow;
}

Items* ItemsList::returnNode(){
	return nowNode;
}

int ItemsList::getCount(){
	return count;
}

Items* ItemsList::getStart(){
	return istart;
}

Items* ItemsList::getEnd(){
	return iend;
}