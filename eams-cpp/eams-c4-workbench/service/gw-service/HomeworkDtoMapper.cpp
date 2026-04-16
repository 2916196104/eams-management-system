/*
 Copyright Zero One Star. All rights reserved.

 Licensed under the Apache License, Version 2.0 (the "License");
*/
#include "stdafx.h"
#include "service/gw-service/HomeworkDtoMapper.h"

oatpp::Object<HomeworkListRowDTO> HomeworkDtoMapper::toListRow(const HomeworkPublishedRow& row, int32_t submitCount) {
	auto dto = HomeworkListRowDTO::createShared();
	dto->homework_id = oatpp::String(std::to_string(row.id).c_str());
	dto->title = oatpp::String(row.title.c_str());
	dto->class_name = oatpp::String(row.className.c_str());
	dto->submit_count = submitCount;
	dto->create_time = oatpp::String(row.addTime.c_str());
	return dto;
}

oatpp::Object<HomeworkSubmitRecordDTO> HomeworkDtoMapper::toSubmitRecord(const HomeworkRecordRow& row) {
	auto dto = HomeworkSubmitRecordDTO::createShared();
	dto->record_id = oatpp::String(row.id.c_str());
	dto->student_id = oatpp::String(row.studentId.c_str());
	dto->submit_content = oatpp::String(row.content.c_str());
	dto->submit_time = oatpp::String(row.addTime.c_str());
	dto->score = row.score;
	dto->comment = oatpp::String(row.comment.c_str());
	dto->comment_time = oatpp::String(row.commentTime.c_str());
	dto->comment_teacher = oatpp::String(row.commentTeacher.c_str());
	return dto;
}

void HomeworkDtoMapper::fillDetail(const oatpp::Object<HomeworkDetailDataDTO>& data, const HomeworkDetailRow& row,
	const std::list<HomeworkRecordRow>& records, const std::string& attachmentHint) {
	data->homework_id = oatpp::String(std::to_string(row.id).c_str());
	data->title = oatpp::String(row.title.c_str());
	data->class_name = oatpp::String(row.className.c_str());
	data->class_id = oatpp::String(std::to_string(row.classId).c_str());
	data->content = oatpp::String(row.content.c_str());
	data->create_time = oatpp::String(row.addTime.c_str());
	data->attachment = oatpp::String(attachmentHint.c_str());
	auto lst = oatpp::List<oatpp::Object<HomeworkSubmitRecordDTO>>::createShared();
	for (const auto& r : records) {
		lst->push_back(toSubmitRecord(r));
	}
	data->submit_list = lst;
}
