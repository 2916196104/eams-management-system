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

#include "controller-huitailang/addintendedstudentcontroller.h"

#include "enrollment/EnrollmentController.h"
#include "enrollment/EnrolledRecordController.h"

#include "makabaka-controller/TeacherListController/TeacherListController.h"
#include "makabaka-controller/classListController/ClassListController.h"

#include "huitailang-controller/commentrecordcontroller.h"
#include "huitailang-controller/getrollcallrecord.h"

//#include "controller_zhong\Student_Class_Hour Records\ClassHourRecordsController.h"
//#include "controller_zhong\Student_Course_Progress\StudentCourseProgressController.h"
//#include "controller_zhong\Student_Enrollment_Records\StudentEnrollmentRecordsController.h"

#include"makabaka-controller/SchedulingController.h"

#include "hh-controller/CustomerController.h"
#include "hh-controller/ClassroomController.h"

#include "lxianyu-controller/StudentFileController.h"

#include "workbench/CurrentUserController.h"

#include "gw-controller/HomeworkController.h"

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
	ROUTER_SIMPLE_BIND(EnrollmentController);
	ROUTER_SIMPLE_BIND(EnrolledRecordController);

	ROUTER_SIMPLE_BIND(TeacherListController);
	ROUTER_SIMPLE_BIND(ClassListController);

	ROUTER_SIMPLE_BIND(getcommentrecord);
	ROUTER_SIMPLE_BIND(getrollrecllrecord);
	ROUTER_SIMPLE_BIND(addintendedstudent);

	/*ROUTER_SIMPLE_BIND(ClassHourRecordsController);
	ROUTER_SIMPLE_BIND(CourseProgressController);
	ROUTER_SIMPLE_BIND(EnrollmentRecordsController);*/

	ROUTER_SIMPLE_BIND(SchedulingController);

	ROUTER_SIMPLE_BIND(CustomerController);
	ROUTER_SIMPLE_BIND(ClassroomController);

	ROUTER_SIMPLE_BIND(StudentFileController);

	ROUTER_SIMPLE_BIND(CurrentUserController);

	ROUTER_SIMPLE_BIND(HomeworkController);
}
