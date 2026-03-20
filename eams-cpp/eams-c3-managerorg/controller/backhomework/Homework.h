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
	//流程中显示有 作业标题，班级，发布者，提交量，页码
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("homework.gethomeworklist.summary"), GetHomeworkList, GetHomeworkListPageJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_PAGE_PARAMS();                                                                                                 //分页参数
		API_DEF_ADD_QUERY_PARAMS(String, "title", ZH_WORDS_GETTER("homework.gethomeworklist.title"), "title", false);              //查询作业的标题
		API_DEF_ADD_QUERY_PARAMS(String, "classname", ZH_WORDS_GETTER("homework.gethomeworklist.classname"), "classname", true);  //查询哪个班级的作业
		API_DEF_ADD_QUERY_PARAMS(String, "publisher", ZH_WORDS_GETTER("homework.gethomeworklist.publisher"), "publisher", false);  //查询作业的发布者
);
	//定义查询作业列表（条件+分页）处理，GetHomeworkList
	API_HANDLER_ENDPOINT_AUTH("GET", "org/backhomework/get-homework-list", GetHomeworkList, QUERY(String, title), execGetHomeworkList(title));
	//API_HANDLER_ENDPOINT_OPTION_AUTH(API_M_GET, "/c3/GetHomeworkList", GetHomeworkList, QUERIES(QueryParams, GetHomeworkListQuery),
	//API_HANDLER_QUERY_PARAM(query, SampleQuery, queryParams); return execExportSample(query););


	//定义获取作业详情描述
	// GetHomeworkDetail，获取指定行的详细数据，用于编辑或查看
	//流程中显示有 选择班级 选择作业标题 作业内容
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("homework.gethomeworkdetail.summary"), GetHomeworkDetail, GetHomeworkDetailJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "classname", ZH_WORDS_GETTER("homework.gethomeworkdetail.classname"), "classname", true);  //查询哪个班级的作业
		API_DEF_ADD_QUERY_PARAMS(String, "title", ZH_WORDS_GETTER("homework.gethomeworkdetail.title"), "title", true);              //查询作业的标题
	);
	//定义获取作业描述处理，GetHomeworkDetail
	API_HANDLER_ENDPOINT_AUTH("GET", "org/backhomework/get-homework-detail", GetHomeworkDetail, QUERY(String, classname), execGetHomeworkDetail());


	//定义保存作业描述，SaveHomework
	//新增不用上传唯一id，修改要上传唯一id
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("homework.savehomework.summary"), SaveHomework, SaveHomeworkJsonVO::Wrapper, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "id", ZH_WORDS_GETTER("homework.savehomework.id"), "123456", true);
	);
	//定义保存作业处理，SaveHomework
	API_HANDLER_ENDPOINT_AUTH("POST", "org/backhomework/save-homework", SaveHomework, QUERY(String, id), execSaveHomework());

	// 删除作业
	API_DEF_ENDPOINT_INFO_AUTH(ZH_WORDS_GETTER("Homework.delHomework"), DeleteHomework, ListJsonVO<String>::Wrapper, API_TAG);
	API_HANDLER_ENDPOINT_AUTH(API_M_DEL, "org/backhomework/del-homework", DeleteHomework, BODY_DTO(DeleteHomework::Wrapper, dto), executeDelHomework(dto));

private:	//定义接口执行函数
	// 执行函数：作业列表
	GetHomeworkListPageJsonVO::Wrapper execGetHomeworkList(const String& id);

	GetHomeworkDetailJsonVO::Wrapper execGetHomeworkDetail();

	SaveHomeworkJsonVO::Wrapper execSaveHomework();
	// 删除作业
	ListJsonVO<String>::Wrapper executeDelHomework(const DeleteHomework::Wrapper& dto);

};

#include OATPP_CODEGEN_END(ApiController)

#endif //__HOMEWORK_H__