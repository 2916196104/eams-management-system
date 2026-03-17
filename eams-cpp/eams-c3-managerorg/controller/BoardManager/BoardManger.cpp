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
