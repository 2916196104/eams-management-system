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
 * 提交作业
 */
class HomeworkSubmitDTO : public oatpp::DTO
{
	DTO_INIT(HomeworkSubmitDTO, DTO);
	
    // 学生ID,对应 student_id
    API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("home.homework_record.student_id"), true);
    // 作业ID,对应 homework_id
    API_DTO_FIELD_REQUIRE(UInt64, homeworkId, ZH_WORDS_GETTER("home.homework_record.homework_id"), true);
    // 编辑人
    API_DTO_FIELD_REQUIRE(UInt64, editor, ZH_WORDS_GETTER("home.homework.editor"),true);
    //作业内容,对应 homework表的 content
    API_DTO_FIELD_DEFAULT(String, homework_content, ZH_WORDS_GETTER("home.homework.content"));
    // 作业内容,对应 record表的 content
    API_DTO_FIELD_REQUIRE(String, homework_record_content, ZH_WORDS_GETTER("home.homework_record.content"), true);
    // 图片附件,对应 images 字段
    API_DTO_FIELD_DEFAULT(String, images, ZH_WORDS_GETTER("home.homework_record.images"));

};

/**
 * 删除重做
 */
class HomeworkDeleteDTO : public oatpp::DTO
{
	DTO_INIT(HomeworkDeleteDTO, DTO);

    // homework表的主键
    API_DTO_FIELD_REQUIRE(UInt64, recordId, ZH_WORDS_GETTER("home.homework_record.id"), true);
    // 学生名
    API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("home.homework_record.student_id"), true);
    // 编辑人
    API_DTO_FIELD_REQUIRE(UInt64, editor, ZH_WORDS_GETTER("home.homework.editor"),true);
    // 新的作业内容
    API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("home.homework_record.content"));
    // 新的图片附件
    API_DTO_FIELD_DEFAULT(String, images, ZH_WORDS_GETTER("home.homework_record.images"));
   
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_HOMEWORKDTO_H_