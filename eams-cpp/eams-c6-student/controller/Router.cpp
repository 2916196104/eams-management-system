/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/12/03 14:58:34

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
#include "Router.h"
#include "ApiHelper.h"
#include "controller/intendedstudent/IntendedStudentController.h"
#include "common/CommonController.h"
#include "parentaccount/ParentAccountController.h"
#include "finishstudent/FinishStudentController.h"
#include "summaryclass/SummaryClassController.h"
#include "controller/onlinestudent/OnlineStudentController.h"

// 如果定义了关闭Swagger文档宏
#ifdef CLOSE_SWAGGER_DOC
// ??????????????
#define ROUTER_SIMPLE_BIND(__CLASS__) \
router->addController(__CLASS__::createShared())
#else
// ??????????????
#define ROUTER_SIMPLE_BIND(__CLASS__) \
BIND_CONTROLLER(docEndpoints, router, __CLASS__)
#endif

Router::Router(Endpoints* docEndpoints, HttpRouter* router)
{
	this->docEndpoints = docEndpoints;
	this->router = router;
}

void Router::initRouter()
{
	//#TIP :???????????????????????
	ROUTER_SIMPLE_BIND(CommonController);
	ROUTER_SIMPLE_BIND(ParentAccountController);
	ROUTER_SIMPLE_BIND(FinishStudentController);
	ROUTER_SIMPLE_BIND(CommonController);
	ROUTER_SIMPLE_BIND(SummaryClassController);
	ROUTER_SIMPLE_BIND(ParentAccountController);
	ROUTER_SIMPLE_BIND(IntendedStudentController);
	ROUTER_SIMPLE_BIND(OnlineStudentController);

}
