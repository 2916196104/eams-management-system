/*
 Copyright Zero One Star. All rights reserved.
*/
#include "stdafx.h"
#include "Router.h"
#include "ApiHelper.h"
#include "class/ClassStudentController.h"
#include "class/MyClassController.h"
#include"../controller/class/classController.h"

#ifdef CLOSE_SWAGGER_DOC
#define ROUTER_SIMPLE_BIND(__CLASS__) \
router->addController(__CLASS__::createShared())
#else
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
	ROUTER_SIMPLE_BIND(ClassController);
	ROUTER_SIMPLE_BIND(ClassStudentController);
	ROUTER_SIMPLE_BIND(MyClassController);
}
