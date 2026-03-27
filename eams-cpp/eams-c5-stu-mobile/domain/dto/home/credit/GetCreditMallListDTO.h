#pragma once
#ifndef _GET_CREDIT_MALL_LIST_DTO_H_
#define _GET_CREDIT_MALL_LIST_DTO_H_

#include "../../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * 定义一个积分商品信息的数据传输模型
 */
class CreditMallListDTO : public oatpp::DTO
{
    DTO_INIT(CreditMallListDTO, DTO);

    // 分类名称
    API_DTO_FIELD_DEFAULT(String, category_name, ZH_WORDS_GETTER("get-credit-mall-list.field.category_name"));

    // 礼品名称
    API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("get-credit-mall-list.field.name"));

    // 兑换积分
    API_DTO_FIELD_DEFAULT(Int32, credit, ZH_WORDS_GETTER("get-credit-mall-list.field.credit"));

    // 封面图地址
    API_DTO_FIELD_DEFAULT(String, cover, ZH_WORDS_GETTER("get-credit-mall-list.field.cover"));

};

/**
 * 定义一个积分商品详细信息的数据传输模型
 */
//class CreditMallDetailDTO : public CreditMallDTO
//{
//    DTO_INIT(CreditMallDetailDTO, DTO);
//
//    // 剩余数量
//    //API_DTO_FIELD_DEFAULT(Int32, sale_num, ZH_WORDS_GETTER("get-credit-mall-list.field.sale_num"));
//
//    // 详情内容
//    API_DTO_FIELD_DEFAULT(String, content, ZH_WORDS_GETTER("get-credit-mall-list.field.content"));
//
//};


/**
 * 定义一个积分商品信息分页传输对象
 */
class CreditMallListPageDTO : public PageDTO<CreditMallListDTO::Wrapper>
{
	DTO_INIT(CreditMallListPageDTO, PageDTO<CreditMallListDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)

#endif // !_GET_CREDIT_MALL_LIST_DTO_H_
