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
#include "backhomework/Homework.h"
#include "backhomework/SendHomework.h"
#include "TeaJudgeStu/TeaJudgeStu.h"
#include "StuJudgeTea/StuJudgeTea.h"
#include "GradeTable/GradeTable.h"
#include "GradeTable/GradeManage.h"
#include "BoardManager/BoardManager.h"



// ???????????Swagger?????
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
	//#TIP :?????°§????»…ß’?????????
	ROUTER_SIMPLE_BIND(Homework);
	ROUTER_SIMPLE_BIND(SendHomework);
	ROUTER_SIMPLE_BIND(TeaJudgeStu);
	ROUTER_SIMPLE_BIND(StuJudgeTea);
	ROUTER_SIMPLE_BIND(SaveListController);
	ROUTER_SIMPLE_BIND(DeleteListController);
	ROUTER_SIMPLE_BIND(GradeManage);
	ROUTER_SIMPLE_BIND(GradeTable);
	ROUTER_SIMPLE_BIND(BoardManager);
}
