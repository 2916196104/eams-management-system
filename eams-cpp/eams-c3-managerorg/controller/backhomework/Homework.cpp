#include "Homework.h"
#include "stdafx.h"
#include "../../domain/vo/backhomework/backhomeworkVO.h"


GetHomeworkListPageJsonVO::Wrapper Homework::execGetHomeworkList(const GetHomeworkListQuery::Wrapper& query) {
	return {};
}

GetHomeworkDetailJsonVO::Wrapper Homework::execGetHomeworkDetail(const string& id) {
	return {};
}

SaveHomeworkJsonVO::Wrapper Homework::execSaveHomework(const string& id) {
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