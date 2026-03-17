#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/11/30 16:07:52

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
#ifndef _API_HELPER_
#define _API_HELPER_

#include <string>
// ���Ŀ���ر�ͷ
#include "oatpp/core/Types.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/protocol/http/Http.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
// �ļ��ϴ����ͷ
#include "oatpp/web/mime/multipart/InMemoryDataProvider.hpp"
#include "oatpp/web/mime/multipart/FileProvider.hpp"
#include "oatpp/web/mime/multipart/Reader.hpp"
#include "oatpp/web/mime/multipart/PartList.hpp"
#include "oatpp/web/protocol/http/outgoing/BufferBody.hpp"
// swagger���ͷ
#include "oatpp-swagger/Types.hpp"
// ���η�װ����ͷ
#include "domain/vo/JsonVO.h"
#include "domain/dto/PageDTO.h"
#include "CustomerAuthorizeHandler.h"
#include "URIUtil.h"
using namespace std;
using namespace oatpp::web::protocol::http;

/**
 * �󶨿�����
 * @param __DOC__: doc�˵����ָ��
 * @param __ROUTER__: router����ָ��
 * @param __CLASS__: controller������
 */
#define BIND_CONTROLLER(__DOC__, __ROUTER__, __CLASS__) \
__DOC__->append(__ROUTER__->addController(__CLASS__::createShared())->getEndpoints())

/**
 * ����������ʶ��壬���ڰ���Ȩ���������ഴ����ں���
 * @param __CLASS__: controller������
 */
#define API_ACCESS_DECLARE(__CLASS__) \
public: \
__CLASS__(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) : oatpp::web::server::api::ApiController(objectMapper) { \
	setDefaultAuthorizationHandler(std::make_shared<CustomerAuthorizeHandler>()); \
} \
static std::shared_ptr<__CLASS__> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)) { \
	return std::make_shared<__CLASS__>(objectMapper); \
}

// ��ȡ��������
#define API_M_GET  "GET"
// ������������
#define API_M_POST "POST"
// �޸���������
#define API_M_PUT  "PUT"
// ɾ����������
#define API_M_DEL  "DELETE"
// Token������ͷ�ж�Ӧ������
#define API_H_TOKEN "Authorization"
// WebSocket Token������ͷ�ж�Ӧ������
#define API_H_WS_TOKEN "Sec-WebSocket-Protocol"

//////////////////////////////////////////////////////////////////////////

/**
 * API�������ӱ���
 * @param _TITLE_: �ӿڱ���
 */
#define API_DEF_ADD_TITLE(_TITLE_) info->summary = _TITLE_

// API�������Ӱ�ȫ��֤
#define API_DEF_ADD_AUTH() info->addSecurityRequirement("bearer_auth")

/**
 * API�������ӱ�ǩ
 * @param _TAG_: ��ǩ����
 */
#define API_DEF_ADD_TAG(_TAG_) info->addTag(_TAG_)

// API���������ļ���,��������ʽ���ļ��ϴ�
#define API_DEF_ADD_FILE_STREAM() info->addConsumes<oatpp::swagger::Binary>("application/octet-stream")

/**
 * API���������ļ�����,���ڱ�����ʽ�ϴ����ļ������ַ�ʽ֧�ֶ��ļ��ϴ�
 * @param _TYPE_: �����������ͣ��磺xxxDTO::Wrapper
 */
#define API_DEF_ADD_FILE_FORM(_TYPE_) info->addConsumes<_TYPE_>("multipart/form-data")

/**
 * API����������Ӧ����
 * @param __RESP_TYPE__: ��Ӧ�������ͣ��磺xxxJsonVO::Wrapper
 */
#define API_DEF_ADD_RSP_JSON(__RESP_TYPE__) info->addResponse<__RESP_TYPE__>(Status::CODE_200, "application/json")

/**
 * API����������Ӧ���ݣ���oatpp::Object��װ����
 * @param __RESP_TYPE__: ��Ӧ�������ͣ��磺xxxJsonVO
 */
#define API_DEF_ADD_RSP_JSON_WRAPPER(__RESP_TYPE__) API_DEF_ADD_RSP_JSON(oatpp::Object<__RESP_TYPE__>)

