#pragma once
#ifndef _HOMEWORK_DTO_
#define _HOMEWORK_DTO_
#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class HomeworkDTO : public oatpp::DTO
{
    DTO_INIT(HomeworkDTO, DTO);

    DTO_FIELD(String, class_name);
    DTO_FIELD_INFO(class_name) {
        info->description = ZH_WORDS_GETTER("c5.home.homework.field.class_name");
    }

    DTO_FIELD(String, title);
    DTO_FIELD_INFO(title) {
        info->description = ZH_WORDS_GETTER("c5.home.homework.field.title");
    }

    DTO_FIELD(String, submit_status);
    DTO_FIELD_INFO(submit_status) {
        info->description = ZH_WORDS_GETTER("c5.home.homework.field.submit_status");
    }
};

class HomeworkPageDTO : public PageDTO<HomeworkDTO::Wrapper>
{
    DTO_INIT(HomeworkPageDTO, PageDTO<HomeworkDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif