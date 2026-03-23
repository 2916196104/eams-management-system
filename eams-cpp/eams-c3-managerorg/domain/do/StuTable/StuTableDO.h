#pragma once
#pragma once
#ifndef _STUDENTTABLEDO_H_
#define _STUDENTTABLEDO_H_
#include "../DoInclude.h"
/**
 * 学生表数据模型
 */
class StuTableDO : public BaseDO
{
	// 学生ID（主键）
	MYSQL_SYNTHESIZE(uint64_t, id, Id);
	// 用户ID
	MYSQL_SYNTHESIZE(uint64_t, userId, UserId);
	// 家庭关系
	MYSQL_SYNTHESIZE(int, familyRel, FamilyRel);
	// 是否默认
	MYSQL_SYNTHESIZE(int, asDefault, AsDefault);
	// 学校ID
	MYSQL_SYNTHESIZE(uint64_t, schoolId, SchoolId);
	// 姓名
	MYSQL_SYNTHESIZE(string, name, Name);
	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 阶段
	MYSQL_SYNTHESIZE(int, stage, Stage);
	// 性别
	MYSQL_SYNTHESIZE(int, gender, Gender);
	// 生日
	MYSQL_SYNTHESIZE(string, birthday, Birthday);
	// 头像
	MYSQL_SYNTHESIZE(string, headImg, HeadImg);

	// 关联一个文件实体，存储头像文件信息，但是这里没有File DO
	//CC_SYNTHESIZE(PtrFileDO, file, File);

	// 入学方式
	MYSQL_SYNTHESIZE(uint64_t, joinWay, JoinWay);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 毕业日期
	MYSQL_SYNTHESIZE(string, graduationDate, GraduationDate);
	// 毕业原因
	MYSQL_SYNTHESIZE(string, graduationReason, GraduationReason);
	// 添加时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 顾问
	MYSQL_SYNTHESIZE(uint64_t, counselor, Counselor);
	// 创建人
	MYSQL_SYNTHESIZE(uint64_t, creator, Creator);
	// 编辑人
	MYSQL_SYNTHESIZE(uint64_t, editor, Editor);
	// 编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 身份证号
	MYSQL_SYNTHESIZE(string, idcard, Idcard);
	// 红点等级
	MYSQL_SYNTHESIZE(string, redpointGrade, RedpointGrade);
	// 红点评价
	MYSQL_SYNTHESIZE(string, redpointEvaluate, RedpointEvaluate);
	// 年级
	MYSQL_SYNTHESIZE(string, grade, Grade);
	// 入学日期
	MYSQL_SYNTHESIZE(string, joinDate, JoinDate);
	// 微信登录记录id
	MYSQL_SYNTHESIZE(uint64_t, wxUserId, WxUserId);
	// 学分
	MYSQL_SYNTHESIZE(int, credit, Credit);
	// 组织ID
	MYSQL_SYNTHESIZE(uint64_t, orgId, OrgId);
	// 年级ID
	MYSQL_SYNTHESIZE(int, gradeId, GradeId);
public:
	StuTableDO() : BaseDO("student")
	{
		MYSQL_ADD_FIELD_PK("id", "ui64", id);
		MYSQL_ADD_FIELD("user_id", "ui64", userId);
		MYSQL_ADD_FIELD("family_rel", "i", familyRel);
		MYSQL_ADD_FIELD("as_default", "i", asDefault);
		MYSQL_ADD_FIELD("school_id", "ui64", schoolId);
		MYSQL_ADD_FIELD("name", "s", name);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("stage", "i", stage);
		MYSQL_ADD_FIELD("gender", "i", gender);
		MYSQL_ADD_FIELD("birthday", "s", birthday);
		MYSQL_ADD_FIELD("head_img", "s", headImg);
		MYSQL_ADD_FIELD("join_way", "ui64", joinWay);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("graduation_date", "s", graduationDate);
		MYSQL_ADD_FIELD("graduation_reason", "s", graduationReason);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("counselor", "ui64", counselor);
		MYSQL_ADD_FIELD("creator", "ui64", creator);
		MYSQL_ADD_FIELD("editor", "ui64", editor);
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		MYSQL_ADD_FIELD("idcard", "s", idcard);
		MYSQL_ADD_FIELD("redpoint_grade", "s", redpointGrade);
		MYSQL_ADD_FIELD("redpoint_evaluate", "s", redpointEvaluate);
		MYSQL_ADD_FIELD("grade", "s", grade);
		MYSQL_ADD_FIELD("join_date", "s", joinDate);
		MYSQL_ADD_FIELD("wx_user_id", "ui64", wxUserId);
		MYSQL_ADD_FIELD("credit", "i", credit);
		MYSQL_ADD_FIELD("org_id", "ui64", orgId);
		MYSQL_ADD_FIELD("grade_id", "i", gradeId);
	}
};

// 定义一个智能指针别名方便使用
typedef std::shared_ptr<StuTableDO> PtrStuTableDO;

#endif // !_STUDENTTABLEDO_H_