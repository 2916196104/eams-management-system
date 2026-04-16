#include "stdafx.h"
#include "CardService.h"
#include "dao/listening-card/CardDAO.h"
#include "domain/dto/listening-card/cardDTO.h"
#include "../../Macros.h"


oatpp::List<cardDTO::Wrapper> CardService::getAvailableCardList()
{
    auto list = oatpp::List<cardDTO::Wrapper>::createShared();

    CardDAO dao;
    std::list<CardDO> res;
    try {
        res = dao.queryAvailableCards();
    } catch (const std::exception&) {
        // TODO: 日志
        return list;
    }

    for (const auto& card : res) {
        auto dto = cardDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, card,
            id, Id,
            courseId, CourseId,
            courseName, CourseName,
            title, Title,
            quantity, Quantity,
            lessonCount, LessonCount,
            expireDays, ExpireDays,
            endDate, EndDate,
            state, State,
            editTime, EditTime,
            editorName, EditorName,
            recordCount, RecordCount);
        list->push_back(dto);
    }
    return list;
}

cardRuleDTO::Wrapper CardService::getCardUsageRules()
{
    // 查询数据
    CardRuleDAO dao;
	auto res = dao.queryCardUsageRules();
    // 没有查询到数据，返回空对象
    if (!res) {
        return cardRuleDTO::Wrapper();
    }
	// 查询到的数据转换为DTO对象
	auto dto = cardRuleDTO::createShared();
	ZO_STAR_DOMAIN_DO_TO_DTO_1(dto, res,
        id, Id,
        settingId, SettingId,
        name, Name,
        code, Code,
        value, Value,
        valueType, ValueType,
        info, Info,
		sortNum, SortNum
    )
	return dto;
}

