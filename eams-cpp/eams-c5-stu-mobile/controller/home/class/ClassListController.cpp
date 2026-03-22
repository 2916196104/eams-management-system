#include "stdafx.h"
#include "ClassListController.h"
#include "../../../domain/dto/home/class/ClassListDTO.h"
ClassListJsonVO::Wrapper ClassListController::execQueryById(const String& id)
{
	// 定义返回数据对象
	auto jvo = ClassListJsonVO::createShared();
	//响应结果
	return jvo;
}


