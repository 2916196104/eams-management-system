#pragma once


#ifndef __HOMEWORK_H__
#define __HOMEWORK_H__
#include "domain/vo/BaseJsonVO.h"

#include "domain/GlobalInclude.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include "../../domain/query/backhomework/backhomeworkQuery.h"
#include "../../domain/vo/backhomework/backhomeworkVO.h"
#include "../../domain/dto/backhomework//backhomeworkDTO.h"


#include OATPP_CODEGEN_BEGIN(ApiController)


/*作业控制器*/

class Homework : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Homework);
public:		//定义接口

	//定义查询作业列表（条件+分页）描述，GetHomeworkList
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("Homework.GetHomeworkList.summary"), GetHomeworkList, GetHomeworkListJsonVO::Wrapper, "Homework.GetHomeworkList"
		/*,API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("Homework.GetHomeworkList"), "d934050a8bb373e8f8eed0bf7507ec17", true)*/
	);
	//定义查询作业列表（条件+分页）处理，GetHomeworkList
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c3/GetHomeworkList", GetHomeworkList, QUERY(String, id), execGetHomeworkList());

	//定义获取作业详情描述，GetHomeworkDetail
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("Homework.GetHomeworkDetail.summary"), GetHomeworkDetail, GetHomeworkDetailJsonVO::Wrapper, "Homework.GetHomeworkDetail"
		/*,API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("Homeworkd.GetHomeworkDetail"), "d934050a8bb373e8f8eed0bf7507ec17", true)*/
	);
	//定义获取作业描述处理，GetHomeworkDetail
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c3/GetHomeworkDetail", GetHomeworkDetail, QUERY(String, id), execGetHomeworkDetail());


	//定义保存作业描述，SaveHomework
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("Homework.SaveHomework.summary"), SaveHomework, SaveHomeworkJsonVO::Wrapper, "Homework.SaveHomework"
		/*,API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("Homework.SaveHomework"), "d934050a8bb373e8f8eed0bf7507ec17", true)*/
	);
	//定义保存作业处理，SaveHomework
	API_HANDLER_ENDPOINT_AUTH(API_M_GET, "/c3/SaveHomework", SaveHomework, QUERY(String, id), execSaveHomework());


private:	//定义接口执行函数
	// 执行函数：作业列表
	GetHomeworkListJsonVO::Wrapper execGetHomeworkList();

	GetHomeworkDetailJsonVO::Wrapper execGetHomeworkDetail();

	SaveHomeworkJsonVO::Wrapper execSaveHomework();
};

#include OATPP_CODEGEN_END(ApiController)

#endif