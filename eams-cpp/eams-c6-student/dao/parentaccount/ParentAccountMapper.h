#pragma once
#ifndef _PARENT_ACCOUNT_MAPPER_H_
#define _PARENT_ACCOUNT_MAPPER_H_

#include "Mapper.h"
#include "domain/dto/parentaccount/ParentAccountDTO.h"

/**
 * 家长账号查询结果映射
 */
class ParentAccountMapper : public Mapper<ParentAccountDTO::Wrapper>
{
public:
	ParentAccountDTO::Wrapper mapper(ResultSet* rs) const override
	{
		return ParentAccountDTO::createShared();
	}
};

#endif // !_PARENT_ACCOUNT_MAPPER_H_
