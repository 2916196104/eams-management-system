#pragma once

#ifndef _REDEEMCREDIT_DAO_
#define  _REDEEMCREDIT_DAO_
#include "BaseDAO.h"
#include "../../../../domain/do/home/credit/redeemcredit/RedeemCreditDO.h"



class StudentCreditDAO : public BaseDAO
{
public:
	PtrStudentCreditDO selectByStudentId(uint64_t student_id);
	bool updateCredit(uint64_t id, int credit);

};

class CreditMallDAO : public BaseDAO
{
	public:
		PtrCreditMallDO selectByCreditMallId(uint64_t credit_id);
};

class MaterialDAO : public BaseDAO
{
public:
	PtrMaterialDO selectByMaterialId(uint64_t material_id);
	bool updateNum(uint64_t id, int consume_num);
};

#endif