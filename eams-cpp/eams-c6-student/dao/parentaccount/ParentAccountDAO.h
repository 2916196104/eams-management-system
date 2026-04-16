#pragma once
#ifndef _PARENT_ACCOUNT_DAO_H_
#define _PARENT_ACCOUNT_DAO_H_

#include "BaseDAO.h"
#include"domain/query/parentaccount/ParentAccountQuery.h"
#include"domain/do/student/StudentDO.h"


class ParentAccountDAO : public BaseDAO
{
public:
	uint64_t countParentAccount(const ParentAccountQuery::Wrapper& query);
	list<ParentAccountQueryDO> listParentAccount(const ParentAccountQuery::Wrapper& query);
};

#endif // !_PARENT_ACCOUNT_DAO_H_
