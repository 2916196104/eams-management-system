#include "stdafx.h"
#include "ParentAccountController.h"
#include <bcrypt/bcrypt.h>

ParentAccountPageJsonVO::Wrapper ParentAccountController::execQueryParentAccount(const ParentAccountQuery::Wrapper& query)
{
	auto data = m_parentAccountService.listParentAccount(query);
	auto jvo = ParentAccountPageJsonVO::createShared();
	jvo->success(data);
	return jvo;
}

ParentAccountChangeJsonVO::Wrapper ParentAccountController::excuteParentAccountChange(const ParentAccountChangeDTO::Wrapper& dto) {
    auto jvo = ParentAccountChangeJsonVO::createShared();
    if (!dto || !dto->id) {
        jvo->code = 9999;
        jvo->message = "User ID missing.";
        return jvo;
    }

    ConnPool pool(ServerInfo::getInstance().getDbHost() + ":" + std::to_string(ServerInfo::getInstance().getDbPort()) + "/" + ServerInfo::getInstance().getDbName(),
        ServerInfo::getInstance().getDbUsername(), ServerInfo::getInstance().getDbPassword(), 5);
    Connection* conn = pool.GetConnection();
    if (!conn) return jvo;

    try {
        std::string updateSql = "UPDATE user SET name = ?, state = ? WHERE id = ?";
        PreparedStatement* pstmtUpdate = conn->prepareStatement(updateSql);

        pstmtUpdate->setString(1, dto->name->c_str());
        pstmtUpdate->setInt(2, dto->state.getValue(1));
        pstmtUpdate->setUInt64(3, dto->id);

        int affectedRows = pstmtUpdate->executeUpdate();
        delete pstmtUpdate;

        if (affectedRows > 0) {
            jvo->code = 10000;
            jvo->message = "Success: Account updated.";
        }
        else {
            PreparedStatement* pstmtExist = conn->prepareStatement("SELECT COUNT(1) FROM user WHERE id = ?");
            pstmtExist->setUInt64(1, dto->id);
            ResultSet* resExist = pstmtExist->executeQuery();

            bool exists = false;
            if (resExist->next() && resExist->getInt(1) > 0) exists = true;
            delete resExist; delete pstmtExist;

            if (exists) {
                jvo->code = 10000;
                jvo->message = "Success: No changes detected (data is identical).";
            }
            else {
                jvo->code = 9999;
                jvo->message = "Error: Target User ID not found.";
            }
        }
    }
    catch (std::exception& e) {
        jvo->code = 9999;
        jvo->message = e.what();
    }
    pool.ReleaseConnection(conn);
    return jvo;
}

ParentPasswordChangeJsonVO::Wrapper ParentAccountController::excuteParentPasswordChange(const ParentPasswordChangeDTO::Wrapper& dto)
{
    auto jvo = ParentPasswordChangeJsonVO::createShared();

    if (!dto || !dto->id || !dto->oldPassword || !dto->newPassword) {
        jvo->code = 9999;
        jvo->message = "Invalid request: All fields are required.";
        return jvo;
    }

    if (dto->oldPassword.getValue("") == dto->newPassword.getValue("")) {
        jvo->code = 9999;
        jvo->message = "Error: New password cannot be the same as the old one.";
        return jvo;
    }

    ConnPool pool(ServerInfo::getInstance().getDbHost() + ":" + std::to_string(ServerInfo::getInstance().getDbPort()) + "/" + ServerInfo::getInstance().getDbName(),
        ServerInfo::getInstance().getDbUsername(), ServerInfo::getInstance().getDbPassword(), 5);
    Connection* conn = pool.GetConnection();
    if (!conn) return jvo;

    try {
        std::string getPwdSql = "SELECT password FROM user WHERE id = ?";
        PreparedStatement* pstmtGet = conn->prepareStatement(getPwdSql);
        pstmtGet->setUInt64(1, dto->id);
        ResultSet* resPwd = pstmtGet->executeQuery();

        if (!resPwd->next()) {
            jvo->code = 9999;
            jvo->message = "Error: User ID not found.";
            delete resPwd; delete pstmtGet;
            pool.ReleaseConnection(conn);
            return jvo;
        }

        std::string dbPasswordHash = resPwd->getString("password");
        delete resPwd; delete pstmtGet;

        if (!bcrypt::validatePassword(dto->oldPassword->c_str(), dbPasswordHash)) {
            jvo->code = 9999;
            jvo->message = "Error: Old password verification failed.";
            pool.ReleaseConnection(conn);
            return jvo;
        }

        std::string newHash = bcrypt::generateHash(dto->newPassword->c_str());

        std::string updateSql = "UPDATE user SET password = ? WHERE id = ?";
        PreparedStatement* pstmtUpdate = conn->prepareStatement(updateSql);
        pstmtUpdate->setString(1, newHash);
        pstmtUpdate->setUInt64(2, dto->id);

        int affectedRows = pstmtUpdate->executeUpdate();
        delete pstmtUpdate;

        if (affectedRows > 0) {
            jvo->code = 10000;
            jvo->message = "Success: Password has been reset.";
        }
        else {
            jvo->code = 10000;
            jvo->message = "Success: Password record maintained.";
        }

    }
    catch (std::exception& e) {
        jvo->code = 9999;
        jvo->message = e.what();
    }

    pool.ReleaseConnection(conn);
    return jvo;
}
