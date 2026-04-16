#include "stdafx.h"
#include "BoardManager.h"
#include "service/BoardManager/BoardManagerService.h"

StringJsonVO::Wrapper BoardManager::executeAddBoard(const BoardAddDTO::Wrapper& dto, const PayloadDTO& payload)
{
	
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
	std::string id = std::to_string(BoardService().saveBoard(dto));
	if (id != "") {
		jvo->success(id);
	}
	else
	{
		jvo->fail({});
	}

	return jvo;

}

ListJsonVO<String>::Wrapper BoardManager::execRemoveBoard(const List<String>& ids)
{
	
	// 定义返回数据对象
	auto jvo = ListJsonVO<String>::createShared();
	// 参数校验
	if (ids->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// 执行数据删除
	if (BoardService().removeData(ids)) {
		jvo->success(ids);
	}
	else
	{
		jvo->fail(nullptr);
	}

	return jvo;


}

ListJsonVO<String>::Wrapper BoardManager::execStartBoard(const List<String>& ids, const PayloadDTO& payload)
{
	
	// 定义返回数据对象
	auto jvo = ListJsonVO<String>::createShared();
	// 参数校验
	if (ids->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// 执行数据修改
	BoardUpdateDTO::Wrapper dto = BoardUpdateDTO::createShared();;
	dto->setPayload(&payload);
	if (BoardService().updateData1(ids,dto)) {
		jvo->success(ids);
	}
	else
	{
		jvo->fail(nullptr);
	}

	return jvo;


}

ListJsonVO<String>::Wrapper BoardManager::execEndBoard(const List<String>& ids, const PayloadDTO& payload)
{
	
	// 定义返回数据对象
	auto jvo = ListJsonVO<String>::createShared();
	// 参数校验
	if (ids->empty())
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}
	// 执行数据修改
	BoardUpdateDTO::Wrapper dto;
	dto->setPayload(&payload);
	if (BoardService().updateData2(ids, dto)) {
		jvo->success(ids);
	}
	else
	{
		jvo->fail(nullptr);
	}

	return jvo;


}

// ========== 新增：获取公告列表接口实现 ==========
BoardPageJsonVO::Wrapper BoardManager::execGetBoardList(const BoardQuery::Wrapper& query)
{
	
	// 查询数据
	auto result = BoardService().listAll(query);
	// 响应结果
	auto jvo = BoardPageJsonVO::createShared();
	jvo->success(result);
	return jvo;


}

// ========== 新增：获取公告详情接口实现 ==========
GetBoardDetailJsonVO::Wrapper BoardManager::execGetBoardDetail(const oatpp::String& boardId, const oatpp::String& boardTitle, const oatpp::String& boardType) {
	BoardService service;
	return service.getBoardDetail(boardId, boardTitle, boardType);
}