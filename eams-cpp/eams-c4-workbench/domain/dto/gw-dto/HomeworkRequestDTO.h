#pragma once
#ifndef HOMEWORK_REQUEST_DTO_H
#define HOMEWORK_REQUEST_DTO_H

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/** 发布作业请求体 JSON */
class HomeworkAddBodyDTO : public oatpp::DTO {
	DTO_INIT(HomeworkAddBodyDTO, DTO);
	DTO_FIELD(String, admin_id) = "";
	DTO_FIELD(String, class_id) = "";
	DTO_FIELD(String, title) = "";
	DTO_FIELD(String, content) = "";
	DTO_FIELD(String, attachment) = "";
};

/** 点评作业请求体 JSON */
class HomeworkCommentBodyDTO : public oatpp::DTO {
	DTO_INIT(HomeworkCommentBodyDTO, DTO);
	DTO_FIELD(String, submit_id) = "";
	DTO_FIELD(String, admin_id) = "";
	DTO_FIELD(Int32, score) = 0;
	DTO_FIELD(String, content) = "";
};

#include OATPP_CODEGEN_END(DTO)

#endif
