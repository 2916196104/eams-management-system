#pragma once
#ifndef _CLASSROOMDAO_H_
#define _CLASSROOMDAO_H_

#include "BaseDAO.h"
#include "domain/do/Schedule/ClassroomDO.h"
#include "domain/dto/Schedule/ClassroomDTO.h"
#include "domain/query/Schedule/ClassroomQuery.h"

class ClassroomDAO :public BaseDAO
{
public:
    // 获取数据条数
    uint64_t count(const ClassroomQuery::Wrapper& query);
    // 获取教室列表
    std::list<PtrClassroomDO> selectAll(const ClassroomQuery::Wrapper& query);
};

#endif