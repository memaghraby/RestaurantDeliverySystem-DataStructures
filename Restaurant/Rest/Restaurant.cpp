#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;

#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include"Motorcycle.h"
#include"Order.h"
#include"..\Generic_DS\Queue.h"
#include "..\CancellationEvent.h"
#include "..\PromotionEvent.h"


Restaurant::Restaurant() 
{
	pGUI = NULL;
	for (int i = 0; i < 4; i++)
	{
		Served_VIP[i] = 0;
		Served_Frozen[i] = 0;
		Served_Normal[i] = 0;
	}
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
		
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		Interactive();
		break;
	case MODE_STEP:
		StepByStep();
		break;
	case MODE_SLNT:
		Silent();
		break;
	
	};

}



//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
void Restaurant::ExecuteEvents(int CurrentTimeStep)
{
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return;

		pE->Execute(this);
		EventsQueue.dequeue(pE);	//remove event from the queue
		delete pE;		//deallocate event object from memory
	}
	
}


Restaurant::~Restaurant()
{
		delete pGUI;
}




////////////////////////////////////////////////////////////////////////////////
void Restaurant::StepByStep() {
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));
	pGUI->PrintMessage("please enter the name of the file you want to load: ");
	string S = pGUI->GetString() + ".txt";
	ifstream inputFile;
	inputFile.open( S , ios::in);
	if (inputFile.is_open())
		LoadData(inputFile);
	else pGUI->PrintMessage("Didn't load file, click to END program");
	inputFile.close();
	pGUI->UpdateInterface();
	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty() || pGUI->GetOrderCount()!=0)
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);


		//assigning motorcycles
		FinishedMotorcycles(CurrentTimeStep);
		Assigning_VIP_Motorcycles(CurrentTimeStep);
		Assigning_Frozen_Motorcycles(CurrentTimeStep);
		Assigning_Normal_Motorcycles(CurrentTimeStep);
		

		ExecuteEvents(CurrentTimeStep);	

		//auto promotion:
		AutoPromotion(CurrentTimeStep);

		pGUI->UpdateInterface();

		PrintLastStep();

		PrintInStatusBar();

		Sleep(1000);
		CurrentTimeStep++;	//advance timestep
	}
	pGUI->PrintMessage("please enter the name of the file you want to Save: ");
	SaveFile();
    pGUI->PrintMessage("Saving the details right now ");
	Sleep(1000);
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

}


void Restaurant::Interactive() {
	Order* pOrd;
	Event* pEv;
	srand(time(NULL));
	pGUI->PrintMessage("please enter the name of the file you want to load: ");
	string S = pGUI->GetString() + ".txt";
	ifstream inputFile;
	inputFile.open( S , ios::in);
	if (inputFile.is_open())
		LoadData(inputFile);
	else pGUI->PrintMessage("Didn't load file, click to END program");
	inputFile.close();
	pGUI->UpdateInterface();
	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty() || pGUI->GetOrderCount()!=0)
	{
		//print current timestep
		char timestep[10];
		itoa(CurrentTimeStep, timestep, 10);
		pGUI->PrintMessage(timestep);


		//assigning motorcycles
		FinishedMotorcycles(CurrentTimeStep);
		Assigning_VIP_Motorcycles(CurrentTimeStep);
		Assigning_Frozen_Motorcycles(CurrentTimeStep);
		Assigning_Normal_Motorcycles(CurrentTimeStep);
		

		ExecuteEvents(CurrentTimeStep);	

		//auto promotion:
		AutoPromotion(CurrentTimeStep);

		pGUI->UpdateInterface();

		PrintLastStep();

		PrintInStatusBar();

		pGUI->waitForClick();
		CurrentTimeStep++;	//advance timestep
	}
	pGUI->PrintMessage("please enter the name of the file you want to Save: ");
	SaveFile();
    pGUI->PrintMessage("Saving the details right now ");
	Sleep(1000);
	pGUI->PrintMessage("generation done, click to END program");
	pGUI->waitForClick();

}

