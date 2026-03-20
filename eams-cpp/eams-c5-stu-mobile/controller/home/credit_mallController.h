#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2026/3/18 22:10:00

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

	  https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _CREDIT_MALL_CONTROLLER_
#define _CREDIT_MALL_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/query/home/CreditMallQuery.h"
#include "domain/dto/home/credit_mallDTO.h"
#include "domain/vo/home/credit_mallVO.h"

// 0 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("credit_mall.tags.t1")
#define API_TAG2 ZH_WORDS_GETTER("credit_mall.tags.t2")

/**
 * 积分商城礼品控制器
 * 提供积分商城礼品的增删改查、导入导出等接口
 * 区分：批量分页查询（school/material/category）、单ID精准查询
 */
class CreditMallController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
	// 2 定义控制器访问入口
	API_ACCESS_DECLARE(CreditMallController);
	// 3 定义接口
public:
	// ====================== 批量分页查询接口（按不同维度筛选） ======================
	// 3.1 通用多条件分页查询（支持所有筛选条件组合）
	ENDPOINT_INFO(queryCreditMall) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("credit_mall.get.summary"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(credit_mallPageVO); // 分页VO（多条数据）
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_PAGE_PARAMS(); // 必带分页参数
		// 所有批量筛选条件（非必传，组合筛选）
		API_DEF_ADD_QUERY_PARAMS(UInt64, "school_id", ZH_WORDS_GETTER("credit_mall.field.school_id"), 123, false);
		API_DEF_ADD_QUERY_PARAMS(UInt64, "material_id", ZH_WORDS_GETTER("credit_mall.field.material_id"), 123, false);
		API_DEF_ADD_QUERY_PARAMS(UInt64, "category_id", ZH_WORDS_GETTER("credit_mall.field.category_id"), 123, false);
		API_DEF_ADD_QUERY_PARAMS(String, "category_name", ZH_WORDS_GETTER("credit_mall.field.category_name"), "", false);
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("credit_mall.field.name"), "", false);
		API_DEF_ADD_QUERY_PARAMS(Boolean, "state", ZH_WORDS_GETTER("credit_mall.field.state"), "true", false);
	}
	ENDPOINT(API_M_GET, "/credit-mall", queryCreditMall, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(userQuery, CreditMallQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryCreditMall(userQuery)); // 返回分页数据
	}

	// 3.2 专属：按学校ID分页查询（语义更清晰，仅筛选school_id）
	ENDPOINT_INFO(queryCreditMallBySchoolId) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("credit_mall.get.summary-school_id"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(credit_mallPageVO); // 分页VO（多条数据）
		API_DEF_ADD_TAG(API_TAG);
		API_DEF_ADD_PAGE_PARAMS(); // 必带分页参数
		// 仅保留school_id参数（必传，精准筛选该学校下的所有礼品）
		API_DEF_ADD_QUERY_PARAMS(UInt64, "school_id", ZH_WORDS_GETTER("credit_mall.field.school_id"), 123, true);
	}
	ENDPOINT(API_M_GET, "/credit-mall/by-school-id", queryCreditMallBySchoolId, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(userQuery, CreditMallQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryCreditMallBySchoolId(userQuery)); // 返回分页数据
	}

	// 3.3 专属：按物料ID分页查询
	ENDPOINT_INFO(queryCreditMallByMaterialId) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("credit_mall.get.summary-material_id"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(credit_mallPageVO); // 分页VO（多条数据）
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(UInt64, "material_id", ZH_WORDS_GETTER("credit_mall.field.material_id"), 123, true);
	}
	ENDPOINT(API_M_GET, "/credit-mall/by-material-id", queryCreditMallByMaterialId, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(userQuery, CreditMallQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryCreditMallByMaterialId(userQuery));
	}

	// 3.4 专属：按分类ID分页查询
	ENDPOINT_INFO(queryCreditMallByCategoryId) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("credit_mall.get.summary-category_id"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(credit_mallPageVO); // 分页VO（多条数据）
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(UInt64, "category_id", ZH_WORDS_GETTER("credit_mall.field.category_id"), 123, true);
	}
	ENDPOINT(API_M_GET, "/credit-mall/by-category-id", queryCreditMallByCategoryId, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(userQuery, CreditMallQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryCreditMallByCategoryId(userQuery));
	}

	// 3.5 专属：按分类名称分页查询
	ENDPOINT_INFO(queryCreditMallByCategoryName) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("credit_mall.get.summary-category_name"));
		API_DEF_ADD_AUTH();
		API_DEF_ADD_RSP_JSON_WRAPPER(credit_mallPageVO); // 分页VO（多条数据）
		API_DEF_ADD_PAGE_PARAMS();
		API_DEF_ADD_QUERY_PARAMS(String, "category_name", ZH_WORDS_GETTER("credit_mall.field.category_name"), "", true);
	}
	ENDPOINT(API_M_GET, "/credit-mall/by-category-name", queryCreditMallByCategoryName, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(userQuery, CreditMallQuery, queryParams);
		API_HANDLER_RESP_VO(execQueryCreditMallByCategoryName(userQuery));
	}

	// ====================== 单ID精准查询（返回单条数据，无分页） ======================
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("credit_mall.query-by-id.summary"), queryCreditMallById, credit_mallVO::Wrapper, API_TAG, // 单条VO（无分页）
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("credit_mall.field.id"), "", true); // id必传，唯一标识
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/credit-mall/query-by-id", queryCreditMallById, QUERY(String, id), execQueryCreditMallById(id));

	// ====================== 其他核心接口（保留原有逻辑，适配业务） ======================
	// 导出Excel（分页筛选后导出）
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("credit_mall.export.summary"), exportCreditMall, CreditMallQuery, Void, API_TAG);
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/credit-mall/export", exportCreditMall, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, CreditMallQuery, queryParams); return execExportCreditMall(query););

	// 导出PDF（分页筛选后导出）
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("credit_mall.export-pdf.summary"), exportCreditMallPdf, CreditMallQuery, StringJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/credit-mall/export-pdf", exportCreditMallPdf, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, CreditMallQuery, queryParams); API_HANDLER_RESP_VO(execExportCreditMallPdf(query)););

	// 导入接口
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("credit_mall.import.summary"), importCreditMall, credit_mallImportDTO::Wrapper, StringJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/credit-mall/import", importCreditMall, REQUEST(std::shared_ptr<IncomingRequest>, request), execImportCreditMall(request, authObject->getPayload()));

	// 新增接口
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("credit_mall.post.summary"), addCreditMall, StringJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/credit-mall", addCreditMall, BODY_DTO(credit_mallAddDTO::Wrapper, dto), execAddCreditMall(dto, authObject->getPayload()));

	// 修改接口
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("credit_mall.put.summary"), modifyCreditMall, StringJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/credit-mall", modifyCreditMall, BODY_DTO(credit_mallDTO::Wrapper, dto), execModifyCreditMall(dto, authObject->getPayload()));

	// 批量删除接口
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("credit_mall.delete.summary"), removeCreditMall, ListJsonVO<String>::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "/credit-mall", removeCreditMall, BODY_DTO(List<String>, ids), execRemoveCreditMall(ids));

	// 声明式服务接口（单条/批量）
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("credit_mall.query-one.summary"), queryOneCreditMall, credit_mallVO::Wrapper, API_TAG2,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("credit_mall.field.id"), "", true);
	);
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/credit-mall/query-one", queryOneCreditMall, QUERY(String, id), execQueryOneCreditMall(id, authObject->getPayload()));

	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("credit_mall.query-all.summary"), queryAllCreditMall, CreditMallQuery, credit_mallPageVO::Wrapper, API_TAG2);
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/credit-mall/query-all", queryAllCreditMall, CreditMallQuery, execQueryAllCreditMall(query, authObject->getPayload()));

