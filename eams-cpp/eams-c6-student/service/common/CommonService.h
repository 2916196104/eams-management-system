#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:08:56

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
#ifndef _COMMON_SERVICE_
#define _COMMON_SERVICE_
#include "../../lib-oatpp/include/domain/vo/BaseJsonVO.h"
#include "domain/vo/common/CommonVO.h"
#include "domain/query/common/CommonQuery.h"
#include "domain/dto/common/CommonDTO.h"
#include "../../dao/common/CommonDAO.h"
class StudentService {
public:
	void ModifyStudentHeadImg(ModifyStudentHeadImgDTO::Wrapper dto);
	StudentDTO::Wrapper GetStudentDetailById(uint64_t studentId);
};
class RegistrationRecordService {
public:
	RegistrationPageDTO::Wrapper GetRegistrationRecordWithPage(RegistrationPageQuery::Wrapper query);

};
//班级列表服务
class getClassListService
{
public:
	// 分页查询所有班级列表数据
	getClassListPageDTO::Wrapper listAll(const getClassListQuery::Wrapper& query);
};

//课程统计服务
class getCourseStatisticsService
{
public:
	// 分页查询所有课程统计数据
	getCourseStatisticsPageDTO::Wrapper listAll(const getCourseStatisticsQuery::Wrapper& query);

};

//加入班级服务
class JoinclassService
{
public:
	// 分页查询可加入的班级列表
	JoinclassPageDTO::Wrapper listAll(const JoinclassQuery::Wrapper& query);

	// 学生加入班级
	bool joinClass(const oatpp::String& studentId, const oatpp::String& className);

};

//跟进记录服务
class ContactRecordService
{
public:
	// 删除跟进记录
	StringJsonVO::Wrapper deleteContactRecord(const DeleteContactRecordDTO::Wrapper& dto);
};

#endif // !_SAMPLE_SERVICE_

