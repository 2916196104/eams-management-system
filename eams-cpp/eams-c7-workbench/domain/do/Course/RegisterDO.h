#pragma once
#ifndef REGISTERDO_H_
#define REGISTERDO_H_

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"
#include "../../../../lib-mysql/include/BaseDO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class RegisterDO : public BaseDO
{
	MYSQL_SYNTHESIZE(int64_t, id, Id);
	MYSQL_SYNTHESIZE(int64_t, studentId, StudentId);
	MYSQL_SYNTHESIZE(int64_t, courseId, CourseId);
	MYSQL_SYNTHESIZE(int64_t, subjectId, SubjectId);
	MYSQL_SYNTHESIZE(std::string, startDate, StartDate);
	MYSQL_SYNTHESIZE(std::string, expireDate, ExpireDate);
	MYSQL_SYNTHESIZE(int32_t, countLessonTotal, CountLessonTotal);
	MYSQL_SYNTHESIZE(double, amount, Amount);
	MYSQL_SYNTHESIZE(double, discountAmount, DiscountAmount);
	MYSQL_SYNTHESIZE(double, paidAmount, PaidAmount);
	MYSQL_SYNTHESIZE(std::string, remark, Remark);
	MYSQL_SYNTHESIZE(int64_t, creator, Creator);
	MYSQL_SYNTHESIZE(std::string, addTime, AddTime);
	MYSQL_SYNTHESIZE(int32_t, deleted, Deleted);
	MYSQL_SYNTHESIZE(int32_t, verifyState, VerifyState);

public:
	RegisterDO() : BaseDO("student_course")
	{
		MYSQL_ADD_FIELD_PK("id", "l", id);
		MYSQL_ADD_FIELD("student_id", "l", studentId);
		MYSQL_ADD_FIELD("course_id", "l", courseId);
		MYSQL_ADD_FIELD("subject_id", "l", subjectId);
		MYSQL_ADD_FIELD("start_date", "s", startDate);
		MYSQL_ADD_FIELD("expire_date", "s", expireDate);
		MYSQL_ADD_FIELD("count_lesson_total", "i", countLessonTotal);
		MYSQL_ADD_FIELD("amount", "f", amount);
		MYSQL_ADD_FIELD("discount_amount", "f", discountAmount);
		MYSQL_ADD_FIELD("paid_amount", "f", paidAmount);
		MYSQL_ADD_FIELD("remark", "s", remark);
		MYSQL_ADD_FIELD("creator", "l", creator);
		MYSQL_ADD_FIELD("add_time", "s", addTime);
		MYSQL_ADD_FIELD("deleted", "i", deleted);
		MYSQL_ADD_FIELD("verify_state", "i", verifyState);
	}
};

typedef std::shared_ptr<RegisterDO> PtrRegisterDO;

#include OATPP_CODEGEN_END(DTO)
#endif