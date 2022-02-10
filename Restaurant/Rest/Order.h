#ifndef __ORDER_H_
#define __ORDER_H_

#include "..\Defs.h"

class Order
{

protected:
	int ID;         //Each order has a unique ID (from 1 --> 999 )
	ORD_TYPE type;		//order type: Normal, Frozen, VIP
	REGION Region;  //Region of this order
	int Distance;	//The distance (in meters) between the order location and the resturant 
	                
	double totalMoney;	//Total order money

	int ArrTime, ServeTime, FinishTime, WaitingTime;	//arrival, service start, and finish times
	bool Active; //added
	bool Served; //

public:
	Order(int Atime, int ID, ORD_TYPE r_Type, REGION r_region, int dist, double money);
	virtual ~Order();

	int GetID();
	ORD_TYPE GetType() const;
	REGION GetRegion() const;
	int GetDistance() const;
	int GetMoney() const;
	int GetArrivalTime() const;
	ORD_TYPE Getordertype() const;
	int GetWaitingTime() const;
	int GetFinishTime() const;
	int GetServeTime() const;
	void SetWaitingTime(int WT);
	void SetFinishTime(int FT);
	void SetServeTime(int ST);
	void SetDistance(int d);
	void SetType(ORD_TYPE rtype);
	void SetMoney(double mon);
	
	// TODO: Add More Member Functions As Needed
	

};

#endif