#pragma once
#ifndef _FINISH_STUDENT_DAO_H_
#define _FINISH_STUDENT_DAO_H_

#include "BaseDAO.h"
#include "ApiHelper.h"
#include "domain/dto/finishstudent/FinishStudentDTO.h"

/**
 * 缁撲笟瀛﹀憳鏁版嵁璁块棶灞?
 */
class FinishStudentDAO : public BaseDAO
{
public:
	std::list<FinishStudentDTO::Wrapper> listFinishStudentByIds(const oatpp::List<oatpp::String>& ids);
	int updateFinishStudent(const FinishStudentDTO::Wrapper& dto);
};

#endif // !_FINISH_STUDENT_DAO_H_
