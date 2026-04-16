#pragma once
#ifndef _GET_CREDIT_MALL_LIST_VO_H_
#define _GET_CREDIT_MALL_LIST_VO_H_

#include "../../../GlobalInclude.h"
#include "../../../dto/home/credit/GetCreditMallListDTO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个积分商品信息显示JsonVO对象，用于响应给客户端
 */

class CreditMallListJsonVO : public JsonVO<CreditMallListDTO::Wrapper>
{
	DTO_INIT(CreditMallListJsonVO, JsonVO<CreditMallListDTO::Wrapper>)
};

class CreditMallListPageJsonVO : public JsonVO<CreditMallListPageDTO::Wrapper>
{
	DTO_INIT(CreditMallListPageJsonVO, JsonVO<CreditMallListPageDTO::Wrapper>)
};

//class CreditMallDetailJsonVO : public JsonVO<CreditMallDetailDTO::Wrapper>
//{
//	DTO_INIT(CreditMallDetailJsonVO, JsonVO<CreditMallDetailDTO::Wrapper>)
//};


#include OATPP_CODEGEN_END(DTO)

#endif // !_GET_CREDIT_MALL_LIST_VO_H_
