#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 14:23:49

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
#ifndef _SAMPLE_DAO_
#define _SAMPLE_DAO_
#include "BaseDAO.h"
#include "../../domain/query/common/CommonQuery.h"
#include "../../domain/dto/common/CommonDTO.h"
class StudentDAO :public BaseDAO
{
public:
	void updateStudentHeadImg(uint64_t studentId, const std::string& headImg);
	StudentDTO::Wrapper getStudentDetailById(uint64_t studentId);
};
class RegistrationRecordDAO :public BaseDAO
{
public:
	uint64_t count(uint64_t studentId);
	// 不使用 DO：SQL JOIN 结果直接映射成 DTO
	std::list<RegistrationDTO::Wrapper> selectRegistrationRecordWithPage(const RegistrationPageQuery::Wrapper& query);
	
};
#endif // !_SAMPLE_DAO_
