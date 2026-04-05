#pragma once
#ifndef _SELECTTEACHERSERVICE_H_
#define _SELECTTEACHERSERVICE_H_
#include "domain/dto/Schedule/SelectTeacherDTO.h"
#include "domain/query/Schedule/SelectTeacherQuery.h"
#include "domain/do/Schedule/SelectTeacherDO.h"
#include "dao/Schedule/SelectTeacherDAO.h"
#include "dao/Schedule/SelectTeacherWrapper.h"
class SelectTeacherService
{
public:
	// 分页查询所有数据
	SelectTeacherPageDTO::Wrapper listAll(const SelectTeacherQuery::Wrapper& query);
};
#endif