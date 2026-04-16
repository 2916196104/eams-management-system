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
#include "home/credit_mallController.h"
#include "login/SendPassSMTP.h"
#include "home/credit/redeemcredit/RedeemCreditController.h"
#include "../controller/home/LessonComment/LessonCommentController.h"
#include "home/EnrollCourse/EnrollCourseController.h"
#include"home/announcement/GetallannouncementController.h"
#include"home/announcement/GetdisplayedannouncementController.h"
#include"schedule/GettimeableController.h"
#include "login/RegisterController.h"
#include "controller/home/trialCard/GetTrialCardListController.h"
#include "controller/schedule/AppointmentController.h"
#include "home/homework/HomeworkController.h"
#include"home/class/ClassStudentController.h"
#include "home/credit/GetcreditmalllistController.h"


// 如果定义了关闭Swagger文档宏
#ifdef CLOSE_SWAGGER_DOC
// 简化绑定控制器宏定义
#define ROUTER_SIMPLE_BIND(__CLASS__) \
router->addController(__CLASS__::createShared())
#else
// 简化绑定控制器宏定义
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
	//#TIP :系统扩展路由定义，写在这个后面
	ROUTER_SIMPLE_BIND(RedeemCreditController);
	ROUTER_SIMPLE_BIND(LessonCommentController);
	ROUTER_SIMPLE_BIND(EnrollCourseController);
	ROUTER_SIMPLE_BIND(GetallannouncementController);
	ROUTER_SIMPLE_BIND(GetdisplayedannouncementController);
	ROUTER_SIMPLE_BIND(GettimeableController);
	ROUTER_SIMPLE_BIND(RegisterController);
	ROUTER_SIMPLE_BIND(GetTrialCardListController);
	ROUTER_SIMPLE_BIND(AppointmentController);
	ROUTER_SIMPLE_BIND(HomeworkController);
	ROUTER_SIMPLE_BIND(ClassStudentController);
	ROUTER_SIMPLE_BIND(GetCreditMallListController);

	ROUTER_SIMPLE_BIND(CreditMallController);
	ROUTER_SIMPLE_BIND(SendPassSMTPControl);
	
}
