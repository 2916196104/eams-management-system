#include "stdafx.h"
#include "loginDAO.h"
#include "NacosClient.h"
#include "RedisClient.h"
#include "ServerInfo.h"
#include "domain/do/login/loginDO.h"

// 查找数据库中是否有该用户
uint64_t LoginDAO::count(const std::string& mobile)
{
	string sql = "SELECT COUNT(*) FROM user WHERE mobile = ?";
	SqlParams params;
	SQLPARAMS_PUSH(params, "s", std::string, mobile);
	return sqlSession->executeQueryNumerical(sql, params);
}



// 获取Redis中的验证码
std::string LoginDAO::getValue(const std::string& key)
{
	// 定义Redis客户端
	ZO_CREATE_REDIS_CLIENT(rc);

	// 在数据库中获取对应的验证码
	std::string value = rc.execute<std::string>([&](Redis* redis) -> std::string {
		auto val = redis->get(key);
		if (val.has_value())
		{
			return val.value();
		}
		return "";
		});
	return value;
}

// 保存验证码
bool LoginDAO::saveCode(const std::string& key, const std::string& val, int expireSeconds)
{	
	// 定义Redis客户端
	ZO_CREATE_REDIS_CLIENT(rc);

	// 存储验证码
	bool ok = rc.execute<bool>([&](Redis* redis) {
		bool setRes = redis->set(key, val);
		bool expireRes = redis->expire(key, expireSeconds); // 过期时间
		return setRes && expireRes;
		});
	return ok;
}

// 删除验证码
bool LoginDAO::deleteKey(const std::string& key)
{
	// 定义Redis客户端
	ZO_CREATE_REDIS_CLIENT(rc);
	// 执行删除
    bool ok = rc.execute<bool>([&](Redis* redis) {
		return redis->del(key);
		});
	return ok;
}

// 修改密码
bool LoginDAO::updatePassword(const std::string& mobile, const std::string& email, const std::string& newPassword)
{
	string sql = "UPDATE `user` SET `password` = ? WHERE `mobile` = ? AND `email` = ?";
	return sqlSession->executeUpdate(sql, "%s%s%s", newPassword, mobile, email) > 0;
}
