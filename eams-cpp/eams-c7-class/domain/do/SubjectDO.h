#pragma once
#ifndef _SUBJECT_DO_H_
#define _SUBJECT_DO_H_

#include "../GlobalInclude.h"
#include "BaseDO.h"
#include <string>

using oatpp::UInt64;
using oatpp::Int32;
using oatpp::String;
using oatpp::Boolean;

/**
 * 科目表领域对象
 * 对应表名: subject
 */
class SubjectDO : public BaseDO {
public:
    SubjectDO() : BaseDO("subject") {
        addColField(new DOField("id", "ll", std::bind(&SubjectDO::getIdPtr, this), false, true));
        addColField(new DOField("name", "s", std::bind(&SubjectDO::getNamePtr, this), false, false));
        addColField(new DOField("info", "s", std::bind(&SubjectDO::getInfoPtr, this), true, false));
        addColField(new DOField("creator", "ll", std::bind(&SubjectDO::getCreatorPtr, this), true, false));
        addColField(new DOField("editor", "ll", std::bind(&SubjectDO::getEditorPtr, this), true, false));
        addColField(new DOField("add_time", "s", std::bind(&SubjectDO::getAddTimePtr, this), true, false));
        addColField(new DOField("edit_time", "s", std::bind(&SubjectDO::getEditTimePtr, this), true, false));
        addColField(new DOField("deleted", "i", std::bind(&SubjectDO::getDeletedPtr, this), false, false));
        addColField(new DOField("sort_num", "i", std::bind(&SubjectDO::getSortNumPtr, this), true, false));
        addColField(new DOField("org_id", "ll", std::bind(&SubjectDO::getOrgIdPtr, this), true, false));
    }

    // 字段定义
    UInt64 id = UInt64(1);
    String name;
    String info;
    UInt64 creator = UInt64(1);
    UInt64 editor = UInt64(1);
    String addTime;
    String editTime;
    Boolean deleted = false;
    Int32 sortNum = 0;
    UInt64 orgId = UInt64(1);

    // Getter 指针方法
    void* getIdPtr() { return &id; }
    void* getNamePtr() { return &name; }
    void* getInfoPtr() { return &info; }
    void* getCreatorPtr() { return &creator; }
    void* getEditorPtr() { return &editor; }
    void* getAddTimePtr() { return &addTime; }
    void* getEditTimePtr() { return &editTime; }
    void* getDeletedPtr() { return &deleted; }
    void* getSortNumPtr() { return &sortNum; }
    void* getOrgIdPtr() { return &orgId; }

    // Getter/Setter
    void setId(UInt64 val) { id = val; }
    UInt64 getId() const { return id; }

    void setName(const String& val) { name = val; }
    String getName() const { return name; }

    void setInfo(const String& val) { info = val; }
    String getInfo() const { return info; }

    void setCreator(UInt64 val) { creator = val; }
    UInt64 getCreator() const { return creator; }

    void setEditor(UInt64 val) { editor = val; }
    UInt64 getEditor() const { return editor; }

    void setAddTime(const String& val) { addTime = val; }
    String getAddTime() const { return addTime; }

    void setEditTime(const String& val) { editTime = val; }
    String getEditTime() const { return editTime; }

    void setDeleted(Boolean val) { deleted = val; }
    Boolean getDeleted() const { return deleted; }

    void setSortNum(Int32 val) { sortNum = val; }
    Int32 getSortNum() const { return sortNum; }

    void setOrgId(UInt64 val) { orgId = val; }
    UInt64 getOrgId() const { return orgId; }

    // 领域行为
    bool isDeleted() const { return deleted; }
    bool isValid() const { return !deleted; }
    void markDeleted() { deleted = true; }
    String getDisplayName() const { return name; }
};

// 智能指针类型定义
using PtrSubjectDO = std::shared_ptr<SubjectDO>;

#endif // !_SUBJECT_DO_H_