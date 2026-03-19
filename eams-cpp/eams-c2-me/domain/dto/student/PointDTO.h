#pragma once


#include "../../GlobalInclude.h"


#include OATPP_CODEGEN_BEGIN(DTO)



/**
 * 定义一个完整用户信息的数据传输模型
 */
class PointDTO : public oatpp::DTO {
    DTO_INIT(PointDTO, DTO);

    
    API_DTO_FIELD(Int32, student_id, ZH_WORDS_GETTER("Student.id"), true, 0);
    API_DTO_FIELD(Int32, credit, ZH_WORDS_GETTER("Student.changed_credit"), true, 0);
    API_DTO_FIELD(Int32, current_credit, ZH_WORDS_GETTER("Student.current_credit"), true, 0);
    API_DTO_FIELD(String, add_time, ZH_WORDS_GETTER("Student.add_time"), true, "");
    API_DTO_FIELD(String, remark, ZH_WORDS_GETTER("Student.remark"), true, "");
};



/**
 * 定义一个用户信息分页传输对象
 */
class PointPageDTO : public PageDTO<PointDTO::Wrapper>
{
	DTO_INIT(PointPageDTO, PageDTO<PointDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
