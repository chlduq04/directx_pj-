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
	while(inow!=iend){
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

void ItemsList::delNode(Items* node){
	node->getPrev()->setNext(node->getNext());
	node->getNext()->setPrev(node->getPrev());
	delete node;
	count--;
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

