#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/01 17:39:36

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

#ifndef _POSTSTUDENTINFOCONTROLLER_
#define _POSTSTUDENTINFOCONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/AddStudent/AddStudentVO.h"
#include "domain/dto/AddStudent/AddStudentDTO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

#define API_TAG ZH_WORDS_GETTER("translation.tags.t1")
#define API_TAG2 ZH_WORDS_GETTER("translation.tags.t2")

class PostStudentInfoController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(PostStudentInfoController);
public://定义接口
	//ENDPOINT_INFO(createStudent) {
	//	info->summary = ZH_WORDS_GETTER("translation.AddStudent");
	//	info->addConsumes<Object<AddStudentDTO>>("application/json");
	//	//支持授权
	//	API_DEF_ADD_AUTH();
	//	//定义响应参数格式
	//	API_DEF_ADD_RSP_JSON(StringJsonVO::Wrapper);
	//	//定义请求参数格式
	//	API_DEF_ADD_PAGE_PARAMS();
	//}
	// 3.1 定义新增接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("translation.post.summary"), createStudent, StringJsonVO::Wrapper, API_TAG);
	// 3.2 定义新增接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c7-workbench/add_student/info", createStudent, BODY_DTO(AddStudentDTO::Wrapper, dto), execAddStudent(dto, authObject->getPayload()));

private://定义执行函数
    // 使用 AddStudentDTO::Wrapper 作为入参和 Object<T> 完全一致
	StringJsonVO::Wrapper execAddStudent(const AddStudentDTO::Wrapper& studentDto, const PayloadDTO& payload);
};

/**
* @brief 添加学员
* @path /add_student/info
* @method POST
* @tag 添加学员信息
*
* @param AddStudentDTO body 请求体，包含添加学员所需的信息。 name,phonenumber,type,sex 必须（required=true)
* @return 返回包含添加结果的JSON对象。
* @response 200{
*  "code": 200,
*	"message": "success",
*	"data": {
*		"name": "张三",
*		"phonenumber": "12345678901",
*		"type": "意向学员",
*		"sex": "男"
*	}
* }
* @response 400{
*  "code": 400,
*	"message": "Bad Request",
*	"data": null
* }
*/
#undef API_TAG
#undef API_TAG2
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // _POSTSTUDENTINFOCONTROLLER_