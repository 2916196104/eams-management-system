#pragma once
#ifndef _CHECK_IN_DTO_H
#define _CHECK_IN_DTO_H
#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class CheckInDTO :public oatpp::DTO {
    DTO_INIT(CheckInDTO, DTO);

    DTO_FIELD(Int32, courseId);
    DTO_FIELD_INFO(courseId) {
        info->description = ZH_WORDS_GETTER("CheckIn.field.courseId");
    }
    
    DTO_FIELD(String, courseType);
    DTO_FIELD_INFO(courseType) {
        info->description = ZH_WORDS_GETTER("CheckIn.field.courseType");
    }

    DTO_FIELD(String, courseName);
    DTO_FIELD_INFO(courseName) {
        info->description = ZH_WORDS_GETTER("CheckIn.field.courseName");
    }

    DTO_FIELD(String, teacher);
    DTO_FIELD_INFO(teacher) {
        info->description = ZH_WORDS_GETTER("CheckIn.field.teacher");
    }

    DTO_FIELD(String, classRoom);
    DTO_FIELD_INFO(classRoom) {
        info->description = ZH_WORDS_GETTER("CheckIn.field.classRoom");
    }

    DTO_FIELD(String, timeRange);
    DTO_FIELD_INFO(timeRange) {
        info->description = ZH_WORDS_GETTER("CheckIn.field.timeRange");
    }

    DTO_FIELD(String, status);
    DTO_FIELD_INFO(status) {
        info->description = ZH_WORDS_GETTER("CheckIn.field.status");
    }

    DTO_FIELD(String, userSignStatus);
    DTO_FIELD_INFO(userSignStatus) {
        info->description = ZH_WORDS_GETTER("CheckIn.field.userSignStatus");
    }
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
};

#include OATPP_CODEGEN_END(DTO)
#endif 

