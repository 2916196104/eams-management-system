#pragma once
#ifndef _CLASS_STUDENT_DAO_H_
#define _CLASS_STUDENT_DAO_H_

#include "BaseDAO.h"
#include "domain/do/class_student/ClassStudentDO.h"
#include "domain/query/timetable/TimetableQuery.h"

using PtrClassStudentDO = std::shared_ptr<ClassStudentDO>;

struct ClassStudentBaseInfo
{
    uint64_t studentId = 0;
    std::string studentName;
    int32_t gender = 0;
};

/**
 * 班级学员关联表 数据操作层
 */
class ClassStudentDAO : public BaseDAO
{
public:
    // 1. 获取学员总数量 (用于分页)
    uint64_t count(const StuListQuery::Wrapper& query);

    // 按班级统计参与人数
    uint64_t countByClassId(uint64_t classId);

    // 2. 分页查询班级下的学员列表
    std::list<PtrClassStudentDO> selectAll(const StuListQuery::Wrapper& query);

    // 3. 根据学员ID查询他所报名的课程信息
    std::list<PtrClassStudentDO> selectByStudentId(const std::string& studentId);

    // 查询班级学员基础信息（关联 student）
    std::list<ClassStudentBaseInfo> selectStudentBaseWithPage(uint64_t classId, uint64_t pageIndex, uint64_t pageSize);

    // 4. 新增学员到班级 (用于“添加学员到课次”接口)
    uint64_t insert(const PtrClassStudentDO& doObj);
};

#endif // !_CLASS_STUDENT_DAO_H_