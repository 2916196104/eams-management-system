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

    // ÍÆ¼öÐ´·¨£¨·ÀÖ¹×¢ÈëÇÒÂß¼­ÇåÎú£©£º
    string sql = "select id from user where mobile = ? LIMIT 1;";
    uint64_t userId = sqlSession->executeQueryNumerical(sql, "s", phone);

	return userId;
}

