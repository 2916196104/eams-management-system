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
#include "../../domain/GlobalInclude.h" 

#include OATPP_CODEGEN_BEGIN(DTO)

class AddStudentDTO : public oatpp::DTO
{
    // 关键：必须初始化 DTO
    DTO_INIT(AddStudentDTO, DTO);

public:
    //// 示例字段（根据您的注释补齐）
    //DTO_FIELD(String, name);
    //DTO_FIELD(String, phonenumber);
    //DTO_FIELD(String, type);
    //DTO_FIELD(String, sex);
};
#include OATPP_CODEGEN_END(DTO)
#endif // _ADDSTUDENTDTO_H_