/**
 * API��������ͨ�ò�������
 * @param _TITLE_: �ӿڱ���
 * @param __RESP_TYPE__: �ӿ���Ӧ�������͡��磺"UserPageJsonVO::Wrapper"��"StringJsonVO::Wrapper"
 * @param __TAG__: ��ǩ����
 */
#define API_DEF_ADD_COMMON(_TITLE_, __RESP_TYPE__, __TAG__) \
API_DEF_ADD_TITLE(_TITLE_); \
API_DEF_ADD_TAG(__TAG__); \
API_DEF_ADD_RSP_JSON(__RESP_TYPE__)

/**
 * API��������ͨ�ò������壬�����ʱ��ᶨ����Ȩ����
 * @param _TITLE_: �ӿڱ���
 * @param __RESP_TYPE__: �ӿ���Ӧ�������͡��磺"UserPageJsonVO::Wrapper"��"StringJsonVO::Wrapper"
 * @param __TAG__: ��ǩ����
 */
#define API_DEF_ADD_COMMON_AUTH(_TITLE_, __RESP_TYPE__, __TAG__) \
API_DEF_ADD_AUTH(); \
API_DEF_ADD_COMMON(_TITLE_, __RESP_TYPE__, __TAG__)

// ������ƽ̨������Ϣ������������
#ifndef LINUX
#define API_PAGE_INDEX_DESC u8"��ѯҳ��"
#define API_PAGE_SIZE_DESC u8"��ѯ����"
#else
#define API_PAGE_INDEX_DESC "page index"
#define API_PAGE_SIZE_DESC "page size"
#endif
// API�������ӷ�ҳ����˵��
#define API_DEF_ADD_PAGE_PARAMS() \
info->queryParams.add<UInt64>("pageIndex").description = API_PAGE_INDEX_DESC;\
info->queryParams["pageIndex"].addExample("default", oatpp::UInt64(1)); \
info->queryParams.add<UInt64>("pageSize").description = API_PAGE_SIZE_DESC; \
info->queryParams["pageSize"].addExample("default", oatpp::UInt64(10))

/**
 * API�������Ӳ�ѯ����˵��
 * @param _TYPE_: �ֶ��������͡��磺String��UInt32��
 * @param _FIELD_NAME_: �ֶ����ơ��磺"age"��"sex"
 * @param _DESCRIPTION_: �ֶ�������
 * @param _EXAMPLE_VAL_: ʾ��ֵ���磺"li si"��123
 * @param _REQUIRE_: �Ƿ�ش�������boolֵ���磺true��false
 */
#define API_DEF_ADD_QUERY_PARAMS(_TYPE_, _FIELD_NAME_, _DESCRIPTION_, _EXAMPLE_VAL_, _REQUIRE_) \
info->queryParams.add<_TYPE_>(_FIELD_NAME_).description = _DESCRIPTION_; \
info->queryParams[_FIELD_NAME_].addExample("default", _TYPE_(_EXAMPLE_VAL_)); \
info->queryParams[_FIELD_NAME_].required = _REQUIRE_

/**
 * API��������·������˵��
 * @param _TYPE_: �ֶ��������͡��磺String��UInt32��
 * @param _FIELD_NAME_: �ֶ����ơ��磺"age"��"sex"
 * @param _DESCRIPTION_: �ֶ�������
 * @param _EXAMPLE_VAL_: ʾ��ֵ���磺"li si"��123
 * @param _REQUIRE_: �Ƿ�ش�������boolֵ���磺true��false
 */
#define API_DEF_ADD_PATH_PARAMS(_TYPE_, _FIELD_NAME_, _DESCRIPTION_, _EXAMPLE_VAL_, _REQUIRE_) \
info->pathParams.add<_TYPE_>(_FIELD_NAME_).description = _DESCRIPTION_; \
info->pathParams[_FIELD_NAME_].addExample("default", _TYPE_(_EXAMPLE_VAL_)); \
info->pathParams[_FIELD_NAME_].required = _REQUIRE_

// ����������չ����չ����غ�
#define API_DEF_EXPAND( x ) x
// ����ձ��
#define API_DEF_NOTHING

/**
 * API��������
 * @param __TITLE__: Api��������
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param __RESP_TYPE__: ��Ӧ���������磺XxxJsonVO::Wrapper
 * @param __TAG__: Api������ǩ
 * @param ...: ��չѡ��
 */