void Restaurant::Silent()
{
Order* pOrd;
	Event* pEv;
	srand(time(NULL));
	pGUI->PrintMessage("please enter the name of the file you want to load: ");
	string S = pGUI->GetString() + ".txt";
	ifstream inputFile;
	inputFile.open( S , ios::in);
	if (inputFile.is_open())
		LoadData(inputFile);
	else pGUI->PrintMessage("Didn't load file, click to END program");
	inputFile.close();
	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while (!EventsQueue.isEmpty() || pGUI->GetOrderCount()!=0)
	{
		

		//assigning motorcycles
		FinishedMotorcycles(CurrentTimeStep);
		Assigning_VIP_Motorcycles(CurrentTimeStep);
		Assigning_Frozen_Motorcycles(CurrentTimeStep);
		Assigning_Normal_Motorcycles(CurrentTimeStep);
		

		ExecuteEvents(CurrentTimeStep);	

		//auto promotion:
		AutoPromotion(CurrentTimeStep);

		CurrentTimeStep++;	//advance timestep

	}
	pGUI->ResetDrawingList();
	pGUI->UpdateInterface();
	pGUI->PrintMessage("please enter the name of the file you want to Save: ");
	SaveFile();
    pGUI->PrintMessage("Saving the details right now ");
	Sleep(1000);
	pGUI->PrintMessage("generation done,ENDING program");
	Sleep(1000);

}



void Restaurant::Assigning_VIP_Motorcycles(int c)
{
	for (int i = 0; i < 4; i++)
	{
		Order* OrderToServe = NULL;
		Motorcycle* motor = NULL;

		if (!VIP_order[i].isEmpty()) {
			if (!VIP_motor[i].isEmpty()) {
				VIP_motor[i].dequeue(motor);
			}
			else if (!Normal_motor[i].isEmpty()) {
				Normal_motor[i].dequeue(motor);
			}
			else if (!Frozen_motor[i].isEmpty()) {
				Frozen_motor[i].dequeue(motor);
			}
			if (motor) {
				VIP_order[i].dequeue(OrderToServe);
				pGUI->DeleteServedOrder(OrderToServe->GetID());
				OrderToServe->SetWaitingTime(c - OrderToServe->GetArrivalTime());
				OrderToServe->SetServeTime(OrderToServe->GetDistance() / motor->GetSpeed());
				OrderToServe->SetFinishTime(OrderToServe->GetArrivalTime() + OrderToServe->GetWaitingTime() + OrderToServe->GetServeTime());
				motor->SetOrder(OrderToServe);
				motor->SetAvailableTime(OrderToServe->GetFinishTime() + OrderToServe->GetServeTime());
				int priority = -motor->GetAvailableTime();
				Motors_In_Service.enqueue(motor, priority);
				LastStepMotorcycles.enqueue(motor);
				Served_VIP[i]++;
				ServedOrders[OrderToServe->GetRegion()].enqueue(OrderToServe, -OrderToServe->GetFinishTime(), OrderToServe->GetServeTime());
				ServedOrder.enqueue(OrderToServe, -OrderToServe->GetFinishTime(), -OrderToServe->GetServeTime());
			}
		}
	}
}

void Restaurant::Assigning_Frozen_Motorcycles(int c)
{
	for (int i = 0; i < 4; i++)
	{
		Order* OrderToServe = NULL;
		Motorcycle* motor = NULL;

		if (!Frozen_order[i].isEmpty()) {
			if (!Frozen_motor[i].isEmpty()) {
				Frozen_motor[i].dequeue(motor);
				Frozen_order[i].dequeue(OrderToServe);
				pGUI->DeleteServedOrder(OrderToServe->GetID());
				OrderToServe->SetWaitingTime(c - OrderToServe->GetArrivalTime());
				OrderToServe->SetServeTime(OrderToServe->GetDistance() / motor->GetSpeed());
				OrderToServe->SetFinishTime(OrderToServe->GetArrivalTime() + OrderToServe->GetWaitingTime() + OrderToServe->GetServeTime());
				motor->SetOrder(OrderToServe);
				motor->SetAvailableTime(OrderToServe->GetFinishTime() + OrderToServe->GetServeTime());
				int priority = -motor->GetAvailableTime();
				Motors_In_Service.enqueue(motor, priority);
				LastStepMotorcycles.enqueue(motor);
			    Served_Frozen[i]++;
				ServedOrders[OrderToServe->GetRegion()].enqueue(OrderToServe, -OrderToServe->GetFinishTime(), OrderToServe->GetServeTime());
				ServedOrder.enqueue(OrderToServe, -OrderToServe->GetFinishTime(), -OrderToServe->GetServeTime());
			}
		}
	}
}

