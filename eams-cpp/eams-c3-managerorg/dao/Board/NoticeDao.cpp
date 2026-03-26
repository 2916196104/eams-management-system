#include "stdafx.h"
#include "NoticeDao.h"
#include "NoticeMapper.h"

std::list<PtrNoticeSettingDO> NoticeDAO::selectAll()
{
    string sql = "SELECT id, name, code, enabled, wx_template_id, "
        "sms_enabled, sms_template, force_enable, description, "
        "sort, receiver_type, wx_template_desc "
        "FROM setting_notice "
        "ORDER BY sort ASC";
    return sqlSession->executeQuery<PtrNoticeSettingDO>(sql, PtrNoticeMapper()); // ✅
}

PtrNoticeSettingDO NoticeDAO::selectById(int id)
{
    string sql = "SELECT id, name, code, enabled, wx_template_id, "
        "sms_enabled, sms_template, force_enable, description, "
        "sort, receiver_type, wx_template_desc "
        "FROM setting_notice WHERE id = ?";
    return sqlSession->executeQueryOne<PtrNoticeSettingDO>(
        sql,
        PtrNoticeMapper(),
        "%d",
        std::to_string(id)
    );
}

PtrNoticeSettingDO NoticeDAO::selectByCode(const std::string& code)
{
    if (code.empty()) return nullptr;
    string sql = "SELECT id, name, code, enabled, wx_template_id, "
        "sms_enabled, sms_template, force_enable, description, "
        "sort, receiver_type, wx_template_desc "
        "FROM setting_notice WHERE code = ?";
    return sqlSession->executeQueryOne<PtrNoticeSettingDO>(
        sql,
        PtrNoticeMapper(),
        "%s",
        code
    );
}