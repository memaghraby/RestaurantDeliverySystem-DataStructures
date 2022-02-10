#pragma once
#ifndef __PRIORITYQUEUE_H_
#define __PRIORITYQUEUE_H_

#include "PriorityNode.h"

template <typename T>
class PriorityQueue
{
private:

	PriorityNode<T>* backPtr;
	PriorityNode<T>* frontPtr;
	int count;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry, double Pr);
	bool enqueue(const T& newEntry, double Pr, double Pr2);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	int getcount() const;
	~PriorityQueue();
};
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: Queue()
The constructor of the Queue class.

*/

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
	count = 0;

}
/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: isEmpty
Sees whether this queue is empty.

Input: None.
Output: True if the queue is empty; otherwise false.
*/
template <typename T>
bool PriorityQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

/*Function:enqueue
Adds newEntry at the back of this queue.

Input: newEntry .
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry, double Pr)
{
	PriorityNode<T>* newNodePtr = new PriorityNode<T>(newEntry, Pr);
	if (!newNodePtr)return false;
	if (isEmpty())
	{
		frontPtr = newNodePtr;
		backPtr = newNodePtr;
		count++;
		return true;
	}
	PriorityNode<T>* curr = frontPtr;
	if (curr->getpriority() < Pr) {
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
		count++;
		return true;
	}
	while (curr->getNext() && curr->getNext()->getpriority() >= Pr) {
		curr = curr->getNext();
	}
	newNodePtr->setNext(curr->getNext());
	curr->setNext(newNodePtr);
	count++;
	return true;

}

template <typename T>
bool PriorityQueue<T>::enqueue(const T& newEntry, double Pr, double Pr2) 
{
	PriorityNode<T>* newNodePtr = new PriorityNode<T>(newEntry, Pr);
	if (!newNodePtr)return false;
	if (isEmpty())
	{
		frontPtr = newNodePtr;
		backPtr = newNodePtr;
		count++;
		return true;
	}
	PriorityNode<T>* curr = frontPtr;
	if (curr->getpriority() < Pr) {
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
		count++;
		return true;
	}
	else if (curr->getpriority() == Pr) {
		if (curr->getItem()->GetServeTime() > Pr2) {
			newNodePtr->setNext(frontPtr);
			frontPtr = newNodePtr;
			count++;
			return true;
		}
	}
	while (curr->getNext() && curr->getNext()->getpriority() >= Pr) {
		if (curr->getNext()->getpriority() == Pr) {
			if (curr->getNext()->getItem()->GetServeTime() <= Pr2)
				curr = curr->getNext();
			else break;
		}
		else curr = curr->getNext();
	}
	newNodePtr->setNext(curr->getNext());
	curr->setNext(newNodePtr);
	count++;
	return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Function: dequeue
Removes the front of this queue. That is, removes the item that was added
earliest.

Input: None.
Output: True if the operation is successful; otherwise false.
*/

template <typename T>
bool PriorityQueue<T>::dequeue(T& frntEntry)
{
	if (isEmpty())
		return false;

	PriorityNode<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;

	count--;
	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

/*
Function: peekFront
gets the front of this queue. The operation does not modify the queue.

Input: None.
Output: The front of the queue.
return: flase if Queue is empty
*/
template <typename T>
bool PriorityQueue<T>::peekFront(T& frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;

}

template <typename T>
int PriorityQueue<T>::getcount() const {
	return count;
}
///////////////////////////////////////////////////////////////////////////////////

template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
}
#endif