#pragma once
#ifndef _REGISTERDAO_H_
#define _REGISTERDAO_H_

#include "../../domain/do/Course/RegisterDO.h"
#include "../../../lib-mysql/include/BaseDAO.h"

class RegisterDAO : public BaseDAO
{
public:
    // 显式构造函数，确保 sqlSession 从基类传递（实际需根据你的 BaseDAO 实现调整）
    RegisterDAO() = default;

    // 插入报名记录
    uint64_t insert(RegisterDO& data);

    // 根据姓名查询学生 ID（返回 0 表示未找到或出错）
    int64_t selectStudentIdByName(const char* name);

    // 根据姓名查询课程 ID（返回 0 表示未找到或出错）
    int64_t selectCourseIdByName(const char* name);

    // 根据姓名查询科目 ID（返回 0 表示未找到或出错）
    int64_t selectSubjectIdByName(const char* name);
};

#endif // _REGISTERDAO_H_