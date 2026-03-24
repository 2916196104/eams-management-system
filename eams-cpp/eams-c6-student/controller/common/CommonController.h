#pragma once
#ifndef COMMON_CONTROLLER_H
#define COMMON_CONTROLLER_H
#include "ApiHelper.h"
#include "../../Macros.h"
#include "ServerInfo.h"
#include "domain/vo/BaseJsonVO.h"
#include "domain/vo/common/CommonVO.h"
#include "domain/query/common/CommonQuery.h"
#include "service/common/CommonService.h"

#include OATPP_CODEGEN_BEGIN(ApiController)
#define API_TAG ZH_WORDS_GETTER("common.api-tag")
class CommonController : public oatpp::web::server::api::ApiController {
	API_ACCESS_DECLARE(CommonController);
public: 
	//获取学员详情
	API_DEF_ENDPOINT_INFO_AUTH(
		ZH_WORDS_GETTER("common.interface.get-student-by-id"), 
		getStudentById, StudentJsonVO::Wrapper,
		API_TAG,
		API_DEF_ADD_QUERY_PARAMS(
			String, "id", ZH_WORDS_GETTER("common.field.student.id"), 
			"d934050a8bb373e8f8eed0bf7507ec17", true
		);
	)
	API_HANDLER_ENDPOINT_AUTH(
		API_M_GET,
		"/c3/common/student/get-by-id", 
		getStudentById,
		QUERY(String, id), 
		executeGetStudentById(id)
	);

	//下载学员头像
	API_DEF_ENDPOINT_INFO(
		ZH_WORDS_GETTER("common.interface.download-student-picture"), loadStudentPicturebyPicturePath, Void, API_TAG,
		API_DEF_ADD_QUERY_PARAMS(String, "picturePath", ZH_WORDS_GETTER("common.field.student.picture-path"), "file/test.jpg", true);
	);
	API_HANDLER_ENDPOINT_OPTION(
		API_M_GET, 
		"/c3/common/student/download-student-picture", 
		loadStudentPicturebyPicturePath,
		QUERY(String, picturePath), 
		return executeLoadStudentPicturebyPicturePath(picturePath);
	);

	//修改学员头像
	ENDPOINT_INFO(modifyStudentPicture) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.modify-student-picture"));//添加接口描述
		API_DEF_ADD_PATH_PARAMS(String, "id", ZH_WORDS_GETTER("common.field.student.id"), "123", true);//添加参数
		API_DEF_ADD_FILE_FORM(FileOnlyDTO::Wrapper);
		API_DEF_ADD_RSP_JSON_WRAPPER(StringJsonVO);//添加返回数据包装
	}
    ENDPOINT(API_M_POST, "/c3/common/student/modify-picture/{id}",modifyStudentPicture,PATH(String,id), REQUEST(std::shared_ptr<IncomingRequest>, request), API_HANDLER_AUTH_PARAME) {
		API_HANDLER_RESP_VO(executeModifyStudentPicture(id,request));
	}

	//查询学员报名记录
	ENDPOINT_INFO(queryRegistrationRecordByPage) {
		API_DEF_ADD_AUTH();//添加权限验证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
        API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.query-student-registration-record"));//添加接口描述
		API_DEF_ADD_PAGE_PARAMS();//添加分页参数
		API_DEF_ADD_RSP_JSON_WRAPPER(RegistrationPageJsonVO);//添加返回数据包装
	}
	ENDPOINT(API_M_GET, "/c3/common/registration-recordf/query-by-page", queryRegistrationRecordByPage, QUERIES(QueryParams, queryParams),API_HANDLER_AUTH_PARAME) {
		API_HANDLER_QUERY_PARAM(query, RegistrationPageQuery, queryParams);//获取参数
		API_HANDLER_RESP_VO(executeQueryRegistrationRecordByPage(query));
	}
	// 学员缴欠费
	ENDPOINT_INFO(payFees) {
		API_DEF_ADD_AUTH();//添加权限认证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.pay-fees"));
		API_DEF_ADD_RSP_JSON_WRAPPER(PayFeesJsonVO);
	}
	ENDPOINT(API_M_POST, "/c6/common/student/pay-fees", payFees,BODY_DTO(PayFeesDTO::Wrapper, dto),API_HANDLER_AUTH_PARAME) {

		API_HANDLER_RESP_VO(exePayFees(dto));
	}
	// 学员退费
	ENDPOINT_INFO(refund) {
		API_DEF_ADD_AUTH();//添加权限认证
		API_DEF_ADD_TAG(API_TAG);//将接口添加到分组
		API_DEF_ADD_TITLE(ZH_WORDS_GETTER("common.interface.refund"));
		API_DEF_ADD_RSP_JSON_WRAPPER(RefundJsonVO);
	}
	ENDPOINT(API_M_POST, "/c6/common/student/refund", refund, BODY_DTO(RefundDTO::Wrapper, dto), API_HANDLER_AUTH_PARAME) {

		API_HANDLER_RESP_VO(executeRefund(dto));
	}
