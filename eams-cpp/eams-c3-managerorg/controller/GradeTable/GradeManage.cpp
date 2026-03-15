#include "GradeManage.h"
#include "stdafx.h"

//3.4 声明了要实现

GradeManagePageJsonVO::Wrapper GradeManage::execQueryPageScore(const GradeManageQuery::Wrapper& query)
{
	return {};
}

Uint64JsonVO::Wrapper GradeManage::execSave(const GradeManageDTO::Wrapper& dto, const const PayloadDTO& payload)
{
	return {};
}
ListJsonVO<String>::Wrapper GradeManage::execRemove(const List<String>& ids)
{
	return {};
}

StringJsonVO::Wrapper  GradeManage::execImportScore(const std::shared_ptr<IncomingRequest>& request, const PayloadDTO& payload)
{
	return {};
}