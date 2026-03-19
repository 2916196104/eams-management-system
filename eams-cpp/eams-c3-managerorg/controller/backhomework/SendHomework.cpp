#include "stdafx.h"
#include "SendHomework.h"

oatpp::List<BackhomeworkVO::Wrapper> SendHomework::executeGetHomeworkList(const BackhomeworkQuery::Wrapper& query)
{
	(void)query; // TODO: 填充获取作业列表逻辑
	return oatpp::List<BackhomeworkVO::Wrapper>::createShared();
}

StringJsonVO::Wrapper SendHomework::executeReviewHomework(const ReviewHomework::Wrapper& req)
{
	(void)req; // TODO: 填充提交点评逻辑
	auto rsp = StringJsonVO::createShared();
	rsp->success("ok");
	return rsp;
}

