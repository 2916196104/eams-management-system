#ifndef __TIMETABLE_DTO_H__
#define __TIMETABLE_DTO_H__

#include "../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*课后作业DTO类*/


class TimetableDTO: public oatpp::DTO
{
	DTO_INIT(TimetableDTO, DTO)
};

#include OATPP_CODEGEN_END(DTO)

#endif