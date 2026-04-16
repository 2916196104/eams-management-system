#pragma once



#ifndef _REDEEMCREDIT_SERVICE_
#define _REDEEMCREDIT_SERVICE_
#include "BaseDAO.h"
#include "../../../../domain/dto/home/credit/redeemcredit/RedeemCreditDTO.h"
#include "../../../../domain/do/home/credit/redeemcredit/RedeemCreditDO.h"


class RedeemCreditService
{
public:
	std::string saveData(const RedeemCreditDTO::Wrapper& dto);
};







#endif