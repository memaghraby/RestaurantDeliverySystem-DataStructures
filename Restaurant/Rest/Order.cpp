#include "Order.h"

Order::Order(int Atime,int id, ORD_TYPE r_Type, REGION r_region, int dist, double money)
{
	ArrTime=Atime;
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	type = r_Type;
	Region = r_region;
	Distance = dist;
	totalMoney = money;
}

Order::~Order()
{
}

int Order::GetID()
{
	return ID;
}


ORD_TYPE Order::GetType() const
{
	return type;
}

REGION Order::GetRegion() const
{
	return Region;
}

void Order::SetDistance(int d)
{
	Distance = d>0?d:0;
}

int Order::GetDistance() const
{
	return Distance;
}

int Order::GetMoney() const{
	return totalMoney;
}

int Order::GetArrivalTime() const{
	return ArrTime;
}

ORD_TYPE Order::Getordertype() const
{
	return type;
}
void Order::SetType(ORD_TYPE rtype)
{
	type=rtype;
}
void Order::SetMoney(double mon)
{
	totalMoney=mon;
}
int Order::GetWaitingTime() const 
{
	return WaitingTime;
}

int Order::GetFinishTime() const
{
	return FinishTime;
}

int Order::GetServeTime() const
{
	return ServeTime;
}


void Order::SetWaitingTime(int WT)
{
	WaitingTime = WT;
}

void Order::SetFinishTime(int FT)
{
	FinishTime = FT;
}

void Order::SetServeTime(int ST)
{
	ServeTime = ST;
}

