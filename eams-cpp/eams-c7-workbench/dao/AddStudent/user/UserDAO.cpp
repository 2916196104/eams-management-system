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
#include "dao/AddStudent/user/UserDAO.h"
#include "SqlHelper.h"

int UserDAO::insert(const UserDO& userDO)
{
    try {
        // 检查必要字段
        if (userDO.getMobile().empty()) {
            std::cerr << "ERROR: 用户信息缺少必要字段: mobile" << std::endl;
            return -1;
        }

        // 生成插入SQL
        SqlParams params;

        // 构建参数化的插入SQL
        string sql = R"(
            INSERT INTO user (id, name, mobile, add_time, creator) 
            VALUES (?, ?, ?, ?, ?)
        )";

        // 绑定参数
        SQLPARAMS_PUSH(params, "ull", uint64_t, userDO.getId());
        SQLPARAMS_PUSH(params, "s", std::string, userDO.getName());
        SQLPARAMS_PUSH(params, "s", std::string, userDO.getMobile());
        SQLPARAMS_PUSH(params, "s", std::string, userDO.getAddTime());
        SQLPARAMS_PUSH(params, "ull", uint64_t, userDO.getCreator());

        // 执行插入
        int result = sqlSession->executeUpdate(sql, params);

        if (result > 0) {
            return result;
        }
        else {
            std::cerr << "ERROR: 插入用户记录失败，影响行数: " << result << std::endl;
            return -1;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "ERROR: 插入用户记录时发生异常: " << e.what() << std::endl;
        return -1;
    }
    catch (...) {
        std::cerr << "ERROR: 插入用户记录时发生未知异常" << std::endl;
        return -1;
    }
}