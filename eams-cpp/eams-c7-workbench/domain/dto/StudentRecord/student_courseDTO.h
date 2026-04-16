#pragma once

#include "../../GlobalInclude.h"

#ifndef _STUDENT_COURSEDTO_H_
#define _STUDENT_COURSEDTO_H_

#include OATPP_CODEGEN_BEGIN(DTO)



/**
 * 课程进度数据传输对象
 * name: 课程名称
  status: 课程状态	
  coursesum: 课程总数
  finishedsum: 已完成课程数
  unfinishedsum: 未完成课程数
 */

class CourseProgressDTO : public oatpp::DTO
{
	DTO_INIT(CourseProgressDTO, DTO);
	// 课程名称
	DTO_FIELD(String, class_name);
	DTO_FIELD_INFO(class_name) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.name");
	}
	// 课程状态
	DTO_FIELD(String, status);
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.status");
	}
	// 课程总数
	DTO_FIELD(Int32, coursesum);
	DTO_FIELD_INFO(coursesum) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.coursesum");
	}
	// 已完成课程数
	DTO_FIELD(Int32, finishedsum);
	DTO_FIELD_INFO(finishedsum) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.finishedsum");
	}
	// 未完成课程数
	DTO_FIELD(Int32, unfinishedsum);
	DTO_FIELD_INFO(unfinishedsum) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.unfinishedsum");
	}

};
/**
 * 课程进度分页传输对象
 */

class CourseProgressPageDTO : public PageDTO<CourseProgressDTO::Wrapper>
{
	DTO_INIT(CourseProgressPageDTO, PageDTO<CourseProgressDTO::Wrapper>);
	
};

/**
 * 学员课时记录数据传输对象
 * name: 课程名称
  status: 课程状态
  finishedsum: 消课数
  unfinishedsum: 剩余课程数
 */

class CourseRecordDTO : public oatpp::DTO
{
	DTO_INIT(CourseRecordDTO, DTO);
	// 课程名称
	DTO_FIELD(String, class_name);
	DTO_FIELD_INFO(class_name) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.name");
	}
	// 课程状态
	DTO_FIELD(String, status);
	DTO_FIELD_INFO(status) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.status");
	}
	// 消课数
	DTO_FIELD(Int32, consume_course_num);
	DTO_FIELD_INFO(consume_course_num) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.consume_course_num");
	}
	// 剩余课程数
	DTO_FIELD(Int32, course_balance);
	DTO_FIELD_INFO(course_balance) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.course_balance");
	}

};
/**
 * 课程进度分页传输对象
 */

class CourseRecordPageDTO : public PageDTO<CourseRecordDTO::Wrapper>
{
	DTO_INIT(CourseRecordPageDTO, PageDTO<CourseRecordDTO::Wrapper>);

};


/**
 * 学员报名数据传输对象
 * name: 课程名称
  time: 报名时间
  buycoursesum: 购买课程数
  pay: 费用
  
 */

class StudentSighnUPDTO : public oatpp::DTO
{
	DTO_INIT(StudentSighnUPDTO, DTO);
	// 课程名称
	DTO_FIELD(String, class_name);
	DTO_FIELD_INFO(class_name) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.name");
	}
	// 课程报名时间
	DTO_FIELD(String, time);
	DTO_FIELD_INFO(time) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.time");
	}
	// 购买课程数
	DTO_FIELD(Int32, buycoursesum);
	DTO_FIELD_INFO(buycoursesum) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.buycoursesum");
	}
	// 费用
	DTO_FIELD(Int32, pay);
	DTO_FIELD_INFO(pay) {
		info->description = ZH_WORDS_GETTER("StudentRecord.course.field.pay");
	}

};
/**
 * 学员报名数据分页传输对象
 */

class StudentSighnUPPageDTO : public PageDTO<StudentSighnUPDTO::Wrapper>
{
	DTO_INIT(StudentSighnUPPageDTO, PageDTO<StudentSighnUPDTO::Wrapper>);

};


#include OATPP_CODEGEN_END(DTO)

#endif