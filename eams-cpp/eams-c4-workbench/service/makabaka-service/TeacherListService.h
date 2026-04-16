#pragma once
#ifndef _TEACHERLISTSERVICE_H_
#define _TEACHERLISTSERVICE_H_

#include"../../domain/dto/makabaka-dto/teacher/teacherDTO.h"
#include"../../domain/query/makabaka-query/teacher/teacherQuery.h"
#include"../../domain/vo/makabaka-vo/teacher/teacherVO.h"


class TeacherListService {
public:
	//∑÷“≥≤È—Ø
	TeacherPageDTO::Wrapper listAll(const TeacherQuery::Wrapper& query);	
};

#endif // !_TEACHERLISTSERVICE_H_