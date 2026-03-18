#pragma once


#ifndef __RECORD_NAME_H__
#define __RECORD_NAME_H__

#include "domain/GlobalInclude.h"
#include "oatpp/web/server/api/ApiController.hpp"

#include "./domain/dto/timetable/TimetableDTO.h"
#include "./domain/vo/timetable/TimetableVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("set_status.flag")

class Record_name: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Record_name);
public:		//定义接口


	// 1. 设置上课状态 接口的定义
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("set_status.title"), modifyStatus, SetStudyStatusRspJsonVO::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_PUT, "/course-table/set-status", modifyStatus, BODY_DTO(SetStudyStatusDTO::Wrapper, dto), updateModifyStatus(dto, authObject->getPayload()));




	

private:	//定义接口执行函数

	SetStudyStatusRspJsonVO::Wrapper updateModifyStatus(const SetStudyStatusDTO::Wrapper& dto, const PayloadDTO& payload);
	
};

#undef API_TAG

#include OATPP_CODEGEN_END(ApiController)

#endif