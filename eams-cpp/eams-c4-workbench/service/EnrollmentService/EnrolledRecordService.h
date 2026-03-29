#pragma once
#ifndef ENROLLEDRECORDSERVOCE_H_
#define ENROLLEDRECORDSERVOCE_H_
#include"../../domain/dto/EnrollmentDTO/EnrolledRecordDTO.h"
#include"../../domain/query/EnrollmentQuery/EnrolledRecordQuery.h"
#include"../../domain/vo/EnrollmentVO/EnrollecRecordVO.h"

class EnrolledRecordService
{
	
public:
	//获取报名记录列表数据
	EnrolledRecordPageDTO::Wrapper getEnrolledRecordList(const EnrolledQuery::Wrapper& query); 
	//获取报名记录详情数据
	EnrolledRecordDTO::Wrapper getEnrolledRecordDetail(const Int32 id);
};
#endif // !ENROLLEDRECORDSERVOCE_H_
