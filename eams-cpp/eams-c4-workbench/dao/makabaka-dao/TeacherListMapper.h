#pragma once

#ifndef _TEACHERLISTMAPPER_H_
#define _TEACHERLISTMAPPER_H_

#include"Mapper.h"
#include"../../domain/dto/makabaka-dto/teacher/teacherDTO.h"

class TeacherListMapper :public Mapper<TeacherDTO::Wrapper> {
public:
	TeacherDTO::Wrapper mapper(ResultSet* resultSet) const override {
		auto dto = TeacherDTO::createShared();
		std::string id = resultSet->getString("id");
		if (!id.empty()) dto->id = oatpp::String(id);

		std::string name = resultSet->getString("name");
		if (!name.empty()) dto->name = oatpp::String(name);

		std::string position_id = resultSet->getString("position_id");
		if (!position_id.empty()) dto->position_id = oatpp::String(position_id);

		std::string position_name = resultSet->getString("position_name");
		if (!position_id.empty()) dto->position_name = oatpp::String(position_name);
		return dto;
	}
};
#endif // !_TEACHERLISTMAPPER_H_
