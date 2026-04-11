#pragma once
#ifndef ENROLLMENTDTO_H
#define ENROLLMENTDTO_H
#include"../../GlobalInclude.h"
#include OATPP_CODEGEN_BEGIN(DTO)
/*
* 保存报名数据传输对象
*/
class EnrollDTO : public oatpp::DTO
{
	DTO_INIT(EnrollDTO, DTO);
	DTO_FIELD(Int32, studentId);
	DTO_FIELD_INFO(studentId) {
		info->description = ZH_WORDS_GETTER("enrollment.field.studentId");
	}
	DTO_FIELD(Int32, courseId);
	DTO_FIELD_INFO(courseId) {
		info->description = ZH_WORDS_GETTER("enrollment.field.courseId");
	}
	DTO_FIELD(String, paidCourseAmount);
	DTO_FIELD_INFO(paidCourseAmount) {
		info->description = ZH_WORDS_GETTER("enrollment.field.paidCourseAmount");
	}
	DTO_FIELD(String, courseAmount);
	DTO_FIELD_INFO(courseAmount) {
		info->description = ZH_WORDS_GETTER("enrollment.field.courseAmount");
	}
	DTO_FIELD(Int32, OrgId);
	DTO_FIELD_INFO(OrgId) {
		info->description = ZH_WORDS_GETTER("enrollment.field.OrgId");
	}
	DTO_FIELD(Int32, Operator);
	DTO_FIELD_INFO(Operator) {
		info->description = ZH_WORDS_GETTER("enrollment.field.Operator");
	}
	CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
public:
	std::string validate() {
		std::string errorMsg;
		if (studentId <= 0) {
			errorMsg += ZH_WORDS_GETTER("enrollment.validate.studentId") + ";";
		}
		if (courseId <= 0) {
			errorMsg += ZH_WORDS_GETTER("enrollment.validate.courseId") + ";";
		}
		return errorMsg;
	}
	
};
 class EnrollmentSaveDTO : public oatpp::DTO {

	 DTO_INIT(EnrollmentSaveDTO, DTO);
	 //学生编号
	 DTO_FIELD(Int32, studentId);
	 DTO_FIELD_INFO(studentId) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.studentId");
	 }
	 DTO_FIELD(Int32, courseId);
	 DTO_FIELD_INFO(courseId) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.courseId");
	 }
	 DTO_FIELD(Int32, subjectId);
	 DTO_FIELD_INFO(subjectId) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.subjectId");
	 }
	 DTO_FIELD(String, startDate);
	 DTO_FIELD_INFO(startDate) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.startDate");
	 }
	 DTO_FIELD(String, expireDate);
	 DTO_FIELD_INFO(expireDate) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.expireDate");
	 }
	 DTO_FIELD(String, remark);
	 DTO_FIELD_INFO(remark) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.remark");
	 }
	 DTO_FIELD(Int32, countLessonTotal);
	 DTO_FIELD_INFO(countLessonTotal) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.countLessonTotal");
	 }
	 DTO_FIELD(Int32, countLessonCompete);
	 DTO_FIELD_INFO(countLessonCompete) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.countLessonCompete");
	 }
	 DTO_FIELD(Int32, countLessonRefund);
	 DTO_FIELD_INFO(countLessonRefund) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.countLessonRefund");
	 }
	 DTO_FIELD(String, courseAmount);
	 DTO_FIELD_INFO(courseAmount) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.courseAmount");
	 }
	 DTO_FIELD(String, discountCourseAmount);
	 DTO_FIELD_INFO(discountCourseAmount) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.discountCourseAmount");
	 }
	 DTO_FIELD(String, paidCourseAmount);
	 DTO_FIELD_INFO(paidCourseAmount) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.paidCourseAmount");
	 }
	 DTO_FIELD(Int32, payOff);
	 DTO_FIELD_INFO(payOff) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.payOff");
	 }
	 DTO_FIELD(Int32, Operator);
	 DTO_FIELD_INFO(Operator) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.Operator");
	 }
	 DTO_FIELD(Int32, Creator);
	 DTO_FIELD_INFO(Creator) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.Creator");
	 }
	 DTO_FIELD(String, AddTime);
	 DTO_FIELD_INFO(AddTime) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.AddTime");
	 }
	 DTO_FIELD(Int32, Editor);
	 DTO_FIELD_INFO(Editor) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.Editor");
	 }
	 DTO_FIELD(String, EditTime);
	 DTO_FIELD_INFO(EditTime) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.EditTime");
	 }
	 DTO_FIELD(Int32, Deleted);
	 DTO_FIELD_INFO(Deleted) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.Deleted");
	 }
	 DTO_FIELD(Int32, VerifyState);
	 DTO_FIELD_INFO(VerifyState) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.VerifyState");
	 }
	 DTO_FIELD(String, WarningTimes);
	 DTO_FIELD_INFO(WarningTimes) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.WarningTimes");
	 }
	 DTO_FIELD(Int32, Priority);
	 DTO_FIELD_INFO(Priority) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.Priority");
	 }
	 DTO_FIELD(Int32, UnitPrice);
	 DTO_FIELD_INFO(UnitPrice) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.UnitPrice");
	 }
	 DTO_FIELD(Int32, FromTrial);
	 DTO_FIELD_INFO(FromTrial) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.FromTrial");
	 }
	 DTO_FIELD(Int32, OrgId);
	 DTO_FIELD_INFO(OrgId) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.OrgId");
	 }
	 CC_SYNTHESIZE(const PayloadDTO*, _payload, Payload);
	 public:
		 std::string validate() {
			 std::string errorMsg;
			 if (studentId <= 0) {
				 errorMsg += ZH_WORDS_GETTER("enrollment.validate.studentId") + ";";
			 }
			 if (courseId <= 0) {
				 errorMsg += ZH_WORDS_GETTER("enrollment.validate.courseId") + ";";
			 }
			 if (subjectId <= 0) {
				 errorMsg += ZH_WORDS_GETTER("enrollment.validate.subjectId") + ";";
			 }
			 //其他字段的校验逻辑
			 return errorMsg;
		 }
};
 /*
 * 报名数据传输对象
 */
 class EnrollmentDTO : public EnrollmentSaveDTO
 {
	 DTO_INIT(EnrollmentDTO, EnrollmentSaveDTO);
	 DTO_FIELD(Int32, id);
	 DTO_FIELD_INFO(id) {
		 info->description = ZH_WORDS_GETTER("enrollment.field.id");
	 }
 };
#include OATPP_CODEGEN_END(DTO)
#endif // ENROLLMENTDTO_H