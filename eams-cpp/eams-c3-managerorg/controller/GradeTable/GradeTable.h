#pragma once


#ifndef __GRADETABLE_H__
#define __GRADETABLE_H__

#include "ApiHelper.h"
#include "domain/GlobalInclude.h"
#include "domain/query/GradeTable/GradeTableQuery.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/GradeTable/GradeTableVO.h"
#include "oatpp/web/server/api/ApiController.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

/*成绩单控制器*/
class GradeTable: public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(GradeTable);
public:		//定义接口

private:	//定义接口执行函数

};

/* Controller for get grade list */
class RecordListController : public oatpp::web::server::api::ApiController
{
    API_ACCESS_DECLARE(RecordListController);

public:
    /* swagger info for query + page endpoint */
    API_DEF_ENDPOINT_INFO_QUERY_AUTH(
        ZH_WORDS_GETTER("grade_table.record_list.get_record_list_title"),
        GetRecordList,
        RecordListQuery,
        RecordListJsonVO::Wrapper,
        ZH_WORDS_GETTER("grade_table.tag")
    );

    API_HANDLER_ENDPOINT_QUERY_AUTH(
        API_M_GET,
        "/app/common/grade/recordList",
        GetRecordList,
        RecordListQuery,
        ExecRecordListQuery(query, authObject->getPayload())
    );

private:
    RecordListJsonVO::Wrapper ExecRecordListQuery(
        const RecordListQuery::Wrapper& query,
        const PayloadDTO& payload
    );
};

#include OATPP_CODEGEN_END(ApiController)

#endif