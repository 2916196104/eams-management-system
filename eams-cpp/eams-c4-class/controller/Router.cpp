/*
 Copyright Zero One Star. All rights reserved.
*/
#include "stdafx.h"
#include "Router.h"
#include "ApiHelper.h"
#include "class/ClassStudentController.h"
#include "workbench/CurrentUserController.h"

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
	ROUTER_SIMPLE_BIND(CurrentUserController);
	ROUTER_SIMPLE_BIND(ClassStudentController);
}
