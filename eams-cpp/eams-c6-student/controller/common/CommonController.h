#pragma once
#ifndef COMMON_CONTROLLER_H
#define COMMON_CONTROLLER_H
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/common/CommonVO.h"
#include "domain/dto/common/CommonDTO.h"
#include "domain/query/common/CommonQuery.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("common.api-tag")

class CommonController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(CommonController);
public:
	//获取学员详情
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("common.interface.get-student-by-id"), 
		getStudentById, StudentJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(
			String, "id", ZH_WORDS_GETTER("common.field.student.id"), 
			"d934050a8bb373e8f8eed0bf7507ec17", true
		);
	)
	API_HANDLER_ENDPOINT_AUTH(
		API_M_GET,
		"/c6/common/student/get-by-id", 
		getStudentById,
		QUERY(String, id), 
		executeGetStudentById(id)
	);
	//修改学员头像
	ENDPOINT_INFO(modifyStudentPicture) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.modify-student-picture"));//添加接口描述
		API_DEF_ADD_PATH_PARAMS(String, "picturePath", ZH_WORDS_GETTER("common.field.student.picture-path"), "123", true);//添加参数
		API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);//添加返回数据包装
	}
    ENDPOINT(API_M_POST, "/c6/common/student/modify-picture/{picturePath}",modifyStudentPicture,PATH(String,picturePath),API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeModifyStudentPicture(picturePath));
	}

	//查询学员报名记录
	ENDPOINT_INFO(queryRegistrationRecordByPage) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.query-student-registration-record"));//添加接口描述
		API_DEF_ADD_QUERY_PARAMS(Int64, "id", ZH_WORDS_GETTER("common.field.student.id"), 213423231, true);
		API_DEF_ADD_PAGE_PARAMS();//添加分页参数
		API_DEF_ADD_RSP_JSON_WRAPPER(RegistrationPageJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_GET, "/c6/common/registration-recordf/query-by-page", queryRegistrationRecordByPage, QUERIES(QueryParams, queryParams),API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, RegistrationPageQuery, queryParams);//获取参数
		API_HANDLER_RESP_VO(executeQueryRegistrationRecordByPage(query));
	}	
	//获取学员课次数据
	ENDPOINT_INFO(getCourseCountData) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.get-student-course-count"));//添加接口描述
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("common.field.student.id"), "123", true);//添加参数
		API_DEF_ADD_RSP_JSON_WRAPPER(CourseCountJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_GET, "/c6/common/interface/get-student-course-count", getCourseCountData, PATH(String,id), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeGetCourseCountData(id));
	}
	//保存学员
	ENDPOINT_INFO(SaveStudent) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.save-student"));//添加接口描述
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("common.field.student.id"), "123", true);//添加参数
		API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_GET, "/c6/common/interface/save-student", SaveStudent, PATH(String, id), BODY_DTO(SaveStudentDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeSaveStudent(id));
	}
	// 3.1 学员报名课程申请描述 
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("common.interface.enrollstudentCourse"), EnrollStudentCourselist, StringJsonVO::Wrapper, API_TAG);
	// 3.2 学员报名课程申请处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/c6/common/enrollment/student/apply",
		EnrollStudentCourselist,
		BODY_DTO(RegistrationApplyDTO::Wrapper, dto),
		executeEnrollStudentCourse(dto, authObject->getPayload())
	);

	// 3.1 学员阶段设置描述 
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("common.interface.studentstage"), StudentStage, StringJsonVO::Wrapper, API_TAG);
	// 3.2 学员阶段设置处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_PUT,
		"/c6/common/enrollment/student/stage",
		StudentStage,
		BODY_DTO(StudentStageUpdateDTO::Wrapper, dto),
		executeModifyStudentStage(dto, authObject->getPayload())
	);


private:
	StudentJsonVO::Wrapper executeGetStudentById(const String& id){
		return StudentJsonVO::createShared();
	}
    StringJsonVO::Wrapper executeModifyStudentPicture(const String& picturePath){
		return StringJsonVO::createShared();
	}
	RegistrationPageJsonVO::Wrapper executeQueryRegistrationRecordByPage(const RegistrationPageQuery::Wrapper& query){
		return RegistrationPageJsonVO::createShared();
	}
	CourseCountJsonVO::Wrapper executeGetCourseCountData(const String& id) {
		return CourseCountJsonVO::createShared();
	}

	StringJsonVO::Wrapper executeSaveStudent(const String& id) {
		return StringJsonVO::createShared();
	}

	// 3.3 增数据
	StringJsonVO::Wrapper executeEnrollStudentCourse(const RegistrationApplyDTO::Wrapper& dto, const PayloadDTO& payload) {
		return StringJsonVO::createShared();
	}
	// 3.3 修改数据
	StringJsonVO::Wrapper executeModifyStudentStage(const StudentStageUpdateDTO::Wrapper& dto, const PayloadDTO& payload) {

		return StringJsonVO::createShared();
	}
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) 

#endif