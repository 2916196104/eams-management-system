#pragma once
#ifndef _ENROLLEDRECORD_DTO_
#define _ENROLLEDRECORD_DTO_
#include"../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)
/*
* 报名记录数据传输对象
*/
class EnrolledRecordDTO :public oatpp::DTO
{
	DTO_INIT(EnrolledRecordDTO, DTO);
	DTO_FIELD(String,studentName);
	DTO_FIELD_INFO(studentName) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.studentName");
	}
	DTO_FIELD(String, courseName);
	DTO_FIELD_INFO(courseName) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.courseName");
	}
	DTO_FIELD(String, subjectName);
	DTO_FIELD_INFO(subjectName) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.subjectName");
	}
	DTO_FIELD(String, startDate);
	DTO_FIELD_INFO(startDate) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.startDate");
	}
	DTO_FIELD(String, expireDate);
	DTO_FIELD_INFO(expireDate) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.expireDate");
	}
	//课程金额
	DTO_FIELD(String, courseAmount);
	DTO_FIELD_INFO(courseAmount) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.courseAmount");
	}
	//优惠金额	
	DTO_FIELD(String, discountCourseAmount);
	DTO_FIELD_INFO(discountCourseAmount) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.discountCourseAmount");
	}
	//实付金额
	DTO_FIELD(String, paidCourseAmount);
	DTO_FIELD_INFO(paidCourseAmount) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.paidCourseAmount");
	}
	//欠付金额
	DTO_FIELD(String, owedCourseAmount);
	DTO_FIELD_INFO(owedCourseAmount) {
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
/*
* 报名记录分页传输对象
*/
class EnrolledRecordListDTO :public oatpp::DTO
{
	DTO_INIT(EnrolledRecordListDTO, DTO);
	DTO_FIELD(String, studentName);
	DTO_FIELD_INFO(studentName) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.studentName");
	}
	DTO_FIELD(String, courseName);
	DTO_FIELD_INFO(courseName) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.courseName");
	}
	//课程时间开始时间
	DTO_FIELD(String, startCourseTime);
	DTO_FIELD_INFO(startCourseTime) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.startCourseTime");
	}
	//课程时间结束时间
	DTO_FIELD(String, endCourseTime);
	DTO_FIELD_INFO(endCourseTime) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.endCourseTime");
	}
	//报名费用
	DTO_FIELD(String, courseAmount);
	DTO_FIELD_INFO(courseAmount) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.courseAmount");
	}

};
class EnrolledRecordPageDTO :public PageDTO<EnrolledRecordListDTO::Wrapper>
{
	DTO_INIT(EnrolledRecordPageDTO,PageDTO<EnrolledRecordDTO::Wrapper>);
	// 唯一标识报名记录列表识别
	DTO_FIELD(String,id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.id");
	}
};
/*
* 报名记录详情传输对象
*/
class EnrolledRecordDetailDTO :public EnrolledRecordDTO
{
	DTO_INIT(EnrolledRecordDetailDTO, EnrolledRecordDTO);
	// 其他报名记录详情字段
	DTO_FIELD(Int32, id);
	DTO_FIELD_INFO(id) {
		info->description = ZH_WORDS_GETTER("enrollRecord.field.id");
	}
};
#include OATPP_CODEGEN_END(DTO)
#endif // !ENROLLEDRECORDDTO
