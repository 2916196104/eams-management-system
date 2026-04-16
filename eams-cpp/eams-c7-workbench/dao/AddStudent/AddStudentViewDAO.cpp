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
#include "dao/AddStudent/AddStudentViewDAO.h"
#include "dao/AddStudent/AddStudentViewMapper.h"
#include "SqlHelper.h"
uint64_t AddStudentViewDAO::getUserIdByPhone(string phone)
{
	if (phone.empty()) return 0;

    // 推荐写法（防止注入且逻辑清晰）：
    string sql = "select id from user where mobile = ? LIMIT 1;";
    uint64_t userId = sqlSession->executeQueryNumerical(sql, "s", phone);

	return userId;
}
uint64_t AddStudentViewDAO::insertStudent(const StudentDO& studentDO)
{
    try {
        // 检查必要字段
        if (studentDO.getUserId() == 0 || studentDO.getName().empty()) {
            std::cerr << "ERROR: 学生信息缺少必要字段: user_id=" << studentDO.getUserId()
                << ", name=" << studentDO.getName() << std::endl;
            return 0;
        }

        // 生成插入SQL
        SqlParams params;

        // 构建参数化的插入SQL
        string sql = R"(
            INSERT INTO student (
                id, user_id, family_rel, school_id, name, 
                stage, gender, birthday, remark, add_time, 
                creator, idcard, grade, join_date
            ) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
        )";

        // 绑定参数
        SQLPARAMS_PUSH(params, "ull", uint64_t, studentDO.getId());
        SQLPARAMS_PUSH(params, "ull", uint64_t, studentDO.getUserId());
        SQLPARAMS_PUSH(params, "i", int32_t, studentDO.getFamilyRel());
        SQLPARAMS_PUSH(params, "ull", uint64_t, studentDO.getSchoolId());
        SQLPARAMS_PUSH(params, "s", std::string, studentDO.getName());
        SQLPARAMS_PUSH(params, "i", int32_t, studentDO.getStage());
        SQLPARAMS_PUSH(params, "i", int32_t, studentDO.getGender());
        SQLPARAMS_PUSH(params, "s", std::string, studentDO.getBirthday());
        SQLPARAMS_PUSH(params, "s", std::string, studentDO.getRemark());
        SQLPARAMS_PUSH(params, "s", std::string, studentDO.getAddTime());
        SQLPARAMS_PUSH(params, "ull", uint64_t, studentDO.getCreator());
        SQLPARAMS_PUSH(params, "s", std::string, studentDO.getIdcard());
        SQLPARAMS_PUSH(params, "i", int32_t, studentDO.getGrade());
        SQLPARAMS_PUSH(params, "s", std::string, studentDO.getJoinDate());

        // 执行插入
        int result = sqlSession->executeUpdate(sql, params);

        if (result > 0) {
            return studentDO.getId();
        }
        else {
            std::cerr << "ERROR: 插入学生记录失败，影响行数: " << result << std::endl;
            return 0;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: 插入学生记录时发生异常: " << e.what() << std::endl;
        return 0;
    }
    catch (...) {
        std::cerr << "ERROR: 插入学生记录时发生未知异常" << std::endl;
        return 0;
    }
}
