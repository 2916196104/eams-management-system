#pragma once

#include "../../DoInclude.h"

class StlistDO :public BaseDO
{
	MYSQL_SYNTHESIZE(int, id, Id); // 主键 (bigint(20) UNSIGNED)
	MYSQL_SYNTHESIZE(int, familyRel, FamilyRel); // 家庭关系 (tinyint(4))
	MYSQL_SYNTHESIZE(string, name, Name); // 姓名 (varchar(20))
	MYSQL_SYNTHESIZE(int, gender, Gender); // 性别 (tinyint(2))
	MYSQL_SYNTHESIZE(string, birthday, Birthday); // 生日 (date)
	MYSQL_SYNTHESIZE(string, addTime, AddTime); // 加入时间 (datetime(0))
	MYSQL_SYNTHESIZE(string, idcard, Idcard); // 身份证号 (varchar(30))
	MYSQL_SYNTHESIZE(int, grade, Grade); // 入学年份 (year)
	MYSQL_SYNTHESIZE(string, joinDate, JoinDate); // 入学日期 (date)
	MYSQL_SYNTHESIZE(int, credit, Credit); // 学生积分 (int(20))
	MYSQL_SYNTHESIZE(long long, orgId, OrgId); // 创建者所属组织ID (bigint(20))
	MYSQL_SYNTHESIZE(int, gradeId, GradeId); // 年级ID (int(11))
public:
	StlistDO() :BaseDO("student")
	{
		MYSQL_ADD_FIELD_PK("id", "i", id);
		MYSQL_ADD_FIELD("family_rel", "i", familyRel); // 家庭关系
		MYSQL_ADD_FIELD("name", "s", name); // 姓名
		MYSQL_ADD_FIELD("gender", "i", gender); // 性别
		MYSQL_ADD_FIELD("birthday", "dt", birthday); // 生日
		MYSQL_ADD_FIELD("add_time", "dt", addTime); // 加入时间
		MYSQL_ADD_FIELD("idcard", "s", idcard); // 身份证号
		MYSQL_ADD_FIELD("grade", "i", grade); // 入学年份
		MYSQL_ADD_FIELD("join_date", "dt", joinDate); // 入学日期
		MYSQL_ADD_FIELD("credit", "i", credit); // 学生积分
		MYSQL_ADD_FIELD("org_id", "bi", orgId); // 创建者所属组织ID
		MYSQL_ADD_FIELD("grade_id", "i", gradeId); // 年级ID
	}
};

//视图DO
class StlistViewDO :public StlistDO
{
	//学生手机号
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	//剩余课时
	MYSQL_SYNTHESIZE(int, closeTime, CloseTime);
};

typedef std::shared_ptr<StlistViewDO> PtrStlistViewDO;
