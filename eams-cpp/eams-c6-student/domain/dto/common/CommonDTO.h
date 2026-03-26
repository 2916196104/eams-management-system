#pragma once
#ifndef CommonDTO_h
#define CommonDTO_h
#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)
class StudentAddDTO : public oatpp::DTO {
	DTO_INIT(StudentAddDTO, DTO);
	API_DTO_FIELD_DEFAULT(String, picturePath, ZH_WORDS_GETTER("common.field.student.picture-path"));
	API_DTO_FIELD_DEFAULT(String, name, ZH_WORDS_GETTER("common.field.student.name"));
	API_DTO_FIELD_DEFAULT(String, phone, ZH_WORDS_GETTER("common.field.student.phone"));
	API_DTO_FIELD_DEFAULT(Int32, leftCourseCount, ZH_WORDS_GETTER("common.field.student.left-course-count"));
	API_DTO_FIELD_DEFAULT(Int32, leftPoints, ZH_WORDS_GETTER("common.field.student.left-points"));
	API_DTO_FIELD_DEFAULT(Int32, stage, ZH_WORDS_GETTER("common.field.student.stage"));
	API_DTO_FIELD_DEFAULT(Int32, sex, ZH_WORDS_GETTER("common.field.student.sex"));
	API_DTO_FIELD_DEFAULT(Int32, age, ZH_WORDS_GETTER("common.field.student.age"));
	API_DTO_FIELD_DEFAULT(String, birthday, ZH_WORDS_GETTER("common.field.student.birthday"));
	API_DTO_FIELD_DEFAULT(String, identificationNumber, ZH_WORDS_GETTER("common.field.student.identification-number"));
	API_DTO_FIELD_DEFAULT(String, parentName, ZH_WORDS_GETTER("common.field.student.parent-name"));
	API_DTO_FIELD_DEFAULT(Int32, relationType, ZH_WORDS_GETTER("common.field.student.relation-type"));
	API_DTO_FIELD_DEFAULT(Int32, grade, ZH_WORDS_GETTER("common.field.student.grade"));
	API_DTO_FIELD_DEFAULT(String, enterTime, ZH_WORDS_GETTER("common.field.student.enter-time"));
	API_DTO_FIELD_DEFAULT(String, accurateEnterTime, ZH_WORDS_GETTER("common.field.student.accurate-enter-time"));
	API_DTO_FIELD_DEFAULT(String, note, ZH_WORDS_GETTER("common.field.student.note"));
	API_DTO_FIELD_DEFAULT(Int32, courseProgress, ZH_WORDS_GETTER("common.field.student.course-progress"));
};
class StudentDTO :public StudentAddDTO {
	DTO_INIT(StudentDTO, StudentAddDTO);
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.student.id"));
};
class ModifyStudentHeadImgDTO :public oatpp::DTO {
	DTO_INIT(ModifyStudentHeadImgDTO, DTO);
	API_DTO_FIELD_DEFAULT(Int64, id, ZH_WORDS_GETTER("common.field.student.id"));
	API_DTO_FIELD_DEFAULT(String, picturePath, ZH_WORDS_GETTER("common.field.student.picture-path"));
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







/**
 * 调整积分DTO
 */
class ModifyPointsDTO : public oatpp::DTO
{
	DTO_INIT(ModifyPointsDTO, DTO);
	//id
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.student.id"));
	// 调整积分数
	API_DTO_FIELD_DEFAULT(String, modify_points, ZH_WORDS_GETTER("common.field.student.modify-points"));
	// 调整原因
	API_DTO_FIELD_DEFAULT(String, modify_reason, ZH_WORDS_GETTER("common.field.student.modify-reason"));
	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:

};






/**
 * 添加跟进记录
 */
class AddFollowUpRecordDTO : public oatpp::DTO
{
	DTO_INIT(AddFollowUpRecordDTO, DTO);
	//id
	API_DTO_FIELD_DEFAULT(Int32, id, ZH_WORDS_GETTER("common.field.student.id"));
	// 跟进阶段
	API_DTO_FIELD_DEFAULT(String, follow_up_stage, ZH_WORDS_GETTER("common.field.student.follow-up-stage"));
	//联系途径
	API_DTO_FIELD_DEFAULT(String, contact_channel, ZH_WORDS_GETTER("common.field.student.contact-channel"));
	//联系时间
	API_DTO_FIELD_DEFAULT(String, contact_time, ZH_WORDS_GETTER("common.field.student.contact-time"));
	//下次联系时间
	API_DTO_FIELD_DEFAULT(String, next_contact_time, ZH_WORDS_GETTER("common.field.student.next-contact-time"));
	//联系方式
	API_DTO_FIELD_DEFAULT(String, contact_way, ZH_WORDS_GETTER("common.field.student.contact-way"));
	//跟进内容
	API_DTO_FIELD_DEFAULT(String, follow_up_content, ZH_WORDS_GETTER("common.field.student.follow-up-content"));

	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:

};






/**
 * 查询跟进记录DTO
 */
class QueryDTO : public oatpp::DTO
{
	DTO_INIT(QueryDTO, DTO);
	// 跟进时间
	API_DTO_FIELD_DEFAULT(String, follow_up_time, ZH_WORDS_GETTER("common.field.student.follow-up-time"));
	//跟进人
	API_DTO_FIELD_DEFAULT(String, follow_up_person, ZH_WORDS_GETTER("common.field.student.follow-up-person"));
	//客户
	API_DTO_FIELD_DEFAULT(String, customer, ZH_WORDS_GETTER("common.field.student.customer"));
	//阶段
	API_DTO_FIELD_DEFAULT(String, follow_up_stage, ZH_WORDS_GETTER("common.field.student.follow-up-stage"));
	//跟进方式
	API_DTO_FIELD_DEFAULT(String, follow_up_way, ZH_WORDS_GETTER("common.field.student.follow-up-way"));
	//下次跟进时间
	API_DTO_FIELD_DEFAULT(String, next_follow_up_time, ZH_WORDS_GETTER("common.field.student.next-follow-up-time"));
	//记录时间
	API_DTO_FIELD_DEFAULT(String, record_time, ZH_WORDS_GETTER("common.field.student.record-time"));
	//跟进内容
	API_DTO_FIELD_DEFAULT(String, follow_up_content, ZH_WORDS_GETTER("common.field.student.follow-up-content"));


	// 关联一个PayloadDTO负载数据对象
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:

}; class QueryFollowUprecordsDTO : public PageDTO<QueryDTO::Wrapper>
{
	DTO_INIT(QueryFollowUprecordsDTO, PageDTO<QueryDTO::Wrapper>);
};




#include OATPP_CODEGEN_END(DTO)
#endif