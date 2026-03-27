#include "stdafx.h"
#include "CommonController.h"
#include "../../lib-mysql/include/ConnectionPool.h"
#include "../../domain/do/DoInclude.h"
#include "../../dao/common/CommonDAO.h"
PayFeesJsonVO::Wrapper helper(const PayFeesDTO::Wrapper& dto) {
	auto vo = PayFeesJsonVO::createShared();
	StudentCourseDAO dao;
	PtrStudentCourseDO data = dao.selectByIds(dto->studentId, dto->courseId, dto->subjectId);
	if (!data) {
		vo->setStatus(RS_FAIL);
		vo->message = "Student course record not found";
		return vo;
	}

	if (data->getPayOff() == 1) {
		vo->setStatus(RS_FAIL);
		vo->message = "Paid in full";
		return vo;
	}
	double tempAmount = round(data->getAmount() * 100) / 100.0;
	double tempPaidAmount = round(data->getPaidAmount() * 100) / 100.0;
	double toPay = round((tempAmount - tempPaidAmount) * 100) / 100.0;

	if (toPay < dto->payAmount) {
		vo->setStatus(RS_FAIL);
		vo->message = "The amount paid exceeds the amount due";
		return vo;
	}
	double newPaidAmount = round((dto->payAmount + tempPaidAmount) * 100) / 100.0;
	data->setPaidAmount(newPaidAmount);
	if (std::fabs(toPay - dto->payAmount) <= 1e-6) {
		data->setPayOff(1);
	}
	int rows = dao.update(*data);
	if (rows == 0) {
		vo->setStatus(RS_FAIL);
		vo->message = "Update failed, please try again later";
		return vo;
	}
	vo->setStatus(RS_SUCCESS);
	double remaining = round((data->getAmount() - data->getPaidAmount()) * 100) / 100.0;
	vo->message = "Payment successful, the remaining amount to be paid is:" + std::to_string(remaining);
	return vo;
}



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
	return helper(dto);
	//业务逻辑
	//1.创建数据库
	//ConnPool pool("127.0.0.1:3307/zo_eams", "root", "270153", 100);
	//Connection* conn = pool.GetConnection();
	//if (!conn) {
	//	vo->setStatus(RS_FAIL);
	//	vo->message = "The server is busy, please try again later";
	//	return vo;
	//}
	////2.从数据库中的student_coruse表中查找是否有studentId、courseId、subjectId，没有的话返回错误
	//PreparedStatement* pstmt = conn->prepareStatement(
	//	"SELECT pay_off, amount,paid_amount FROM student_course WHERE student_id = ? AND course_id = ? AND subject_id = ?"
	//);
	//pstmt->setInt(1, dto->studentId);   // 学生ID
	//pstmt->setInt(2, dto->courseId);    // 课程ID
	//pstmt->setInt(3, dto->subjectId);   // 科目ID
	//// 执行查询
	//ResultSet* res = pstmt->executeQuery();
	//if (!res->next()) {
	//	vo->setStatus(RS_FAIL);
	//	vo->message = "Student course record not found";

	//	// 释放资源
	//	delete res;
	//	delete pstmt;
	//	pool.ReleaseConnection(conn);
	//	return vo;
	//}
	//double amount = res->getDouble("amount");    // 总金额
	//double paidAmount = res->getDouble("paid_amount"); // 已支付金额
	//int  payOff = res->getInt("pay_off");//是否付清
	////3.查看是否已付清，已付清返回"已付清"
	//if (payOff == 1) {
	//	vo->setStatus(RS_FAIL);
	//	vo->message = "Paid in full";
	//	// 释放资源
	//	delete res;
	//	delete pstmt;
	//	pool.ReleaseConnection(conn);
	//	return vo;
	//}
	////4.查看还剩下未付的款额，看amount是否大于未付的款额，大的话返回错误
	//if (int(amount - paidAmount) < int(dto->payAmount)) {
	//	vo->setStatus(RS_FAIL);
	//	vo->message = "The amount paid exceeds the amount due";
	//	// 释放资源
	//	delete res;
	//	delete pstmt;
	//	pool.ReleaseConnection(conn);
	//	return vo;
	//}
	////5.更新未付的款额，返回还未结清的款项，并带回成功信息
	//paidAmount += dto->payAmount;
	//if (paidAmount == amount) payOff = 1;
	//pstmt = conn->prepareStatement(
	//	"UPDATE student_course SET paid_amount = ?, pay_off = ? WHERE student_id = ? AND course_id = ? AND subject_id = ?"
	//);
	//pstmt->setDouble(1, paidAmount);
	//pstmt->setInt(2, payOff);
	//pstmt->setInt(3, dto->studentId);
	//pstmt->setInt(4, dto->courseId);
	//pstmt->setInt(5, dto->subjectId);
	//int affectedRows = pstmt->executeUpdate();
	//delete pstmt;
	//if (affectedRows == 0) {
	//	vo->setStatus(RS_FAIL);
	//	vo->message = "Update failed, please try again later";
	//}
	//else {
	//	vo->setStatus(RS_SUCCESS);
	//	std::string respondse = "支付成功,剩余待缴金额为：" + std::to_string((amount - paidAmount));
	//	vo->message = respondse;
	//}
	//delete res;
	//pool.ReleaseConnection(conn);
	//return vo;
}

/**
 * 调整积分执行函数
 */
StringJsonVO::Wrapper CommonController::execModifyPoints(const ModifyPointsDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	// 参数校验
	if (!dto->id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	//// 执行数据修改
	//dto->setPayload(&payload);
	//if (AdjustPointsService().updateData(dto)) {
	//	jvo->success(dto->name);
	//}
	//else
	//{
	//	jvo->fail(dto->name);
	//}
	// 响应结果
	return jvo;
}



/**
 * 添加跟进记录执行函数
 */
StringJsonVO::Wrapper CommonController::execAddFollowUpRecord(const AddFollowUpRecordDTO::Wrapper& dto, const PayloadDTO& payload)
{
	// 定义返回数据对象
	auto jvo = StringJsonVO::createShared();
	// 参数校验
	if (!dto->id)
	{
		jvo->init(nullptr, RS_PARAMS_INVALID);
		return jvo;
	}

	// 执行数据修改
	//dto->setPayload(&payload);
	//if (AddFollowUpRecordService().updateData(dto)) {
	//	jvo->success(dto->name);
	//}
	//else
	//{
	//	jvo->fail(dto->name);
	//}
	//// 响应结果
	return jvo;
}

QueryFollowUprecordsJsonVO::Wrapper CommonController::execQueryFollowUprecords(const FollowUprecordsQuery::Wrapper& query)
{
	// 查询数据
	//auto result = SampleService().listAll(query);
	// 响应结果
	auto jvo = QueryFollowUprecordsJsonVO::createShared();
	jvo->success(QueryFollowUprecordsDTO::createShared());
	return jvo;
}
