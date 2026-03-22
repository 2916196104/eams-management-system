#pragma once
#ifndef CommonDTO_h
#define CommonDTO_h
#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class StudentAddDTO : public oatpp::DTO {
	DTO_INIT(StudentAddDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("common.field.student.name"));
	API_DTO_FIELD_DEFAULT(String, phone, ZH_WORDS_GETTER("common.field.student.content"));
	API_DTO_FIELD_DEFAULT(String, picturePath, ZH_WORDS_GETTER("common.field.student.picture-path"));
    API_DTO_FIELD_DEFAULT(Int32, leftCourseCount , ZH_WORDS_GETTER("common.field.student.left-course-count"));
	API_DTO_FIELD_DEFAULT(Int32, leftPoints, ZH_WORDS_GETTER("common.field.student.left-points"));
	API_DTO_FIELD_DEFAULT(Int32, stage, ZH_WORDS_GETTER("common.field.student.stage"));
	API_DTO_FIELD_DEFAULT(Int32, sex, ZH_WORDS_GETTER("common.field.student.sex"));
	API_DTO_FIELD_DEFAULT(Int32, age, ZH_WORDS_GETTER("common.field.student.age"));
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("common.field.student.birthday"));
	API_DTO_FIELD_DEFAULT(String, identificationNumber, ZH_WORDS_GETTER("common.field.student.identification-number"));
	API_DTO_FIELD_DEFAULT(String, parentName, ZH_WORDS_GETTER("common.field.student.parent-name"));
	API_DTO_FIELD_DEFAULT(String, relationType, ZH_WORDS_GETTER("common.field.student.relation-type"));
	API_DTO_FIELD_DEFAULT(Int32, grade, ZH_WORDS_GETTER("common.field.student.grade"));
	API_DTO_FIELD_DEFAULT(String, enterTime, ZH_WORDS_GETTER("common.field.student.enter-time"));
	API_DTO_FIELD_DEFAULT(String, accurateEnterTime, ZH_WORDS_GETTER("common.field.student.accurate-enter-time"));
	API_DTO_FIELD_DEFAULT(String, note, ZH_WORDS_GETTER("common.field.student.note"));
	API_DTO_FIELD_DEFAULT(String, courseProgress, ZH_WORDS_GETTER("common.field.student.course-progress"));
};
class StudentDTO :public StudentAddDTO {
    DTO_INIT(StudentDTO, StudentAddDTO);
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.student.id"));
};
class RegistrationAddDTO : public oatpp::DTO {
	DTO_INIT(RegistrationAddDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, addTime, ZH_WORDS_GETTER("common.field.registration.add-time"));
	API_DTO_FIELD_DEFAULT(String, course, ZH_WORDS_GETTER("common.field.registration.course"));
	API_DTO_FIELD_DEFAULT(String, subject, ZH_WORDS_GETTER("common.field.registration.subject"));
	API_DTO_FIELD_DEFAULT(Int32, buyCount, ZH_WORDS_GETTER("common.field.registration.by-count"));
	API_DTO_FIELD_DEFAULT(Int32, UnitPrice, ZH_WORDS_GETTER("common.field.registration.unit-price"));
	API_DTO_FIELD_DEFAULT(Int32, coursePrice, ZH_WORDS_GETTER("common.field.registration.course-price"));
	API_DTO_FIELD_DEFAULT(Int32, salePrice, ZH_WORDS_GETTER("common.field.registration.sale-price"));
	API_DTO_FIELD_DEFAULT(Int32, realityPrice, ZH_WORDS_GETTER("common.field.registration.reality-price"));
	API_DTO_FIELD_DEFAULT(Int32, arrearage, ZH_WORDS_GETTER("common.field.registration.arrearage"));
	API_DTO_FIELD_DEFAULT(String, beginTime, ZH_WORDS_GETTER("common.field.registration.beginTime"));
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("common.field.registration.endTime"));
	API_DTO_FIELD_DEFAULT(Int32, refundPrice, ZH_WORDS_GETTER("common.field.registration.refund-price"));
	API_DTO_FIELD_DEFAULT(Int32, dropClassCount, ZH_WORDS_GETTER("common.field.registration.drop-class-count"));
	API_DTO_FIELD_DEFAULT(String, refundDescripe, ZH_WORDS_GETTER("common.field.registration.refundDescripe"));
    API_DTO_FIELD_DEFAULT(Int32, refundStatus, ZH_WORDS_GETTER("common.field.registration.refund-status"));
};
class RegistrationDTO :public RegistrationAddDTO {
    DTO_INIT(RegistrationDTO, RegistrationAddDTO);
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.registration.id"));
};
class RegistrationPageDTO : public PageDTO<RegistrationDTO::Wrapper> {
	DTO_INIT(RegistrationPageDTO, PageDTO<RegistrationDTO::Wrapper>);
	
};
class FileOnlyDTO :public oatpp::DTO {
	DTO_INIT(FileOnlyDTO, DTO);
    //API_DTO_FIELD_DEFAULT(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("common.field.file.file"),true);多出第四个参数导致编译错误
	API_DTO_FIELD_REQUIRE(oatpp::swagger::Binary, file, ZH_WORDS_GETTER("common.field.file.file"), true);
};
class CourseCountDTO :public oatpp::DTO {
	DTO_INIT(CourseCountDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, courseName, ZH_WORDS_GETTER("common.field.course.name"));
	API_DTO_FIELD_DEFAULT(Int32, totalCourseCount, ZH_WORDS_GETTER("common.field.course.total"));
	API_DTO_FIELD_DEFAULT(Int32, leftCourseCount, ZH_WORDS_GETTER("common.field.course.left"));
};
class SaveStudentDTO : public oatpp::DTO {
	DTO_INIT(SaveStudentDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, phone, ZH_WORDS_GETTER("common.field.student.phone"));
	API_DTO_FIELD_DEFAULT(String, parentName, ZH_WORDS_GETTER("common.field.student.parent-name"));
	API_DTO_FIELD_DEFAULT(String, relationType, ZH_WORDS_GETTER("common.field.student.relation-type"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("common.field.student.name"));
	API_DTO_FIELD_DEFAULT(Int32, sex, ZH_WORDS_GETTER("common.field.student.sex"));
	API_DTO_FIELD_DEFAULT(String, enterTime, ZH_WORDS_GETTER("common.field.student.enter-time"));
	API_DTO_FIELD_DEFAULT(Int32, grade, ZH_WORDS_GETTER("common.field.student.grade"));
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("common.field.student.birthday"));
	API_DTO_FIELD_DEFAULT(String, identificationNumber, ZH_WORDS_GETTER("common.field.student.identification-number"));
	API_DTO_FIELD_DEFAULT(Int32, source, ZH_WORDS_GETTER("common.field.student.source"));
	API_DTO_FIELD_DEFAULT(String, note, ZH_WORDS_GETTER("common.field.student.note"));
};
class SaveDTO :public SaveStudentDTO {
	DTO_INIT(SaveDTO, SaveStudentDTO);
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.student.id"));
};



