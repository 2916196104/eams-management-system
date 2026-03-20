#pragma once

#ifndef _STAFFDTO_H_
#define _STAFFDTO_H_

#include "../../GlobalInclude.h"
#include "domain/query/PageQuery.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	员工数据传输对象
 */
class StaffDTO : public oatpp::DTO {
  DTO_INIT(StaffDTO, DTO);
};

// 带班记录查询 DTO
class DutyRecordQueryDTO : public PageQuery {
    DTO_INIT(DutyRecordQueryDTO, PageQuery);

    // 员工ID
    DTO_FIELD(UInt64, employeeId, "employeeId");
    DTO_FIELD_INFO(employeeId) {
        info->description = ZH_WORDS_GETTER("getDutyRecord.param1");
        info->required = false;
    }

    // 带班日期
    DTO_FIELD(oatpp::String, dutyDate, "dutyDate");
    DTO_FIELD_INFO(dutyDate) {
        info->description = ZH_WORDS_GETTER("getDutyRecord.param2");
        info->required = false;
    }
};
#include OATPP_CODEGEN_END(DTO)
#endif // _STAFFDTO_H_
