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
#ifndef _ChangePictureController_H_
#define _ChangePictureController_H_

#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/UserRelated/ChangePictureVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen
#define API_TAG2 ZH_WORDS_GETTER("user.tag")
/*
* 修改用户头像控制器
*/
class ChangePictureController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(ChangePictureController);
public:			 //定义接口
	////定义获取用户信息接口描述
	//API_DEF_ENDPOINT_INFO_AUTH(
	//	ZH_WORDS_GETTER("user.changepicture.summary"), queryChangePicture, ChangePictureVO::Wrapper, API_TAG2,
	//	API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("user.field.name"), "name", true);
	//);
	//定义修改接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("user.changepicture.summary"), queryChangePicture, ChangePictureVO::Wrapper, API_TAG2,
	);

	// 3.2 定义修改接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/C7/workbench/ChangePicture", queryChangePicture, QUERY(String, name), execQuaryChangePicture(name));

	////定义获取用户信息接口实现
	//API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/C7/workbench/ChangePicture", queryChangePicture, QUERY(String, name), execQuaryChangePicture(name))
private:		 //定义执行函数
	//定义修改头像接口执行函数
	ChangePictureVO::Wrapper execQuaryChangePicture(const oatpp::String& name);
};

#undef API_TAG2
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // _USERCONTROLLER_H_