#include "Motorcycle.h"


Motorcycle::Motorcycle(int MotorSpeed, REGION MotorRegion, ORD_TYPE MotorType,int ID)
{
	speed = MotorSpeed;
	region = MotorRegion;
	type = MotorType;
	id = ID;
}

void Motorcycle::SetStatus(STATUS TF)
{
	status = TF;
}

void Motorcycle::SetOrder(Order * orderassign)
{
	orderassigned = orderassign;
}

void Motorcycle::SetAvailableTime(int Av)
{
	AvailableTime = Av;
}

int Motorcycle::GetID() const
{
	return id;
}


int Motorcycle::GetSpeed() const
{
	return speed;
}

int Motorcycle::GetAvailableTime() const
{
	return AvailableTime;
}

ORD_TYPE Motorcycle::GetType() const
{
	return type;
}

REGION Motorcycle::GetRegion() const
{
	return region;
}

Order* Motorcycle::GetOrderAssigned() const
{
	return orderassigned;
}

Motorcycle::~Motorcycle()
{
}
