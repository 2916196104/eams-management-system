#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
*/
#ifndef _HOMEWORK_SERVICE_H_
#define _HOMEWORK_SERVICE_H_

#include <cstdint>
#include <memory>
#include <string>

#include "CustomerAuthorizeHandler.h"
#include "domain/dto/gw-dto/CommonResponseDTO.h"

/**
 * 作业业务服务（对齐 arch-demo MenuService：编排 DAO + DTO 转换）
 */
class HomeworkService {
public:
	HomeworkListPageJsonVO::Wrapper getHomeworkList(const std::shared_ptr<CustomerAuthorizeObject>& auth,
		const std::string& adminId, const std::string& classId, int32_t page, int32_t size);

	HomeworkDetailJsonVO::Wrapper getHomeworkDetail(const std::shared_ptr<CustomerAuthorizeObject>& auth,
		const std::string& homeworkId, const std::string& adminId);

	HomeworkAddJsonVO::Wrapper addHomework(const std::shared_ptr<CustomerAuthorizeObject>& auth,
		const std::string& bodyJson);

	HomeworkCommentJsonVO::Wrapper commentHomework(const std::shared_ptr<CustomerAuthorizeObject>& auth,
		const std::string& bodyJson);
};

#endif // !_HOMEWORK_SERVICE_H_
