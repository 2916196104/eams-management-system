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
#include "RefundDAO.h"
#include "RefundMapper.h"

PtrRefundViewDO RefundDAO::selectById(const string& id)
{
    string sql = R"(SELECT 
                        rf.id, 
                        rf.student_id, 
                        rf.student_course_id, 
                        rf.operator, 
                        rf.refund_amount, 
                        rf.refund_lesson_count, 
                        rf.apply_time, 
                        rf.remark, 
                        rf.done_time, 
                        rf.type_num, 
                        rf.verify_state, 
                        rf.verify_time, 
                        rf.verify_staff,
                        -- 关联学员表：获取学员姓名 
                        s.name AS student_name
                    FROM refund rf 
                    -- 关联：学员表 
                    LEFT JOIN student s ON rf.student_id = s.id 
                    WHERE rf.student_id = ? 
                    ORDER BY rf.apply_time DESC)";

    SqlParams params;
    SQLPARAMS_PUSH(params, "s", std::string, id); // 绑定参数
    return sqlSession->executeQueryOne<PtrRefundViewDO>(sql, RefundViewMapper(), params);
}