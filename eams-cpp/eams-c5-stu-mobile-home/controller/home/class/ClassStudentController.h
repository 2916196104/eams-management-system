#pragma once

#ifndef _CLASS_STUDENT_CONTROLLER_H_
#define _CLASS_STUDENT_CONTROLLER_H_

#include "domain/vo/BaseJsonVO.h"
//#include "domain/query/PageQuery.h"
// 替换为ClassStudent相关Query/DTO/VO头文件
#include "domain/query/home/class/ClassStudentQuery.h"
#include "domain/dto/home/class/ClassStudentDTO.h"
#include "domain/vo/home/class/ClassStudentVO.h"

#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("c5.home.class.tag")


// 控制器类名改为ClassStudentController，继承关系不变
class ClassStudentController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(ClassStudentController); // 适配控制器类名
public:
    ENDPOINT_INFO(ClassStudent) { // 端点名称改为ClassStudent
        info->summary = ZH_WORDS_GETTER("c5.home.class.classstudent.query-all.summary"); // 国际化key适配
        API_DEF_ADD_AUTH();
        API_DEF_ADD_TAG(API_TAG);
        // 替换为ClassStudent分页VO
        //API_DEF_ADD_RSP_JSON(ClassStudentPageJsonVO::Wrapper);
        //API_DEF_ADD_RSP_JSON_WRAPPER(ClassStudentPageJsonVO);
        //API_DEF_ADD_PAGE_PARAMS();
        // 查询参数适配class_student表的student_id，国际化key替换
        // 端点信息里重新声明响应VO
        API_DEF_ADD_RSP_JSON(ClassStudentJsonVO::Wrapper);
        API_DEF_ADD_RSP_JSON_WRAPPER(ClassStudentJsonVO);
        info->queryParams.add<Int32>("class_id").description = ZH_WORDS_GETTER("c5.home.class.classstudent.field.class_id");
        info->queryParams["class_id"].addExample("default", oatpp::Int32(1));
    }
    // 端点路径保留（业务路径不变），端点名称改为ClassStudent，参数/鉴权不变
    ENDPOINT(API_M_GET, "/c5home/class-student/list", ClassStudent, QUERIES(QueryParams, params), API_HANDLER_AUTH_PARAME) {
        // 查询参数绑定为ClassStudentQuery
        API_HANDLER_QUERY_PARAM(query, ClassStudentQuery, params);
        // 响应VO替换为ClassStudentPageJsonVO
        API_HANDLER_RESP_VO(executeQueryClassStudent(query));
    }
private:
    // 私有方法名/参数/返回值适配ClassStudent
// 私有方法返回值也改
    ClassStudentJsonVO::Wrapper executeQueryClassStudent(const ClassStudentQuery::Wrapper& query);
};

#undef API_TAG
#include OATPP_CODEGEN_END(ApiController)

#endif // !_CLASS_STUDENT_CONTROLLER_H_