void Restaurant::Assigning_Normal_Motorcycles(int c)
{
	for (int i = 0; i < 4; i++)
	{
		Order* OrderToServe = NULL;
		Motorcycle* motor = NULL;

		if (!Normal_order[i].IsEmpty()) {
			if (!Normal_motor[i].isEmpty()) {
				Normal_motor[i].dequeue(motor);
			}
			else if (!VIP_motor[i].isEmpty()) {
				VIP_motor[i].dequeue(motor);
			}

			if (motor) {
				Normal_order[i].Removefirst(OrderToServe);
				pGUI->DeleteServedOrder(OrderToServe->GetID());
				OrderToServe->SetWaitingTime(c - OrderToServe->GetArrivalTime());
				OrderToServe->SetServeTime(OrderToServe->GetDistance() / motor->GetSpeed());
				OrderToServe->SetFinishTime(OrderToServe->GetArrivalTime() + OrderToServe->GetWaitingTime() + OrderToServe->GetServeTime());
				motor->SetOrder(OrderToServe);
				motor->SetAvailableTime(OrderToServe->GetFinishTime() + OrderToServe->GetServeTime());
				int priority = -motor->GetAvailableTime();
				Motors_In_Service.enqueue(motor, priority);
				LastStepMotorcycles.enqueue(motor);
				Served_Normal[i]++;
				ServedOrders[OrderToServe->GetRegion()].enqueue(OrderToServe, -OrderToServe->GetFinishTime(), OrderToServe->GetServeTime());
				ServedOrder.enqueue(OrderToServe, -OrderToServe->GetFinishTime(), -OrderToServe->GetServeTime());
			}
		}
	}
}


void Restaurant::FinishedMotorcycles(int c)
{
	Motorcycle* Motor = NULL;
	Motors_In_Service.peekFront(Motor);
	while (Motor && Motor->GetAvailableTime() <= c)
	{
		Motors_In_Service.dequeue(Motor);
		switch (Motor->GetType())
		{
		case TYPE_VIP:
			VIP_motor[Motor->GetRegion()].enqueue(Motor,Motor->GetSpeed());
			break;
		case TYPE_NRM:
			Normal_motor[Motor->GetRegion()].enqueue(Motor,Motor->GetSpeed());
			break;
		case TYPE_FROZ:
			Frozen_motor[Motor->GetRegion()].enqueue(Motor,Motor->GetSpeed());
			break;
		};
		Motors_In_Service.peekFront(Motor);
	}
}


//Added:
void Restaurant::AddArrivalOrder(Order *pOrd)
{
	ORD_TYPE ordertype = pOrd->Getordertype();
	pGUI->AddOrderForDrawing(pOrd);


	switch (ordertype)	
	{
	case TYPE_NRM:{
		Normal_order[pOrd->GetRegion()].Insert(pOrd);
		break;}
	case TYPE_FROZ:{
		Frozen_order[pOrd->GetRegion()].enqueue(pOrd);
		break;}
	case TYPE_VIP:{
		double pr = (1.6 * pOrd->GetArrivalTime() + 0.5 * pOrd->GetMoney() + 0.16 * pOrd->GetDistance());
		VIP_order[pOrd->GetRegion()].enqueue(pOrd, pr);
		break;}
	};
}

void Restaurant::cancelOrder(Order* OrdCancel)
{
	if (!OrdCancel)
		return;
	Order* const* ptr = Normal_order[OrdCancel->GetRegion()].toArray();
	int index = -1;
	for (int i = 0; i < Normal_order[OrdCancel->GetRegion()].GetLength(); i++)
	{
		if (ptr[i]->GetID() == OrdCancel->GetID())
		{
			index = i;
			break;
		}
	}
		pGUI->RemoveOrderForDrawing(OrdCancel->GetID());
		pGUI->UpdateInterface();
		Normal_order[OrdCancel->GetRegion()].Remove(index+1);
	
}

Order* Restaurant::getordertocancel(int id)
{
	for (int i = 0; i < 4; i++)
	{
		Order* const* ptr = Normal_order[i].toArray();
		for (int j = 0; j < Normal_order[i].GetLength(); j++)
		{
			if (ptr[j]->GetID() == id)
				return ptr[j];
		}
	}
	return NULL;
}


