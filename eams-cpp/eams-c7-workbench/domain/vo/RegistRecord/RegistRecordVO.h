#pragma once
/*
 Copyright Zero One Star. All rights reserved.

 @Author: awei
 @Date: 2022/10/25 11:34:14

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
#ifndef _REGISTRECORDVO_H_
#define _REGISTRECORDVO_H_

#include "domain/GlobalInclude.h"
#include "domain/dto/RegistRecord/RegistRecordDTO.h"
#include OATPP_CODEGEN_BEGIN(DTO)


/**
 * 示例显示JsonVO，用于响应给客户端的Json对象
 */
class RegistRecordJsonVO : public JsonVO<RegistRecordDTO::Wrapper> {
    DTO_INIT(RegistRecordJsonVO, JsonVO<RegistRecordDTO::Wrapper>);

    DTO_FIELD(Int64, id);
    DTO_FIELD_INFO(id) { info->description = ZH_WORDS_GETTER("translation.id"); }

    DTO_FIELD(String, studentName);
    DTO_FIELD_INFO(studentName) { info->description = ZH_WORDS_GETTER("translation.studentName"); }

    DTO_FIELD(String, courseName);
    DTO_FIELD_INFO(courseName) { info->description = ZH_WORDS_GETTER("translation.courseName"); }

    DTO_FIELD(String, subjectName);
    DTO_FIELD_INFO(subjectName) { info->description = ZH_WORDS_GETTER("translation.subjectName"); }

    DTO_FIELD(String, startDate);
    DTO_FIELD_INFO(startDate) { info->description = ZH_WORDS_GETTER("translation.startDate"); }

    DTO_FIELD(Float64, courseAmount);
    DTO_FIELD_INFO(courseAmount) { info->description = ZH_WORDS_GETTER("translation.courseAmount"); }

    DTO_FIELD(Float64, discountAmount);
    DTO_FIELD_INFO(discountAmount) { info->description = ZH_WORDS_GETTER("translation.discountAmount"); }

    DTO_FIELD(Float64, paidAmount);
    DTO_FIELD_INFO(paidAmount) { info->description = ZH_WORDS_GETTER("translation.paidAmount"); }

    DTO_FIELD(Float64, debt);
    DTO_FIELD_INFO(debt) { info->description = ZH_WORDS_GETTER("translation.debt"); }

    DTO_FIELD(String, expireDate);
    DTO_FIELD_INFO(expireDate) { info->description = ZH_WORDS_GETTER("translation.expireDate"); }

    DTO_FIELD(String, addTime);
    DTO_FIELD_INFO(addTime) { info->description = ZH_WORDS_GETTER("translation.addTime"); }

    DTO_FIELD(String, remark);
    DTO_FIELD_INFO(remark) { info->description = ZH_WORDS_GETTER("translation.remark"); }

    DTO_FIELD(Int32, countLessonTotal);
    DTO_FIELD_INFO(countLessonTotal) { info->description = ZH_WORDS_GETTER("translation.countLessonTotal"); }

    DTO_FIELD(Int32, countLessonComplete);
    DTO_FIELD_INFO(countLessonComplete) { info->description = ZH_WORDS_GETTER("translation.countLessonComplete"); }

    DTO_FIELD(Int32, remainingCount);
    DTO_FIELD_INFO(remainingCount) { info->description = ZH_WORDS_GETTER("translation.remainingCount"); }

    DTO_FIELD(Float64, refundAmount);
    DTO_FIELD_INFO(refundAmount) { info->description = ZH_WORDS_GETTER("translation.refundAmount"); }

    DTO_FIELD(Int32, refundLessonCount);
    DTO_FIELD_INFO(refundLessonCount) { info->description = ZH_WORDS_GETTER("translation.refundLessonCount"); }
};

/**
 * 示例分页显示JsonVO，用于响应给客户端的Json对象
 */
class RegistRecordPageJsonVO : public JsonVO<RegistRecordPageDTO::Wrapper> {
    DTO_INIT(RegistRecordPageJsonVO, JsonVO<RegistRecordPageDTO::Wrapper>);
};


#include OATPP_CODEGEN_END(DTO)

#endif // !_SAMPLE_VO_
