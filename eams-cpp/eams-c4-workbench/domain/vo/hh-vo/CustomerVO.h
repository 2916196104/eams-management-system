#pragma once
#ifndef _CUSTOMER_VO_
#define _CUSTOMER_VO_

#include "../../GlobalInclude.h"
#include "domain/dto/hh-dto/CustomerDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

// 客户数据分页显示JsonVO，用于响应给客户端的Json对象
class CustomerPageJsonVO : public JsonVO<CustomerPageDTO::Wrapper> {
	DTO_INIT(CustomerPageJsonVO, JsonVO<CustomerPageDTO::Wrapper>);
};

// 客户详情数据显示JsonVO，用于相应给客户端的Json对象
class CustomerDetailJsonVO : public JsonVO<CustomerDetailDTO::Wrapper> {
	DTO_INIT(CustomerDetailJsonVO, JsonVO<CustomerDetailDTO::Wrapper>);
};

// 客户课程数据显示JsonVO，用于相应给客户端的Json对象
class CustomerLessonListJsonVO : public JsonVO<CustomerLessonListDTO::Wrapper> {
	DTO_INIT(CustomerLessonListJsonVO, JsonVO<CustomerLessonListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif
