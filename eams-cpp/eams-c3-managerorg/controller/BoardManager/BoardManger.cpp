#include "stdafx.h"
#include "BoardManager.h"

StringJsonVO::Wrapper BoardManager::executeAddBoard(const BoardAddDTO::Wrapper& dto, const PayloadDTO& payload)
{
	return {};
}

ListJsonVO<String>::Wrapper BoardManager::execRemoveBoard(const List<String>& ids)
{
	return {};
}

ListJsonVO<String>::Wrapper BoardManager::execStartBoard(const List<String>& ids)
{
	return {};
}

ListJsonVO<String>::Wrapper BoardManager::execEndBoard(const List<String>& ids)
{
	return {};
}

// ========== 新增：获取公告列表接口实现 ==========
ListJsonVO<String>::Wrapper BoardManager::execGetAnnouncementList(const PayloadDTO& payload)
{
	return {};
}

// ========== 新增：获取公告详情接口实现 ==========
StringJsonVO::Wrapper BoardManager::execGetAnnouncementDetail(const String& id, const PayloadDTO& payload)
{
	return {};
}
