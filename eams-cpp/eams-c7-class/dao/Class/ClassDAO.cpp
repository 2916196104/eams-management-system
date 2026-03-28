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
#include "ClassDAO.h"
#include "ClassMapper.h"

// 条件构建器实现
std::string ClassDAO::queryConditionBuilder(const ClassQuery::Wrapper& query, SqlParams& params)
{
    stringstream sqlCondition;
    sqlCondition << " WHERE c.`deleted` = 0 ";


    // 以下根据实际查询需求，判断字段是否有值，动态拼接条件
    if (query->className) 
    { 
        // 班级名称的模糊查询
        sqlCondition << " AND c.`name` LIKE ?"; 
        SQLPARAMS_PUSH(params, "s", std::string, "%" + query->className.getValue("") + "%");
    }
    if (query->course) 
    { 
        // 课程ID的精确查询
        sqlCondition << " AND c.`course_id` = ?"; 
        SQLPARAMS_PUSH(params, "ll", int64_t, query->course.getValue(0));
    }
    if (query->startTime) 
    { 
        // 创建时间范围查询
        sqlCondition << " AND c.`add_time` >= ?"; 
        SQLPARAMS_PUSH(params, "s", std::string, query->startTime.getValue(""));
    }
    if (query->endTime) 
    {
        sqlCondition << " AND c.`add_time` <= ?"; 
        SQLPARAMS_PUSH(params, "s", std::string, query->endTime.getValue(""));
    }
    // 后续可根据Query中其他字段继续查询
    // if (query->classroom)
    // if (query->enrollment_progress)
    return sqlCondition.str();
}

// 统计数量
uint64_t ClassDAO::count(const ClassQuery::Wrapper& query)
{
    SqlParams params;
    // 为 class 表添加别名 c，使其与 queryConditionBuilder 中的前缀匹配
    string sql = "SELECT COUNT(*) FROM `class` c ";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

// 分页查询
std::list<ClassViewDO> ClassDAO::selectWithPage(const ClassQuery::Wrapper& query)
{
    SqlParams params;

    string sql = "SELECT c.*, t.name as teacher_name, crs.name as course_name FROM `class` c ";
    sql += "LEFT JOIN `staff` t ON c.teacher_id = t.id ";
    sql += "LEFT JOIN `course` crs ON c.course_id = crs.id ";
    sql += queryConditionBuilder(query, params);
    sql += " ORDER BY c.`add_time` DESC ";
    sql += " LIMIT ?, ?";
    SQLPARAMS_PUSH(params, "ll", long long, (query->pageIndex - 1) * query->pageSize);
    SQLPARAMS_PUSH(params, "ll", long long, query->pageSize);
    return sqlSession->executeQuery<ClassViewDO>(sql, ClassViewMapper(), params);
}
// 按ID查询单个
ClassViewDO ClassDAO::selectById(int64_t id) {
    string sql = "SELECT "
        "c.id, c.name, c.course_id, c.classroom_id, c.creator, c.editor, c.add_time, c.edit_time, c.deleted, "
        "c.teacher_id, c.remark, c.be_over, c.over_time, c.over_operator, c.start_date, c.end_date, "
        "c.planned_student_count, c.planned_lesson_count, c.school_id, c.org_id, c.grade_id, "
        "t.name as teacher_name, crs.name as course_name "
        "FROM `class` c "
        "LEFT JOIN `staff` t ON c.teacher_id = t.id "
        "LEFT JOIN `course` crs ON c.course_id = crs.id "
        "WHERE c.`id` = ? AND c.`deleted` = 0";

    return sqlSession->executeQueryOne<ClassViewDO>(sql, ClassViewMapper(), "ll", id);
}
/*
ClassViewDO ClassDAO::selectByName(const std::string& name)
{
    if (name.empty()) {
        return ClassViewDO();
    }

    std::string searchName = name;
    searchName.erase(0, searchName.find_first_not_of(" "));
    searchName.erase(searchName.find_last_not_of(" ") + 1);

    if (searchName.empty()) {
        return ClassViewDO();
    }

    std::string sql = "SELECT c.*, t.name as teacher_name, crs.name as course_name FROM `class` c "
        "LEFT JOIN `staff` t ON c.teacher_id = t.id "
        "LEFT JOIN `course` crs ON c.course_id = crs.id "
        "WHERE c.`deleted` = 0 AND (c.`name` = ? OR c.`name` LIKE ?) LIMIT 1";

    std::string exactName = searchName;
    std::string likeName = "%" + searchName + "%";

    try {
      
        return sqlSession->executeQueryOne<ClassViewDO>(
            sql,
            ClassViewMapper(),
            "%s%s", exactName,likeName
        );
    }
    catch (const std::exception& e) {
        std::cout << "查询异常: " << e.what() << std::endl;
        return ClassViewDO();
    }
}
*/