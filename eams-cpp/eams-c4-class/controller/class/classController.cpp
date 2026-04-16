#include"classController.h"
#include"../../dao/class/ClassDetailDAO.h"
#include"../../service/class/ClassDetailService.h"
#include"stdafx.h"

ClassDetailJsonVO::Wrapper ClassController::execClassDetail(const String &id)
{
	auto result = ClassDetailService().getClassDetail(id);
	auto Jvo = ClassDetailJsonVO::createShared();
	Jvo->success(result);
	return Jvo;
}