#define API_DEF_ENDPOINT_INFO(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, ...) \
ENDPOINT_INFO(__ENDPOINT_FUN_NAME__) { \
	API_DEF_ADD_COMMON(__TITLE__, __RESP_TYPE__, __TAG__); \
	API_DEF_EXPAND(API_DEF_NOTHING __VA_ARGS__) \
} 

/**
 * API�������壬�����ʱ��������Ȩ����
 * @param __TITLE__: Api��������
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param __RESP_TYPE__: ��Ӧ���������磺XxxJsonVO::Wrapper
 * @param __TAG__: Api������ǩ
 * @param ...: ��չѡ��
 */
#define API_DEF_ENDPOINT_INFO_AUTH(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, ...) \
ENDPOINT_INFO(__ENDPOINT_FUN_NAME__) { \
	API_DEF_ADD_COMMON_AUTH(__TITLE__, __RESP_TYPE__, __TAG__); \
	API_DEF_EXPAND(API_DEF_NOTHING __VA_ARGS__) \
}

/**
 * �����������͹���Api��ѯ����������Ϣ
 * @param __QUERY_TYPE__: ��ѯ���������磺XxxQuery
*/
#define API_DEF_QUERY_PARAM_BUILD( __QUERY_TYPE__) \
auto tmp = __QUERY_TYPE__::createShared(); \
for (auto one : __QUERY_TYPE__::Wrapper::getPropertiesMap()) { \
	web::server::api::Endpoint::Info::Param* param = nullptr; \
	auto type = one.second->type; \
	if (type == oatpp::String::Class::getType()) \
		param = &(info->queryParams.add<oatpp::String>(one.first.c_str())); \
	else if (type == oatpp::Int32::Class::getType())\
		param = &(info->queryParams.add<oatpp::Int32>(one.first.c_str())); \
	else if (type == oatpp::UInt32::Class::getType())\
		param = &(info->queryParams.add<oatpp::UInt32>(one.first.c_str())); \
	else if (type == oatpp::Int64::Class::getType())\
		param = &(info->queryParams.add<oatpp::Int64>(one.first.c_str())); \
	else if (type == oatpp::UInt64::Class::getType())\
		param = &(info->queryParams.add<oatpp::UInt64>(one.first.c_str())); \
	else if (type == oatpp::Float32::Class::getType())\
		param = &(info->queryParams.add<oatpp::Float32>(one.first.c_str())); \
	else if (type == oatpp::Float64::Class::getType())\
		param = &(info->queryParams.add<oatpp::Float64>(one.first.c_str())); \
	else if (type == oatpp::Boolean::Class::getType())\
		param = &(info->queryParams.add<oatpp::Boolean>(one.first.c_str())); \
	if(param){ \
		param->description = one.second->info.description; \
		if(tmp[one.first]) \
			param->addExample("default", tmp[one.first]); \
		param->required = one.second->info.required; \
	} \
}

/**
 * API�������壬���ڲ�ѯ�ӿ�
 * @param __TITLE__: Api��������
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param __QUERY_TYPE__: ��ѯ���������磺XxxQuery
 * @param __RESP_TYPE__: ��Ӧ���������磺XxxJsonVO::Wrapper
 * @param __TAG__: Api������ǩ
 */
#define API_DEF_ENDPOINT_INFO_QUERY(__TITLE__, __ENDPOINT_FUN_NAME__, __QUERY_TYPE__, __RESP_TYPE__, __TAG__) \
API_DEF_ENDPOINT_INFO(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, API_DEF_QUERY_PARAM_BUILD(__QUERY_TYPE__);)

/**
 * API�������壬���ڲ�ѯ�ӿڣ������ʱ��������Ȩ����
 * @param __TITLE__: Api��������
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param __QUERY_TYPE__: ��ѯ���������磺XxxQuery
 * @param  __RESP_TYPE__: ��Ӧ���������磺XxxJsonVO::Wrapper
 * @param __TAG__: Api������ǩ
 */
#define API_DEF_ENDPOINT_INFO_QUERY_AUTH(__TITLE__, __ENDPOINT_FUN_NAME__, __QUERY_TYPE__, __RESP_TYPE__, __TAG__) \
API_DEF_ENDPOINT_INFO_AUTH(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, API_DEF_QUERY_PARAM_BUILD(__QUERY_TYPE__);)

