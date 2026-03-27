#include "stdafx.h"
#include "RegisterDAO.h"
#include "RegisterMapper.h"
#include "SqlSession.h"
#include "../../../lib-common/include/id/SnowFlake.h"

string RegisterDAO::generateSnowFlakeId()
{
	return std::to_string(SnowFlake(0, 0).nextId());
}

std::string RegisterDAO::getCurrentDateTime() {
	// 1. 获取当前系统时间（精确到秒）
	auto now = std::chrono::system_clock::now();
	// 2. 转换为time_t类型（兼容传统时间接口）
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);
	// 3. 转换为本地时间（避免UTC时差）
	std::tm now_tm = *std::localtime(&now_c);

	// 4. 格式化输出（YYYY-MM-DD HH:MM:SS）
	std::ostringstream oss;
	oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
	return oss.str();
}

bool RegisterDAO::isMobileExist(const std::string& mobile)
{
	std::stringstream sql;
	sql << "SELECT COUNT(*) FROM user WHERE mobile = ?";
	SqlParams params;
	if (mobile.size()) SQLPARAMS_PUSH(params, "s", std::string, mobile);
	auto res = sqlSession->executeQueryNumerical(sql.str(), params);
	return res == 0 ? false : true;
}

std::string RegisterDAO::insertUser(const PtrRegisterDO pdo)
{
	std::string id = generateSnowFlakeId();
	std::string currentDateTime = getCurrentDateTime();
	std::stringstream sql;
	sql << "INSERT INTO user (id, name, mobile, password, add_time)";
	sql << " VALUES ( ?, ?, ?, ?, ?)";
	SqlParams params;
	// 用户id
	if (id.size()) SQLPARAMS_PUSH(params, "s", std::string, id);
	// 用户名称
	if (pdo->getName().size()) SQLPARAMS_PUSH(params, "s", std::string, pdo->getName());
	// 手机号
	if (pdo->getMobile().size()) SQLPARAMS_PUSH(params, "s", std::string, pdo->getMobile());
	// 密码
	if (pdo->getPassword().size()) SQLPARAMS_PUSH(params, "s", std::string, pdo->getPassword());
	// 注册时间
	if (currentDateTime.size()) SQLPARAMS_PUSH(params, "s", std::string, currentDateTime);

	sqlSession->executeUpdate(sql.str(), params);
	return id;
}