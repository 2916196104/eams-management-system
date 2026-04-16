/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/15 15:54:59

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
#include "StudentLessonCountLogDAO.h"
#include "StudentLessonCountLogMapper.h"

PtrStudentLessonCountLogViewDO StudentLessonCountLogDAO::selectById(const string& id)
{
    string sql = R"(SELECT 
                        log.id, 
                        log.student_id, 
                        log.course_id, 
                        log.lesson_id, 
                        log.change_count, 
                        log.remaining_count, 
                        log.staff_id, 
                        log.add_time,
                        log.remark AS log_remark,
                        -- 关联学员表：获取学员姓名 
                        s.name AS student_name, 
                        -- 关联课程表：获取课程名称 
                        c.name AS course_name, 
                        -- 关联科目表：获取科目 
                        staff.name AS staff_name
                    FROM student_lesson_count_log log 
                    -- 关联：学员表 
                    LEFT JOIN student s ON log.student_id = s.id 
                    -- 关联：课程表 
                    LEFT JOIN course c ON log.course_id = c.id 
                    -- 关联：教师员工表 
                    LEFT JOIN staff sf ON log.staff_id = sf.id 
                    WHERE log.student_id = ? 
                    ORDER BY log.add_time DESC)";

    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, id); // 绑定参数
    // 修改了调用，使用参数列表
    return sqlSession->executeQueryOne<PtrStudentLessonCountLogViewDO>(sql, StudentLessonCountLogViewMapper(), params);
}