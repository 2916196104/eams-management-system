#pragma once

#ifndef _STUDENT_CONTROLLER_
#define _STUDENT_CONTROLLER_

#include "domain/vo/BaseJsonVO.h"
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "./domain/vo/GradeJsonVO.h"
#include "./domain/query/GradeQuery.h"
#include "./domain/vo/PointPageJsonVO.h"
#include "./domain/query/PointQuery.h"
#include "domain/query/student/IdQuery.h"
#include "Macros.h"     //中文词典
#include "domain/dto/student/StudentDTO.h"       // 学员相关DTO（StudentDTO、StudentAddDTO等）


// #include "domain/query/StudentQuery/StudentQuery.h"
#include "domain/query/student/StudentQuery.h"
//#include "domain/query/student/IdQuery.h"
#include "domain/vo/student/StudentVO.h"

// 生成API控制器代码宏
#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("student.tag")

/**
 * 学员控制器（整合查询/删除/切换功能）
 */
class StudentController : public oatpp::web::server::api::ApiController
{
    // 控制器访问入口声明
    API_ACCESS_DECLARE(StudentController);

public:
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("student.query.grade"), queryGrade, GradeListJsonVO::Wrapper, API_TAG);
	// 定义查询所有用户信息接口端点
	//API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/me/getOptionalGrade", queryGrade, GradeQuery, executeQueryGrade(query));
	ENDPOINT(API_M_GET, "/me/getOptionalGrade", queryGrade,API_HANDLER_AUTH_PARAME) {
		return createDtoResponse(Status::CODE_200, executeQueryGrade());
		
	}
    
	API_DEF_ENDPOINT_INFO_QUERY_AUTH(ZH_WORDS_GETTER("student.query.point"), queryPoint, PointQuery, PointPageJsonVO::Wrapper, API_TAG);
	// 定义查询所有用户信息接口端点
	API_HANDLER_ENDPOINT_QUERY_AUTH(API_M_GET, "/me/getMyPoint", queryPoint, PointQuery, executeQueryPoint(query));

   
  
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
    //


	// //切换用户
	// API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("student.switchStudent"), switchStudent, StringJsonVO::Wrapper, API_TAG);
	// API_HANDLER_ENDPOINT_AUTH(
	//   API_M_GET,
	//   "/me/switchStudent",
	//   switchStudent,
	//   QUERY(Int64, id),
	//   executeSwitchStudent(id)
	// );

private: // 定义接口执行函数
	PointPageJsonVO::Wrapper executeQueryPoint(const PointQuery::Wrapper& query);

private: // 定义接口执行函数

    //接口1获取用户详细信息接口执行函数声明
    StringJsonVO::Wrapper executeQueryOne(const String& id);

    //接口2 新增用户信息
    StringJsonVO::Wrapper executeAddStudent(const StudentAddDTO::Wrapper& dto);

	GradeListJsonVO::Wrapper executeQueryGrade();

    // ========== 1. 查询学员列表 ==========    
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("student.getStudentList"),// 接口标题
        queryAllUser,               // 端点函数名
        StudentQuery,                  // Query类型（自动生成参数文档）
        StudentPageJsonVO::Wrapper,    // 响应类型
        API_TAG                     // 标签
    );
    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/me/getStudentList",
        queryAllUser,
        StudentQuery,
        executeQueryAll(query)
    );

    // ========== 2. 删除学员 ==========    
    //接口文档
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("student.removeStudent"),
        removeStudent,         
        IdQuery,                  
        JsonVO<oatpp::Any>::Wrapper, 
        API_TAG                   
    );
    //返回值修改为JsonVO(oatpp::Any::Wrapper)
    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/me/removeStudent",
        removeStudent,
        IdQuery,  
        executeRemoveUser(query)
    );
    //因为是单个id使用IdQuery更符合规范

    // ========== 3. 切换学员 ==========
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        "切换学员",
        switchStudent,
        IdQuery,
        JsonVO<oatpp::Any>::Wrapper,
        API_TAG
    );
    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/me/switchStudent",
        switchStudent,
        IdQuery,
        executeSwitchStudent(query)
    );

private:
    // 执行查询学员列表
    StudentPageJsonVO::Wrapper executeQueryAll(const StudentQuery::Wrapper& query);
    // 执行删除学员
    JsonVO<oatpp::Any>::Wrapper executeRemoveUser(const IdQuery::Wrapper& query);
    // 执行切换学员
    JsonVO<oatpp::Any>::Wrapper executeSwitchStudent(const IdQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) // 结束代码生成

#endif // !_STUDENT_CONTROLLER_