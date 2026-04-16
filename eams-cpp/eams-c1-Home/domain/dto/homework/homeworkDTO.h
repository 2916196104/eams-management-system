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

/**
 * 数据传输对象
 * 提交作业
 */

class HomeworkSubmitDTO : public oatpp::DTO
{
	DTO_INIT(HomeworkSubmitDTO, DTO);

	// 作业ID,对应 homework表的id；record表的homework_id
	API_DTO_FIELD_REQUIRE(UInt64, homeworkId, ZH_WORDS_GETTER("homework.record.homework_id"), true);
	// 学生ID,对应 record表的 student_id
	API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("homework.record.student_id"), true);
	// 编辑人
	API_DTO_FIELD_DEFAULT(UInt64, editor, ZH_WORDS_GETTER("homework.editor"));
	//作业内容,对应 homework表的 content
	API_DTO_FIELD_REQUIRE(String, homework_content, ZH_WORDS_GETTER("homework.content"), true);
	// 作业内容,对应 record表的 content
	API_DTO_FIELD_REQUIRE(String, homework_record_content, ZH_WORDS_GETTER("homework.record.content"), true);
	// 图片附件,对应 images 字段
	API_DTO_FIELD_DEFAULT(String, images, ZH_WORDS_GETTER("homework.record.images"));
	//当前时间
	API_DTO_FIELD_DEFAULT(String, editTime, ZH_WORDS_GETTER("homework.edit_time"));

};

/**
 * 删除重做
 */
class HomeworkDeleteDTO : public oatpp::DTO
{
	DTO_INIT(HomeworkDeleteDTO, DTO);

	// 作业ID
	API_DTO_FIELD_REQUIRE(UInt64, homeworkId, ZH_WORDS_GETTER("homework.record.homework_id"), true);
	// 学生ID
	API_DTO_FIELD_REQUIRE(UInt64, studentId, ZH_WORDS_GETTER("homework.record.student_id"), true);
	// 编辑人
	API_DTO_FIELD_REQUIRE(UInt64, editor, ZH_WORDS_GETTER("homework.editor"), true);
	// 新的作业内容
	API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("homework.record.content"));
	// 新的图片附件
	API_DTO_FIELD_DEFAULT(String, images, ZH_WORDS_GETTER("homework.record.images"));
	//重做信息
	API_DTO_FIELD_DEFAULT(UInt64, deletedCount, ZH_WORDS_GETTER("homework.deleted"));

};
#include OATPP_CODEGEN_END(DTO)

#endif // !_HOMEWORKDTO_H_