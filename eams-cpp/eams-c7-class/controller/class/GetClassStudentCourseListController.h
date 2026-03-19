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
#ifndef _GETCLASSSTUDENTCOURSELISTCONTROLLER_
#define _GETCLASSSTUDENTCOURSELISTCONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Codegen

class GetClassStudentCourseListController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(GetClassStudentCourseListController);
public:			 //定义接口
private:		 //定义执行函数

};

#include OATPP_CODEGEN_END(ApiController) //<- End Codegen

#endif // _GETCLASSSTUDENTCOURSELISTCONTROLLER_