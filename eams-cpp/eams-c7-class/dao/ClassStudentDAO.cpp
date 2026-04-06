/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:26:52

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
#include "stdafx.h"
#include "ClassStudentDAO.h"
#include "ClassStudentMapper.h"

using oatpp::UInt64;
using oatpp::Int32;
using oatpp::String;

// ==================== 查询条件构建器 ====================

std::string ClassStudentDAO::queryClassStudentListBuilder(const ClassStudentListQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE cs.`deleted` = 0 AND s.`deleted` = 0 ";

    // 班级ID（必传）
    if (query->classId) {
        sqlCondition << " AND cs.`class_id` = ?";
        SQLPARAMS_PUSH(params, "ll", int64_t, query->classId.getValue(0));
    }

    // 学员姓名（模糊查询）
    if (query->studentName && !query->studentName->empty()) {
        sqlCondition << " AND s.`name` LIKE ?";
        SQLPARAMS_PUSH(params, "s", std::string, "%" + query->studentName.getValue("") + "%");
    }

    return sqlCondition.str();
}

std::string ClassStudentDAO::queryStudentCourseListBuilder(const StudentCourseListQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE sc.`deleted` = 0 AND c.`deleted` = 0 ";

    // 学员ID（必传）
    if (query->studentId) {
        sqlCondition << " AND sc.`student_id` = ?";
        SQLPARAMS_PUSH(params, "ll", int64_t, query->studentId.getValue(0));
    }

    // 课程名称（模糊查询）
    if (query->courseName && !query->courseName->empty()) {
        sqlCondition << " AND c.`name` LIKE ?";
        SQLPARAMS_PUSH(params, "s", std::string, "%" + query->courseName.getValue("") + "%");
    }

    return sqlCondition.str();
}

// ==================== 获取班级学员列表（分页）相关 ====================

uint64_t ClassStudentDAO::countClassStudentList(const ClassStudentListQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM `class_student` cs "
        "INNER JOIN `student` s ON cs.`student_id` = s.`id` ";
    sql += queryClassStudentListBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<PtrStudentDO> ClassStudentDAO::selectClassStudentList(const ClassStudentListQuery::Wrapper& query)
{
    SqlParams params;

    string sql = "SELECT s.`id`, s.`name`, s.`gender`, s.`birthday`, s.`head_img`, s.`stage`, "
        "s.`join_date`, cs.`id` as class_student_id, cs.`consume_course_id` "
        "FROM `class_student` cs "
        "INNER JOIN `student` s ON cs.`student_id` = s.`id` ";
    sql += queryClassStudentListBuilder(query, params);

    sql += " ORDER BY cs.`add_time` DESC ";
    sql += " LIMIT ?, ?";
    SQLPARAMS_PUSH(params, "ll", long long, (query->pageIndex - 1) * query->pageSize);
    SQLPARAMS_PUSH(params, "ll", long long, query->pageSize);

    return sqlSession->executeQuery<PtrStudentDO>(sql, ClassStudentListMapper(), params);
}

std::map<uint64_t, Int32> ClassStudentDAO::selectRemainingLessonCountByStudentIds(const std::vector<UInt64>& studentIds)
{
    std::map<uint64_t, Int32> result;
    if (studentIds.empty()) {
        return result;
    }

    // 逐个查询（稳定可靠，避免 SQL 语法问题）
    for (auto studentId : studentIds) {
        SqlParams params;
        string sql = "SELECT IFNULL(SUM(`count_lesson_total` - `count_lesson_complete`), 0) as remaining "
            "FROM `student_course` "
            "WHERE `deleted` = 0 AND `student_id` = ?";
        SQLPARAMS_PUSH(params, "ll", int64_t, studentId);

        Int32 remaining = sqlSession->executeQueryNumerical(sql, params);
        result[studentId] = remaining;
    }

    return result;
}

Int32 ClassStudentDAO::selectTotalRemainingLessonCount(UInt64 studentId)
{
    SqlParams params;
    string sql = "SELECT IFNULL(SUM(`count_lesson_total` - `count_lesson_complete`), 0) as remaining "
        "FROM `student_course` "
        "WHERE `deleted` = 0 AND `student_id` = ?";
    SQLPARAMS_PUSH(params, "ll", int64_t, studentId);
    return sqlSession->executeQueryNumerical(sql, params);
}

// ==================== 获取班级学员详情相关 ====================

PtrStudentDO ClassStudentDAO::selectStudentById(UInt64 studentId)
{
    SqlParams params;
    string sql = "SELECT `id`, `name`, `gender`, `birthday`, `head_img`, `stage`, `remark`, "
        "`join_date`, `add_time`, `counselor`, `grade_id`, `credit` "
        "FROM `student` WHERE `id` = ? AND `deleted` = 0";

    SQLPARAMS_PUSH(params, "ll", int64_t, studentId);

    return sqlSession->executeQueryOne<PtrStudentDO>(sql, PtrStudentMapper(), params);
}

String ClassStudentDAO::selectMobileByStudentId(UInt64 studentId)
{
    SqlParams params;
    string sql = "SELECT u.`mobile` FROM `user` u "
        "INNER JOIN `student` s ON s.`user_id` = u.`id` "
        "WHERE s.`id` = ? AND s.`deleted` = 0";

    SQLPARAMS_PUSH(params, "ll", int64_t, studentId);

    return sqlSession->executeQueryOne<String>(sql, StringMapper(), params);
}

String ClassStudentDAO::selectCounselorNameByCounselorId(UInt64 counselorId)
{
    if (counselorId == 0) {
        return "";
    }
    SqlParams params;
    string sql = "SELECT `name` FROM `staff` WHERE `id` = ? AND `deleted` = 0";
    SQLPARAMS_PUSH(params, "ll", int64_t, counselorId);

    return sqlSession->executeQueryOne<String>(sql, StringMapper(), params);
}

uint64_t ClassStudentDAO::countStudentCourseTotal(UInt64 studentId)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM `student_course` WHERE `deleted` = 0 AND `student_id` = ?";
    SQLPARAMS_PUSH(params, "ll", int64_t, studentId);
    return sqlSession->executeQueryNumerical(sql, params);
}

