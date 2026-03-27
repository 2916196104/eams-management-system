#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/03/14 19:15:19

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
#ifndef _HOMEWORKDTO_H_
#define _HOMEWORKDTO_H_
#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 数据传输对象
 */
class HomeworkDTO : public oatpp::DTO
{
	DTO_INIT(HomeworkDTO, DTO);

	API_DTO_FIELD_DEFAULT(UInt64, id, ZH_WORDS_GETTER("homework.field.id"));
	API_DTO_FIELD_DEFAULT(String, title, ZH_WORDS_GETTER("homework.field.title"));
	API_DTO_FIELD_DEFAULT(UInt64, classId, ZH_WORDS_GETTER("homework.field.classId"));
	API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("homework.field.addTime"));
	API_DTO_FIELD_DEFAULT(UInt64, creator, ZH_WORDS_GETTER("homework.field.creator"));
};

class HomeworkDetailDTO : public HomeworkDTO
{
	DTO_INIT(HomeworkDetailDTO, HomeworkDTO);

	API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("homework.field.content"));
	API_DTO_FIELD_DEFAULT(UInt64, editor, ZH_WORDS_GETTER("homework.field.editor"));
	API_DTO_FIELD_DEFAULT(String, editTime, ZH_WORDS_GETTER("homework.field.editTime"));
	API_DTO_FIELD_DEFAULT(UInt64, orgId, ZH_WORDS_GETTER("homework.field.orgId"));
};

class HomeworkAddDTO : public oatpp::DTO
{
	DTO_INIT(HomeworkAddDTO, DTO);

	API_DTO_FIELD_DEFAULT(String, title, ZH_WORDS_GETTER("homework.field.title"));
	API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("homework.field.content"));
	API_DTO_FIELD_DEFAULT(UInt64, classId, ZH_WORDS_GETTER("homework.field.classId"));
	API_DTO_FIELD_DEFAULT(UInt64, creator, ZH_WORDS_GETTER("homework.field.creator"));
	API_DTO_FIELD_DEFAULT(UInt64, orgId, ZH_WORDS_GETTER("homework.field.orgId"));
};

class HomeworkPageDTO : public PageDTO<HomeworkDTO::Wrapper>
{
	DTO_INIT(HomeworkPageDTO, PageDTO<HomeworkDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_HOMEWORKDTO_H_