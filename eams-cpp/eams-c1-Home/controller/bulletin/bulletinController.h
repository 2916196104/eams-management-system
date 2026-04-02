#pragma once
#ifndef _BULLETINCONTROLLER_H_
#define _BULLETINCONTROLLER_H_

#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/PageQuery.h"
#include "domain/vo/bulletin/bulletinVO.h"
#include "domain/dto/bulletin/bulletinDTO.h"
#include "domain/query/bulletin/bulletinQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

//定义接口模块标签
#define BULLETIN_TAG ZH_WORDS_GETTER("bulletin.tag")

//公共模块控制器
class bulletinController : public oatpp::web::server::api::ApiController
{
	// 定义控制器访问入口
	API_ACCESS_DECLARE(bulletinController);
public: // 定义接口

	//1.1 定义获取显示通知公告接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("bulletin.query-title.summary"), qureyTitle, titleJsonVO::Wrapper, BULLETIN_TAG
	);

	//1.2 定义获取显示通知公告接口处理
	ENDPOINT(API_M_GET, "/app/sCenter/advertisement", qureyTitle, API_HANDLER_AUTH_PARAME) {
		// 响应结果
		API_HANDLER_RESP_VO(executeQueryTitle());
	}

	// 2.1 定义获取所有公告（分页）接口描述
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("bulletin.query-list.summary"), queryList, listQuery, listPageJsonVO::Wrapper, BULLETIN_TAG
	);

	// 2.2 定义获取所有公告（分页）接口处理
	ENDPOINT(API_M_GET, "/app/sCenter/advertisementList", queryList, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数
		API_HANDLER_QUERY_PARAM(query, listQuery, params);
		// 响应结果
		API_HANDLER_RESP_VO(executeQueryList(query));
	}

	// 3.1 定义获取小红点提醒接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("bulletin.query-red.summary"), qureyRed, redJsonVO::Wrapper, BULLETIN_TAG,
		API_DEF_ADD_QUERY_PARAMS(Int64, "student_id", ZH_WORDS_GETTER("user.field.student_id"), 1, true);
		);
	// 3.2 定义获取小红点提醒接口处理
	ENDPOINT(API_M_GET, "/app/sCenter/student/redpoint", qureyRed, QUERY(Int64, student_id), API_HANDLER_AUTH_PARAME) {
		// 响应结果
		API_HANDLER_RESP_VO(executeQueryRed(student_id));
	}

private: // 定义接口执行函数

	//1 获取显示通知公告
	titleJsonVO::Wrapper executeQueryTitle();

	//2 获取所有公告（分页）
	listPageJsonVO::Wrapper executeQueryList(const PageQuery::Wrapper& query);

	// 3 获取红点
	redJsonVO::Wrapper executeQueryRed(const Int64& student_id);
};

#include OATPP_CODEGEN_END(ApiController)

#endif // !_BULLETINCONTROLLER_H_