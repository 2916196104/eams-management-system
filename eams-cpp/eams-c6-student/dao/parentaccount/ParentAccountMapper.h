#pragma once
#ifndef _PARENT_ACCOUNT_MAPPER_H_
#define _PARENT_ACCOUNT_MAPPER_H_

#include "Mapper.h"
#include"dao/parentaccount/ParentAccountDAO.h"

//using PtrParentAccountDO = shared_ptr<ParentAccountDO>;
class ParentAccountPageQueryMapper : public Mapper<ParentAccountQueryDO>
{
public:
	ParentAccountQueryDO mapper(ResultSet* rs) const override
	{
		ParentAccountQueryDO data;
		data.setUserId(rs->getInt64(1));
		data.setMobile(rs->getString(2));
		data.setName(rs->getString(3));
		data.setStudentName(rs->getString(4));
		data.setWxName(rs->getString(5));
		data.setLoginTimes(rs->getInt(6));
		data.setLatestLoginTime(rs->getString(7));
		data.setLatestLoginIp(rs->getString(8));
		data.setAddTime(rs->getString(9));
		data.setState(rs->getInt(10));

		return data;
	}
};

#endif // !_PARENT_ACCOUNT_MAPPER_H_
