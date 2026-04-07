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
#ifndef _REGISTRECORDDTO_H_
#define _REGISTRECORDDTO_H_
#include "domain/GlobalInclude.h" 
#include "domain/do/AddStudent/refund/RefundDO.h"

#include OATPP_CODEGEN_BEGIN(DTO)

class RegistRecordDTO : public oatpp::DTO
{
    // 关键：必须初始化 DTO
    DTO_INIT(RegistRecordDTO, DTO);
    DTO_FIELD(Int64, id);
    DTO_FIELD_INFO(id) {
        info->description = ZH_WORDS_GETTER("translation.id");
    }
    DTO_FIELD(String, studentName);
    DTO_FIELD_INFO(studentName) {
        info->description = ZH_WORDS_GETTER("translation.studentName");
    }
    DTO_FIELD(String, courseName);
    DTO_FIELD_INFO(courseName) {
        info->description = ZH_WORDS_GETTER("translation.courseName");
    }
    DTO_FIELD(String, subjectName);
    DTO_FIELD_INFO(subjectName) {
        info->description = ZH_WORDS_GETTER("translation.subjectName");
    }
    DTO_FIELD(String, startDate);
    DTO_FIELD_INFO(startDate) {
        info->description = ZH_WORDS_GETTER("translation.startDate");
    }
    DTO_FIELD(Float64, courseAmount);
    DTO_FIELD_INFO(courseAmount) {
        info->description = ZH_WORDS_GETTER("translation.courseAmount");
    }
    DTO_FIELD(Float64, discountAmount);
    DTO_FIELD_INFO(discountAmount) {
        info->description = ZH_WORDS_GETTER("translation.discountAmount");
    }
    DTO_FIELD(Float64, paidAmount);
    DTO_FIELD_INFO(paidAmount) {
        info->description = ZH_WORDS_GETTER("translation.paidAmount");
    }
    DTO_FIELD(Float64, debt);
    DTO_FIELD_INFO(debt) {
        info->description = ZH_WORDS_GETTER("translation.debt");
    }
    DTO_FIELD(String, expireDate);
    DTO_FIELD_INFO(expireDate) {
        info->description = ZH_WORDS_GETTER("translation.expireDate");
    }
    DTO_FIELD(String, addTime);
    DTO_FIELD_INFO(addTime) {
        info->description = ZH_WORDS_GETTER("translation.addTime");

    }
    DTO_FIELD(String, remark);
    DTO_FIELD_INFO(remark) {
        info->description = ZH_WORDS_GETTER("translation.remark");
    }
    DTO_FIELD(Int32, countLessonTotal);
    DTO_FIELD_INFO(countLessonTotal) {
        info->description = ZH_WORDS_GETTER("translation.countLessonTotal");
    }
    DTO_FIELD(Int32, countLessonComplete);
    DTO_FIELD_INFO(countLessonComplete) {
        info->description = ZH_WORDS_GETTER("translation.countLessonComplete");
    }
    DTO_FIELD(Int32, remainingCount);
    DTO_FIELD_INFO(remainingCount) {
        info->description = ZH_WORDS_GETTER("translation.remainingCount");
    }
    //refund表字段
    DTO_FIELD(Float64, refundAmount);
    DTO_FIELD_INFO(refundAmount) {
        info->description = ZH_WORDS_GETTER("translation.refundAmount");
    }
    DTO_FIELD(Int32, refundLessonCount);
    DTO_FIELD_INFO(refundLessonCount) {
        info->description = ZH_WORDS_GETTER("translation.refundLessonCount");
    }
    // 关联一个PayloadDTO负载数据对象
    CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);

public:

};

/**
 * 分页传输对象
 */
class RegistRecordPageDTO : public PageDTO<RegistRecordDTO::Wrapper>
{
    DTO_INIT(RegistRecordPageDTO, PageDTO<RegistRecordDTO::Wrapper>);
};

#include OATPP_CODEGEN_END(DTO)
#endif // !_REGISTRECORDDTO_H_