/**
 * API�������壬������Ҫ֧���ļ��ϴ��Ľӿ���������
 * @param __TITLE__: Api��������
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param __FORMDATA_TYPE__: �����ļ��������������磺XxxDTO::Wrapper
 * @param __RESP_TYPE__: ��Ӧ���������磺XxxJsonVO::Wrapper
 * @param __TAG__: Api������ǩ
 * @param ...: ��չѡ��
 */
#define API_DEF_ENDPOINT_INFO_FILE(__TITLE__, __ENDPOINT_FUN_NAME__, __FORMDATA_TYPE__, __RESP_TYPE__, __TAG__) \
API_DEF_ENDPOINT_INFO(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, API_DEF_ADD_FILE_FORM(__FORMDATA_TYPE__);)

/**
 * API�������壬������Ҫ֧���ļ��ϴ��Ľӿ��������壬�����ʱ��������Ȩ����
 * @param __TITLE__: Api��������
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param __FORMDATA_TYPE__: �����ļ��������������磺XxxDTO::Wrapper
 * @param __RESP_TYPE__: ��Ӧ���������磺XxxJsonVO::Wrapper
 * @param __TAG__: Api������ǩ
 * @param ...: ��չѡ��
 */
#define API_DEF_ENDPOINT_INFO_FILE_AUTH(__TITLE__, __ENDPOINT_FUN_NAME__, __FORMDATA_TYPE__, __RESP_TYPE__, __TAG__) \
API_DEF_ENDPOINT_INFO_AUTH(__TITLE__, __ENDPOINT_FUN_NAME__, __RESP_TYPE__, __TAG__, API_DEF_ADD_FILE_FORM(__FORMDATA_TYPE__);)

//////////////////////////////////////////////////////////////////////////

// �ӿڴ�������ҳ������ȡ����
#define API_HANDLER_PAGE_PARAME \
QUERY(UInt64, pageIndex), \
QUERY(UInt64, pageSize)

// �ӿڴ�������Ȩ������ȡ����
#define API_HANDLER_AUTH_PARAME \
AUTHORIZATION(std::shared_ptr<CustomerAuthorizeObject>, authObject)

// ��Ȩ����
#define API_HANDLER_AUTN_HEADER HEADER(oatpp::String, token, API_H_TOKEN)

/**
 * �ӿڴ�����������ѯ��������ѯ���ݶ���
 * @param __VAR__: ת����ı������ƣ���query
 * @param __TYPE__: ��ѯ���ݶ������ͣ���XxxQuery
 * @param __PARAMS__: QueryParams�ı������ƣ��磺QUERIES(QueryParams, queryParams),����queryParams
 */
