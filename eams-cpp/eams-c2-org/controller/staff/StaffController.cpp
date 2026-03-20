#include "stdafx.h"
#include "StaffController.h"



// 头像修改逻辑实现（和executeQueryTest格式一致）
StringJsonVO::Wrapper StaffController::executeModifyAvatar(const AvatarUploadDTO::Wrapper& dto) {
	// 创建响应结果
	auto vo = StringJsonVO::createShared();
	vo->success(ZH_WORDS_GETTER("modifyAvatar.resp"));
	return vo;
}