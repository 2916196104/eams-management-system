#pragma once
#ifndef _ENROLLMENTCONTROLLER_H_
#define _ENROLLMENTCONTROLLER_H_
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include"domain/vo/BaseJsonVO.h"
#include"../../domain/dto/EnrollmentDTO/EnrollmentDTO.h"
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Code-Gen Section

#define API_TAG2 "Enrollmemt"
/*
*保存报名控制器接口
*/
class EnrollmentController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(EnrollmentController);
public:

	// 3.1 定义保存报名接口描述
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("enrollment.summary3"), saveEnrollment, Uint64JsonVO::Wrapper, API_TAG2);
	//// 3.2 定义保存报名接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c4/workbench/enrollment/save", saveEnrollment, BODY_DTO(EnrollmentDTO::Wrapper, dto), execSaveEnrolled(dto));
private:
	//3.3 定义保存报名接口执行函数
	Uint64JsonVO::Wrapper execSaveEnrolled(const EnrollmentDTO::Wrapper& dto);

};
#include OATPP_CODEGEN_END(ApiController) //<- End Code-Gen Section	
#endif // !_ENROLLMENTCONTROLLER_