REGION Restaurant::changeREGION(char x)
{
	switch (x)
	{
	case 'A':
	    return A_REG;
			break;
	case 'B':
		return B_REG;
			break;
	case 'C':
		return C_REG;
			break;
	case 'D':
		return D_REG;
			break;
	}
}

ORD_TYPE Restaurant::changeTYP(char y)
{
	switch (y)
	{
	case 'N':
		return 	TYPE_NRM;	//normal order
		break;
	case 'F':
		return TYPE_FROZ;	//frozen
		break;
	case 'V':
		return TYPE_VIP;	//VIP
		break;
	}
}


char Restaurant::changeCHAR(ORD_TYPE z)
{
	switch (z)
	{
	case TYPE_NRM:
		return 'N';	
		break;
	case TYPE_FROZ:
		return 'F';	
		break;
	case TYPE_VIP:
		return 'V';	
		break;
	}
}


void Restaurant::LoadData(ifstream & infile)
{
int TS; char TYP; int ID; int DST;
double MON; char REG;
 int SN,SF,SV; //speeds
 int NA,FA,VA; // no. of motor cyc. in region A
 int NB,FB,VB; // no. of motor cyc. in region B
 int NC,FC,VC; // no. of motor cyc. in region C
 int ND,FD,VD; // no. of motor cyc. in region D
 int AP; // auto promotion.
 int NOE; // no of events.
 //char EventType ; int TS; char TYP; int ID; int DST;
 //double MON; char REG;
 /////infile>>data members
 infile>>SN>>SF>>SV;
 infile>>NA>>FA>>VA;
 infile>>NB>>FB>>VB;
 infile>>NC>>FC>>VC;
 infile>>ND>>FD>>VD;
 infile>>AP;
 infile>>NOE;

 int motorcycle_ids = 1;
 AddNormalMotors(NA, NB, NC, ND, SN, motorcycle_ids);
 AddFrozenMotors(FA, FB, FC, FD, SF, motorcycle_ids);
 AddVIPMotors(VA, VB, VC, VD, SV, motorcycle_ids);

 char EventType;
 int i = 0;
 while(i<NOE)
 {
 infile>>EventType;
 if(EventType=='R')
 {
	 infile >> TS >> TYP >> ID >> DST >> MON >> REG;
	 ORD_TYPE typ=changeTYP(TYP);
	 REGION reg=changeREGION(REG);
	 Event*ev=new ArrivalEvent(TS,ID,typ,reg,DST,MON);
	 AddEvent(ev);
 }
 else if (EventType=='X')
 {
	 infile>>TS>>ID;
	 Event*pointer=new CancellationEvent(TS,ID);
	  AddEvent(pointer);
 }
 else 
 {
	 infile>>TS>>ID>>MON;
	 Event*pointer=new PromotionEvent(TS,ID,MON);
	  AddEvent(pointer);
 }
 i++;
 }

 AutoProm=AP;
}

// autopromotion:
void Restaurant::AutoPromotion(int CurrentTimeStep)
{
	
	for (int i = 0; i < 4; i++)
	{
		Order* const* ptr = Normal_order[i].toArray();
		for (int j = 0; j < Normal_order[i].GetLength(); j++)
		{
			if (CurrentTimeStep-ptr[j]->GetArrivalTime()>=AutoProm)
			{cancelOrder(ptr[j]);
			ptr[j]->SetType(TYPE_VIP);
			AddArrivalOrder(ptr[j]);
			}
		}
	}

}




