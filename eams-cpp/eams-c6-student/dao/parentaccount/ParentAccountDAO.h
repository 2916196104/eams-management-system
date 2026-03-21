#pragma once
#ifndef _PARENT_ACCOUNT_DAO_H_
#define _PARENT_ACCOUNT_DAO_H_

#include "BaseDAO.h"
#include"domain/query/parentaccount/ParentAccountQuery.h"

/**
 * 家长账号数据访问层
 */
class ParentAccountDAO : public BaseDAO
{
public:
	uint64_t countParentAccount(const ParentAccountQuery::Wrapper& query);

};

#endif // !_PARENT_ACCOUNT_DAO_H_
