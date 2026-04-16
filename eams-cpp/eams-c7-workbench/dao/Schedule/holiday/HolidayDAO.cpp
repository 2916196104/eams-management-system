#include "stdafx.h"
#include "HolidayDAO.h"
#include "HolidayMapper.h"

std::list<std::string> HolidayDAO::selectDatesByRange(const std::string& startDate, const std::string& endDate)
{
	string sql = "SELECT date FROM holiday WHERE date >= ? AND date <= ?";
	return sqlSession->executeQuery<std::string>(sql, HolidayDateMapper(), "%s%s", startDate, endDate);
}
