#include "stdafx.h"
#include "CommonController.h"
#include "../../service/common/CommonService.h"
#include<iostream>
#include "../../lib-mysql/include/ConnectionPool.h"
#include "../../domain/do/DoInclude.h"
#include "../../dao/common/CommonDAO.h"
StudentJsonVO::Wrapper CommonController::executeGetStudentById(UInt64 id) {
	auto jvo = StudentJsonVO::createShared();
	StudentService service;
	auto data = service.GetStudentDetailById(id);
	jvo->success(data);
	return jvo;
}
StringJsonVO::Wrapper CommonController::executeModifyStudentPicture(const ModifyStudentHeadImgDTO::Wrapper& dto)
{
	auto jvo = StringJsonVO::createShared();
	StudentService service;
	service.ModifyStudentHeadImg(dto);
	jvo->success("success");
	return jvo;
}
RegistrationPageJsonVO::Wrapper CommonController::executeQueryRegistrationRecordByPage(const RegistrationPageQuery::Wrapper& query) {
	auto jvo = RegistrationPageJsonVO::createShared();
	RegistrationRecordService service;
	auto data = service.GetRegistrationRecordWithPage(query);
	jvo->success(data);
	return jvo;
}
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
	//����У��
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
	//ҵ���߼�
	//1.�������ݿ�
	//ConnPool pool("127.0.0.1:3307/zo_eams", "root", "270153", 100);
	//Connection* conn = pool.GetConnection();
	//if (!conn) {
	//	vo->setStatus(RS_FAIL);
	//	vo->message = "The server is busy, please try again later";
	//	return vo;
	//}
	////2.�����ݿ��е�student_coruse���в����Ƿ���studentId��courseId��subjectId��û�еĻ����ش���
	//PreparedStatement* pstmt = conn->prepareStatement(
	//	"SELECT pay_off, amount,paid_amount FROM student_course WHERE student_id = ? AND course_id = ? AND subject_id = ?"
	//);
	//pstmt->setInt(1, dto->studentId);   // ѧ��ID
	//pstmt->setInt(2, dto->courseId);    // �γ�ID
	//pstmt->setInt(3, dto->subjectId);   // ��ĿID
	//// ִ�в�ѯ
	//ResultSet* res = pstmt->executeQuery();
	//if (!res->next()) {
	//	vo->setStatus(RS_FAIL);
	//	vo->message = "Student course record not found";

	//	// �ͷ���Դ
	//	delete res;
	//	delete pstmt;
	//	pool.ReleaseConnection(conn);
	//	return vo;
	//}
	//double amount = res->getDouble("amount");    // �ܽ��
	//double paidAmount = res->getDouble("paid_amount"); // ��֧�����
	//int  payOff = res->getInt("pay_off");//�Ƿ���
	////3.�鿴�Ƿ��Ѹ��壬�Ѹ��巵��"�Ѹ���"
	//if (payOff == 1) {
	//	vo->setStatus(RS_FAIL);
	//	vo->message = "Paid in full";
	//	// �ͷ���Դ
	//	delete res;
	//	delete pstmt;
	//	pool.ReleaseConnection(conn);
	//	return vo;
	//}
	////4.�鿴��ʣ��δ���Ŀ���amount�Ƿ����δ���Ŀ���Ļ����ش���
	//if (int(amount - paidAmount) < int(dto->payAmount)) {
	//	vo->setStatus(RS_FAIL);
	//	vo->message = "The amount paid exceeds the amount due";
	//	// �ͷ���Դ
	//	delete res;
	//	delete pstmt;
	//	pool.ReleaseConnection(conn);
	//	return vo;
	//}
	////5.����δ���Ŀ����ػ�δ����Ŀ�������سɹ���Ϣ
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
	//	std::string respondse = "֧���ɹ�,ʣ����ɽ��Ϊ��" + std::to_string((amount - paidAmount));
	//	vo->message = respondse;
	//}
	//delete res;
	//pool.ReleaseConnection(conn);
	//return vo;
}
RefundJsonVO::Wrapper CommonController::executeRefund(const RefundDTO::Wrapper& dto) {
	auto vo = RefundJsonVO::createShared();
	if (!dto) {
		vo->setStatus(RS_FAIL);
		vo->message = "Parameter cannot be empty";
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
	if (dto->lessons <= 0) {
		vo->setStatus(RS_FAIL);
		vo->message = "Error in course withdrawal class hour parameter";
		return vo;
	}
	StudentCourseDAO dao;
	auto data = dao.selectByIds(dto->studentId, dto->courseId, dto->subjectId);
	if (!data) {
		vo->setStatus(RS_FAIL);
		vo->message = "Student course record not found";
		return vo;
	}
	RefundDAO Dao;
	auto findData = Dao.selectByIds(data->getId());
	if (findData) {
		vo->setStatus(RS_FAIL);
		vo->message = "Application submitted, please do not submit again";
		return vo;
	}
	if (data->getPaidAmount() < dto->refundAmount) {
		vo->setStatus(RS_FAIL);
		vo->message = "The refunded amount is greater than the paid amount";
		return vo;
	}
	//std::cout << data->getPaidAmount() << " " << dto->refundAmount;
	auto insertData = std::make_shared<RefundDO>();
	time_t now = time(NULL);
	// ����ǰʱ��ת��Ϊ����ʱ��
	struct tm* local_tm = localtime(&now);

	// ʹ�� strftime ��ʽ��ʱ��
	char buffer[80];
	strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", local_tm);
	insertData->setApplyTime(buffer);
	insertData->setRefundAmount(dto->refundAmount);
	insertData->setRefundLessonCount(dto->lessons);
	insertData->setRemark(dto->reason);
	insertData->setStudentCourseId(data->getId());
	insertData->setVerifyState(0);
	insertData->setStudentId(dto->studentId);


	auto row = Dao.insertAutoPk(*insertData);
	if (row == 0) {
		vo->setStatus(RS_FAIL);
		vo->message = "Application failed, please try again later";
		return vo;
	}
	else {
		vo->setStatus(RS_SUCCESS);
		vo->message = "Application successful";
		return vo;
	}
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
