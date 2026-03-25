#include "Homework.h"
#include "stdafx.h"
#include "../../domain/vo/backhomework/backhomeworkVO.h"
#include "../../service/backhomework/HomeworkService.h"

//获取作业列表（条件+分页）
GetHomeworkListJsonVO::Wrapper Homework::execGetHomeworkList(const GetHomeworkListQuery::Wrapper& query) {
	//// 查询数据
	//auto result = HomeworkService().gethomeworklist(query);
	//// 响应结果
	//auto jvo = GetHomeworkListJsonVO::createShared();
	//jvo->success("ok");
	//return jvo;
	return {};
}

//获取作业详情
GetHomeworkDetailJsonVO::Wrapper Homework::execGetHomeworkDetail(const string& id) {
	return {};
}

//保存作业
StringJsonVO::Wrapper Homework::execSaveHomework(const SaveHomeworkDTO::Wrapper& dto, const PayloadDTO& payload) {
	return {};
}

ListJsonVO<String>::Wrapper Homework::executeDelHomework(const DeleteHomework::Wrapper& dto)
{
	(void)dto; // TODO: 实现实际删除逻辑

	auto rsp = ListJsonVO<String>::createShared();
	auto emptyData = oatpp::List<String>::createShared(); // 返回空列表占位
	rsp->success(emptyData);                               // success 需要传入列表数据参数
	return rsp;
}