#include "stdafx.h"
#include "loginService.h"

#include <regex>
#include <random>
#include <sstream>
#include "SimpleDateTimeFormat.h"
#include "id/UuidFacade.h"
#include "dao/login/loginDAO.h"
#include "NacosClient.h"
#include "EmailSender.h"
#include "domain/do/login/loginDO.h"
#include "../../lib-common/include/id/SnowFlake.h"

// 生成验证码
std::string loginService::generateVerifyCode(int len)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, 9);

	std::stringstream ss;
	for (int i = 0; i < len; ++i)
	{
		ss << dis(gen);
	}
	return ss.str();
}

// 构建重置密码邮件内容
std::string loginService::buildMailBody1(const std::string& code)
{
	std::stringstream ss;
	ss << ZH_WORDS_GETTER("login.modify-password.mail.greeting") << "\n\n";
	ss << ZH_WORDS_GETTER("login.modify-password.mail.verify-code-prefix1")
		<< code << "\n";
	ss << ZH_WORDS_GETTER("login.modify-password.mail.expire-prefix")
		<< " "
		<< ZH_WORDS_GETTER("login.modify-password.mail.expire-minutes")
		<< " "
		<< ZH_WORDS_GETTER("login.modify-password.mail.expire-suffix")
		<< "\n\n";
	ss << ZH_WORDS_GETTER("login.modify-password.mail.ignore-tip");
	return ss.str();
}

// 构建邮件内容
std::string loginService::buildMailBody2(const std::string& code)
{
	std::stringstream ss;
	ss << ZH_WORDS_GETTER("login.modify-password.mail.greeting") << "\n\n";
	ss << ZH_WORDS_GETTER("login.modify-password.mail.verify-code-prefix2")
		<< code << "\n";
	ss << ZH_WORDS_GETTER("login.modify-password.mail.expire-prefix")
		<< " "
		<< ZH_WORDS_GETTER("login.modify-password.mail.expire-minutes")
		<< " "
		<< ZH_WORDS_GETTER("login.modify-password.mail.expire-suffix")
		<< "\n\n";
	ss << ZH_WORDS_GETTER("login.modify-password.mail.ignore-tip");
	return ss.str();
}


// 生成Redis_key
std::string loginService::buildRedisKey(const std::string& mobile, const std::string& email)
{
	return "pwd:reset:" + mobile + ":" + email;
}


// 验证手机号码和邮箱格式是否正确
bool loginService::isValidMobileAndEmail(const std::string& mobile, const std::string& email)
{
	static const std::regex reg1("^1[3-9][0-9]{9}$"); // 手机号码格式
	static const std::regex reg2("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$"); // 邮箱格式
	return std::regex_match(mobile, reg1) && std::regex_match(email, reg2);
}


// 发送找回密码验证码
SendResetCodeRespDTO::Wrapper loginService::sendResetCode(const SendResetCodeDTO::Wrapper& dto)
{
	LoginDAO dao;
	// 生成验证码
	const std::string verifyCode = generateVerifyCode(4);

	std::string email = dto->email;
	std::string mobile = dto->mobile;
	
	// 获取邮箱配置
	ZO_CREATE_MAIL_SENDER(Sender);
	Sender.setCharset("utf8");
	Sender.addRecvEmailAddr(email, ZH_WORDS_GETTER("login.text"));
	Sender.setEmailContent(
		ZH_WORDS_GETTER("login.modify-password.mail.subject1"),
		buildMailBody1(verifyCode)
	);

	auto resp = SendResetCodeRespDTO::createShared();

	// 验证手机号和邮箱格式是否正确
	bool valid = isValidMobileAndEmail(mobile, email);
	if (!valid) {
		resp->sendResult = false;
		resp->msg = ZH_WORDS_GETTER("login.send.error4");
		return resp;
	}

	// 构建key值
	std::string key = buildRedisKey(mobile, email);

	// 查看手机号码是否正确
	uint64_t isExist = dao.count(mobile);
	if (isExist < 1) {
		resp->sendResult = false;
		resp->msg = ZH_WORDS_GETTER("login.send.error3");
		return resp;
	}
	
	// 表示5分钟内只能够获取一次验证码，如果存在，则直接返回错误
	std::string value = dao.getValue(key);
	if (!value.empty()) {
		resp->sendResult = false;
		resp->msg = ZH_WORDS_GETTER("login.send.error1");
		return resp;
	}

	// 保存验证码和发送验证码
	bool ok1 = dao.saveCode(key, verifyCode, 300);
	bool ok2 = Sender.send();
	if (!ok1 || !ok2) {
		resp->sendResult = false;
		resp->msg = ZH_WORDS_GETTER("login.send.error2");
		return resp;
	}
	resp->sendResult = true;
	resp->msg = ZH_WORDS_GETTER("login.send.lastSuccess");
	return resp;
}