Int32 ClassStudentDAO::selectTotalLessonComplete(UInt64 studentId)
{
    SqlParams params;
    string sql = "SELECT IFNULL(SUM(`count_lesson_complete`), 0) as total_complete "
        "FROM `student_course` "
        "WHERE `deleted` = 0 AND `student_id` = ?";
    SQLPARAMS_PUSH(params, "ll", int64_t, studentId);
    return sqlSession->executeQueryNumerical(sql, params);
}

// ==================== 获取班级学员课程列表（分页）相关 ====================

uint64_t ClassStudentDAO::countStudentCourseList(const StudentCourseListQuery::Wrapper& query)
{
    SqlParams params;
    string sql = "SELECT COUNT(*) FROM `student_course` sc "
        "INNER JOIN `course` c ON sc.`course_id` = c.`id` ";
    sql += queryStudentCourseListBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<PtrStudentCourseDO> ClassStudentDAO::selectStudentCourseList(const StudentCourseListQuery::Wrapper& query)
{
    SqlParams params;

    string sql = "SELECT sc.`id`, sc.`student_id`, sc.`course_id`, sc.`subject_id`, "
        "sc.`count_lesson_total`, sc.`count_lesson_complete`, sc.`count_lesson_refund`, "
        "sc.`start_date`, sc.`expire_date`, sc.`add_time`, sc.`remark`, sc.`priority`, "
        "c.`name` as course_name, s.`name` as subject_name "
        "FROM `student_course` sc "
        "INNER JOIN `course` c ON sc.`course_id` = c.`id` "
        "LEFT JOIN `subject` s ON sc.`subject_id` = s.`id` ";
    sql += queryStudentCourseListBuilder(query, params);

    sql += " ORDER BY sc.`add_time` DESC ";
    sql += " LIMIT ?, ?";
    SQLPARAMS_PUSH(params, "ll", long long, (query->pageIndex - 1) * query->pageSize);
    SQLPARAMS_PUSH(params, "ll", long long, query->pageSize);

    return sqlSession->executeQuery<PtrStudentCourseDO>(sql, StudentCourseListMapper(), params);
}

std::map<uint64_t, CourseDO> ClassStudentDAO::selectCourseMapByIds(const std::vector<UInt64>& courseIds)
{
    std::map<uint64_t, CourseDO> result;
    if (courseIds.empty()) {
        return result;
    }

    std::string placeholders;
    SqlParams params;
    for (size_t i = 0; i < courseIds.size(); ++i) {
        if (i > 0) placeholders += ", ";
        placeholders += "?";
        SQLPARAMS_PUSH(params, "ll", int64_t, courseIds[i]);
    }

    string sql = "SELECT `id`, `name`, `subject_id`, `lesson_count`, `price` "
        "FROM `course` WHERE `deleted` = 0 AND `id` IN (" + placeholders + ")";

    auto stmt = sqlSession->getConnection()->createStatement();
    auto rows = stmt->executeQuery(sql);

    while (rows->next()) {
        uint64_t courseId = rows->getInt64(1);
        CourseDO course;
        course.setId(courseId);
        course.setName(String(rows->getString(2).c_str()));
        course.setSubjectId(rows->getInt64(3));
        course.setLessonCount(rows->getInt(4));
        course.setPrice(rows->getDouble(5));

        result.emplace(courseId, std::move(course));
    }

    delete stmt;
    return result;
}

std::map<uint64_t, SubjectDO> ClassStudentDAO::selectSubjectMapByIds(const std::vector<UInt64>& subjectIds)
{
    std::map<uint64_t, SubjectDO> result;
    if (subjectIds.empty()) {
        return result;
    }

    std::string placeholders;
    SqlParams params;
    for (size_t i = 0; i < subjectIds.size(); ++i) {
        if (i > 0) placeholders += ", ";
        placeholders += "?";
        SQLPARAMS_PUSH(params, "ll", int64_t, subjectIds[i]);
    }

    string sql = "SELECT `id`, `name` FROM `subject` WHERE `deleted` = 0 AND `id` IN (" + placeholders + ")";

    auto stmt = sqlSession->getConnection()->createStatement();
    auto rows = stmt->executeQuery(sql);

    while (rows->next()) {
        uint64_t subjectId = rows->getInt64(1);
        SubjectDO subject;
        subject.setId(subjectId);
        subject.setName(String(rows->getString(2).c_str()));

        result.emplace(subjectId, std::move(subject));
    }

    delete stmt;
    return result;
}