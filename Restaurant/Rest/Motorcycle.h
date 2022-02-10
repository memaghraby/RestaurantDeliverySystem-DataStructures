#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_

#include"Order.h"
#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	Order* orderassigned;
	int id;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service
	int AvailableTime;
	

public:
	Motorcycle(int MotorSpeed, REGION MotorRegion, ORD_TYPE MotorType,int ID);
	void SetStatus(STATUS TF);
	void SetOrder(Order* orderassign);
	void SetAvailableTime(int Av);
	int GetID()const;
	int GetSpeed() const;
	int GetAvailableTime() const;
	ORD_TYPE GetType() const;
	REGION GetRegion() const;
	Order* GetOrderAssigned() const;
	virtual ~Motorcycle();
};

#endif