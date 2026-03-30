#include "InstitutionService.h"
#include "../dao/Institution/InstitutionDAO.h"
#include <map>

oatpp::List<oatpp::Object<InstitutionDTO>> InstitutionService::getTree() {
    auto rootList = oatpp::List<oatpp::Object<InstitutionDTO>>::createShared();

    InstitutionDAO dao;
    auto doList = dao.selectAllInstitutions();
    if (doList.empty()) return rootList;

    std::map<uint64_t, oatpp::Object<InstitutionDTO>> nodeMap;
    auto allNodes = oatpp::List<oatpp::Object<InstitutionDTO>>::createShared();

    // 1. 手动将 DO 转 DTO
    for (const auto& doObj : doList) {
        auto dto = InstitutionDTO::createShared();

        dto->id = doObj->getId();
        dto->name = doObj->getName().c_str();
        dto->parentId = doObj->getPid();
        dto->level = doObj->getLevel();
        dto->shortname = doObj->getShortname().c_str();
        dto->contactName = doObj->getContactName().c_str();
        dto->phone = doObj->getPhone().c_str();
        dto->fax = doObj->getFax().c_str();
        dto->email = doObj->getEmail().c_str();
        dto->sortNum = doObj->getSortNum();
        dto->state = doObj->getState();
        dto->info = doObj->getInfo().c_str();

        // 存入 Map 和全量列表
        nodeMap[dto->id] = dto; 
        allNodes->push_back(dto);
    }

    // 2. 组装树
    for (const auto& doObj : doList) {
        auto dto = nodeMap[doObj->getId()];
        if (doObj->getPid() == 0) {
            rootList->push_back(dto);
        }
        else {
            auto it = nodeMap.find(doObj->getPid());
            if (it != nodeMap.end()) {
                auto parentDto = it->second;
                if (!parentDto->children) parentDto->children = oatpp::List<oatpp::Object<InstitutionDTO>>::createShared();
                parentDto->children->push_back(dto);
            }
        }
    }
    return rootList;
}

oatpp::String InstitutionService::saveInstitution(const oatpp::Object<InstitutionDTO>& dto, const oatpp::String& username) {
    InstitutionDO data;

    // 判断是新增还是修改
    if (!dto->id || dto->id == 0) {
        // 新增：生成新 ID
        UuidFacade uf;
        data.setId(std::stoull(uf.genUuid()));
    } else {
        // 修改：使用传入的 ID
        data.setId(dto->id);
    }

    data.setName(dto->name.getValue(""));
    data.setPid(dto->parentId ? dto->parentId.getValue(0) : 0);

    data.setLevel(dto->level ? dto->level.getValue(0) : 0);
    data.setShortname(dto->shortname.getValue(""));
    data.setContactName(dto->contactName.getValue(""));
    data.setPhone(dto->phone.getValue(""));
    data.setFax(dto->fax.getValue(""));
    data.setEmail(dto->email.getValue(""));
    data.setSortNum(dto->sortNum ? dto->sortNum.getValue(0) : 0);
    data.setState(dto->state ? dto->state.getValue(0) : 0);
    data.setInfo(dto->info.getValue(""));

    InstitutionDAO dao;
    int rows;
    if (!dto->id || dto->id == 0) {
        // 新增：执行插入
        rows = dao.insert(data);
    } else {
        // 修改：执行更新
        rows = dao.update(data); // 需要在 DAO 中实现 update 方法
    }

    return rows == 1 ? "保存成功" : "";
}