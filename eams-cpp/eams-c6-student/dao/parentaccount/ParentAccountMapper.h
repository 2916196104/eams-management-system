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
		auto dto = ParentAccountDTO::createShared();
		dto->userId = rs->getInt64("user_id");
		dto->mobile = rs->getString("mobile").c_str();
		dto->name = rs->getString("name").c_str();
		dto->studentName = rs->getString("student_name").c_str();
		dto->wxName = rs->getString("wx_name").c_str();
		dto->loginTimes = rs->getInt("login_times");
		dto->latestLoginTime = rs->getString("latest_login_time").c_str();
		dto->latestLoginIp = rs->getString("latest_login_ip").c_str();
		dto->addTime = rs->getString("add_time").c_str();
		dto->state = rs->getInt("state");
		return dto;
	}
};

#endif // !_PARENT_ACCOUNT_MAPPER_H_
