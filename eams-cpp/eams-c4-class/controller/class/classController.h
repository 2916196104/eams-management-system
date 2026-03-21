#pragma once
#ifndef CLASSCONTROLLER_H_
#define CLASSCONTROLLER_H_
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include"domain/vo/BaseJsonVO.h"
#include"../../domain/dto/ClassDTO/classDetailDTO.h"
#include"../../domain/vo/ClassVO/ClassDetailVO.h"
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Code-Gen Section

#define API_TAG ZH_WORDS_GETTER("class.tag")

class ClassController : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(ClassController);
public:
	// 3.1 定义班级详情接口描述
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("class1.summary"),classDetail, ClassDetailJsonVO::Wrapper, API_TAG);
	// 3.2 定义ID查询接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "c4/class/class_detail",classDetail ,BODY_DTO(ClassDetailDTO::Wrapper,dto),execClassDetail(dto));

private:
	ClassDetailJsonVO::Wrapper execClassDetail(const ClassDetailDTO::Wrapper& dto);

};

#include OATPP_CODEGEN_END(ApiController) //<- End Code-Gen Section
#endif // !CLASSCONTROLLER_H_
