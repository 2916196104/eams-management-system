#pragma once
#ifndef _FINISH_STUDENT_SERVICE_H_
#define _FINISH_STUDENT_SERVICE_H_

#include "ApiHelper.h"
#include "dao/finishstudent/FinishStudentDAO.h"

class FinishStudentService
{
private:
	FinishStudentDAO m_finishStudentDAO;
public:
	std::list<FinishStudentDTO::Wrapper> listFinishStudentByIds(const oatpp::List<oatpp::UInt64>& ids);
	int importFinishStudent(const std::list<FinishStudentDTO::Wrapper>& rows);
};

#endif // !_FINISH_STUDENT_SERVICE_H_
