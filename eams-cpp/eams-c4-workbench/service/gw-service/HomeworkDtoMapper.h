#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
*/
#ifndef _HOMEWORK_DTO_MAPPER_H_
#define _HOMEWORK_DTO_MAPPER_H_

#include <list>
#include <string>

#include "domain/dto/gw-dto/CommonResponseDTO.h"
#include "dao/gw-dao/HomeworkQueryRow.h"

/**
 * 查询行 / 领域数据 → 前端 DTO（对齐 arch-demo 中 TreeMenuMapper：objectMapper 式转换）
 */
class HomeworkDtoMapper {
public:
	static oatpp::Object<HomeworkListRowDTO> toListRow(const HomeworkPublishedRow& row, int32_t submitCount);
	static oatpp::Object<HomeworkSubmitRecordDTO> toSubmitRecord(const HomeworkRecordRow& row);
	static void fillDetail(const oatpp::Object<HomeworkDetailDataDTO>& data, const HomeworkDetailRow& row,
		const std::list<HomeworkRecordRow>& records, const std::string& attachmentHint);
};

#endif // !_HOMEWORK_DTO_MAPPER_H_
