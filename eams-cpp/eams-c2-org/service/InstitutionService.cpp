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

    // 生成 ID (假设你们框架里有 UuidFacade)
    UuidFacade uf;
    data.setId(std::stoull(uf.genUuid()));

    data.setName(dto->name.getValue(""));
    data.setPid(dto->parentId ? dto->parentId.getValue(0) : 0);

    // 审计字段
    // data.setCreator(std::stoull(username->std_str())); 
    data.setAddTime("2026-03-01 10:00:00"); // 实际应调用 SimpleDateTimeFormat::format()
    data.setLevel(3);

    InstitutionDAO dao;
    // 直接调用基类的 insert！自动生成 SQL 并绑定参数！
    int rows = dao.insert(data);

    return rows == 1 ? "保存成功" : "";
}