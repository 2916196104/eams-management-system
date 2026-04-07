#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2025/07/12 21:01:07

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
#ifndef _STUDENTLESSONCOUNTLOGDAO_H_
#define _STUDENTLESSONCOUNTLOGDAO_H_
#include "BaseDAO.h"
#include "domain/do/AddStudent/LessonLog/StudentLessonCountLogDO.h"

/**
 * 文件数据操作类
 */
class StudentLessonCountLogDAO : public BaseDAO
{
public:
	// 通过id查询数据
	PtrStudentLessonCountLogViewDO selectById(const string& id);
};

#endif // !#define _STUDENTLESSONCOUNTLOGDAO_H_
