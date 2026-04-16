#pragma once
#ifndef ADDINTENDEDSTUDENTCONTROLLER_H
#define ADDINTENDEDSTUDENTCONTROLLER_H
#include "ServerInfo.h" //中文字典需要引入的头文件
#include "Macros.h"   //中文字典需要引入的头文件
#include "../../domain/dto/dto-huitailang/intendedstudentdto.h"
#include "../../domain/vo/vo-huitailang/intednedstudentvo.h"
#include "../lib-oatpp/include/ApiHelper.h"
#include "domain/vo/BaseJsonVO.h"

#define API_TAG ZH_WORDS_GETTER("intendedstudent.text2")

#include OATPP_CODEGEN_BEGIN(ApiController)
class addintendedstudent : public oatpp::web::server::api::ApiController
{
	API_ACCESS_DECLARE(addintendedstudent);
public: // 定义接口

	// 3.1 定义新增接口描述

	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("intendedstudent.text2"), addstudent, intendedstudentJsonVO::Wrapper, API_TAG);
	// 3.2 定义新增接口处理
	API_HANDLER_ENDPOINT_AUTH(API_M_POST, "/c4-workbench/addintendedstudent", addstudent,
		BODY_DTO(intendedstudentDTO::Wrapper, dto), executeaddintendedstudent(dto, authObject->getPayload()));
private: // 定义接口执行函数 执行函数的返回值是响应给前端的json函数
	//这里返回值stringJsonVo 也是在vo中定义了相应的头文件
	StringJsonVO::Wrapper executeaddintendedstudent(const intendedstudentDTO::Wrapper& dto, const PayloadDTO& payload);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)



#endif // !ADDINTENDEDSTUDENTCONTROLLER_H
