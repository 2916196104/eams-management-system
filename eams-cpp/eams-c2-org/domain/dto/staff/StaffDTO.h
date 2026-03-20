#pragma once

#ifndef _STAFFDTO_H_
#define _STAFFDTO_H_

#include "../../GlobalInclude.h"

#include OATPP_CODEGEN_BEGIN(DTO)

/*
	员工数据传输对象
 */
class StaffDTO : public oatpp::DTO {
  DTO_INIT(StaffDTO, DTO);
};


//头像上传表单DTO
class AvatarUploadDTO : public oatpp::DTO {
    DTO_INIT(AvatarUploadDTO, DTO);

    // 员工ID
    DTO_FIELD(UInt64, employeeId, "employeeId");
    DTO_FIELD_INFO(employeeId) {
        info->description = ZH_WORDS_GETTER("modifyAvatar.param1");
        info->required = true;
    }

    // 头像文件
    DTO_FIELD(oatpp::String, avatarFile, "avatarFile");
    DTO_FIELD_INFO(avatarFile) {
        info->description = ZH_WORDS_GETTER("modifyAvatar.param2");
        info->required = true;
    }
};

#include OATPP_CODEGEN_END(DTO)
#endif // _STAFFDTO_H_
