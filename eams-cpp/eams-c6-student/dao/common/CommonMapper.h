#pragma once
#ifndef COMMONMAPPER_H
#define COMMONMAPPER_H
#include "Mapper.h"
#include "../../domain/dto/common/CommonDTO.h"
#include "../../domain/do/student/StudentDO.h"
#include "../../domain/do/common/CommonDO.h"
class RegistrationRecordMapper : public Mapper<RegistrationDTO::Wrapper> {
public:
	RegistrationDTO::Wrapper mapper(ResultSet* rs) const override {
		auto dto = RegistrationDTO::createShared();

		// SQL 椤哄簭锛堜繚鎸佷綘褰撳墠 CommonDAO.cpp 鐨?SELECT 瀛楁椤哄簭锛?
		// 1 sc.add_time
		// 2 c.name
		// 3 sub.name
		// 4 sc.count_lesson_total
		// 5 sc.unit_price
		// 6 sc.course_amount
		// 7 sc.discount_amount
		// 8 sc.paid_amount
		// 9 sc.amount-sc.paid_amount
		// 10 sc.start_date
		// 11 sc.expire_date
		// 12 ref.refund_amount
		// 13 ref.refund_amount/sc.unit_price
		// 14 ref.remark
		// 15 ref.verify_state

		dto->addTime = rs->getString(1).c_str();
		dto->course = rs->getString(2).c_str();
		dto->subject = rs->getString(3).c_str();

		dto->buyCount = rs->getInt(4);
		dto->UnitPrice = rs->getInt(5);
		dto->coursePrice = rs->getInt(6);

		dto->salePrice = rs->getInt(7);
		dto->realityPrice = rs->getInt(8);
		dto->arrearage = rs->getInt(9);

		dto->beginTime = rs->getString(10).c_str();
		dto->endTime = rs->getString(11).c_str();

		dto->refundPrice = rs->getInt(12);
		dto->dropClassCount = rs->getInt(13);
		dto->refundDescripe = rs->getString(14).c_str();
		dto->refundStatus = rs->getInt(15);

		// 褰撳墠 SQL 鏈繑鍥?sc.id锛屽洜姝?dto->id 涓嶈祴鍊硷紙鍙湪闇€瑕佹椂鎶?sc.id 鍔犲埌 SELECT 鍓嶉潰骞跺悓姝ヨ皟鏁翠笅鏍囷級
		return dto;
	}
};
class StudentDetailMapper :public Mapper<StudentDTO::Wrapper> {
public:
	StudentDTO::Wrapper mapper(ResultSet* rs) const override {
		auto dto = StudentDTO::createShared();
		dto->picturePath = rs->getString(1).c_str();
		dto->name = rs->getString(2).c_str();
		dto->phone = rs->getString(3).c_str();
		dto->leftCourseCount = rs->getInt(4);
		dto->leftPoints = rs->getInt(5);
		dto->stage = rs->getInt(6);
		dto->sex = rs->getInt(7);
		dto->age = rs->getInt(8);
		dto->birthday = rs->getString(9).c_str();
		dto->identificationNumber = rs->getString(10).c_str();
		dto->parentName = rs->getString(11).c_str();
		dto->relationType = rs->getInt(12);
		dto->grade = rs->getInt(13);
		dto->enterTime = rs->getString(14).c_str();
		dto->accurateEnterTime = rs->getString(15).c_str();
		dto->note = rs->getString(16).c_str();
		dto->courseProgress = rs->getInt(17);
		return dto;
	}
};

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
