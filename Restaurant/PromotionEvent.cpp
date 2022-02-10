#include"PromotionEvent.h"
#include"Rest\Restaurant.h"


PromotionEvent::PromotionEvent(int eTime, int oID, double eMoney):Event(eTime, oID)
{
	ExMon=eMoney;
}



void PromotionEvent::Execute(Restaurant* pRest)
{

	Order* OrdtoProm = pRest->getordertocancel(OrderID);
	if (OrdtoProm)
	{
		pRest->cancelOrder(OrdtoProm);
		OrdtoProm->SetType(TYPE_VIP);
		OrdtoProm->SetMoney(OrdtoProm->GetMoney() + ExMon);
		pRest->AddArrivalOrder(OrdtoProm);
	}
	
}
