#pragma once
#ifndef _FINISH_STUDENT_MAPPER_H_
#define _FINISH_STUDENT_MAPPER_H_

#include "Mapper.h"
#include "domain/dto/finishstudent/FinishStudentDTO.h"


class FinishStudentMapper : public Mapper<FinishStudentDTO::Wrapper>
{
public:
	FinishStudentDTO::Wrapper mapper(ResultSet* rs) const override
	{
		auto dto = FinishStudentDTO::createShared();
		dto->id = rs->getInt64("id");
		dto->studentName = rs->getString("student_name").c_str();
		dto->parentName = rs->getString("parent_name").c_str();
		dto->familyRel = rs->getInt("family_rel");
		dto->mobile = rs->getString("mobile").c_str();
		dto->counselor = rs->getString("counselor").c_str();
		dto->grade = rs->getString("grade").c_str();
		dto->schoolName = rs->getString("school_name").c_str();
		dto->lessonCount = rs->getInt("lesson_count");
		dto->points = rs->getInt("points");
		dto->gender = rs->getInt("gender");
		dto->age = rs->getInt("age");
		dto->remark = rs->getString("remark").c_str();
		dto->graduationDate = rs->getString("graduation_date").c_str();
		return dto;
	}
};

#endif // !_FINISH_STUDENT_MAPPER_H_
