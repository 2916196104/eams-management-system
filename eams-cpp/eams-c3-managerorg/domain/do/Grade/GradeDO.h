#pragma once
#ifndef _GRADE_DO_H_
#define _GRADE_DO_H_

#include "domain/do/DoInclude.h"

/**
 * 学生轻量级实体类（联查用，仅需 id + name）
 * 对应数据库表：student
 */
class StudentDO : public BaseDO
{
	// 学生编号
	MYSQL_SYNTHESIZE(int64_t, id, Id);
	// 学生姓名
	MYSQL_SYNTHESIZE(string, name, Name);
public:
	StudentDO() : BaseDO("student")
	{
		MYSQL_ADD_FIELD_PK("id", "bi", id);
		MYSQL_ADD_FIELD("name", "s", name);
	}
};
// 学生智能指针别名
typedef shared_ptr<StudentDO> PtrStudentDO;


/**
 * 成绩单数据库实体类
 * 对应数据库表：grade
 * 联查时会关联 grade_record（取成绩）和 student（取学生姓名）
 */
class GradeDO : public BaseDO
{
public:
	GradeDO() : BaseDO("grade")
	{
		MYSQL_ADD_FIELD_PK("id", "bi", id);
		MYSQL_ADD_FIELD("title", "s", title);
		MYSQL_ADD_FIELD("info", "s", info);
		MYSQL_ADD_FIELD("creator", "bi", creator);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("deleted", "b", deleted);
		MYSQL_ADD_FIELD("edit_time", "s", edit_time);
		MYSQL_ADD_FIELD("org_id", "bi", org_id);
	}

private:
	// ========== grade 表字段 ==========
	// 主键
	MYSQL_SYNTHESIZE(int64_t, id, Id);
	// 考核项标题
	MYSQL_SYNTHESIZE(string, title, Title);
	// 考核项说明
	MYSQL_SYNTHESIZE(string, info, Info);
	// 创建者
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	// 创建时间
	MYSQL_SYNTHESIZE(string, add_time, AddTime);
	// 逻辑删除
	MYSQL_SYNTHESIZE(bool, deleted, Deleted);
	// 编辑时间
	MYSQL_SYNTHESIZE(string, edit_time, EditTime);
	// 创建者所属组织ID
	MYSQL_SYNTHESIZE(int64_t, org_id, OrgId);

	// ========== 联查字段（来自 grade_record 表） ==========
    // 这里无需关联完整的表
	// 成绩记录ID（grade_record.id）
	MYSQL_SYNTHESIZE(int64_t, record_id, RecordId);
	// 学生成绩（grade_record.score）
	MYSQL_SYNTHESIZE(int8_t, score, Score);

	// ========== 联查关联对象（来自 student 表） ==========
	// 学生信息（取学生姓名用）
	CC_SYNTHESIZE(PtrStudentDO, student, Student);
};

// 成绩单智能指针别名
typedef shared_ptr<GradeDO> PtrGradeDO;

#endif // !_GRADE_DO_H_