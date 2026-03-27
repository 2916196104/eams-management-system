#pragma once
#ifndef _COMMON_MAPPER_
#define _COMMON_MAPPER_

#include "Mapper.h"
#include "../../domain/do/student/StudentDO.h"
#include "../../domain/do/common/CommonDO.h"
// 班级列表字段匹配映射
class getClassListMapper : public Mapper<getClassListDO>
{
public:
	getClassListDO mapper(ResultSet* resultSet) const override
	{
		getClassListDO data;
		data.setId(resultSet->getString(1));
		data.setClassName(resultSet->getString(2));
		data.setSubject(resultSet->getString(3));
		data.setClassroom(resultSet->getString(4));
		data.setStudentCount(resultSet->getInt(5));
		data.setMaxStudentCount(resultSet->getInt(6));
		return data;
	}
};

// 班级列表字段匹配映射 - 创建智能指针对象
class PtrgetClassListMapper : public Mapper<PtrgetClassListDO>
{
public:
	PtrgetClassListDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<getClassListDO>();
		data->setId(resultSet->getString(1));
		data->setClassName(resultSet->getString(2));
		data->setSubject(resultSet->getString(3));
		data->setClassroom(resultSet->getString(4));
		data->setStudentCount(resultSet->getInt(5));
		data->setMaxStudentCount(resultSet->getInt(6));
		return data;
	}
};

// 课程统计字段匹配映射
class getCourseStatisticsMapper : public Mapper<getCourseStatisticsDO>
{
public:
	getCourseStatisticsDO mapper(ResultSet* resultSet) const override
	{
		getCourseStatisticsDO data;
		data.setCourse(resultSet->getString(1));
		data.setTotalHours(resultSet->getInt(2));
		data.setRemainingHours(resultSet->getInt(3));
		data.setAttendedHours(resultSet->getInt(4));
		data.setExpireDate(resultSet->getString(5));
		data.setCancelPriority(resultSet->getInt(6));
		return data;
	}
};

//课程统计字段匹配映射 - 创建智能指针对象
class PtrgetCourseStatisticsMapper : public Mapper<PtrgetCourseStatisticsDO>
{
public:
	PtrgetCourseStatisticsDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<getCourseStatisticsDO>();
		data->setCourse(resultSet->getString(1));
		data->setTotalHours(resultSet->getInt(2));
		data->setRemainingHours(resultSet->getInt(3));
		data->setAttendedHours(resultSet->getInt(4));
		data->setExpireDate(resultSet->getString(5));
		data->setCancelPriority(resultSet->getInt(6));
		return data;
	}
};

// 加入班级字段匹配映射
class JoinclassMapper : public Mapper<JoinclassDO>
{
public:
	JoinclassDO mapper(ResultSet* resultSet) const override
	{
		JoinclassDO data;
		data.setClassName(resultSet->getString(1));
		data.setSchool(resultSet->getString(2));
		return data;
	}
};

// 加入班级字段匹配映射 - 创建智能指针对象

class PtrJoinclassMapper : public Mapper<PtrJoinclassDO>
{
public:
	PtrJoinclassDO mapper(ResultSet* resultSet) const override
	{
		auto data = std::make_shared<JoinclassDO>();
		data->setClassName(resultSet->getString(1));
		data->setSchool(resultSet->getString(2));
		return data;
	}
};
//student_course数据表字段匹配映射
class PtrStudentCourseMapper : public Mapper<PtrStudentCourseDO> {
public:
	PtrStudentCourseDO mapper(ResultSet* resultSet) const override {
		auto data = std::make_shared<StudentCourseDO>();

		// 核心ID
		data->setId(resultSet->getUInt64("id"));
		data->setStudentId(resultSet->getUInt64("student_id"));
		data->setCourseId(resultSet->getUInt64("course_id"));
		data->setSubjectId(resultSet->getUInt64("subject_id"));

		// 时间
		data->setStartDate(resultSet->getString("start_date"));
		data->setExpireDate(resultSet->getString("expire_date"));

		// 备注
		data->setRemark(resultSet->getUInt64("remark"));

		// 课次
		data->setCountLessonTotal(resultSet->getUInt64("count_lesson_total"));
		data->setCountLessonComplete(resultSet->getUInt64("count_lesson_complete"));
		data->setCountLessonRefund(resultSet->getUInt64("count_lesson_refund"));

		// 金额
		data->setCourseAmount(resultSet->getDouble("course_amount"));
		data->setDiscountAmount(resultSet->getDouble("discount_amount"));
		data->setAmount(resultSet->getDouble("amount"));
		data->setPaidAmount(resultSet->getDouble("paid_amount"));

		// 支付状态
		data->setPayOff(resultSet->getInt("pay_off"));

		// 操作人 / 创建人 / 编辑人
		data->setOpt(resultSet->getUInt64("operator"));
		data->setCreator(resultSet->getUInt64("creator"));
		data->setAddTime(resultSet->getString("add_time"));
		data->setEditor(resultSet->getUInt64("editor"));
		data->setEditTime(resultSet->getString("edit_time"));

		// 状态
		data->setDeleted(resultSet->getInt("deleted"));
		data->setVerifyState(resultSet->getInt("verify_state"));

		// 提醒与优先级
		data->setWarningTimes(resultSet->getInt("warning_times"));
		data->setPriority(resultSet->getInt("priority"));

		// 单价与体验
		data->setUnitPrice(resultSet->getDouble("unit_price"));
		data->setFromTrial(resultSet->getInt("from_trial"));

		// 组织ID
		data->setOrgId(resultSet->getUInt64("org_id"));

		return data;
	}
};
class PtrRefundMapper :public Mapper<PtrRefundDO> {
public:
	PtrRefundDO mapper(ResultSet* resultSet) const override {
		auto data = std::make_shared<RefundDO>();
		data->setStudentCourseId(resultSet->getUInt64("student_course_id"));
		data->setId(resultSet->getUInt64("id"));
		data->setStudentId(resultSet->getUInt64("student_id"));
		data->setStudentCourseId(resultSet->getUInt64("student_course_id"));
		data->setRefundAmount(resultSet->getDouble("refund_amount"));
		data->setRefundLessonCount(resultSet->getUInt64("refund_lesson_count"));
		data->setApplyTime(resultSet->getString("apply_time"));
		data->setRemark(resultSet->getString("remark"));
		data->setVerifyState(resultSet->getInt("verify_state"));
		return data;
	}
private:
};
class StudentCourseMapper : public Mapper<StudentCourseDO>
{
public:
	StudentCourseDO mapper(ResultSet* resultSet) const override
	{
		StudentCourseDO data;
		data.setStudentId(resultSet->getUInt64("student_id"));
		data.setCourseId(resultSet->getUInt64("course_id"));
		data.setSubjectId(resultSet->getUInt64("subject_id"));
		return data;
	}
};
#endif 
