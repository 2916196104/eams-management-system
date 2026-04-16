#pragma once

#ifndef __HOMEWORK_H__
#define __HOMEWORK_H__
#include "domain/vo/BaseJsonVO.h"

#include "domain/GlobalInclude.h"
#include "ApiHelper.h"
#include "oatpp/web/server/api/ApiController.hpp"
#include "../../domain/query/backhomework/backhomeworkQuery.h"
#include "../../domain/vo/backhomework/backhomeworkVO.h"
#include "../../domain/dto/backhomework//backhomeworkDTO.h"


#include OATPP_CODEGEN_BEGIN(ApiController)

#define API_TAG ZH_WORDS_GETTER("Homework.backhomework")

//作业控制器（处理老师布置的作业主数据操作
class Homework : public oatpp::web::server::api::ApiController
{
	//定义控制器访问入口
	API_ACCESS_DECLARE(Homework);
public:		//定义接口

	//定义查询作业列表（条件+分页）描述
	//GetHomeworkList，每条数据只有关键数据与唯一表示，完整数据通过详情接口获取。
	//流程中显示可填入作业标题，班级，发布者，页码，返回作业id，标题，班级，发布者，提交量等信息
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("homework.gethomeworklist.summary"), GetHomeworkList, GetHomeworkListJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_PAGE_PARAMS();                                                                                                 //分页参数
		API_DEF_ADD_QUERY_PARAMS(String, "title", ZH_WORDS_GETTER("homework.gethomeworklist.title"), "title", false);              //查询作业的标题
		API_DEF_ADD_QUERY_PARAMS(UInt64, "class_id", ZH_WORDS_GETTER("homework.gethomeworklist.class_id"), 123, false);  //查询哪个班级的作业
		API_DEF_ADD_QUERY_PARAMS(UInt64, "creator", ZH_WORDS_GETTER("homework.gethomeworklist.creator"), 123, false);       //查询作业的发布者/创建人
);
	//定义查询作业列表（条件+分页）处理，GetHomeworkList
	API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "c3-org/backhomework/get-homework-list", GetHomeworkList, QUERIES(QueryParams, queryParams),
		API_HANDLER_QUERY_PARAM(query, GetHomeworkListQuery, queryParams); API_HANDLER_RESP_VO(execGetHomeworkList(query)););

	//定义获取作业详情描述
	// GetHomeworkDetail，获取指定行的详细数据，用于编辑或查看
	//流程中点击，应该是传作业id，返回作业的标题，班级，内容
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("homework.gethomeworkdetail.summary"), GetHomeworkDetail, GetHomeworkDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(UInt64, "id", ZH_WORDS_GETTER("homework.gethomeworkdetail.id"), 1, true);  //查询作业，必须传作业id
	);
	//定义获取作业描述处理，GetHomeworkDetail
	API_HANDLER_ENDPOINT_AUTH("GET", "c3-org/backhomework/get-homework-detail", GetHomeworkDetail, QUERY(UInt64, id), execGetHomeworkDetail(id));

	//定义保存作业描述，SaveHomework
	//新增不用上传唯一id，修改要上传唯一id
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("homework.savehomework.summary"), SaveHomework, SaveHomeworkJsonVO::Wrapper, API_TAG,);
	//定义保存作业处理，SaveHomework
	API_HANDLER_ENDPOINT_AUTH("POST", "c3-org/backhomework/save-homework", SaveHomework, BODY_DTO(SaveHomeworkDTO::Wrapper, dto), execSaveHomework(dto, authObject->getPayload()));

	// 删除作业
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("Homework.delHomework"), DeleteHomework, ListJsonVO<String>::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "c3-org/backhomework/del-homework", DeleteHomework, BODY_DTO(DeleteHomework::Wrapper, dto), executeDelHomework(dto));

private:	//定义接口执行函数
	// 执行函数：作业列表
	GetHomeworkListJsonVO::Wrapper execGetHomeworkList(const GetHomeworkListQuery::Wrapper& query);
	//获取作业详情
	GetHomeworkDetailJsonVO::Wrapper execGetHomeworkDetail(UInt64 id);
	//保存作业
	StringJsonVO::Wrapper execSaveHomework(const SaveHomeworkDTO::Wrapper& dto, const PayloadDTO& payload);
	// 删除作业
	ListJsonVO<String>::Wrapper executeDelHomework(const DeleteHomework::Wrapper& dto);
};

#include OATPP_CODEGEN_END(ApiController)
#undef API_TAG
#endif //__HOMEWORK_H__