private:
	// ====================== 批量分页查询执行函数（新增专属函数） ======================
	credit_mallPageVO::Wrapper execQueryCreditMall(const CreditMallQuery::Wrapper& query); // 通用多条件分页
	credit_mallPageVO::Wrapper execQueryCreditMallBySchoolId(const CreditMallQuery::Wrapper& query); // 按学校ID分页
	credit_mallPageVO::Wrapper execQueryCreditMallByMaterialId(const CreditMallQuery::Wrapper& query); // 按物料ID分页
	credit_mallPageVO::Wrapper execQueryCreditMallByCategoryId(const CreditMallQuery::Wrapper& query); // 按分类ID分页
	credit_mallPageVO::Wrapper execQueryCreditMallByCategoryName(const CreditMallQuery::Wrapper& query); // 按分类名称分页

	// ====================== 单ID查询执行函数（返回单条数据） ======================
	credit_mallVO::Wrapper execQueryCreditMallById(const String& id); // 单条数据，无分页

	// ====================== 其他执行函数 ======================
	std::shared_ptr<OutgoingResponse> execExportCreditMall(const CreditMallQuery::Wrapper& query);
	StringJsonVO::Wrapper execExportCreditMallPdf(const CreditMallQuery::Wrapper& query);
	StringJsonVO::Wrapper execImportCreditMall(std::shared_ptr<IncomingRequest> request, const PayloadDTO& payload);
	StringJsonVO::Wrapper execAddCreditMall(const credit_mallAddDTO::Wrapper& dto, const PayloadDTO& payload);
	StringJsonVO::Wrapper execModifyCreditMall(const credit_mallDTO::Wrapper& dto, const PayloadDTO& payload);
	ListJsonVO<String>::Wrapper execRemoveCreditMall(const List<String>& ids);
	credit_mallVO::Wrapper execQueryOneCreditMall(const String& id, const PayloadDTO& payload);
	credit_mallPageVO::Wrapper execQueryAllCreditMall(const CreditMallQuery::Wrapper& query, const PayloadDTO& payload);
};

#undef API_TAG
#undef API_TAG2

#include OATPP_CODEGEN_END(ApiController)
#endif // _CREDIT_MALL_CONTROLLER_