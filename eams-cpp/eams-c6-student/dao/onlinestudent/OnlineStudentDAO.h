#pragma once
#ifndef _ONLINESTUDENT_DAO_
#define _ONLINESTUDENT_DAO_

#include "BaseDAO.h"
#include "OnlineStudentMapper.h"
#include <vector>
#include <string>

class OnlineExportDAO : public BaseDAO
{
public:
	std::list<PtrStudentDetail> selectByIds(const std::vector<std::string>& ids);
};

#endif