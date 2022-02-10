#ifndef __RESTAURANT_H_
#define __RESTAURANT_H_

#include "..\Defs.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"
#include "..\GUI\GUI.h"
#include "..\Generic_DS\Queue.h"
#include "..\Events\Event.h"
#include"..\Generic_DS\PriorityNode.h"
#include"..\Generic_DS\PriorityQueue.h"
#include"..\Generic_DS\List.h"
#include "Motorcycle.h"


#include "Order.h"

// it is the maestro of the project
class Restaurant  
{	
private:
	GUI *pGUI;
	Queue<Event*> EventsQueue;	//Queue of all events that will be loaded from file
	
	PriorityQueue<Order*> VIP_order[4];
	List<Order*> Normal_order[4];
	Queue<Order*> Frozen_order[4];
	

	PriorityQueue<Motorcycle*> VIP_motor[4];
	PriorityQueue<Motorcycle*> Normal_motor[4];
	PriorityQueue<Motorcycle*> Frozen_motor[4];

	PriorityQueue<Motorcycle*> Motors_In_Service;

	int AutoProm;

	Queue<Motorcycle*> LastStepMotorcycles;

	int Served_VIP[4];
	int Served_Normal[4];
	int Served_Frozen[4];

	PriorityQueue<Order*> ServedOrders[4];
	PriorityQueue<Order*> ServedOrder;

public:
	
	Restaurant();
	~Restaurant();
	void AddEvent(Event* pE);	//adds a new event to the queue of events
	void ExecuteEvents(int TimeStep);	//executes all events at current timestep
	void RunSimulation();
	void LoadData(ifstream & infile);
	ORD_TYPE changeTYP(char x);
	REGION changeREGION(char y);
	char changeCHAR(ORD_TYPE z);

	void Interactive();
	void StepByStep();
	void Silent();

	/// ==> 
	void PrintInStatusBar();
	void AddArrivalOrder(Order* po);
	void cancelOrder(Order* OrdCancel);
	Order* getordertocancel(int id);
	void AddNormalMotors(int NA, int NB, int NC, int ND, int SN,int &x);
	void AddFrozenMotors(int FA, int FB, int FC, int FD, int SF, int &x);
	void AddVIPMotors(int VA, int VB, int VC, int VD, int SV, int &x);
	void AutoPromotion(int c);
	void Assigning_VIP_Motorcycles(int c);
	void Assigning_Frozen_Motorcycles(int c);
	void Assigning_Normal_Motorcycles(int c);
	void FinishedMotorcycles(int c);
	void SaveFile();
	void PrintLastStep();
};

#endif