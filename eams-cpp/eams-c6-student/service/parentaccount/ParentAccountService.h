#pragma once
#ifndef _PARENT_ACCOUNT_SERVICE_H_
#define _PARENT_ACCOUNT_SERVICE_H_
#include"domain/vo/parentaccount/ParentAccountVO.h"
#include"domain/query/parentaccount/ParentAccountQuery.h"
#include"domain/dto/parentaccount/ParentAccountDTO.h"
#include"dao/parentaccount/ParentAccountDAO.h"
/**
 * 家长账号业务层
 */
class ParentAccountService
{
private:
	ParentAccountDAO m_parentAccountDAO;
public:
	ParentAccountPageDTO listParentAccount(const ParentAccountQuery::Wrapper& query);
};

#endif // !_PARENT_ACCOUNT_SERVICE_H_
