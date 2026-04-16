#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/14 19:27:22

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
#ifndef _ATTENDANCEVO_H_
#define _ATTENDANCEVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/attendance-records/attendanceDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 上课记录列表显示对象
 */
class attendance_recordsJsonVO : public JsonVO<attendance_recordsDTO::Wrapper>
{
	DTO_INIT(attendance_recordsJsonVO, JsonVO<attendance_recordsDTO::Wrapper>);
};

/*
* 上课记录分页显示对象
*/
class attendance_recordsPageJsonVO : public JsonVO<attendance_recordsPageDTO::Wrapper>
{
	DTO_INIT(attendance_recordsPageJsonVO, JsonVO<attendance_recordsPageDTO::Wrapper>);
};

/*
* 评价课次显示对象
*/
/*
class attendance_recordsEvaluateJsonVO : public JsonVO<attendance_recordsEvaluateDTO::Wrapper>
{
	DTO_INIT(attendance_recordsEvaluateJsonVO, JsonVO<attendance_recordsEvaluateDTO::Wrapper>);
};
*/
#include OATPP_CODEGEN_END(DTO)

#endif // !_ATTENDANCEVO_H_