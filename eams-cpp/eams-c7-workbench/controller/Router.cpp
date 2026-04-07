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
#include "UserRelated/UserInformationController.h"
#include "UserRelated/UserProfileController.h"
#include "UserRelated/ChangePictureController.h"
#include "Course/CourseController.h"
#include "MyCustomers/GetMyCustomersController.h"
#include "MyCustomers/GetStudentCoursesController.h"
#include "MyCustomers/GetStudentDetailController.h"
#include "Homework/HomeworkController.h"
#include "Schedule/SelectClassController.h"
#include "Schedule/SelectTeacherController.h"
#include "UserRelated/MonthlyDataController.h"
#include "Schedule/repeatCoursesArrangeController.h"
#include "Schedule/freeCoursesArrangeController.h"
#include "StudentRecord/StlistController.h"
#include "StudentRecord/StclassRecordController.h"
#include "StudentRecord/StprofileDetailsController.h"
#include "StudentRecord/student_coursecontroller.h"
#include "RegistRecord/GetRegistRecordDetailsController.h"
#include "RegistRecord/GetRegistRecordListController.h"
#include "AddStudent/PostStudentInfoController.h"
#include "Course/RegisterController.h"
#include "Homework/HomeworkListController.h"
#include "Schedule/ClassroomController.h"
#include "SignAndRemark/RemarkController.h"
#include "SignAndRemark/SignController.h"


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
	ROUTER_SIMPLE_BIND(GetUserInformationController);
	ROUTER_SIMPLE_BIND(GetUserProfileController);
	ROUTER_SIMPLE_BIND(ChangePictureController);
	ROUTER_SIMPLE_BIND(CourseController);
	ROUTER_SIMPLE_BIND(GetMyCustomersController);
	ROUTER_SIMPLE_BIND(GetStudentCoursesController);
	ROUTER_SIMPLE_BIND(GetStudentDetailController);
	ROUTER_SIMPLE_BIND(HomeworkController);
	ROUTER_SIMPLE_BIND(SelectClassController);
	ROUTER_SIMPLE_BIND(SelectTeacherController);
	ROUTER_SIMPLE_BIND(MonthlyDataController);
	ROUTER_SIMPLE_BIND(repeatCoursesArrangeController);
	ROUTER_SIMPLE_BIND(freeCoursesArrangeController);
	ROUTER_SIMPLE_BIND(StlistController);
	ROUTER_SIMPLE_BIND(StclassRecordController);
	ROUTER_SIMPLE_BIND(StprofileDetailsController);
	ROUTER_SIMPLE_BIND(StudentRecord::CourseControllor);
	ROUTER_SIMPLE_BIND(GetRegistRecordDetailsController);
	ROUTER_SIMPLE_BIND(GetRegistRecordListController);
	ROUTER_SIMPLE_BIND(RegisterController);
	ROUTER_SIMPLE_BIND(HomeworkListController);
	ROUTER_SIMPLE_BIND(SignController);
	ROUTER_SIMPLE_BIND(RemarkController);
	ROUTER_SIMPLE_BIND(ClassroomController);
	ROUTER_SIMPLE_BIND(PostStudentInfoController);
}
