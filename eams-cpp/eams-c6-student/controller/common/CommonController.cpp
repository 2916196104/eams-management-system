#include "stdafx.h"
#include "CommonController.h"
#include "../../lib-mysql/include/ConnectionPool.h"
PayFeesJsonVO::Wrapper CommonController::exePayFees(const PayFeesDTO::Wrapper& dto) {
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