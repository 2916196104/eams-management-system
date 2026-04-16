#pragma once
#ifndef _STUDENT_COURSE_DO_
#define _STUDENT_COURSE_DO_
//classroom表格do对象
#include "../eams-c7-workbench/domain/do/DoInclude.h"

/**
 * STUDENT_COURSE数据库实体类
 */
class StudentCourseDO : public BaseDO
{
	// 主键ID (bigint -> string 或 int64_t，这里保持 string 兼容)
	MYSQL_SYNTHESIZE(int64_t, id, Id);
	// 学生ID (bigint -> string 或 int64_t)
	MYSQL_SYNTHESIZE(int64_t, student_id, StudentId);
	// 课程ID (bigint -> string 或 int64_t)
	MYSQL_SYNTHESIZE(int64_t, course_id, CourseId);
	// 科目ID (bigint -> string 或 int64_t)
	MYSQL_SYNTHESIZE(int64_t, subject_id, SubjectId);
	// 课程开始日期 (date -> string)
	MYSQL_SYNTHESIZE(string, start_date, StartDate);
	// 课程到期日期 (date -> string)
	MYSQL_SYNTHESIZE(string, expire_date, ExpireDate);
	// 备注信息 (varchar(255) -> string)
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 总课时数 (int -> int)
	MYSQL_SYNTHESIZE(int, count_lesson_total, CountLessonTotal);
	// 已完成课时数 (int -> int)
	MYSQL_SYNTHESIZE(int, count_lesson_complete, CountLessonComplete);
	// 已退费课时数 (int -> int)
	MYSQL_SYNTHESIZE(int, count_lesson_refund, CountLessonRefund);
	// 课程原价 (decimal(10,2) -> double)
	MYSQL_SYNTHESIZE(double, course_amount, CourseAmount);
	// 优惠金额 (decimal(10,2) -> double)
	MYSQL_SYNTHESIZE(double, discount_amount, DiscountAmount);
	// 应收金额 (decimal(10,2) -> double)
	MYSQL_SYNTHESIZE(double, amount, Amount);
	// 实付金额 (decimal(10,2) -> double)
	MYSQL_SYNTHESIZE(double, paid_amount, PaidAmount);
	// 是否结清标识 (tinyint(1) -> int)
	MYSQL_SYNTHESIZE(int, pay_off, PayOff);
	// 操作人 (bigint -> string 或 int64_t，避免关键字冲突)
	MYSQL_SYNTHESIZE(int64_t, operator_, Operator);
	// 创建人 (bigint -> string 或 int64_t)
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	// 数据添加时间 (datetime -> string)
	MYSQL_SYNTHESIZE(string, add_time, AddTime);
	// 修改人 (bigint -> string 或 int64_t)
	MYSQL_SYNTHESIZE(string, editor, Editor);
	// 数据修改时间 (datetime -> string)
	MYSQL_SYNTHESIZE(string, edit_time, EditTime);
	// 是否删除标识 (tinyint(1) -> int)
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 审核状态 (tinyint -> int)
	MYSQL_SYNTHESIZE(int, verify_state, VerifyState);
	// 提醒次数 (tinyint -> int)
	MYSQL_SYNTHESIZE(int, warning_times, WarningTimes);
	// 优先级 (tinyint -> int)
	MYSQL_SYNTHESIZE(int, priority, Priority);
	// 课时单价 (decimal(10,2) -> double)
	MYSQL_SYNTHESIZE(double, unit_price, UnitPrice);
	// 是否来自试听课标识 (tinyint(1) -> int)
	MYSQL_SYNTHESIZE(int, from_trial, FromTrial);
	// 所属机构ID (bigint -> string 或 int64_t)
	MYSQL_SYNTHESIZE(int64_t, org_id, OrgId);
public:
	StudentCourseDO() : BaseDO("student_course")
	{
		MYSQL_ADD_FIELD_PK("id", "l", id);
		MYSQL_ADD_FIELD("student_id", "l", student_id);
		MYSQL_ADD_FIELD("course_id", "l", course_id);
		MYSQL_ADD_FIELD("subject_id", "l", subject_id);
		MYSQL_ADD_FIELD("start_date", "s", start_date);
		MYSQL_ADD_FIELD("expire_date", "s", expire_date);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("count_lesson_total", "i", count_lesson_total);
		MYSQL_ADD_FIELD("count_lesson_complete", "i", count_lesson_complete);
		MYSQL_ADD_FIELD("count_lesson_refund", "i", count_lesson_refund);
		MYSQL_ADD_FIELD("course_amount", "d", course_amount);
		MYSQL_ADD_FIELD("discount_amount", "d", discount_amount);
		MYSQL_ADD_FIELD("amount", "d", amount);
		MYSQL_ADD_FIELD("paid_amount", "d", paid_amount);
		MYSQL_ADD_FIELD("pay_off", "i", pay_off);
		MYSQL_ADD_FIELD("operator", "l", operator_);
		MYSQL_ADD_FIELD("creator", "l", creator);
		MYSQL_ADD_FIELD("add_time", "s", add_time);
		MYSQL_ADD_FIELD("editor", "s", editor);
		MYSQL_ADD_FIELD("edit_time", "s", edit_time);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("verify_state", "i", verify_state);
		MYSQL_ADD_FIELD("warning_times", "i", warning_times);
		MYSQL_ADD_FIELD("priority", "i", priority);
		MYSQL_ADD_FIELD("unit_price", "d", unit_price);
		MYSQL_ADD_FIELD("from_trial", "i", from_trial);
		MYSQL_ADD_FIELD("org_id", "l", org_id);
	}
};

// 给SampleDO智能指针设定一个别名方便使用
typedef std::shared_ptr<StudentCourseDO> PtrStudentCourseDO;




#endif 