// 修改密码
UpdatePasswordRespDTO::Wrapper loginService::updatePassword(const UpdatePasswordDTO::Wrapper& dto)
{
	LoginDAO dao;
	const std::string mobile = dto->mobile;
	const std::string email = dto->email;
	const std::string inputCode = dto->verifyCode;
	const std::string newPassword = dto->newPassword;

	auto resp = UpdatePasswordRespDTO::createShared();

	// 构建key值
	std::string key = buildRedisKey(mobile, email);

	// 获取数据库中的验证码
	std::string value = dao.getValue(key);
	// 验证码不对则返回
	if (value != inputCode) {
		resp->updateResult = false;
		resp->msg = ZH_WORDS_GETTER("login.update.error1");
		return resp;
	}

	// 验证手机号和邮箱格式是否正确
	bool valid = isValidMobileAndEmail(mobile, email);
	if (!valid) {
		resp->updateResult = false;
		resp->msg = ZH_WORDS_GETTER("login.update.error3");
		return resp;
	}

	// 修改密码
	bool ok1 = dao.updatePassword(mobile, email, newPassword);

	if (!ok1) {
		resp->updateResult = false;
		resp->msg = ZH_WORDS_GETTER("login.update.error2");
		return resp;
	}
	// 密码修改成功后删除验证码
	bool ok2 = dao.deleteKey(key);

	resp->updateResult = true;
	resp->msg = ZH_WORDS_GETTER("login.update.lastSuccess");
	return resp;
}


// 发送注册短信验证
SendRegisterCodeRespDTO::Wrapper loginService::sendRegisterCode(const SendRegisterCodeDTO::Wrapper& dto)
{
	LoginDAO dao;
	// 生成验证码
	const std::string verifyCode = generateVerifyCode(4);

	std::string email = dto->email;
	std::string mobile = dto->mobile;

	// 获取邮箱配置
	ZO_CREATE_MAIL_SENDER(Sender);
	Sender.setCharset("utf8");
	Sender.addRecvEmailAddr(email, ZH_WORDS_GETTER("login.text"));
	Sender.setEmailContent(
		ZH_WORDS_GETTER("login.modify-password.mail.subject2"),
		buildMailBody2(verifyCode)
	);

	auto resp = SendRegisterCodeRespDTO::createShared();

	// 验证手机号和邮箱格式是否正确
	bool valid = isValidMobileAndEmail(mobile, email);
	if (!valid) {
		resp->sendResult = false;
		resp->msg = ZH_WORDS_GETTER("login.register.error1");
		return resp;
	}

	// 构建key值
	std::string key = buildRedisKey(mobile, email);

	// 表示5分钟内只能够获取一次验证码，如果存在，则直接返回错误
	std::string value = dao.getValue(key);
	if (!value.empty()) {
		resp->sendResult = false;
		resp->msg = ZH_WORDS_GETTER("login.register.error6");
		return resp;
	}

	// 保存验证码和发送验证码
	bool ok1 = dao.saveCode(key, verifyCode, 300);
	bool ok2 = Sender.send();
	if (!ok1 || !ok2) {
		resp->sendResult = false;
		resp->msg = ZH_WORDS_GETTER("login.register.error4");
		return resp;
	}
	resp->sendResult = true;
	resp->msg = ZH_WORDS_GETTER("login.register.lastSuccess1");
	return resp;
}


// 注册账号
RegisterRespDTO::Wrapper loginService::saveAccount(const RegisterDTO::Wrapper& dto)
{
	LoginDAO dao;
	const std::string mobile = dto->mobile;
	const std::string email = dto->email;
	const std::string inputCode = dto->verifyCode;

	// 构建key值
	std::string key = buildRedisKey(mobile, email);



	auto resp = RegisterRespDTO::createShared();

	// 验证手机号和邮箱格式是否正确
	bool valid = isValidMobileAndEmail(mobile, email);
	if (!valid) {
		resp->registerResult = false;
		resp->msg = ZH_WORDS_GETTER("login.register.error1");
		return resp;
	}

	// 查看手机号是否存在
	uint64_t isExist = dao.count(mobile);
	// 如果存在，则返回错误
	if (isExist == 1) {
		resp->registerResult = false;
		resp->msg = ZH_WORDS_GETTER("login.register.error5");
		return resp;
	}

	// 获取数据库中的验证码
	std::string value = dao.getValue(key);
	// 验证码不对则返回
	if (value != inputCode) {
		resp->registerResult = false;
		resp->msg = ZH_WORDS_GETTER("login.register.error2");
		return resp;
	}

	// 组装数据
	LoginDO data;
	ZO_STAR_DOMAIN_DTO_TO_DO(data, dto, Mobile, mobile, Email, email, Name, name, Password, password);
	// 生成id
	SnowFlake sf(1, 1);
	uint64_t id = sf.nextId();
	// 雪花算法生成失败会返回0，必须做校验
	if (id == 0) {
		resp->registerResult = false;
		resp->msg = ZH_WORDS_GETTER("login.register.error3");
		return resp;
	}
    data.setId(id);
	// 设置创建时间
	data.setAddTime(SimpleDateTimeFormat::format());

	int result = dao.insert(data);
	// 注册失败
	if (result == 0) {
        resp->registerResult = false;
        resp->msg = ZH_WORDS_GETTER("login.register.error3");
	}
	// 注册成功，删除验证码
    dao.deleteKey(key);
	// 返回成功
    resp->registerResult = true;
    resp->msg = ZH_WORDS_GETTER("login.register.lastSuccess2");
	return resp;
}