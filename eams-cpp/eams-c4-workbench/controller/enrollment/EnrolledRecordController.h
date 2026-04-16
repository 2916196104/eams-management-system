#pragma once
#ifndef _ENROLLEDRECORDCONTROLLER_H_
#define _ENROLLEDRECORDCONTROLLER_H_
#include "ApiHelper.h"
#include "ServerInfo.h"
#include "Macros.h"
#include"domain/vo/BaseJsonVO.h"
#include"../../domain/vo/EnrollmentVO/EnrollecRecordVO.h"
#include"../../../lib-oatpp/include/domain/query/PageQuery.h"
#include"../../domain/query/EnrollmentQuery/EnrolledRecordQuery.h"
#include OATPP_CODEGEN_BEGIN(ApiController) //<- Begin Code-Gen Section

#define API_TAG1 ZH_WORDS_GETTER("StudentFile.get.tag2")	
/*
* 报名记录控制器接口
*/
class EnrolledRecordController : public oatpp::web::server::api::ApiController
{
	//定义控制器访问接口
	API_ACCESS_DECLARE(EnrolledRecordController);
public:
	// 3.1 定义获取报名记录接口描述
	ENDPOINT_INFO(EnrolledRecord) {
		// 定义接口标题
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("enrollment.summary1"));
		//定义默认授权验证
		API_DEF_ADD_AUTH();
		// 定义接口标签
		API_DEF_ADD_TAG(API_TAG1);
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(EnrolledRecordListJsonVO);//根据情况在设置
		//定义分页查询参数
		API_DEF_ADD_PAGE_PARAMS();
		//姓名
		//API_DEF_ADD_QUERY_PARAMS(String,"name",ZH_WORDS_GETTER(" "),"zhang san",false);
	}
	// 3.2 定义获取报名记录接口处理
	ENDPOINT(API_M_GET, "/c4-workbench/enrollment/record", EnrolledRecord,QUERIES(QueryParams,queryEnrolled),API_HANDLER_AUTH_PARAME) {
		//解析查询参数
		API_HANDLER_QUERY_PARAM(RecordQuery, EnrolledQuery, queryEnrolled);
		// 响应结果
		API_HANDLER_RESP_VO(execQueryNameList(RecordQuery));
	}
	// 3.1 定义获取报名记录详情接口描述
	ENDPOINT_INFO(EnrolledDetail) {
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("enrollment.summary2"));
		//定义接口标签
		API_DEF_ADD_TAG(API_TAG1);
		//定义默认授权验证
		API_DEF_ADD_AUTH();
		// 定义响应参数格式
		API_DEF_ADD_RSP_JSON_WRAPPER(EnrolledRecordDetailJsonVO);//根据情况在设置
		// 定义查询参数
		API_DEF_ADD_QUERY_PARAMS(String,"id",ZH_WORDS_GETTER("EnrolledRecord.field.id"),"number", true);
	}
	// 3.2 定义获取报名记录详情接口处理
	ENDPOINT(API_M_GET, "/c4-workbench/enrollment/detail", EnrolledDetail, QUERY(String,id), API_HANDLER_AUTH_PARAME) {
		int Intid = stoi(id);
		// 响应结果
		API_HANDLER_RESP_VO(execEnrolledDetail(Intid));
	}
private:
	//3.3 定义获取报名记录接口执行函数
	EnrolledRecordListJsonVO::Wrapper execQueryNameList(const EnrolledQuery::Wrapper& Record);
	//3.3 定义获取报名记录详情接口执行函数
	EnrolledRecordDetailJsonVO::Wrapper execEnrolledDetail(const Int32 &id);
};
#include OATPP_CODEGEN_END(ApiController) //<- End Code-Gen Section	
#endif // !_ENROLLMENTCONTROLLER_