#define API_HANDLER_QUERY_PARAM(__VAR__, __TYPE__, __PARAMS__) \
auto __VAR__ = __TYPE__::createShared(); \
for (auto& param : __PARAMS__.getAll()) { \
	auto data = param.second.getMemoryHandle().get(); \
	auto typeval = __VAR__[param.first.toString()].getValueType(); \
	if (typeval == oatpp::String::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::String(URIUtil::urlDecode(data->c_str())); \
	else if (typeval == oatpp::Int32::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::Int32(stoi(*data)); \
	else if (typeval == oatpp::UInt32::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::UInt32(stoi(*data)); \
	else if (typeval == oatpp::Int64::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::Int64(stoll(*data)); \
	else if (typeval == oatpp::UInt64::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::UInt64(stoull(*data)); \
	else if (typeval == oatpp::Float32::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::Float32(stof(*data)); \
	else if (typeval == oatpp::Float64::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::Float64(stod(*data)); \
	else if (typeval == oatpp::Boolean::Class::getType())\
		__VAR__[param.first.toString()] = oatpp::Boolean(*data == "true" || *data == "1"); \
}

/**
 * �ӿڴ�������ӦVO����
 * @param __VO__: ��Ӧ���ݶ���
 */
#define API_HANDLER_RESP_VO(__VO__) return createDtoResponse(Status::CODE_200, __VO__)

/**
 * �ӿڴ�������ӦVO���ݣ���oatpp::Object��װ����
 * @param __VO__: ��Ӧ���ݶ���
 */
#define API_HANDLER_RESP_VO_WRAPPER(__VO__) API_HANDLER_RESP_VO(oatpp::Object<__VO__>)

/**
 * API�˵㶨��
 * @param _METHOD_: ����ʽ���磺API_M_GET
 * @param _PATH_: �˵���ʵ�ַ���磺/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param _PARAM_MACRO_: ָ��һ���������������ꡣ�磺BODY_DTO(SampleDTO::Wrapper, dto)
 * @param _EXECUTE_: �����߼�������execXXX�������磺execModifySample(dto)
 */
#define API_HANDLER_ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_) { \
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API�˵㶨�壬�����ʱ��������Ȩ����
 * @param _METHOD_: ����ʽ���磺API_M_GET
 * @param _PATH_: �˵���ʵ�ַ���磺/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param _PARAM_MACRO_: ָ��һ���������������ꡣ�磺BODY_DTO(SampleDTO::Wrapper, dto)
 * @param _EXECUTE_: �����߼�������execXXX�������磺execModifySample(dto)
 */
#define API_HANDLER_ENDPOINT_AUTH(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, API_HANDLER_AUTH_PARAME) { \
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API�˵㶨�壬�������������
 * @param _METHOD_: ����ʽ���磺API_M_GET
 * @param _PATH_: �˵���ʵ�ַ���磺/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param _EXECUTE_: �����߼�������execXXX�������磺execModifySample(dto)
 */
#define API_HANDLER_ENDPOINT_NOPARAM(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__) { \
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API�˵㶨�壬��������������������ʱ��������Ȩ����
 * @param _METHOD_: ����ʽ���磺API_M_GET
 * @param _PATH_: �˵���ʵ�ַ���磺/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param _EXECUTE_: �����߼�������execXXX�������磺execModifySample(dto)
 */
#define API_HANDLER_ENDPOINT_NOPARAM_AUTH(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, API_HANDLER_AUTH_PARAME) { \
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API�˵㶨�壬���ڴ��������ѯ���������󣬲�ѯ����������ı�����Ϊquery
 * @param _METHOD_: ����ʽ���磺API_M_GET
 * @param _PATH_: �˵���ʵ�ַ���磺/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param _QUERY_TYPE_: ��ѯ�������͡��磺SampleQuery
 * @param _EXECUTE_: �����߼�������execXXX�������磺execQuerySample(query)
 */
#define API_HANDLER_ENDPOINT_QUERY(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _QUERY_TYPE_, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, QUERIES(QueryParams, queryParams)) { \
	API_HANDLER_QUERY_PARAM(query, _QUERY_TYPE_, queryParams);\
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API�˵㶨�壬���ڴ��������ѯ���������󣬲�ѯ����������ı�����Ϊquery�������ʱ��������Ȩ����
 * @param _METHOD_: ����ʽ���磺API_M_GET
 * @param _PATH_: �˵���ʵ�ַ���磺/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param _QUERY_TYPE_: ��ѯ�������͡��磺SampleQuery
 * @param _EXECUTE_: �����߼�������execXXX�������磺execQuerySample(query, authObject->getPayload())
 */
#define API_HANDLER_ENDPOINT_QUERY_AUTH(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _QUERY_TYPE_, _EXECUTE_) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) { \
	API_HANDLER_QUERY_PARAM(query, _QUERY_TYPE_, queryParams);\
	API_HANDLER_RESP_VO(_EXECUTE_); \
}

/**
 * API�˵㶨��,���ƻ������߼�
 * @param _METHOD_: ����ʽ���磺API_M_GET
 * @param _PATH_: �˵���ʵ�ַ���磺/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param _PARAM_MACRO_: ָ��һ���������������ꡣ�磺BODY_DTO(SampleDTO::Wrapper, dto)
 * @param ...: ��չ�����߼�
 */
#define API_HANDLER_ENDPOINT_OPTION(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, ...) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_) { \
	API_DEF_EXPAND(API_DEF_NOTHING __VA_ARGS__) \
}

/**
 * API�˵㶨��,���ƻ������߼�,�����ʱ��������Ȩ����
 * @param _METHOD_: ����ʽ���磺API_M_GET
 * @param _PATH_: �˵���ʵ�ַ���磺/user/query-by-name
 * @param __ENDPOINT_FUN_NAME__: Api�˵㺯������
 * @param _PARAM_MACRO_: ָ��һ���������������ꡣ�磺BODY_DTO(SampleDTO::Wrapper, dto)
 * @param ...: ��չ�����߼�,��չ�߼���Ҫ�Լ���д�����߼����磺return createOkResponse(result);
 */
#define API_HANDLER_ENDPOINT_OPTION_AUTH(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, ...) \
ENDPOINT(_METHOD_, _PATH_, __ENDPOINT_FUN_NAME__, _PARAM_MACRO_, API_HANDLER_AUTH_PARAME) { \
	API_DEF_EXPAND(API_DEF_NOTHING __VA_ARGS__) \
}

//////////////////////////////////////////////////////////////////////////

/**
 * DTO�ֶζ����
 * @param _TYPE_: �ֶ����͡��磺String��Int32��List<Int32>��List<SampleQuery::Wrapper>
 * @param _NAME_: �ֶ����ơ��磺name��sex
 * @param _DESCRIPTION_: �ֶ�����
 * @param _REQUIRE_: �Ƿ�ش��������磺true��false
 * @param _DEFAULT_: �ֶ�Ĭ��ֵ��ע���������Ĭ��ֵ��������ֶ�ֵû�б����Ǿͻᱣ��ֵΪĬ��ֵ���磺"zhangsan" ��123
 */
#define API_DTO_FIELD(_TYPE_, _NAME_, _DESCRIPTION_, _REQUIRE_, _DEFAULT_) \
DTO_FIELD(_TYPE_, _NAME_) = _DEFAULT_; \
DTO_FIELD_INFO(_NAME_) { \
	info->description = _DESCRIPTION_; \
	info->required = _REQUIRE_; \
}

/**
 * DTO�ֶζ���꣬�󲿷����Ա���ϵͳĬ��
 * @param _TYPE_: �ֶ����͡��磺String��Int32��List<Int32>��List<SampleQuery::Wrapper>
 * @param _NAME_: �ֶ����ơ��磺name��sex
 * @param _DESCRIPTION_: �ֶ�����
 */
#define API_DTO_FIELD_DEFAULT(_TYPE_, _NAME_, _DESCRIPTION_) \
DTO_FIELD(_TYPE_, _NAME_); \
DTO_FIELD_INFO(_NAME_) { \
	info->description = _DESCRIPTION_; \
}

/**
 * DTO�ֶζ���֧꣬�������Ƿ�������
 * @param _TYPE_: �ֶ����͡��磺String��Int32��List<Int32>��List<SampleQuery::Wrapper>
 * @param _NAME_: �ֶ����ơ��磺name��sex
 * @param _DESCRIPTION_: �ֶ�����
 * @param _REQUIRE_: �Ƿ�ش��������磺true��false
 */
#define API_DTO_FIELD_REQUIRE(_TYPE_, _NAME_, _DESCRIPTION_, _REQUIRE_) \
DTO_FIELD(_TYPE_, _NAME_); \
DTO_FIELD_INFO(_NAME_) { \
	info->description = _DESCRIPTION_; \
	info->required = _REQUIRE_; \
}

//////////////////////////////////////////////////////////////////////////

/**
 * ��ʼ��multipart���ݶ�ȡ�����Ͷ�ȡ��
 * @param _VAR_CONTAINER_: ����������
 * @param _VAR_READER_: ��ȡ��������
 */
#define API_MULTIPART_INIT(_VAR_CONTAINER_, _VAR_READER_) \
namespace multipart = oatpp::web::mime::multipart; \
/* ����multipart���� */ \
auto _VAR_CONTAINER_ = std::make_shared<multipart::PartList>(request->getHeaders()); \
/* ����multipart��ȡ�� */ \
multipart::Reader _VAR_READER_(_VAR_CONTAINER_.get())

/**
 * ���ö�ȡ���ֵ��ڴ���
 * @param _READER_: ��ȡ��
 * @param _FIELD_NAME_: �ֶ����ơ��磺"nickname"
 * @param _MDS_: ����ȡ���ݴ�С������-1��ʾ��ȡ���ֶ�ȫ������
 */
#define API_MULTIPART_CONFIG_MEMO(_READER_, _FIELD_NAME_, _MDS_) \
_READER_.setPartReader(_FIELD_NAME_, multipart::createInMemoryPartReader(_MDS_))

/**
 * ���ö�ȡ���ֵ��ڴ��У�Ϊ����û�����ö�ȡ��С���ֶ����ö�ȡ��С�����Ҷ�ȡ���ڴ���
 * @param _READER_: ��ȡ��
 * @param _MDS_: ����ȡ���ݴ�С������-1��ʾ��ȡ���ֶ�ȫ������
 */
#define API_MULTIPART_CONFIG_MEMO_DEFAULT(_READER_, _MDS_) \
_READER_.setDefaultPartReader(multipart::createInMemoryPartReader(_MDS_));

/**
 * ���ö�ȡ���ֵ��ļ��У�һ������ֱ�ӱ����ļ�����
 * @param _READER_: ��ȡ��
 * @param _FIELD_NAME_: �ֶ����ơ��磺"file"
 * @param _PATH_: �ļ�����ȫ·�����磺"/tmp/zo/file.png"
 */
#define API_MULTIPART_CONFIG_FILE(_READER_, _FIELD_NAME_, _PATH_) \
_READER_.setPartReader(_FIELD_NAME_, multipart::createFilePartReader(_PATH_))

/**
 * �����������ͱ�������
 * @param _CONTAINER_: ��ȡ����
 * @param _FIELD_NAME_: �ֶ����ơ��磺"age"
 * @param _TYPE_: �������͡��磺Int32��UInt32��Float32�ȵ�
 * @param _VAR_: �洢���������ơ��磺age
 * @param _TYPE_TRANS_FUN_: ��������ת���������磺stoi��stoll��stoull��stof��stod
 */
#define API_MULTIPART_PARSE_FORM_FIELD_NUM(_CONTAINER_, _FIELD_NAME_, _TYPE_, _VAR_, _TYPE_TRANS_FUN_) \
oatpp::_TYPE_ _VAR_ = nullptr; \
auto part##_VAR_ = _CONTAINER_->getNamedPart(_FIELD_NAME_); \
if(part##_VAR_){ \
	_VAR_ = oatpp::_TYPE_(_TYPE_TRANS_FUN_(part##_VAR_->getPayload()->getInMemoryData().getValue(""))); \
}

/**
 * �����ַ������ͱ�������
 * @param _CONTAINER_: ��ȡ����
 * @param _FIELD_NAME_: �ֶ����ơ��磺"nickname"
 * @param _VAR_: �洢���������ơ��磺nickname
 */
#define API_MULTIPART_PARSE_FORM_FIELD_STR(_CONTAINER_, _FIELD_NAME_, _VAR_) \
oatpp::String _VAR_ = nullptr; \
auto part##_VAR_ = _CONTAINER_->getNamedPart(_FIELD_NAME_); \
if(part##_VAR_){ \
	_VAR_ = part##_VAR_->getPayload()->getInMemoryData().getValue(""); \
}

/**
 * �����������ͱ�������
 * @param _CONTAINER_: ��ȡ����
 * @param _FIELD_NAME_: �ֶ����ơ��磺"isopen"
 * @param _VAR_: �洢���������ơ��磺isopen
 */
#define API_MULTIPART_PARSE_FORM_FIELD_BOO(_CONTAINER_, _FIELD_NAME_, _VAR_) \
oatpp::Boolean _VAR_ = nullptr; \
auto part##_VAR_ = _CONTAINER_->getNamedPart(_FIELD_NAME_); \
if(part##_VAR_){ \
	std::string tmp = part##_VAR_->getPayload()->getInMemoryData().getValue(""); \
	_VAR_ = Boolean(tmp == "true" || tmp == "1"); \
}

/**
 * �����ļ����ݣ���ʱ�������ڴ��е��ļ����ݵ��洢������
 * @param _CONTAINER_: ��ȡ����
 * @param _FIELD_NAME_: �ֶ����ơ��磺"head"
 * @param _VAR_: �洢���������ơ��磺head
 */
#define API_MULTIPART_PARSE_FILE_FIELD(_CONTAINER_, _FIELD_NAME_, _VAR_) \
oatpp::String _VAR_ = nullptr; \
auto part##_VAR_ = _CONTAINER_->getNamedPart(_FIELD_NAME_); \
if(part##_VAR_){ \
	_VAR_ = part##_VAR_->getPayload()->getInMemoryData(); \
}

#endif // !_API_HELPER_