class RegistrationApplyDTO : public oatpp::DTO {

	DTO_INIT(RegistrationApplyDTO, DTO);

	// 学生姓名
	API_DTO_FIELD_DEFAULT(String, studentName, ZH_WORDS_GETTER("common.field.student.name"));
	// 选择课程
	API_DTO_FIELD_DEFAULT(String, course, ZH_WORDS_GETTER("common.field.registration.course"));
	// 报名类型
	API_DTO_FIELD_DEFAULT(String, subject, ZH_WORDS_GETTER("common.field.registration.subject"));
	// 开始日期
	API_DTO_FIELD_DEFAULT(String, beginTime, ZH_WORDS_GETTER("common.field.registration.begin-time"));
	// 有效期至
	API_DTO_FIELD_DEFAULT(String, endTime, ZH_WORDS_GETTER("common.field.registration.end-time"));
	// 购买课时数
	API_DTO_FIELD_DEFAULT(Int32, buyCount, ZH_WORDS_GETTER("common.field.registration.by-count"));
	//课程金额
	API_DTO_FIELD_DEFAULT(Int32, coursePrice, ZH_WORDS_GETTER("common.field.registration.course-price"));
	// 实收金额 (用于校验余额)
	API_DTO_FIELD_DEFAULT(Int32, realityPrice, ZH_WORDS_GETTER("common.field.registration.reality-price"));
	//优惠金额
	API_DTO_FIELD_DEFAULT(Int32, salePrice, ZH_WORDS_GETTER("common.field.registration.sale-price"));
	// 收款经手人
	API_DTO_FIELD_DEFAULT(String, handler, "common.field.registration.price-people");
	// 备注
	API_DTO_FIELD_DEFAULT(String, note, ZH_WORDS_GETTER("common.field.student.note"));

};


class StudentStageUpdateDTO : public oatpp::DTO {
	DTO_INIT(StudentStageUpdateDTO, DTO);

	// 学员 ID 列表 (多选项)
	API_DTO_FIELD_DEFAULT(List<String>, ids, ZH_WORDS_GETTER("common.field.student.id"));

	// 目标阶段：1-意向
	API_DTO_FIELD_DEFAULT(Int32, stage1, ZH_WORDS_GETTER("common.field.student.stage"));

};

/**
 * 删除跟进记录请求 DTO
 */
class DeleteContactRecordDTO : public oatpp::DTO {
	DTO_INIT(DeleteContactRecordDTO, DTO);

	// 跟进记录 ID 列表
	API_DTO_FIELD_DEFAULT(List<Int64>, ids, "contact-record.field.ids");
};

#include OATPP_CODEGEN_END(DTO)
#endif