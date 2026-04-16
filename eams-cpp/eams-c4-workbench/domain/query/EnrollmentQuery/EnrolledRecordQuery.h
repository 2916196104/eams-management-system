#pragma once
#ifndef _ENROLLEDRECORD_QUERY_
#define _ENROLLEDRECORD_QUERY_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/** 
 * 报名记录分页查询对象
 */
class EnrolledQuery : public PageQuery
{
	DTO_INIT(EnrolledQuery, PageQuery);
	// 课程名称
	DTO_FIELD(String, CourseName);
	DTO_FIELD_INFO(CourseName) {
		info->description = ZH_WORDS_GETTER("sample.field.name");
	}
	// 学生名称
	DTO_FIELD(String, StudentName);
	DTO_FIELD_INFO(StudentName) {
		info->description = ZH_WORDS_GETTER("sample.field.name");
	}
	//课程开始时间
	DTO_FIELD(String, StartDate);
	DTO_FIELD_INFO(StartDate) {
		info->description = ZH_WORDS_GETTER("enrollment.field.startDate");
	}
	//课程结束时间
	DTO_FIELD(String, ExpireDate);
	DTO_FIELD_INFO(ExpireDate) {
		info->description = ZH_WORDS_GETTER("enrollment.field.expireDate");
	}
	//报名费用
	DTO_FIELD(Float32, Amount);
	DTO_FIELD_INFO(Amount) {
		info->description = ZH_WORDS_GETTER("enrollment.field.amount");
	}
	
};
/*
 * 报名记录详情查询对象
 */
class EnrolledDetailQuery : public EnrolledQuery
{
	DTO_INIT(EnrolledDetailQuery, EnrolledQuery);
	// 报名记录唯一ID
	DTO_FIELD(Int32, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("enrollment.field.id");
	}
	//科目名称
	DTO_FIELD(String, SubjectName);
	DTO_FIELD_INFO(SubjectName) {
		info->description = ZH_WORDS_GETTER("enrollment.field.subjectName");
	}
	//课程金额
	DTO_FIELD(Int32, courseAmount);
	DTO_FIELD_INFO(courseAmount) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.courseAmount");
	}
	//优惠金额
	DTO_FIELD(Int32, discountCourseAmount);
	DTO_FIELD_INFO(discountCourseAmount) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.discountCourseAmount");
	}
	//实付金额
	DTO_FIELD(Int32, paidCourseAmount);
	DTO_FIELD_INFO(paidCourseAmount) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.paidCourseAmount");
	}
	//欠付金额
	DTO_FIELD(Int32, oweCourseAmount);
	DTO_FIELD_INFO(oweCourseAmount) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.oweCourseAmount");
	}
	//记录提交时间
	DTO_FIELD(String, submitTime);
	DTO_FIELD_INFO(submitTime) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.submitTime");
	}
	//备注说明
	DTO_FIELD(String, remark);
	DTO_FIELD_INFO(remark) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.remark");
	}
	//课程总课次
	DTO_FIELD(Int32, totalLessons);
	DTO_FIELD_INFO(totalLessons) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.totalLessons");
	}
	//已上课次
	DTO_FIELD(Int32, completedLessons);
	DTO_FIELD_INFO(completedLessons) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.completedLessons");
	}
	//剩余课次
	DTO_FIELD(Int32, remainingLessons);
	DTO_FIELD_INFO(remainingLessons) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.remainingLessons");
	}
	//退款信息
	DTO_FIELD(String, refundInfo);
	DTO_FIELD_INFO(refundInfo) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.refundInfo");
	}
};
#endif // !_ENROLLEDRECORD_QUERY_
