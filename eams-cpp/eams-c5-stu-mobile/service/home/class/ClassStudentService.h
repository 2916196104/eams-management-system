#pragma once

#ifndef _CLASS_STUDENT_SERVICE_
#define _CLASS_STUDENT_SERVICE_
// 替换VO/Query/DTO头文件路径，统一为ClassStudent命名
#include "domain/vo/home/class/ClassStudentVO.h"
#include "domain/query/home/class/ClassStudentQuery.h"
#include "domain/dto/home/class/ClassStudentDTO.h"

// 服务类名改为ClassStudentService
class ClassStudentService
{
public:
    // 方法返回值和参数均替换为ClassStudent相关DTO/Query
    ClassStudentPageDTO::Wrapper listAll(const ClassStudentQuery::Wrapper& query);
};

#endif // !_CLASS_STUDENT_SERVICE_