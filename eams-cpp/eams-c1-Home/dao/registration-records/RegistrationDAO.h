/*
 @Author: abinng
 @Date: 2026/03/23 18:32:10
 @File: RegistrationDAO.h
*/
#pragma once
#ifndef _REGISTRATION_DAO_H_
#define _REGISTRATION_DAO_H_ 

#include "BaseDAO.h"
#include "domain/do/registration-records/RegistrationDO.h"
#include "domain/query/registration-records/registrationquery.h"

/**
 * 报名记录查询操作
 */
class RegistrationDAO : public BaseDAO {
public:
    // 统计记录总数
    uint64_t count(const RegistrationRecordQuery::Wrapper& query);
    // 通过查询条件查询数据
    std::list<PtrRegistrationViewDO> selectByQuery(const RegistrationRecordQuery::Wrapper& query);
};


#endif // !_REGISTRATION_DAO_H_
