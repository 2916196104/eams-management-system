#pragma once

#ifndef _HOMEWORK_VO_
#define _HOMEWORK_VO_

#include "../../../GlobalInclude.h"
// 引入适配homework表的DTO头文件（路径需根据实际项目调整）
#include "../../../dto/home/homework/HomeworkDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 单条作业数据返回VO：适配HomeworkDTO
class HomeworkJsonVO : public JsonVO<HomeworkDTO::Wrapper> {
    DTO_INIT(HomeworkJsonVO, JsonVO<HomeworkDTO::Wrapper>)
};

// 作业分页数据返回VO：适配HomeworkPageDTO
class HomeworkPageJsonVO : public JsonVO<HomeworkPageDTO::Wrapper> {
    DTO_INIT(HomeworkPageJsonVO, JsonVO<HomeworkPageDTO::Wrapper>)
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_HOMEWORK_VO_