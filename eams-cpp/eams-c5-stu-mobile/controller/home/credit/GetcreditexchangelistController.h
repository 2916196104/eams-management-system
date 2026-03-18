#pragma once
#ifndef _GETCREDITEXCHANGELISTCONTROLLER_H_
#define _GETCREDITEXCHANGELISTCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/query/home/credit/CreditexchangelistQuery.h"
#include "domain/dto/home/credit/CreditexchangelistDTO.h"
#include "domain/vo/home/credit/CreditexchangelistVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("c5.home.credit.exchange.tag.t1")

class GetcreditexchangelistController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(GetcreditexchangelistController);
public:
	ENDPOINT_INFO(Getcreditexchangelist) {
		info->summary = ZH_WORDS_GETTER("c5.home.credit.exchange.query-all.summary");
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON(CreditexchangelistPageJsonVO::Wrapper);
		API_DEF_ADD_PAGE_PARAMS();
		//info->queryParams.add<Int32>("student_id").description = ZH_WORDS_GETTER("c5.home.credit.exchange.field.student_id");
		//info->queryParams["student_id"].addExample("default", oatpp::Int32(1));
		API_DEF_ADD_QUERY_PARAMS(Int32, "student_id", ZH_WORDS_GETTER("c5.home.credit.exchange.field.student-id"), 1, true);

	}
	ENDPOINT(API_M_GET, "/c5/home/credit/creditexchangelist", Getcreditexchangelist, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, CreditexchangelistQuery, params);
		API_HANDLER_RESP_VO(executeQueryCreditexchangelistQuery(query));
	}
private:
	CreditexchangelistPageJsonVO::Wrapper executeQueryCreditexchangelistQuery(const CreditexchangelistQuery::Wrapper& query);
};


#include OATPP_CODEGEN_END(ApiController)


#endif // !_GETCREDITEXCHANGELISTCONTROLLER_H_
