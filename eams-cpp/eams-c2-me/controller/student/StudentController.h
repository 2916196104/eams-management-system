#pragma once

#ifndef _STUDENT_CONTROLLER_ 
#define _STUDENT_CONTROLLER_ 

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"     //中文词典
#include "D:/01StarProject/WorkSpaseTeamCopy/zero-one-eams2603/eams-cpp/eams-c2-me/domain/dto/student/StudentDTO.h"       // 学员相关DTO（StudentDTO、StudentAddDTO等）

// 1 定义API控制器使用宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("sample.tags")

/*
 * 学员控制器
 */
class StudentController : public oatpp::web::server::api::ApiController // 1 继承控制器
{
  // 2 定义控制器访问入口
  API_ACCESS_DECLARE(StudentController);
  
public:
	// 3 定义接口
    //===================接口1获取用户详细信息接口============//
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("user.query-one.summary"),
        queryOne,
        StringJsonVO::Wrapper, API_TAG,
        API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("user.field.id"), "ae65c714d48d4f34b52479f5482c0edd", true);
    );

    API_HANDLER_ENDPOINT_AUTH(API_M_GET,
        "/me/currentStudentQueryOne",
        queryOne,
        QUERY(String, id),
        executeQueryOne(id));

	//================接口2新增保存学员信息（新增学员信息）接口=========//
        // 定义新增用户信息接口描述
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORDS_GETTER("user.add-user.summary"), 
        addUser, 
        StringJsonVO::Wrapper, 
        API_TAG);
    // 定义新增用户信息接口端点
    API_HANDLER_ENDPOINT_AUTH(
        API_M_POST, 
        "/me/addStudent", 
        addUser, 
        BODY_DTO(StudentAddDTO::Wrapper, dto),
        executeAddStudent(dto));

	//==========接口3上传头像接口（示例，未实现）==================//


private: // 定义接口执行函数
    //接口1获取用户详细信息接口执行函数声明
    StringJsonVO::Wrapper executeQueryOne(const String& id);

    //接口2 新增用户信息
    StringJsonVO::Wrapper executeAddStudent(const StudentAddDTO::Wrapper& dto);

};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) //<- End Codegen
#endif // !_STUDENT_CONTROLLER_
