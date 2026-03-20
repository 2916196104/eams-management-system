#pragma once
#ifndef _ONLINESTUDENT_DO_
#define _ONLINESTUDENT_DO_
#include "../DoInclude.h"

/**
 * 在线学员导出数据（联表查询）
 */
class OnlineExportDO : public BaseDO
{
	// 学员姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 手机号码（user.mobile）
	MYSQL_SYNTHESIZE(string, mobile, Mobile);
	// 性别（0女 1男）
	MYSQL_SYNTHESIZE(uint8_t, gender, Gender);
	// 家长姓名（user.name）
	MYSQL_SYNTHESIZE(string, parentName, ParentName);
	// 家长关系（0本人 1父亲 2母亲 3其他）
	MYSQL_SYNTHESIZE(uint8_t, familyRel, FamilyRel);
	// 学校名称（org.name）
	MYSQL_SYNTHESIZE(string, schoolName, SchoolName);
	// 年级名称（class_grade.name）
	MYSQL_SYNTHESIZE(string, gradeName, GradeName);
	// 顾问姓名（staff.name）
	MYSQL_SYNTHESIZE(string, counselorName, CounselorName);
	// 生日
	MYSQL_SYNTHESIZE(string, birthday, Birthday);

public:
	OnlineExportDO() : BaseDO("")
	{
		// 联表查询结果，不绑定单表，所以表名传空
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("mobile", "s", mobile);
		MYSQL_ADD_FIELD("gender", "i", gender);
		MYSQL_ADD_FIELD("parent_name", "s", parentName);
		MYSQL_ADD_FIELD("family_rel", "i", familyRel);
		MYSQL_ADD_FIELD("school_name", "s", schoolName);
		MYSQL_ADD_FIELD("grade_name", "s", gradeName);
		MYSQL_ADD_FIELD("counselor_name", "s", counselorName);
		MYSQL_ADD_FIELD("birthday", "s", birthday);
	}
};

// 给OnlineExportDO智能指针设定一个别名方便使用
typedef std::shared_ptr<OnlineExportDO> PtrStudentExportDO;

#endif // !_ONLINESTUDENT_DO_
