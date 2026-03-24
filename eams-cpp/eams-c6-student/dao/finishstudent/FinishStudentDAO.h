#pragma once
#ifndef _FINISH_STUDENT_DAO_H_
#define _FINISH_STUDENT_DAO_H_

#include "BaseDAO.h"
#include "ApiHelper.h"
#include "domain/dto/finishstudent/FinishStudentDTO.h"
#include "domain/do/student/StudentDO.h"

/**
 * 结业学员数据访问�?
 */
class FinishStudentDAO : public BaseDAO
{
public:
	std::list<FinishStudentDTO::Wrapper> listFinishStudentByIds(const oatpp::List<oatpp::UInt64>& ids);
	int updateFinishStudentBatch(const std::list<FinishStudentDO>& rows);
};

#endif // !_FINISH_STUDENT_DAO_H_


