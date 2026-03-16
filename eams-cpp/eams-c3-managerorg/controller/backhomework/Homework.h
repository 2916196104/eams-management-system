#pragma once


#ifndef __HOMEWORK_H__
#define __HOMEWORK_H__

#include "domain/GlobalInclude.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include OATPP_CODEGEN_BEGIN(ApiController)
#include "domain/vo/backhome/backhomeVO.h"

/*作业控制器*/

class Homework: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Homework);
public:		//定义接口
    
    //定义查询作业列表（条件+分页）描述，GetHomeworkList
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORD_GETTER("获取作业列表(条件+分页)"),
        HomeworkListVO::Wrapper,
        API_TAG,
        API_DEF_ADD_QUERY_PARAMS(String, "pageNum", ZH_WORDS_GETTER("页码"), "", false),
        API_DEF_ADD_QUERY_PARAMS(String, "pageSize", ZH_WORDS_GETTER("每页条数"), "", false),
        API_DEF_ADD_QUERY_PARAMS(String, "title", ZH_WORDS_GETTER("作业标题(模糊)"), "", true),
        API_DEF_ADD_QUERY_PARAMS(String, "gradeId", ZH_WORDS_GETTER("年级ID"), "", true)
    );
    //定义查询作业列表（条件+分页）处理，GetHomeworkList
    ENDPOINT(API_M_GET, "/c3/org/homework/GetHomeworkList", GetHomeworkList,
        QUERIES(QueryParams, query),
        API_HANDLER_AUTH_PARALLEL);

    //定义获取作业详情，GetHomeworkDetail
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORD_GETTER("获取作业详情"),
        HomeworkDetailVO::Wrapper,
        API_TAG,
        API_DEF_ADD_PATH_PARAM(String, "id", ZH_WORDS_GETTER("作业ID"), "", false)
    );
    //定义获取作业描述，GetHomeworkDetail
    ENDPOINT(API_M_GET, "/c3/org/homework/GetHomeworkDetail/{id}", GetHomeworkDetail,
        PATH(String, id),
        API_HANDLER_AUTH_PARALLEL);

    //定义保存/更新作业详情，SaveHomework
    API_DEF_ENDPOINT_INFO_AUTH(
        ZH_WORD_GETTER("保存/更新作业"),
        JsonVO<Int32>::Wrapper,
        API_TAG
    );
    //定义保存/更新作业描述，SaveHomework
    ENDPOINT(API_M_POST, "/c3/org/homework/SaveHomework", SaveHomework,
        BODY_DTO(Object<HomeworkDTO>, dto),
        API_HANDLER_AUTH_PARALLEL);

private:	//定义接口执行函数
    // 执行函数：作业列表
    GetHomeworkListJsonVO::Wrapper execQueryHomeworkList(const HomeworkPageQuery::Wrapper& query);
    // 执行函数：作业详情
    GetHomeworkDetailJsonVO::Wrapper execGetHomeworkDetail(const oatpp::String& id);
    // 执行函数：保存作业
    SaveHomeworkJsonVO<Int32>::Wrapper execSaveHomework(const Object<HomeworkDTO>& dto);
};

#include OATPP_CODEGEN_END(ApiController)

#endif