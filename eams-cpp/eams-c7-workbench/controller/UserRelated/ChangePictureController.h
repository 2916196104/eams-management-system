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
#include "ApiHelper.h"
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


	//// 定义描述
	//API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("user.changepicture.summary"), uploadImage, FileOnlyDTO::Wrapper, ChangePictureVO::Wrapper, API_TAG2);
	//// 定义端点
	//API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/C7/workbench/ChangePicture", uploadImage, REQUEST(std::shared_ptr<IncomingRequest>, request), execQueryChangePicture(request));


	// 定义一个单文件上传接口
	// 定义描述
	API_DEF_ENDPOINT_INFO_FILE_AUTH(ZH_WORDS_GETTER("user.changepicture.summary"), uploadImage, FileOnlyDTO::Wrapper, ChangePictureVO::Wrapper, API_TAG2);
	// 定义端点
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c7-workbench/ChangePicture", uploadImage, REQUEST(std::shared_ptr<IncomingRequest>, request), execQueryChangePicture(authObject->getPayload(), request));




private:		 //定义执行函数
	//定义修改头像接口执行函数
	ChangePictureVO::Wrapper execQueryChangePicture(const PayloadDTO& payload, std::shared_ptr<IncomingRequest> request);

};

#undef API_TAG2
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // _USERCONTROLLER_H_