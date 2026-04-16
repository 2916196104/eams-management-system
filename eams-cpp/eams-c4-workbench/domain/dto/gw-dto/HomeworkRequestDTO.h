#pragma once
#ifndef HOMEWORK_REQUEST_DTO_H
#define HOMEWORK_REQUEST_DTO_H

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/** 作业列表查询参数（与响应分页字段 pageIndex/pageSize 命名一致） */
class HomeworkListQueryDTO : public oatpp::DTO {
	DTO_INIT(HomeworkListQueryDTO, DTO);
	API_DTO_FIELD(String, teacher_id, ZH_WORDS_GETTER("homework.query.teacher_id"), false, "");
	API_DTO_FIELD(String, admin_id, ZH_WORDS_GETTER("homework.query.admin_id_compat"), false, "");
	API_DTO_FIELD(String, class_id, ZH_WORDS_GETTER("homework.query.class_id"), true, "");
	API_DTO_FIELD(UInt64, pageIndex, ZH_WORDS_GETTER("homework.query.pageIndex"), false, 1);
	API_DTO_FIELD(UInt64, pageSize, ZH_WORDS_GETTER("homework.query.pageSize"), false, 10);
	API_DTO_FIELD(Int32, page, ZH_WORDS_GETTER("homework.query.page_compat"), false, 0);
	API_DTO_FIELD(Int32, size, ZH_WORDS_GETTER("homework.query.size_compat"), false, 0);
};

/** 作业详情查询参数 */
class HomeworkDetailQueryDTO : public oatpp::DTO {
	DTO_INIT(HomeworkDetailQueryDTO, DTO);
	API_DTO_FIELD(String, homework_id, ZH_WORDS_GETTER("homework.query.homework_id"), true, "");
	API_DTO_FIELD(String, teacher_id, ZH_WORDS_GETTER("homework.query.teacher_id"), false, "");
	API_DTO_FIELD(String, admin_id, ZH_WORDS_GETTER("homework.query.admin_id_compat"), false, "");
};

/** 发布作业请求体 JSON */
class HomeworkAddBodyDTO : public oatpp::DTO {
	DTO_INIT(HomeworkAddBodyDTO, DTO);
	API_DTO_FIELD(String, teacher_id, ZH_WORDS_GETTER("homework.body.add.teacher_id"), false, "");
	API_DTO_FIELD(String, admin_id, ZH_WORDS_GETTER("homework.body.add.admin_id_compat"), false, "");
	API_DTO_FIELD(String, class_id, ZH_WORDS_GETTER("homework.body.add.class_id"), true, "");
	API_DTO_FIELD(String, title, ZH_WORDS_GETTER("homework.body.add.title"), true, "");
	API_DTO_FIELD(String, content, ZH_WORDS_GETTER("homework.body.add.content"), false, "");
	API_DTO_FIELD(String, attachment, ZH_WORDS_GETTER("homework.body.add.attachment"), false, "");
};

/** 点评作业：评分与文字（嵌套对象，便于 OpenAPI 展示） */
class HomeworkCommentReviewDTO : public oatpp::DTO {
	DTO_INIT(HomeworkCommentReviewDTO, DTO);
	API_DTO_FIELD(Int32, score, ZH_WORDS_GETTER("homework.body.comment.score"), true, 0);
	API_DTO_FIELD(String, content, ZH_WORDS_GETTER("homework.body.comment.content"), false, "");
};

/** 点评作业请求体 JSON */
class HomeworkCommentBodyDTO : public oatpp::DTO {
	DTO_INIT(HomeworkCommentBodyDTO, DTO);
	API_DTO_FIELD(String, teacher_id, ZH_WORDS_GETTER("homework.body.comment.teacher_id"), false, "");
	API_DTO_FIELD(String, admin_id, ZH_WORDS_GETTER("homework.body.comment.admin_id_compat"), false, "");
	API_DTO_FIELD(String, submit_id, ZH_WORDS_GETTER("homework.body.comment.submit_id"), true, "");
	API_DTO_FIELD(Int32, score, ZH_WORDS_GETTER("homework.body.comment.score_flat"), false, 0);
	API_DTO_FIELD(String, content, ZH_WORDS_GETTER("homework.body.comment.content_flat"), false, "");
	DTO_FIELD(Object<HomeworkCommentReviewDTO>, review);
	DTO_FIELD_INFO(review) {
		info->description = ZH_WORDS_GETTER("homework.body.comment.review");
		info->required = false;
	}
};

#include OATPP_CODEGEN_END(DTO)

#endif
