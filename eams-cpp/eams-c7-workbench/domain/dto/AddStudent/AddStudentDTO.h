#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 10:59:38

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

      https://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
*/
#ifndef _ADDSTUDENTDTO_H_
#define _ADDSTUDENTDTO_H_
#include "domain/GlobalInclude.h" 

#include OATPP_CODEGEN_BEGIN(DTO)

class AddStudentDTO : public oatpp::DTO
{
    // 关键：必须初始化 DTO
    DTO_INIT(AddStudentDTO, DTO);
    DTO_FIELD(String, name);
    DTO_FIELD_INFO(name) {
        info->description = ZH_WORDS_GETTER("translation.field.name");
    }
    DTO_FIELD(String, phonenumber);
    DTO_FIELD_INFO(phonenumber) {
        info->description = ZH_WORDS_GETTER("translation.field.phonenumber");
    }
    DTO_FIELD(Int32, stage);
    DTO_FIELD_INFO(stage) {
        info->description = ZH_WORDS_GETTER("translation.field.stage");
    }
    DTO_FIELD(Int32, gender);
    DTO_FIELD_INFO(gender) {
        info->description = ZH_WORDS_GETTER("translation.field.gender");
    }
    DTO_FIELD(String, birthday);
    DTO_FIELD_INFO(birthday) {
        info->description = ZH_WORDS_GETTER("translation.field.birthday");
    }
    DTO_FIELD(String, idcard);
    DTO_FIELD_INFO(idcard) {
        info->description = ZH_WORDS_GETTER("translation.field.idcard");
    }
    DTO_FIELD(String, remark);
    DTO_FIELD_INFO(remark) {
        info->description = ZH_WORDS_GETTER("translation.tag");
    }
    //pc上的字段
    DTO_FIELD(String, username);
    DTO_FIELD_INFO(username) {
        info->description = ZH_WORDS_GETTER("translation.username");
    }
    DTO_FIELD(Int32, kinship);
    DTO_FIELD_INFO(kinship) {
        info->description = ZH_WORDS_GETTER("translation.kinship");
    }
    DTO_FIELD(String, admitTime);
    DTO_FIELD_INFO(admitTime) {
        info->description = ZH_WORDS_GETTER("translation.admitTime");
    }
    DTO_FIELD(Int32, grade);
    DTO_FIELD_INFO(grade) {
        info->description = ZH_WORDS_GETTER("translation.grade");
    }
    DTO_FIELD(Int64, schoolId);
    DTO_FIELD_INFO(schoolId) {
        info->description = ZH_WORDS_GETTER("translation.schoolId");
    }
    // 关联一个PayloadDTO负载数据对象
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
    //数据校验
    std::string validate() {
        if (!name || name->empty()) {
            return "name invalidate.";
        }
        if (!phonenumber || phonenumber->empty()) {
            return "phonenumber invalidate.";
        }
        return "";
    }
};
#include OATPP_CODEGEN_END(DTO)
#endif // _ADDSTUDENTDTO_H_