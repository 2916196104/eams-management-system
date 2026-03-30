#pragma once
#ifndef STUDENTDO_H
#define STUDENTDO_H
#include "DoInclude.h"

#include "../do/DoInclude.h"

/**
 * student表数据库实体类
 */
class StudentDO : public BaseDO
{
	// 主键
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 家长id
	MYSQL_SYNTHESIZE(uint64_t, userId, UserId);
	// 家庭关系
	MYSQL_SYNTHESIZE(int, familyRel, FamilyRel);
	// 家长默认查看的学员
	MYSQL_SYNTHESIZE(int, asDefault, AsDefault);
	// 所属分校
	MYSQL_SYNTHESIZE(uint64_t, schoolId, SchoolId);
	// 姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 逻辑删除
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 阶段状态0意向学员
	MYSQL_SYNTHESIZE(int, stage, Stage);
	// 性别
	MYSQL_SYNTHESIZE(int, gender, Gender);
	// 生日
	MYSQL_SYNTHESIZE(string, birthday, Birthday);
	// 头像
	MYSQL_SYNTHESIZE(string, headImg, HeadImg);
	// 加入方式
	MYSQL_SYNTHESIZE(int, joinWay, JoinWay);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 结业日期
	MYSQL_SYNTHESIZE(string, graduationDate, GraduationDate);
	// 结业原因
	MYSQL_SYNTHESIZE(string, graduationReason, GraduationReason);
	// 加入时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 顾问
	MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor);
	// 创建者
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	// 编辑人
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
	// 编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 身份证号
	MYSQL_SYNTHESIZE(string, idcard, Idcard);
	// 红点标记成绩最后查看时间
	MYSQL_SYNTHESIZE(string, redpointGrade, RedpointGrade);
	// 红点标记点评最后查看时间
	MYSQL_SYNTHESIZE(string, redpointEvaluate, RedpointEvaluate);
	// 入学年份
	MYSQL_SYNTHESIZE(string, grade, Grade);
	// 入学日期
	MYSQL_SYNTHESIZE(string, joinDate, JoinDate);
	// 微信登录记录id
	MYSQL_SYNTHESIZE(uint64_t, wxAccessId, WxAccessId);
	// 学生积分
	MYSQL_SYNTHESIZE(int, credit, Credit);
	// 创建者所属组织ID
	MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);
	// 年级ID
	MYSQL_SYNTHESIZE(uint64_t, gradeId, GradeId);

public:
	StudentDO() : BaseDO("student")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "ull", id);
		// 家长id
		MYSQL_ADD_FIELD("user_id", "ull", userId);
		// 家庭关系
		MYSQL_ADD_FIELD("family_rel", "i", familyRel);
		// 家长默认查看的学员
		MYSQL_ADD_FIELD("as_default", "i", asDefault);
		// 所属分校
		MYSQL_ADD_FIELD("school_id", "ull", schoolId);
		// 姓名
		MYSQL_ADD_FIELD("`name`", "s", name);
		// 逻辑删除
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		// 阶段状态0意向学员
		MYSQL_ADD_FIELD("stage", "i", stage);
		// 性别
		MYSQL_ADD_FIELD("gender", "i", gender);
		// 生日
		MYSQL_ADD_FIELD("birthday", "s", birthday);
		// 头像
		MYSQL_ADD_FIELD("head_img", "s", headImg);
		// 加入方式
		MYSQL_ADD_FIELD("join_way", "i", joinWay);
		// 备注
		MYSQL_ADD_FIELD("remark", "s", remark);
		// 结业日期
		MYSQL_ADD_FIELD("graduation_date", "s", graduationDate);
		// 结业原因
		MYSQL_ADD_FIELD("graduation_reason", "s", graduationReason);
		// 加入时间
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		// 顾问
		MYSQL_ADD_FIELD("counselor", "ull", counselor);
		// 创建者
		MYSQL_ADD_FIELD("creator", "ull", creator);
		// 编辑人
		MYSQL_ADD_FIELD("editor", "ull", editor);
		// 编辑时间
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		// 身份证号
		MYSQL_ADD_FIELD("idcard", "s", idcard);
		// 红点标记成绩最后查看时间
		MYSQL_ADD_FIELD("redpoint_grade", "s", redpointGrade);
		// 红点标记点评最后查看时间
		MYSQL_ADD_FIELD("redpoint_evaluate", "s", redpointEvaluate);
		// 入学年份
		MYSQL_ADD_FIELD("grade", "s", grade);
		// 入学日期
		MYSQL_ADD_FIELD("join_date", "s", joinDate);
		// 微信登录记录id
		MYSQL_ADD_FIELD("wx_access_id", "ull", wxAccessId);
		// 学生积分
		MYSQL_ADD_FIELD("credit", "i", credit);
		// 创建者所属组织ID
		MYSQL_ADD_FIELD("org_id", "ull", orgId);
		// 年级ID
		MYSQL_ADD_FIELD("grade_id", "ull", gradeId);
	}
};

// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<StudentDO> PtrStudentDO;



#endif