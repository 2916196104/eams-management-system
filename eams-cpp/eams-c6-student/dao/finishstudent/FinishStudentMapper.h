#pragma once
#ifndef _FINISH_STUDENT_MAPPER_H_
#define _FINISH_STUDENT_MAPPER_H_

#include "Mapper.h"
#include "domain/dto/finishstudent/FinishStudentDTO.h"

/**
 * 结业学员查询结果映射
 */
class FinishStudentMapper : public Mapper<FinishStudentDTO::Wrapper>
{
public:
	FinishStudentDTO::Wrapper mapper(ResultSet* rs) const override
	{
		return FinishStudentDTO::createShared();
	}
};

#endif // !_FINISH_STUDENT_MAPPER_H_