void Restaurant::AddNormalMotors(int NA, int NB, int NC, int ND, int SN, int &id)
{
	int limitspeed = SN + 10;
	for (int i = 0; i < NA; i++)
	{
		Motorcycle* mtr = new Motorcycle(SN, A_REG, TYPE_NRM, id);
		Normal_motor[0].enqueue(mtr,SN);
		id++;
		SN++;
		if (SN == limitspeed)SN = SN - 10;
	}
	for (int i = 0; i < NB; i++)
	{
		Motorcycle* mtr = new Motorcycle(SN, B_REG, TYPE_NRM, id);
		Normal_motor[1].enqueue(mtr,SN);
		id++;
		SN++;
		if (SN == limitspeed)SN = SN - 10;
	}
	for (int i = 0; i < NC; i++)
	{
		Motorcycle* mtr = new Motorcycle(SN, C_REG, TYPE_NRM, id);
		Normal_motor[2].enqueue(mtr,SN);
		id++;
		SN++;
		if (SN == limitspeed)SN = SN - 10;
	}
	for (int i = 0; i < ND; i++)
	{
		Motorcycle* mtr = new Motorcycle(SN, D_REG, TYPE_NRM, id);
		Normal_motor[3].enqueue(mtr,SN);
		id++;
		SN++;
		if (SN == limitspeed)SN = SN - 10;
	}
}
void Restaurant::AddFrozenMotors(int FA, int FB, int FC, int FD, int SF, int &id)
{
	int limitspeed = SF + 10;
	for (int i = 0; i < FA; i++)
	{
		Motorcycle* mtr = new Motorcycle(SF, A_REG, TYPE_FROZ, id);
		Frozen_motor[0].enqueue(mtr,SF);
		id++;
		SF++;
		if (SF == limitspeed)SF = SF - 10;
	}
	for (int i = 0; i < FB; i++)
	{
		Motorcycle* mtr = new Motorcycle(SF, B_REG, TYPE_FROZ, id);
		Frozen_motor[1].enqueue(mtr, SF);
		id++;
		SF++;
		if (SF == limitspeed)SF = SF - 10;
	}
	for (int i = 0; i < FC; i++)
	{
		Motorcycle* mtr = new Motorcycle(SF, C_REG, TYPE_FROZ, id);
		Frozen_motor[2].enqueue(mtr, SF);
		id++;
		SF++;
		if (SF == limitspeed)SF = SF - 10;
	}
	for (int i = 0; i < FD; i++)
	{
		Motorcycle* mtr = new Motorcycle(SF, D_REG, TYPE_FROZ, id);
		Frozen_motor[3].enqueue(mtr, SF);
		id++;
		SF++;
		if (SF == limitspeed)SF = SF - 10;
	}
}

void Restaurant::AddVIPMotors(int VA, int VB, int VC, int VD, int SV, int &id)
{
	int limitspeed = SV + 10;
	for (int i = 0; i < VA; i++)
	{
		Motorcycle* mtr = new Motorcycle(SV, A_REG, TYPE_VIP, id);
		VIP_motor[0].enqueue(mtr,SV);
		id++;
		SV++;
		if (SV == limitspeed)SV = SV - 10;
	}
	for (int i = 0; i < VB; i++)
	{
		Motorcycle* mtr = new Motorcycle(SV, B_REG, TYPE_VIP, id);
		VIP_motor[1].enqueue(mtr, SV);
		id++;
		SV++;
		if (SV == limitspeed)SV = SV - 10;
	}
	for (int i = 0; i < VC; i++)
	{
		Motorcycle* mtr = new Motorcycle(SV, C_REG, TYPE_VIP, id);
		VIP_motor[2].enqueue(mtr, SV);
		id++;
		SV++;
		if (SV == limitspeed)SV = SV - 10;
	}
	for (int i = 0; i < VD; i++)
	{
		Motorcycle* mtr = new Motorcycle(SV, D_REG, TYPE_VIP, id);
		VIP_motor[3].enqueue(mtr, SV);
		id++;
		SV++;
		if (SV == limitspeed)SV = SV - 10;
	}
}

