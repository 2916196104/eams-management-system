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
		"/c3/common/student/get-by-id", 
		getStudentById,
		QUERY(String, id), 
		executeGetStudentById(id)
	);

	//下载学员头像
	API_DEF_ENDPOINT_INFO(
		ZH_WORDS_GETTER("common.interface.download-student-picture"), loadStudentPicturebyPicturePath, Void, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "picturePath", ZH_WORDS_GETTER("common.field.student.picture-path"), "file/test.jpg", true);
	);
	API_HANDLER_ENDPOINT_OPTION(
		API_M_GET, 
		"/c3/common/student/download-student-picture", 
		loadStudentPicturebyPicturePath,
		QUERY(String, picturePath), 
		return executeLoadStudentPicturebyPicturePath(picturePath);
	);

	//修改学员头像
	ENDPOINT_INFO(modifyStudentPicture) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.modify-student-picture"));//添加接口描述
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("common.field.student.id"), "123", true);//添加参数
		API_DEF_ADD_FILE_FORM(FileOnlyDTO::Wrapper);
		API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);//添加返回数据包装
	}
    ENDPOINT(API_M_POST, "/c3/common/student/modify-picture/{id}",modifyStudentPicture,PATH(String,id), REQUEST(std::shared_ptr<IncomingRequest>, request), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeModifyStudentPicture(id,request));
	}

	//查询学员报名记录
	ENDPOINT_INFO(queryRegistrationRecordByPage) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.query-student-registration-record"));//添加接口描述
		API_DEF_ADD_PAGE_PARAMS();//添加分页参数
		API_DEF_ADD_RSP_JSON_WRAPPER(RegistrationPageJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_GET, "/c3/common/registration-recordf/query-by-page", queryRegistrationRecordByPage, QUERIES(QueryParams, queryParams),API_HANDLER_AUTH_PARAME) {
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
	ENDPOINT(API_M_GET, "/c3/common/interface/get-student-course-count", getCourseCountData, PATH(String,id), API_HANDLER_AUTH_PARAME) {
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
	ENDPOINT(API_M_GET, "/c3/common/interface/save-student", SaveStudent, PATH(String, id), BODY_DTO(SaveStudentDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeSaveStudent(id));
	}


	// 3.1 学员报名课程申请描述 
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("common.interface.enrollstudentCourse"), EnrollStudentCourselist, StringJsonVO::Wrapper, API_TAG);
	// 3.2 学员报名课程申请处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/c3/common/enrollment/student/apply",
		EnrollStudentCourselist,
		BODY_DTO(RegistrationApplyDTO::Wrapper, dto),
		executeEnrollStudentCourse(dto, authObject->getPayload())
	);

	// 3.1 学员阶段设置描述 
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("common.interface.studentstage"), StudentStage, StringJsonVO::Wrapper, API_TAG);
	// 3.2 学员阶段设置处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_PUT,
		"/c3/common/enrollment/student/stage",
		StudentStage,
		BODY_DTO(StudentStageUpdateDTO::Wrapper, dto),
		executeModifyStudentStage(dto, authObject->getPayload())
	);

	// 删除跟进记录描述 
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("common.interface.delete-contact-record"), deleteContactRecord, StringJsonVO::Wrapper, API_TAG);
	// 删除跟进记录处理
	API_HANDLER_ENDPOINT_AUTH(
		API_M_POST,
		"/c3/common/contact-record/delete",
		deleteContactRecord,
		BODY_DTO(DeleteContactRecordDTO::Wrapper, dto),
		executeDeleteContactRecord(dto)
	);











	// 3.1 定义调整积分接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("common.interface.modify-student-points"), modifySample, StringJsonVO::Wrapper, API_TAG);
	// 3.2 定义调整积分接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/modify-points", modifySample, BODY_DTO(ModifyPointsDTO::Wrapper, dto), execModifyPoints(dto, authObject->getPayload()));





	// 3.1 定义添加跟进记录接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("common.interface.add-follow-up-record"), addSample, StringJsonVO::Wrapper, API_TAG);
	// 3.2 定义添加跟进记录接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/add-follow-up-record", addSample, BODY_DTO(AddFollowUpRecordDTO::Wrapper, dto), execAddFollowUpRecord(dto, authObject->getPayload()));







	// 3.1 定义查询跟进记录接口描述
	ENDPOINT_INFO(querySample) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.query-follow-up-records"));
		// 定义默认授权参数（可选定义，如果定义了，下面ENDPOINT里面需要加入API_HANDLER_AUTH_PARAME）
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(QueryFollowUprecordsJsonVO);
		// 定义标签
		API_DEF_ADD_TAG(API_TAG);
		// 定义分页查询参数描述
		API_DEF_ADD_PAGE_PARAMS();
		// 定义其他查询参数描述
		API_DEF_ADD_QUERY_PARAMS(String, "name", ZH_WORDS_GETTER("sample.field.name"), "zhang san", false);
		API_DEF_ADD_QUERY_PARAMS(String, "follow_up_stage", ZH_WORDS_GETTER("common.field.student.follow-up-stage"), ZH_WORDS_GETTER("common.field.student.lost-stage"), false);
		API_DEF_ADD_QUERY_PARAMS(String, "follow_up_person", ZH_WORDS_GETTER("common.field.student.follow-up-person"), "li shi", false);
		API_DEF_ADD_QUERY_PARAMS(String, "startdate", ZH_WORDS_GETTER("common.field.student.startdate"), "2021-3-20", false);
		API_DEF_ADD_QUERY_PARAMS(String, "enddate", ZH_WORDS_GETTER("common.field.student.enddate"), "2026-03-20", false);
	}
	// 3.2 定义查询跟进记录接口处理
	ENDPOINT(API_M_GET, "/query-follow-up-records", querySample, QUERIES(QueryParams, queryParams), API_HANDLER_AUTH_PARAME) {
		// 解析查询参数为Query领域模型
		API_HANDLER_QUERY_PARAM(addQuery, FollowUprecordsQuery, queryParams);
		// 呼叫执行函数响应结果
		API_HANDLER_RESP_VO(execQueryFollowUprecords(addQuery));
	}


private:
	



	StudentJsonVO::Wrapper executeGetStudentById(const String& id){
		return StudentJsonVO::createShared();
	}
    StringJsonVO::Wrapper executeModifyStudentPicture(const String& id,std::shared_ptr<IncomingRequest>request){
		return StringJsonVO::createShared();
	}
	RegistrationPageJsonVO::Wrapper executeQueryRegistrationRecordByPage(const RegistrationPageQuery::Wrapper& query){
		return RegistrationPageJsonVO::createShared();
	}
	std::shared_ptr<OutgoingResponse> executeLoadStudentPicturebyPicturePath(const String& picturePath){
		return nullptr;
	}
<<<<<<< HEAD
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

	// 删除跟进记录
	StringJsonVO::Wrapper executeDeleteContactRecord(const DeleteContactRecordDTO::Wrapper& dto) {
		return StringJsonVO::createShared();
	}
=======


	// 3.3 调整积分接口执行函数
	StringJsonVO::Wrapper execModifyPoints(const ModifyPointsDTO::Wrapper& dto, const PayloadDTO& payload);


	// 3.3 添加跟进记录
	StringJsonVO::Wrapper execAddFollowUpRecord(const AddFollowUpRecordDTO::Wrapper& dto, const PayloadDTO& payload);

	
	// 查询跟进记录
	QueryFollowUprecordsJsonVO::Wrapper execQueryFollowUprecords(const FollowUprecordsQuery::Wrapper& query);
>>>>>>> c6-a-luo




};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) 

#endif