private:
	StudentJsonVO::Wrapper executeGetStudentById(const String& id){
		return StudentJsonVO::createShared();
	}
    StringJsonVO::Wrapper executeModifyStudentPicture(const String& id,std::shared_ptr<IncomingRequest>request){
		return StringJsonVO::createShared();
	}
	RegistrationPageJsonVO::Wrapper executeQueryRegistrationRecordByPage(const RegistrationPageQuery::Wrapper& query){
		return RegistrationPageJsonVO::createShared();
	}
	std::shared_ptr<OutgoingResponse> executeLoadStudentPicturebyPicturePath(const String& picturePath){
		return nullptr;
	}
	PayFeesJsonVO::Wrapper exePayFees(const PayFeesDTO::Wrapper& dto) {
		//参数校验
		auto vo = PayFeesJsonVO::createShared();
		if (!dto) {
			vo->setStatus(RS_FAIL);
			vo->message = "Parameter cannot be empty";
			return vo;
		}
		if (dto->payAmount <= 0 || !dto->payAmount) {
			vo->setStatus(RS_FAIL);
			vo->message = "The payment amount must be greater than zero";
			return vo;
		}
		if (!dto->studentId) {
			vo->setStatus(RS_FAIL);
			vo->message = "Student ID cannot be empty";
			return vo;
		}
		if (!dto->courseId) {
			vo->setStatus(RS_FAIL);
			vo->message = "The course ID cannot be empty";
			return vo;
		}
		if (!dto->subjectId) {
			vo->setStatus(RS_FAIL);
			vo->message = "Subject ID cannot be empty";
			return vo;
		}
		//业务逻辑
		//1.创建数据库
		ConnPool pool("127.0.0.1:3307/zo_eams", "root", "270153", 100);
		Connection* conn = pool.GetConnection();
		if (!conn) {
			vo->setStatus(RS_FAIL);
			vo->message = "The server is busy, please try again later";
			return vo;
		}
		//2.从数据库中的student_coruse表中查找是否有studentId、courseId、subjectId，没有的话返回错误
		PreparedStatement* pstmt = conn->prepareStatement(
			"SELECT pay_off, amount,paid_amount FROM student_course WHERE student_id = ? AND course_id = ? AND subject_id = ?"
		);
		pstmt->setInt(1, dto->studentId);   // 学生ID
		pstmt->setInt(2, dto->courseId);    // 课程ID
		pstmt->setInt(3, dto->subjectId);   // 科目ID
		// 执行查询
		ResultSet* res = pstmt->executeQuery();
		if (!res->next()) {
			vo->setStatus(RS_FAIL);
			vo->message = "Student course record not found";

			// 释放资源
			delete res;
			delete pstmt;
			pool.ReleaseConnection(conn);
			return vo;
		}
		double amount = res->getDouble("amount");    // 总金额
		double paidAmount = res->getDouble("paid_amount"); // 已支付金额
		int  payOff = res->getInt("pay_off");//是否付清
		//3.查看是否已付清，已付清返回"已付清"
		if (payOff == 1) {
			vo->setStatus(RS_FAIL);
			vo->message = "Paid in full";
			// 释放资源
			delete res;
			delete pstmt;
			pool.ReleaseConnection(conn);
			return vo;
		}
		//4.查看还剩下未付的款额，看amount是否大于未付的款额，大的话返回错误
		if (int(amount - paidAmount) < int(dto->payAmount)) {
			vo->setStatus(RS_FAIL);
			vo->message = "The amount paid exceeds the amount due";
			// 释放资源
			delete res;
			delete pstmt;
			pool.ReleaseConnection(conn);
			return vo;
		}
		//5.更新未付的款额，返回还未结清的款项，并带回成功信息
		paidAmount += dto->payAmount;
		if (paidAmount == amount) payOff = 1;
		pstmt = conn->prepareStatement(
			"UPDATE student_course SET paid_amount = ?, pay_off = ? WHERE student_id = ? AND course_id = ? AND subject_id = ?"
		);
		pstmt->setDouble(1, paidAmount);
		pstmt->setInt(2, payOff);
		pstmt->setInt(3, dto->studentId);
		pstmt->setInt(4, dto->courseId);
		pstmt->setInt(5, dto->subjectId);
		int affectedRows = pstmt->executeUpdate();
		delete pstmt;
		if (affectedRows == 0) {
			vo->setStatus(RS_FAIL);
			vo->message = "Update failed, please try again later";
		}
		else {
			vo->setStatus(RS_SUCCESS);
			std::string respondse = "支付成功,剩余待缴金额为：" + std::to_string((amount - paidAmount));
			vo->message = respondse;
		}
		delete res;
		pool.ReleaseConnection(conn);
		return vo;
	}
	RefundJsonVO::Wrapper executeRefund(const RefundDTO::Wrapper& dto) {
		return {};
	}
};
#undef API_TAG
#include OATPP_CODEGEN_END(ApiController) 
#endif