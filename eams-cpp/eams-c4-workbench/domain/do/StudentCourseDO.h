#pragma once
#ifndef STUDENTCOURSEDO_H
#define STUDENTCOURSEDO_H

#include "../do/DoInclude.h"

/**
 * student_course表数据库实体类
 */
class StudentCourseDO : public BaseDO
{
	// 主键ID
	MYSQL_SYNTHESIZE(long long, id, Id);
	// 学生id
	MYSQL_SYNTHESIZE(long long, studentId, StudentId);
	// 课程id
	MYSQL_SYNTHESIZE(long long, courseId, CourseId);
	// 科目id
	MYSQL_SYNTHESIZE(long long, subjectId, SubjectId);
	// 开始时间
	MYSQL_SYNTHESIZE(string, startDate, StartDate);
	// 过期日期
	MYSQL_SYNTHESIZE(string, expireDate, ExpireDate);
	// 备注
	MYSQL_SYNTHESIZE(string, remark, Remark);
	// 购买总课次
	MYSQL_SYNTHESIZE(int, countLessonTotal, CountLessonTotal);
	// 已上课次
	MYSQL_SYNTHESIZE(int, countLessonComplete, CountLessonComplete);
	// 退款次数
	MYSQL_SYNTHESIZE(int, countLessonRefund, CountLessonRefund);
	// 套餐金额
	MYSQL_SYNTHESIZE(double, courseAmount, CourseAmount);
	// 优惠金额
	MYSQL_SYNTHESIZE(double, discountAmount, DiscountAmount);
	// 成交/合约金额
	MYSQL_SYNTHESIZE(double, amount, Amount);
	// 实付金额
	MYSQL_SYNTHESIZE(double, paidAmount, PaidAmount);
	// 是否付清 0否1是
	MYSQL_SYNTHESIZE(int, payOff, PayOff);
	// 经手人
	MYSQL_SYNTHESIZE(long long, operatorId, OperatorId);
	// 创建人
	MYSQL_SYNTHESIZE(long long, creator, Creator);
	// 录入时间
	MYSQL_SYNTHESIZE(string, addTime, AddTime);
	// 编辑人
	MYSQL_SYNTHESIZE(long long, editor, Editor);
	// 编辑时间
	MYSQL_SYNTHESIZE(string, editTime, EditTime);
	// 删除标记
	MYSQL_SYNTHESIZE(int, deleted, Deleted);
	// 审核状态
	MYSQL_SYNTHESIZE(int, verifyState, VerifyState);
	// 不足时已提醒次数
	MYSQL_SYNTHESIZE(int, warningTimes, WarningTimes);
	// 消课优先级
	MYSQL_SYNTHESIZE(int, priority, Priority);
	// 单价
	MYSQL_SYNTHESIZE(double, unitPrice, UnitPrice);
	// 是否来自于体验试用
	MYSQL_SYNTHESIZE(int, fromTrial, FromTrial);
	// 报名老师所属组织ID
	MYSQL_SYNTHESIZE(long long, orgId, OrgId);

public:
	StudentCourseDO() : BaseDO("student_course")
	{
		// 主键
		MYSQL_ADD_FIELD_PK("id", "i", id);
		// 学生id
		MYSQL_ADD_FIELD("student_id", "i", studentId);
		// 课程id
		MYSQL_ADD_FIELD("course_id", "i", courseId);
		// 科目id
		MYSQL_ADD_FIELD("subject_id", "i", subjectId);
		// 开始时间
		MYSQL_ADD_FIELD("start_date", "s", startDate);
		// 过期日期
		MYSQL_ADD_FIELD("expire_date", "s", expireDate);
		// 备注
		MYSQL_ADD_FIELD("remark", "s", remark);
		// 购买总课次
		MYSQL_ADD_FIELD("count_lesson_total", "i", countLessonTotal);
		// 已上课次
		MYSQL_ADD_FIELD("count_lesson_complete", "i", countLessonComplete);
		// 退款次数
		MYSQL_ADD_FIELD("count_lesson_refund", "i", countLessonRefund);
		// 套餐金额
		MYSQL_ADD_FIELD("course_amount", "d", courseAmount);
		// 优惠金额
		MYSQL_ADD_FIELD("discount_amount", "d", discountAmount);
		// 成交/合约金额
		MYSQL_ADD_FIELD("amount", "d", amount);
		// 实付金额
		MYSQL_ADD_FIELD("paid_amount", "d", paidAmount);
		// 是否付清 0否1是
		MYSQL_ADD_FIELD("pay_off", "i", payOff);
		// 经手人
		MYSQL_ADD_FIELD("operator", "i", operatorId);
		// 创建人
		MYSQL_ADD_FIELD("creator", "i", creator);
		// 录入时间
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		// 编辑人
		MYSQL_ADD_FIELD("editor", "i", editor);
		// 编辑时间
		MYSQL_ADD_FIELD("edit_time", "s", editTime);
		// 删除标记
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		// 审核状态
		MYSQL_ADD_FIELD("verify_state", "i", verifyState);
		// 不足时已提醒次数
		MYSQL_ADD_FIELD("warning_times", "i", warningTimes);
		// 消课优先级
		MYSQL_ADD_FIELD("priority", "i", priority);
		// 单价
		MYSQL_ADD_FIELD("unit_price", "d", unitPrice);
		// 是否来自于体验试用
		MYSQL_ADD_FIELD("from_trial", "i", fromTrial);
		// 报名老师所属组织ID
		MYSQL_ADD_FIELD("org_id", "i", orgId);
	}
};

typedef std::shared_ptr<StudentCourseDO> PtrStudentCourseDO;

#endif // STUDENTCOURSEDO_H