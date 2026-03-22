#include "stdafx.h"
#include "service/finishstudent/FinishStudentService.h"

std::list<FinishStudentDTO::Wrapper> FinishStudentService::listFinishStudentByIds(const oatpp::List<oatpp::String>& ids)
{
	return m_finishStudentDAO.listFinishStudentByIds(ids);
}

int FinishStudentService::importFinishStudent(const std::list<FinishStudentDTO::Wrapper>& rows)
{
	int updatedRows = 0;
	for (const auto& row : rows) {
		updatedRows += m_finishStudentDAO.updateFinishStudent(row);
	}
	return updatedRows;
}
