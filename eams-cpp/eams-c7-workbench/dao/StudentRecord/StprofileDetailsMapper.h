#pragma once

#include "../../domain/do/StudentRecord/stclassrecord/StclassRecordDO.h"
#include "Mapper.h"

class StprofileDetailsViewMapper :public Mapper<StprofileDetailsViewDO>
{
public:
	StprofileDetailsViewDO mapper(ResultSet* res) const override
	{
		StprofileDetailsViewDO data;
		data.setFamilyRel(res->getInt("family_rel")); // 家庭关系 (tinyint(4))
		data.setName(res->getString("name")); // 姓名 (varchar(20))
		data.setStage(res->getInt("stage")); // 阶段状态0意向学员 (tinyint(2))
		data.setGender(res->getInt("gender")); // 性别 (tinyint(2))
		data.setBirthday(res->getString("birthday")); // 生日 (date)
		data.setAddTime(res->getString("add_time")); // 加入时间 (datetime(0))
		data.setIdcard(res->getString("idcard")); // 身份证号 (varchar(30))
		data.setGrade(res->getInt("grade")); // 入学年份 (year)
		data.setJoinDate(res->getString("join_date")); // 入学日期 (date)
		data.setCredit(res->getInt("credit")); // 学生积分 (int(20))
		data.setMobile(res->getString("mobile"));
		data.setCloseTime(res->getInt("close_time"));
		data.setLessonCount(res->getInt("lesson_count"));
		data.setFamilyName(res->getString("family_name"));
		data.setClassName(res->getString("class_name"));		
		return data;
	}
};