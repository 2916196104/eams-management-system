#include "stdafx.h"
#include "BoardManager.h"

StringJsonVO::Wrapper BoardManager::executeAddBoard(const BoardAddDTO::Wrapper& dto, const PayloadDTO& payload)
{
	/*
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	// 参数校验
	std::string errmsg = dto->validate();
	if (errmsg != "")
	{
		jvo->init(errmsg, RS_PARAMS_INVALID);
		return jvo;
	}
	// 执行数据新增
	dto->setPayload(&payload);
	//这里注意要调用的是雪花算法
	std::string id = SampleService().saveData(dto);
	if (id != "") {
		jvo->success(id);
	}
	else
	{
		jvo->fail({});
	}

	return jvo;
	*/
	return {};
}

ListJsonVO<String>::Wrapper BoardManager::execRemoveBoard(const List<String>& ids)
{
	/*
	// 定义返回数据对象
	auto jvo = ListJsonVO<String>::createShared();
	// 参数校验
	if (ids->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// 执行数据删除
	if (SampleService().removeData(ids)) {
		jvo->success(ids);
	}
	else
	{
		jvo->fail(nullptr);
	}

	return jvo;
	*/
	return {};

}

ListJsonVO<String>::Wrapper BoardManager::execStartBoard(const List<String>& ids, const PayloadDTO& payload)
{
	/*
	// 定义返回数据对象
	auto jvo = ListJsonVO<String>::createShared();
	// 参数校验
	if (ids->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// 执行数据修改
	BoardAddDTO::Wrapper dto;
	dto->setPayload(&payload);
	if (SampleService().updateData1(ids,dto)) {
		jvo->success(ids);
	}
	else
	{
		jvo->fail(nullptr);
	}

	return jvo;
	*/
	return {};

}

ListJsonVO<String>::Wrapper BoardManager::execEndBoard(const List<String>& ids, const PayloadDTO& payload)
{
	/*
	// 定义返回数据对象
	auto jvo = ListJsonVO<String>::createShared();
	// 参数校验
	if (ids->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// 执行数据修改
	BoardAddDTO::Wrapper dto;
	dto->setPayload(&payload);
	if (SampleService().updateData2(ids, dto)) {
		jvo->success(ids);
	}
	else
	{
		jvo->fail(nullptr);
	}

	return jvo;
	*/
	return {};

}

// ========== 新增：获取公告列表接口实现 ==========
BoardPageJsonVO::Wrapper BoardManager::execGetBoardList(const BoardQuery::Wrapper& query)
{
	/*
	// 查询数据
	auto result = SampleService().listAll(query);
	// 响应结果
	auto jvo = BoardPageJsonVO::createShared();
	jvo->success(result);
	return jvo;
	*/
	return {};

}

// ========== 新增：获取公告详情接口实现 ==========
GetBoardDetailJsonVO::Wrapper BoardManager::execGetBoardDetail(const oatpp::String& boardId, const oatpp::String& boardTitle, const oatpp::String& boardType)
{
	auto response = GetBoardDetailJsonVO::createShared();
	response->code = 0;
	response->message = "success";
	// 这里需要根据boardId、boardTitle和boardType查询公告详情，暂时返回空数据
	response->data = GetBoardDetailDTO::createShared();
	// 示例数据
	response->data->boardtitle = boardTitle;
	response->data->boardtext = "公告内容示例";
	response->data->boardtype = boardType;
	response->data->boardstatus = "1";
	return response;
}