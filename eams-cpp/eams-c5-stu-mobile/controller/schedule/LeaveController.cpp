#include"stdafx.h"
#include "LeaveController.h"

StringJsonVO::Wrapper LeaveController::execAddLeave(const LeaveDTO::Wrapper& add)
{
	auto jvo = StringJsonVO::createShared();
	jvo->success("success");

	return jvo;
}
