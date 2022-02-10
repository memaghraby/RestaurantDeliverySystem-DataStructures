#pragma once
#ifndef __PRIORITYNODE_H_
#define __PRIORITYNODE_H_

template < typename T>
class PriorityNode
{
private:
	T item; // A data item
	PriorityNode<T>* next; // Pointer to next node
	int Priority;

public:
	PriorityNode();
	PriorityNode(const T & r_Item, double Pr);	//passing by const ref.
	PriorityNode(const T & r_Item, PriorityNode<T>* nextNodePtr, double Pr);
	void setItem(const T & r_Item);
	void setNext(PriorityNode<T>* nextNodePtr);
	T getItem() const;
	PriorityNode<T>* getNext() const;
	double getpriority() const;
}; // end Node


template < typename T>
PriorityNode<T>::PriorityNode()
{
	next = nullptr;
	Priority = 0;
}

template < typename T>
PriorityNode<T>::PriorityNode(const T& r_Item, double Pr)
{
	item = r_Item;
	next = nullptr;
	Priority = Pr;
}

template < typename T>
PriorityNode<T>::PriorityNode(const T& r_Item, PriorityNode<T>* nextNodePtr, double Pr)
{
	item = r_Item;
	next = nextNodePtr;
	Priority = Pr;
}
template < typename T>
void PriorityNode<T>::setItem(const T& r_Item)
{
	item = r_Item;
}

template < typename T>
void PriorityNode<T>::setNext(PriorityNode<T>* nextNodePtr)
{
	next = nextNodePtr;
}

template < typename T>
T PriorityNode<T>::getItem() const
{
	return item;
}

template < typename T>
PriorityNode<T>* PriorityNode<T>::getNext() const
{
	return next;
}


template < typename T>
double PriorityNode<T>::getpriority() const
{
	return Priority;
}

#endif