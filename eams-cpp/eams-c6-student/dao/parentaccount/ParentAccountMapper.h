#pragma once
#ifndef _PARENT_ACCOUNT_MAPPER_H_
#define _PARENT_ACCOUNT_MAPPER_H_

#include "Mapper.h"
#include"dao/parentaccount/ParentAccountDAO.h"
/**
 * ??????????????
 */
//using PtrParentAccountDO = shared_ptr<ParentAccountDO>;
class ParentAccountPageQueryMapper : public Mapper<ParentAccountQueryDO>
{
public:
	ParentAccountQueryDO mapper(ResultSet* rs) const override
	{
		//auto data = make_shared<ParentAccountDO>();
		ParentAccountQueryDO data;
		data.setUserId(rs->getString(1));
		data.setMobile(rs->getString(2));
		data.setName(rs->getString(3));
		data.setStudentName(rs->getString(4));
		data.setWxName(rs->getString(5));
		data.setLoginTimes(rs->getInt(6));
		data.setLatestLoginTime(rs->getString(7));
		data.setLatestLoginIp(rs->getString(8));
		data.setAddTime(rs->getString(9));
		data.setState(rs->getInt(10));
		/*data->setUserId(rs->getString("user_id"));
		data->setMobile(rs->getString("mobile"));
		data->setName(rs->getString("name"));
		data->setStudentName(rs->getString("student_name"));
		data->setWxName(rs->getString("wx_name"));
		data->setLoginTimes(rs->getInt("login_times"));
		data->setLatestLoginTime(rs->getString("latest_login_time"));
		data->setLatestLoginIp(rs->getString("latest_login_ip"));
		data->setAddTime(rs->getString("add_time"));
		data->setState(rs->getInt("state"));*/
		return data;
	}
};

#endif // !_PARENT_ACCOUNT_MAPPER_H_
