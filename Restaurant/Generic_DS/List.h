#pragma once
#include"Node.h"
#include<iostream>

template<class T>
class  List
{
private:
 Node<T>* Head;
 int count;

public:
	List();
	bool IsEmpty();
	int GetLength();
	bool Insert(T newEntry);
	bool Remove(int pos);
	bool RemovePointer(T pos);
	bool Removefirst(T& pos);
	void Clear();
	T GetEntry(int pos);
	Node<T>* GetNodeAt(int pos);
	const T * toArray() const;


};

template<class T>
List<T>::List() {
	Head = NULL;
	count = 0;
}

template<class T>
bool List<T>::IsEmpty(){
	return count==0;}

template<class T>
int List<T>::GetLength(){
	return count;}

template<class T>
bool List<T>::Insert(T newEntry){

	if(Head==NULL) 
	{
		Head=new Node<T>;
		Head->setItem(newEntry);
		Head->setNext(NULL);
		count++;
		return true;
	}
	Node<T>*curr=Head;
	while(curr && curr->getNext())
	{
		curr=curr->getNext();
	}
	Node<T>*n=new Node<T>;
	n->setItem(newEntry);
	curr->setNext(n);
	n->setNext(NULL);
	count++;
	return true;

}
template<class T>
Node<T>* List<T>::GetNodeAt(int pos)
{
   if(pos>=1 && pos<=count)
   {
	   Node<T>*curr=Head;
	   for(int i=1 ;i<pos;i++)
	   {
		   curr=curr->getNext();
	   }
	   return curr;
   }
}

template<class T>
bool List<T>::Remove(int pos){
	/*if (pos == 0)
	{
		Node<T>* scan = Head;
		Head = Head->getNext();
		delete scan;
		count--;
		return true;
	}*/
	bool Abletoremove=(pos>=1 && pos<=count);
	if(Abletoremove){
	Node<T>* scan=NULL;
	if(pos==1)
	{
		scan=Head;
		Head=Head->getNext();
		
	}
	else {
		Node<T>*previous=GetNodeAt(pos-1);
		scan=previous->getNext();
		previous->setNext(scan->getNext());
	}
	scan->setNext(NULL);
	delete scan;
	scan=NULL;
	count--;
	}
	return Abletoremove;
}

template<class T>
bool List<T>::RemovePointer(T pos)
{
	if(IsEmpty())return false;
	int c=1;
	Node<T>*curr=Head;
	while(curr){
		if(curr->getItem()==pos){
			Remove(c);
			return true;
		}
		curr=curr->getNext();
		c++;
	}
	return false;

}

	template<class T>
	void List<T>::Clear()
	{
		while(!IsEmpty()){
			remove(1);
	}
	}
template<class T>
	T List<T>::GetEntry(int pos){
		Node<T>*scan=Head;
		if(pos==1){return Head->getItem();}
		for(int i=1;i<pos;i++)
		{scan=scan->getNext();}
		return scan->getItem();
	}

	
	template < class T>
	const T * List<T>::toArray() const
	{
		T * ListContents = new T[count];
		Node<T>* curPtr = Head;
		int counter = 0;
		while ((curPtr != nullptr) && (counter < count))
		{
			ListContents[counter] = curPtr->getItem();
			curPtr = curPtr->getNext();
			counter++;
		} // end while
		return ListContents;
	} // end toArray

	template < class T>
	bool List<T>::Removefirst(T& pos) {
		if (count == 0)return false;
		Node<T>* curPtr = Head;
		pos = curPtr->getItem();
		Head = Head->getNext();
		delete curPtr;
		count--;
		return true;
	}





