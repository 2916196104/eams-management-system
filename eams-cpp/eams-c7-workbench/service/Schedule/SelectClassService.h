#pragma once
#ifndef _SELECTCLASSSERVICE_H_
#define _SELECTCLASSSERVICE_H_
#include "domain/dto/Schedule/SelectClassDTO.h"
#include "domain/query/Schedule/SelectClassQuery.h"
#include "domain/do/Schedule/SelectClassDO.h"
#include "dao/Schedule/SelectClassDAO.h"
#include "dao/Schedule/SelectClassWrapper.h"
class SelectClassService
{
public:
	// 分页查询所有数据
	SelectClassPageDTO::Wrapper listAll(const SelectClassQuery::Wrapper& query);
};
#endif