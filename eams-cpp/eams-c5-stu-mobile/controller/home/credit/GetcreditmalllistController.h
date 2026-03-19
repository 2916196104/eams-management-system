#pragma once
#ifndef _GETCREDITMALLLISTCONTROLLER_H_
#define _GETCREDITMALLLISTCONTROLLER_H_

#include "ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/query/home/credit/CreditmalllistQuery.h"
#include "domain/dto/home/credit/CreditmalllistDTO.h"
#include "domain/vo/home/credit/CreditmalllistVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("c5.home.credit.tag")

class GetcreditmalllistController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(GetcreditmalllistController);
public:
	ENDPOINT_INFO(Getcreditmalllist) {
		info->summary = ZH_WORDS_GETTER("c5.home.credit.mall.query-all.summary");
		API_DEF_ADD_AUTH();
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_RSP_JSON(CreditmalllistPageJsonVO::Wrapper);
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(String, "credit_mall_name", ZH_WORDS_GETTER("c5.home.credit.mall.field.name"), "book", false);

	}
	ENDPOINT(API_M_GET, "/c5/home/credit/creditmalllist", Getcreditmalllist, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, CreditmalllistQuery, params);
		API_HANDLER_RESP_VO(executeQueryCreditmalllistQuery(query));
	}
private:
	CreditmalllistPageJsonVO::Wrapper executeQueryCreditmalllistQuery(const CreditmalllistQuery::Wrapper& query);
};


#include OATPP_CODEGEN_END(ApiController)


#endif // !_GETCREDITMALLLISTCONTROLLER_H_
