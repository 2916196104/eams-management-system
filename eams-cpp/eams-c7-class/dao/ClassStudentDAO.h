#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:23:49

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _CLASS_STUDENT_DAO_
#define _CLASS_STUDENT_DAO_

#include "BaseDAO.h"
#include "domain/do/ClassStudentDO.h"
#include "domain/do/StudentDO.h"
#include "domain/do/StudentCourseDO.h"
#include "domain/do/CourseDO.h"
#include "domain/do/SubjectDO.h"
#include "domain/query/StudentQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

using oatpp::UInt64;
using oatpp::Int32;
using oatpp::String;

/**
 * 班级学员表数据库操作实现
 */
class ClassStudentDAO : public BaseDAO
{
private:
    // 查询条件构建器（班级学员列表）
    inline std::string queryClassStudentListBuilder(const ClassStudentListQuery::Wrapper& query, SqlParams& params);

    // 查询条件构建器（学员课程列表）
    inline std::string queryStudentCourseListBuilder(const StudentCourseListQuery::Wrapper& query, SqlParams& params);

public:
    // ==================== 获取班级学员列表（分页）相关 ====================
    // 统计满足条件的班级学员数量
    uint64_t countClassStudentList(const ClassStudentListQuery::Wrapper& query);

    // 分页查询班级学员列表（返回智能指针列表）
    std::list<PtrStudentDO> selectClassStudentList(const ClassStudentListQuery::Wrapper& query);

    // 批量查询学员剩余课时（根据学员ID列表）
    std::map<uint64_t, Int32> selectRemainingLessonCountByStudentIds(const std::vector<UInt64>& studentIds);

    // 查询单个学员的剩余课时汇总
    Int32 selectTotalRemainingLessonCount(UInt64 studentId);

    // ==================== 获取班级学员详情相关 ====================
    // 通过学员ID查询单个学员详情
    PtrStudentDO selectStudentById(UInt64 studentId);

    // 通过学员ID获取家长手机号（关联user表）
    String selectMobileByStudentId(UInt64 studentId);

    // 通过顾问ID获取顾问姓名
    String selectCounselorNameByCounselorId(UInt64 counselorId);

    // 统计学员报名课程总数
    uint64_t countStudentCourseTotal(UInt64 studentId);

    // 统计学员已完成课时总数
    Int32 selectTotalLessonComplete(UInt64 studentId);

    // ==================== 获取班级学员课程列表（分页）相关 ====================
    // 统计满足条件的学员课程数量
    uint64_t countStudentCourseList(const StudentCourseListQuery::Wrapper& query);

    // 分页查询学员课程列表（返回智能指针列表）
    std::list<PtrStudentCourseDO> selectStudentCourseList(const StudentCourseListQuery::Wrapper& query);

    // 根据课程ID批量查询课程信息
    std::map<uint64_t, CourseDO> selectCourseMapByIds(const std::vector<UInt64>& courseIds);

    // 根据科目ID批量查询科目信息
    std::map<uint64_t, SubjectDO> selectSubjectMapByIds(const std::vector<UInt64>& subjectIds);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_CLASS_STUDENT_DAO_