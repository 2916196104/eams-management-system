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

std::string ClassDAO::queryConditionBuilder(const classQuery::Wrapper& query, SqlParams& params)
{
	std::stringstream sqlCondition;
	sqlCondition << " WHERE t1.id in (select class_id from class_student ";

	// 只根据 student_id 过滤
	sqlCondition << " WHERE student_id=?";
	SQLPARAMS_PUSH(params, "i", uint32_t, query->student_id.getValue(0));
    sqlCondition << " and deleted = 0) AND t1.deleted !=1";
	return sqlCondition.str();
}

uint64_t ClassDAO::count(const classQuery::Wrapper& query)
{
    SqlParams params;
    std::string sql = "SELECT COUNT(1) FROM class t1 ";
    sql += queryConditionBuilder(query, params);
    return sqlSession->executeQueryNumerical(sql, params);
}

std::list<ClassDO> ClassDAO::selectWithPage(const classQuery::Wrapper& query)
{
    SqlParams params;

    std::string sql =
        "SELECT "
        "  t1.*, "
        "  t3.name AS classroom, "
        "  t4.name AS teacher_name, "
        "  t7.name AS course_name, "
        "  (SELECT COUNT(0) "
        "     FROM class_student t0 "
        "    WHERE t0.class_id = t1.id AND t0.deleted = 0) AS student_count "
        "FROM class t1 "
        "LEFT JOIN classroom t3 ON t3.id = t1.classroom_id "
        "LEFT JOIN staff t4 ON t4.id = t1.teacher_id "
        "LEFT JOIN course t7 ON t7.id = t1.course_id ";

    // 只加 student_id 条件
    sql += queryConditionBuilder(query, params);

    sql += " ORDER BY t1.id DESC ";

    int offset = (query->pageIndex - 1) * query->pageSize;
    sql += " LIMIT " + std::to_string(offset) + "," + std::to_string(query->pageSize);

    return sqlSession->executeQuery<ClassDO>(sql, ClassMapper(), params);
}

/*
        SELECT
        s.gender,
        s.name
        FROM student s
        WHERE s.deleted = 0
        AND s.id IN(
            SELECT cs.student_id
            FROM class_student cs
            WHERE cs.class_id = 1
            AND cs.deleted = 0
        );
*/
std::list<StudentDO> StudentDAO::selectByClassId(uint64_t class_id)
{
    SqlParams params;

    std::string sql =
        "SELECT "
        "  s.gender, "
        "  s.name "
        "FROM student s "
        "WHERE s.deleted = 0 "
        "  AND s.id IN ("
        "      SELECT cs.student_id "
        "      FROM class_student cs "
        "      WHERE cs.class_id = ? "
        "        AND cs.deleted = 0"
        "  ) "
        "ORDER BY s.id DESC";
    SQLPARAMS_PUSH(params, "i", uint64_t, class_id);

    return sqlSession->executeQuery<StudentDO>(sql, StudentListMapper(), params);
}

ClassDO ClassDAO::selectById(uint64_t id)
{
    SqlParams params;

    std::string sql =
        "SELECT "
        "  t1.name, "
        "  t1.start_date, "
        "  t1.end_date, "
        "  t1.remark, "
        "  t3.name AS classroom, "
        "  t4.name AS teacher_name, "
        "  t7.name AS course_name, "
        "  ( SELECT COUNT(0) "
        "      FROM class_student t0 "
        "     WHERE t0.class_id = t1.id AND t0.deleted = 0 "
        "  ) AS student_count, "
        "  ( SELECT COUNT(0) "
        "      FROM lesson l "
        "     WHERE l.class_id = t1.id "
        "       AND l.date <= CURDATE() "
        "       AND l.end_time < CURTIME() "
        "  ) AS over_lesson_count "
        "FROM class t1 "
        "LEFT JOIN classroom t3 ON t3.id = t1.classroom_id "
        "LEFT JOIN staff t4 ON t4.id = t1.teacher_id "
        "LEFT JOIN course t7 ON t7.id = t1.course_id "
        "WHERE t1.id = ? AND t1.deleted != 1";

    SQLPARAMS_PUSH(params, "i", uint64_t, id);

	return sqlSession->executeQueryOne<ClassDO>(sql, ClassMapper(), params);
}