void Restaurant::PrintInStatusBar() {
	char availableno[10];
	itoa(Normal_order[0].GetLength(), availableno, 10);
	pGUI->PrintMessageCoordinates(10, 430, "No of NormalOrders-> RegA=" + (string)availableno);
	itoa(Normal_order[1].GetLength(), availableno, 10);
	pGUI->PrintMessageCoordinates(250, 430, "RegB=" + (string)availableno);
	itoa(Normal_order[2].GetLength(), availableno, 10);
	pGUI->PrintMessageCoordinates(340, 430, "RegC=" + (string)availableno);
	itoa(Normal_order[3].GetLength(), availableno, 10);
	pGUI->PrintMessageCoordinates(440, 430, "RegD=" + (string)availableno);
	itoa(VIP_order[0].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(10, 450, "No of VIPOrders-> RegA=" + (string)availableno);
	itoa(VIP_order[1].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(250, 450, "RegB=" + (string)availableno);
	itoa(VIP_order[2].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(340, 450, "RegC=" + (string)availableno);
	itoa(VIP_order[3].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(440, 450, "RegD=" + (string)availableno);
	itoa(Frozen_order[0].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(10, 470, "No of FrozenOrders-> RegA=" + (string)availableno);
	itoa(Frozen_order[1].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(250, 470, "RegB=" + (string)availableno);
	itoa(Frozen_order[2].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(340, 470, "RegC=" + (string)availableno);
	itoa(Frozen_order[3].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(440, 470, "RegD=" + (string)availableno);


	
	itoa(Normal_motor[0].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(10, 490, "No of NMotorcycles-> RegA=" + (string)availableno);
	itoa(Normal_motor[1].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(250, 490, "RegB=" + (string)availableno);
	itoa(Normal_motor[2].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(340, 490, "RegC=" + (string)availableno);
	itoa(Normal_motor[3].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(440, 490, "RegD=" + (string)availableno);
	itoa(Frozen_motor[0].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(10, 510, "No of FMotorcycles-> RegA=" + (string)availableno);
	itoa(Frozen_motor[1].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(250, 510, "RegB=" + (string)availableno);
	itoa(Frozen_motor[2].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(340, 510, "RegC=" + (string)availableno);
	itoa(Frozen_motor[3].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(440, 510, "RegD=" + (string)availableno);
	itoa(VIP_motor[0].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(10, 530, "No of VMotorcycles-> RegA=" + (string)availableno);
	itoa(VIP_motor[1].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(250, 530, "RegB=" + (string)availableno);
	itoa(VIP_motor[2].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(340, 530, "RegC=" + (string)availableno);
	itoa(VIP_motor[3].getcount(), availableno, 10);
	pGUI->PrintMessageCoordinates(440, 530, "RegD=" + (string)availableno);
	
}



void Restaurant::PrintLastStep()
{
	char availableno[10];
	char available[10];
	Motorcycle* motor;
	int a = 80;   int b = 80;    int c = 80;       int d = 80;
	char m, o;
	pGUI->PrintMessageCoordinates(10, 550, "RegA: ");
	pGUI->PrintMessageCoordinates(10, 570, "RegB: ");
	pGUI->PrintMessageCoordinates(10, 590, "RegC: ");
	pGUI->PrintMessageCoordinates(10, 610, "RegD: ");
	while (LastStepMotorcycles.dequeue(motor))
	{
		itoa(motor->GetID(), availableno, 10);
		itoa(motor->GetOrderAssigned()->GetID(), available, 10);
		m = changeCHAR(motor->GetType());
		o = changeCHAR(motor->GetOrderAssigned()->GetType());
		switch (motor->GetRegion())
		{
		case A_REG:
			pGUI->PrintMessageCoordinates(a, 550, m + (string)availableno + '(' + o + (string)available + ')');
			a += 100;
			break;
		case B_REG:
			pGUI->PrintMessageCoordinates(b, 570, m + (string)availableno + '(' + o + (string)available + ')');
			b += 100;
			break;
		case C_REG:
			pGUI->PrintMessageCoordinates(c, 590, m + (string)availableno + '(' + o + (string)available + ')');
			c += 100;
			break;
		case D_REG:
			pGUI->PrintMessageCoordinates(d, 610, m + (string)availableno + '(' + o + (string)available + ')');
			d += 100;
			break;
		}	
	}

	itoa(Served_Normal[0], availableno, 10);
	pGUI->PrintMessageCoordinates(10, 630, "Served NormalOrders-> RegA=" + (string)availableno);
	itoa(Served_Normal[1], availableno, 10);
	pGUI->PrintMessageCoordinates(250, 630, "RegB=" + (string)availableno);
	itoa(Served_Normal[2], availableno, 10);
	pGUI->PrintMessageCoordinates(340, 630, "RegC=" + (string)availableno);
	itoa(Served_Normal[3], availableno, 10);
	pGUI->PrintMessageCoordinates(440, 630, "RegD=" + (string)availableno);
	itoa(Served_VIP[0], availableno, 10);
	pGUI->PrintMessageCoordinates(10, 650, "Served VIPOrders-> RegA=" + (string)availableno);
	itoa(Served_VIP[1], availableno, 10);
	pGUI->PrintMessageCoordinates(250, 650, "RegB=" + (string)availableno);
	itoa(Served_VIP[2], availableno, 10);
	pGUI->PrintMessageCoordinates(340, 650, "RegC=" + (string)availableno);
	itoa(Served_VIP[3], availableno, 10);
	pGUI->PrintMessageCoordinates(440, 650, "RegD=" + (string)availableno);
	itoa(Served_Frozen[0], availableno, 10);
	pGUI->PrintMessageCoordinates(10, 670, "Served FrozenOrders-> RegA=" + (string)availableno);
	itoa(Served_Frozen[1], availableno, 10);
	pGUI->PrintMessageCoordinates(250, 670, "RegB=" + (string)availableno);
	itoa(Served_Frozen[2], availableno, 10);
	pGUI->PrintMessageCoordinates(340, 670, "RegC=" + (string)availableno);
	itoa(Served_Frozen[3], availableno, 10);
	pGUI->PrintMessageCoordinates(440, 670, "RegD=" + (string)availableno);


}
void Restaurant::SaveFile()
{
	ofstream outputfile;
	string FileName=pGUI->GetString() + ".txt";
	outputfile.open(FileName ,ios::out);
	Order * pOrd;
	int TotalOrders=0;
	int TotalMotors=0;
	int TotalAvrSTime=0;
	int TotalAvrWTime=0;

	outputfile<<"\n\n";
	outputfile<<"FT\t " <<"ID\t "<<"AT\t "<<"WT\t " <<"ST\t";
	outputfile<<"\n\n";

	

	while(ServedOrder.dequeue(pOrd) && pOrd!=nullptr)
	 { 
		
		outputfile<<pOrd->GetFinishTime()<< "\t " <<pOrd->GetID()
			<< "\t " <<pOrd->GetArrivalTime() << "\t " <<pOrd->GetWaitingTime()
			<< "\t " <<pOrd->GetServeTime()<<endl;
	 }


	outputfile<<"................................................\n";
	outputfile<<"................................................\n";

	for (int i = 0; i < REG_CNT ; i++)
	 {	
	int numOrders=0,numVIP=0,numNorm=0,numFrozen=0,AvgWTime=0,AvgSTime=0;
	int motosVIP= VIP_motor[i].getcount();
	int motosNORM=Normal_motor[i].getcount();
	int motosFROZ=Frozen_motor[i].getcount();

	while(ServedOrders[i].dequeue(pOrd) && pOrd!=nullptr)
	 { 
		numOrders++;
		AvgWTime+=pOrd->GetWaitingTime();
		AvgSTime+=pOrd->GetServeTime();
		if(pOrd->GetType()==TYPE_VIP)
		numVIP++;
		else if (pOrd->GetType()==TYPE_FROZ)
		numFrozen++;
		else
		numNorm++;
	 }

	int motos=motosVIP+motosNORM+motosFROZ;
	
	if(numOrders != 0)
	{
		AvgSTime/=numOrders;
		AvgWTime/=numOrders;
	}

	if(i==0) outputfile<< "Region A:\n";
	else if (i==1)outputfile<< "Region B:\n";
	else if (i==2)outputfile<< "Region C:\n";
	else outputfile<< "Region D:\n";


	outputfile<< "\tOrders: "<<numOrders<<" "<<"[Norm: "<<numNorm<<" , Froz: " <<numFrozen<<", VIP: "<<numVIP<<"]\n";
	outputfile<< "\tMotors: "<<motos<<"[Norm: "<<motosNORM<<" , Froz: " <<motosFROZ<<", VIP: "<<motosVIP<<"]\n";
	outputfile<<"\tAvg Wait = "<<AvgWTime<<", Avg Serv = "<<AvgSTime<<"\n";
    int orders=numFrozen+numNorm+numVIP;
	int motors=motosVIP+motosNORM+motosFROZ;
	TotalOrders+=orders;
	TotalMotors+=motors;
	TotalAvrSTime+=AvgSTime;
	TotalAvrWTime+=AvgWTime;

	pOrd=nullptr;
}

	outputfile<<"\n\nTotal Information for the whole restaurant:\n";
	TotalAvrSTime/=4;
	TotalAvrWTime/=4;
	outputfile<<"\tOrders: "<<TotalOrders<<"\n\tMotors: "<<TotalMotors<<"\n\tAvg Wait = "<<TotalAvrWTime<<
		" , Avg Serv = "<<TotalAvrSTime;

    outputfile.close(); 
}
	
