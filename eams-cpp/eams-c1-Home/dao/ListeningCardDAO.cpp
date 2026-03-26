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
#include "ListeningCardDAO.h"
#include "MyListeningCardMapper.h"

std::list<cardDO> ListeningCardDAO::selectCardByUserId(const string& userId)
{
	string sql = "SELECT \
        r.course_id,\
        t.title,\
        r.expired_date,\
        r.lesson_count,\
        r.add_time \
        FROM \
        course_trial_record r \
        LEFT JOIN \
        course_trial t ON r.trial_id = t.id \
        WHERE \
        r.user_id = ? \
        AND t.deleted = 0 \
        ORDER BY \
        r.add_time DESC; ";
	
    return sqlSession->executeQuery<cardDO>(sql, MyListeningCardMapper(), "%s", userId);
}