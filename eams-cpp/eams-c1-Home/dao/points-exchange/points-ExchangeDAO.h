#pragma once


/*
 Copyright Zero One Star. All rights reserved.

 @Author: 光
 @Date: 2026/03/23
*/
#ifndef _EXCHANGE_DAO_H_
#define _EXCHANGE_DAO_H_

#include "stdafx.h"
#include "domain/GlobalInclude.h"
#include "domain/do/points-exchange/exchangeDo.h"
#include "BaseDAO.h"

class ExchangeDAO : public BaseDAO
{
private:
	

	/*
	插入兑换记录
	*/
public:
	


	  int64_t insert(const PtrExchangeDO& exchange);


	  /*
	  * 更新学生积分变动记录
	  */
	  int64_t insertCreditChangeRecord(const PtrExchangeDO& exchange, const int64_t& current_credit);

	  /*
	  查询学生当前积分
	  */
	  int64_t getStudentCurrentCredit(const int64_t& studentId);

	  /*
	  扣除学生积分
	  */
	  int deductStudentCredit(const int64_t& studentId, const int64_t& credit);
	
	

};



#endif // !_EXCHANGE_DAO_H_