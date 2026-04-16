#pragma once
#ifndef ENROLLEDRECORD_DO_
#define ENROLLEDRECORD_DO_
#include"../DoInclude.h"
class EnrolledRecordDO :public BaseDO
{
	//主键ID--来自StudentCourse表的id
	MYSQL_SYNTHESIZE(int, id, Id);
	//课程名称
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	//学生名称
	MYSQL_SYNTHESIZE(string, studentName, StudentName);
	//课程开始时间
	MYSQL_SYNTHESIZE(string, startDate, StartDate);
	//课程过期时间
	MYSQL_SYNTHESIZE(string,expireDate,ExpireDate);
	//报名费用
	MYSQL_SYNTHESIZE(string, amount, Amount);

public:
	EnrolledRecordDO() : BaseDO("enrolled_record")
	{
		//主键ID
		MYSQL_ADD_FIELD_PK("id", "i", id);	
		//课程名称
		MYSQL_ADD_FIELD("course_name", "s", courseName);
		//学生名称
		MYSQL_ADD_FIELD("student_name", "s", studentName);
		//课程开始时间
		MYSQL_ADD_FIELD("start_date", "s", startDate);
		//课程过期时间
		MYSQL_ADD_FIELD("expire_date", "s", expireDate);
		//报名费用
		MYSQL_ADD_FIELD("amount", "d", amount);
	}
};
class EnrolledRecordDetailDO : public BaseDO
{
	//主键ID--来自StudentCourse表的id
	MYSQL_SYNTHESIZE(int, id, Id);
	//课程名称
	MYSQL_SYNTHESIZE(string, courseName, CourseName);
	//学生名称
	MYSQL_SYNTHESIZE(string, studentName, StudentName);
	//科目名称
	MYSQL_SYNTHESIZE(string, subjectName, SubjectName);
	//课程开始时间
	MYSQL_SYNTHESIZE(string, startDate, StartDate);
	//课程过期时间
	MYSQL_SYNTHESIZE(string, expireDate, ExpireDate);
	//课程金额
	MYSQL_SYNTHESIZE(string, courseAmount, CourseAmount);
	//优惠金额
	MYSQL_SYNTHESIZE(string, discountAmount, DiscountAmount);
	//实付金额
	MYSQL_SYNTHESIZE(string, paidAmount, PaidAmount);
	//欠付金额
	MYSQL_SYNTHESIZE(string, owedAmount, OwedAmount);
	//提交记录时间
	MYSQL_SYNTHESIZE(string, submitTime, SubmitTime);
	//备注说明
	MYSQL_SYNTHESIZE(string, remark, Remark);
	//课程总次数
	MYSQL_SYNTHESIZE(int, totalLessons, TotalLessons);
	//已上课次
	MYSQL_SYNTHESIZE(int, completedLessons, CompletedLessons);
	//剩余课次
	MYSQL_SYNTHESIZE(int, remainingLessons, RemainingLessons);
	//退款信息
	MYSQL_SYNTHESIZE(string, refundInfo, RefundInfo);

public:
	EnrolledRecordDetailDO() : BaseDO("enrolled_record_detail")
	{
		//主键ID
		MYSQL_ADD_FIELD_PK("id", "i", id);
		//课程名称
		MYSQL_ADD_FIELD("course_name", "s", courseName);
		//学生名称
		MYSQL_ADD_FIELD("student_name", "s", studentName);
		//科目名称
		MYSQL_ADD_FIELD("subject_name", "s", subjectName);
		//课程开始时间
		MYSQL_ADD_FIELD("start_date", "s", startDate);
		//课程过期时间
		MYSQL_ADD_FIELD("expire_date", "s", expireDate);
		//课程金额
		MYSQL_ADD_FIELD("course_amount", "d", courseAmount);
		//优惠金额
		MYSQL_ADD_FIELD("discount_amount", "d", discountAmount);
		//实付金额
		MYSQL_ADD_FIELD("paid_amount", "d", paidAmount);
		//欠付金额
		MYSQL_ADD_FIELD("owe_amount", "d", owedAmount);
		//提交记录时间
		MYSQL_ADD_FIELD("submit_time", "s", submitTime);
		//备注说明
		MYSQL_ADD_FIELD_NULLABLE("remark", "s", remark,true);
		//课程总次数
		MYSQL_ADD_FIELD("total_lessons", "i", totalLessons);
		//已上课次
		MYSQL_ADD_FIELD("completed_lessons", "i", completedLessons);
		//剩余课次
		MYSQL_ADD_FIELD("remaining_lessons", "i", remainingLessons);
		//退款信息
		MYSQL_ADD_FIELD_NULLABLE("refund_info", "s", refundInfo,true);
	}
};
typedef std::shared_ptr<EnrolledRecordDO> PtrEnrolledRecordDO;
typedef std::shared_ptr<EnrolledRecordDetailDO> PtrEnrolledRecordDetailDO;
#endif