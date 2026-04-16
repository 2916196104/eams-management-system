#pragma once
#ifndef _HOMEWORK_CONTROLLER_
#define _HOMEWORK_CONTROLLER_

#include "ServerInfo.h" // 中文字典需要引入的头文件
#include "Macros.h"     // 中文字典需要引入的头文件
#include "ApiHelper.h"
#include "domain/dto/gw-dto/CommonResponseDTO.h"
#include "domain/dto/gw-dto/HomeworkRequestDTO.h"

using namespace oatpp;

#define API_TAG ZH_WORDS_GETTER("homework.tag")

#include OATPP_CODEGEN_BEGIN(ApiController)

class HomeworkController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(HomeworkController);
public:
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("homework.list.summary"), getHomeworkList, HomeworkListQueryDTO,
		HomeworkListPageJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/c4-workbench/homework/list", getHomeworkList, HomeworkListQueryDTO,
		executeGetHomeworkList(authObject, query))

		API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("homework.detail.summary"), getHomeworkDetail, HomeworkDetailQueryDTO,
			HomeworkDetailJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/c4-workbench/homework/detail", getHomeworkDetail, HomeworkDetailQueryDTO,
		executeGetHomeworkDetail(authObject, query))

		API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.add.summary"), addHomework, HomeworkAddJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c4-workbench/homework/add", addHomework,
		BODY_DTO(HomeworkAddBodyDTO::Wrapper, body),
		executeAddHomework(authObject, body))

		API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.comment.summary"), commentHomework, HomeworkCommentJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c4-workbench/homework/comment", commentHomework,
		BODY_DTO(HomeworkCommentBodyDTO::Wrapper, body),
		executeCommentHomework(authObject, body))

private:
	HomeworkListPageJsonVO::Wrapper executeGetHomeworkList(const std::shared_ptr<CustomerAuthorizeObject>& authObject,
		const HomeworkListQueryDTO::Wrapper& query);
	HomeworkDetailJsonVO::Wrapper executeGetHomeworkDetail(const std::shared_ptr<CustomerAuthorizeObject>& authObject,
		const HomeworkDetailQueryDTO::Wrapper& query);
	HomeworkAddJsonVO::Wrapper executeAddHomework(const std::shared_ptr<CustomerAuthorizeObject>& authObject,
		const HomeworkAddBodyDTO::Wrapper& body);
	HomeworkCommentJsonVO::Wrapper executeCommentHomework(const std::shared_ptr<CustomerAuthorizeObject>& authObject,
		const HomeworkCommentBodyDTO::Wrapper& body);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // _HOMEWORK_CONTROLLER_