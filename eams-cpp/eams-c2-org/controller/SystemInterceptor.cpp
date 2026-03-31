/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/11/29 16:43:14

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
#include "stdafx.h"
#include <sstream>
#include <string>
#include <iostream>
#include "oatpp/web/protocol/http/outgoing/ResponseFactory.hpp"
#include "SystemInterceptor.h"
#include "Message.h"
#include "domain/vo/NoDataJsonVO.h"
#include "ApiHelper.h"

using namespace oatpp::web::protocol::http;
using namespace oatpp::web::protocol::http::outgoing;

// 跨域属性设置
#define CROS_FIELD_SETTING(__RES__) \
__RES__->putHeaderIfNotExists("Access-Control-Allow-Origin", "*"); \
__RES__->putHeaderIfNotExists("Access-Control-Allow-Methods", "*"); \
__RES__->putHeaderIfNotExists("Access-Control-Expose-Headers", "*"); \
__RES__->putHeaderIfNotExists("Access-Control-Allow-Credentials", "true"); \
__RES__->putHeaderIfNotExists("Access-Control-Allow-Headers", "Content-Type,Access-Token,Authorization");

std::shared_ptr<oatpp::web::server::interceptor::RequestInterceptor::OutgoingResponse> CrosRequestInterceptor::intercept(const std::shared_ptr<IncomingRequest>& request)
{
#ifndef CLOSE_CROS_SUPPORT
	auto method = request->getStartingLine().method;
	if (method == "OPTIONS")
	{
		auto res = OutgoingResponse::createShared(Status::CODE_200, nullptr);
		CROS_FIELD_SETTING(res)
			return res;
	}
#endif
	return nullptr;
}

std::shared_ptr<oatpp::web::server::interceptor::ResponseInterceptor::OutgoingResponse> CrosResponseInterceptor::intercept(const std::shared_ptr<IncomingRequest>& request, const std::shared_ptr<OutgoingResponse>& response)
{
#ifndef CLOSE_CROS_SUPPORT
	CROS_FIELD_SETTING(response)
#endif
		return response;
}

std::shared_ptr<Response> createErrorRespone(std::string message, std::shared_ptr<oatpp::data::mapping::ObjectMapper> mapper) {
	auto error = NoDataJsonVO::createShared();
	error->init(RS_UNAUTHORIZED);
	error->message = message;
	auto response = ResponseFactory::createResponse(Status::CODE_200, error, mapper);
	return response;
}

CheckRequestInterceptor::CheckRequestInterceptor(const std::shared_ptr<oatpp::data::mapping::ObjectMapper>& objectMapper)
{
	m_objectMapper = objectMapper;
}

std::shared_ptr<oatpp::web::server::interceptor::RequestInterceptor::OutgoingResponse> CheckRequestInterceptor::intercept(const std::shared_ptr<IncomingRequest>& request)
{

	return nullptr;
}
