#pragma once
#ifndef _SCHEDULE_CONTROLLER_H_
#define _SCHEDULE_CONTROLLER_H_

// 引入领域模型文件
#include "domain/vo/BaseJsonVO.h"
#include "domain/query/schedule/ScheduleQuery.h"
#include "domain/dto/schedule/ScheduleDTO.h"
#include "domain/vo/schedule/ScheduleVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

// 定义这个 Controller 在 Swagger 上的分组标签
#define API_TAG ZH_WORDS_GETTER("schedule.tags.main")

/**
 * 课表与签到控制器
 * 作用：处理所有与课表查询、学生签到相关的 HTTP 请求
 */
class ScheduleController : public oatpp::web::server::api::ApiController
{
	// 设置认证处理器
	API_ACCESS_DECLARE(ScheduleController);
public:
	// 生成 Swagger 文档
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(
		ZH_WORDS_GETTER("schedule.query.summary"), // 接口标题
		querySchedule,                             // 对应的 C++ 函数标识
		ScheduleQuery,                             // 接口接收的参数类型
		ListJsonVO<ScheduleVO::Wrapper>::Wrapper,  // 接口返回的数据类型
		API_TAG                                    // 接口的分组标签
	);

	// 将 URL 和 C++ 函数绑定
	API_HANDLER_ENDPOINT_QUERY_AUTH(
		API_M_GET,                  // 请求方法：GET
		"/schedule/query",          // 接口路径
		querySchedule,              // C++ 函数标识
		ScheduleQuery,              // Query 参数类型
		execQuerySchedule(query, authObject->getPayload()) // 实际调用的函数
	);

	// 生成 Swagger 文档
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("schedule.signin.summary"),
		signIn,
		StringJsonVO::Wrapper, // 签到成功返回字符串提示
		API_TAG
	);

	// 将 URL 和 C++ 函数绑定
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/schedule/sign-in",
		signIn,
		BODY_DTO(SignInDTO::Wrapper, dto), // 用 BODY_DTO 宏解析请求体里的 JSON
		execSignIn(dto, authObject->getPayload())
	);

private:

	// 获取课表列表
	ListJsonVO<ScheduleVO::Wrapper>::Wrapper execQuerySchedule(const ScheduleQuery::Wrapper& query, const PayloadDTO& payload);

	// 学生签到
	StringJsonVO::Wrapper execSignIn(const SignInDTO::Wrapper& dto, const PayloadDTO& payload);
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)
#endif // _SCHEDULE_CONTROLLER_