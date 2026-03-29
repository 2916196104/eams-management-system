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
#ifndef _HOMEWORKVO_H_
#define _HOMEWORKVO_H_

#include "domain/vo/BaseJsonVO.h"
#include "../../GlobalInclude.h"
#include "../../dto/homework/homeworkDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义显示对象
 */
class HomeworkPageJsonVO : public JsonVO<HomeworkPageDTO::Wrapper>
{
	DTO_INIT(HomeworkPageJsonVO, JsonVO<HomeworkPageDTO::Wrapper>);
};

class HomeworkListJsonVO : public JsonVO<oatpp::List<HomeworkDTO::Wrapper>>
{
	DTO_INIT(HomeworkListJsonVO, JsonVO<oatpp::List<HomeworkDTO::Wrapper>>);
};
class HomeworkDetailJsonVO : public JsonVO<HomeworkDetailDTO::Wrapper>
{
	DTO_INIT(HomeworkDetailJsonVO, JsonVO<HomeworkDetailDTO::Wrapper>);
};

/**
 * 定义显示对象
 * 作业信息VO（返回给前端的数据）
 */

class HomeworkJsonVO : public oatpp::DTO
{
    DTO_INIT(HomeworkJsonVO, DTO);





    DTO_FIELD(UInt64, recordId);        // 记录ID
    DTO_FIELD(UInt64, homeworkId);       // 作业ID
    DTO_FIELD(UInt64, studentId);        // 学生ID
    DTO_FIELD(String, content);           // 提交内容
    DTO_FIELD(String, images);            // 图片
    DTO_FIELD(String, addTime);           // 提交时间
};
class HomeworkDeleteJsonVO : public JsonVO<HomeworkDeleteDTO::Wrapper>
{
    DTO_INIT(HomeworkDeleteJsonVO, JsonVO<HomeworkDeleteDTO::Wrapper>);
};

class HomeworkSubmitJsonVO : public JsonVO<HomeworkSubmitDTO::Wrapper>
{
    DTO_INIT(HomeworkSubmitJsonVO, JsonVO<HomeworkSubmitDTO::Wrapper>);
};
#include OATPP_CODEGEN_END(DTO)

#endif 