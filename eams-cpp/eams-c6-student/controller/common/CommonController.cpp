#include "stdafx.h"
#include "CommonController.h"




/**
 * 调整积分执行函数
 */
StringJsonVO::Wrapper CommonController::execModifyPoints(const ModifyPointsDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	// 参数校验
	if (!dto->id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	//// 执行数据修改
	//dto->setPayload(&payload);
	//if (AdjustPointsService().updateData(dto)) {
	//	jvo->success(dto->name);
	//}
	//else
	//{
	//	jvo->fail(dto->name);
	//}
	// 响应结果
	return jvo;
}



/**
 * 添加跟进记录执行函数
 */
StringJsonVO::Wrapper CommonController::execAddFollowUpRecord(const AddFollowUpRecordDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	// 参数校验
	if (!dto->id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行数据修改
	//dto->setPayload(&payload);
	//if (AddFollowUpRecordService().updateData(dto)) {
	//	jvo->success(dto->name);
	//}
	//else
	//{
	//	jvo->fail(dto->name);
	//}
	//// 响应结果
	return jvo;
}

QueryFollowUprecordsJsonVO::Wrapper CommonController::execQueryFollowUprecords(const FollowUprecordsQuery::Wrapper& query)
{
	// 查询数据
	//auto result = SampleService().listAll(query);
	// 响应结果
	auto jvo = QueryFollowUprecordsJsonVO::createShared();
	jvo->success(QueryFollowUprecordsDTO::createShared());
	return jvo;
}
