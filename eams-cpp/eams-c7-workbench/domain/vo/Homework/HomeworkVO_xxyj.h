#pragma once

#ifndef _HOMEWORK_VO_H_
#define _HOMEWORK_VO_H_

#include "../../GlobalInclude.h"
#include "../eams-c7-workbench/domain/dto/Homework/HomeworkDTO_xxyj.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 作业详情显示JsonVO，用于响应给客户端的Json对象
 */
class HomeworkDetailJsonVO : public JsonVO<HomeworkDetailDTO::Wrapper> {
    DTO_INIT(HomeworkDetailJsonVO, JsonVO<HomeworkDetailDTO::Wrapper>);
};

/**
 * 作业提交记录显示JsonVO，用于响应给客户端的Json对象
 */
class HomeworkRecordJsonVO : public JsonVO<HomeworkRecordDTO::Wrapper> {
    DTO_INIT(HomeworkRecordJsonVO, JsonVO<HomeworkRecordDTO::Wrapper>);
};

/**
 * 作业提交记录列表显示JsonVO
 */
class HomeworkRecordListJsonVO : public JsonVO<HomeworkRecordListDTO::Wrapper> {
    DTO_INIT(HomeworkRecordListJsonVO, JsonVO<HomeworkRecordListDTO::Wrapper>);
};

/**
 * 点评结果JsonVO
 */
class ReviewResultJsonVO : public JsonVO<ReviewResultDTO::Wrapper> {
    DTO_INIT(ReviewResultJsonVO, JsonVO<ReviewResultDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_HOMEWORK_VO_H_