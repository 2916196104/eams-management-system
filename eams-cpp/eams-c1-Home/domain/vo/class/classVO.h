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
#ifndef _CLASSVO_H_
#define _CLASSVO_H_

#include "../../GlobalInclude.h"
#include "../../dto/class/classDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 班级列表显示对象
 
class classListJsonVO : public JsonVO<ClassListDTO::Wrapper>
{
	DTO_INIT(classListJsonVO, JsonVO<ClassListDTO::Wrapper>);
};
*/
/*
* 班级分页显示对象
*/
class classPageJsonVO : public JsonVO<ClassPageDTO::Wrapper>
{
	DTO_INIT(classPageJsonVO, JsonVO<ClassPageDTO::Wrapper>);
};

/*
* 班级详情显示对象
*/
class classInfoJsonVO : public JsonVO<ClassInfoDTO::Wrapper>
{
	DTO_INIT(classInfoJsonVO, JsonVO<ClassInfoDTO::Wrapper>);
};

/*
* 学生列表显示对象
*/
class studentListJsonVO : public JsonVO<StudentListDTO::Wrapper>
{
	DTO_INIT(studentListJsonVO, JsonVO<StudentListDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)

#endif // !_CLASSVO_H_