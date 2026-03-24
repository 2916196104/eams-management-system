#include "stdafx.h"
#include "CardService.h"
#include "dao/listening-card/CardDAO.h"
#include "domain/dto/listening-card/cardDTO.h"
#include "../../Macros.h"
 

/*

 * DO转DTO帮助宏，注意该宏只支持30个字段转换，超出30个字段，反复调用该宏调用即可
 * @param target: 属性值接收目标对象
 * @param src: 属性值来源对象
 * @param ...: 字段参数：目标对象字段名,来源对象get方法名称(去除get后剩余部分)。如:id,Id,name,Name......

#define ZO_STAR_DOMAIN_DO_TO_DTO(target, src, ...) ZO_STAR_EXPAND(ZO_STAR_PASTE(target, src, ZO_STAR_DOMAIN_FILED_DO_TO_DTO, __VA_ARGS__))
#define ZO_STAR_DOMAIN_DO_TO_DTO_1(target, src, ...) ZO_STAR_EXPAND(ZO_STAR_PASTE(target, src, ZO_STAR_DOMAIN_FILED_DO_TO_DTO_1, __VA_ARGS__))
*/
/*
    cardDTO::Wrapper CardService::getAvailableCardList() {
        // 查询数据
        CardDAO dao;
        auto res = dao.queryAvailableCards();

	    // 没有查询到数据，返回空列表
        if (res.empty()) {
            return cardDTO::Wrapper();
	    }
	    // 查询到的数据转换为DTO列表
	    auto dtoList = std::make_shared<std::vector<cardDTO::Wrapper>>();
        for (const auto& card : res) {
            auto dto = cardDTO::createShared();
		    ZO_STAR_DOMAIN_DO_TO_DTO(dto, card, id, Id, courseId, CourseId, title, Title, quantity, Quantity, remainingQuantity, RemainingQuantity, lessonCount, LessonCount, expireDays, ExpireDays, endDate, EndDate, state, State, creator, Creator, editor, Editor);
		    dtoList->push_back(dto);
        }
	    return dtoList;
    }
*/
oatpp::List<cardDTO::Wrapper> CardService::getAvailableCardList()
{
    auto list = oatpp::List<cardDTO::Wrapper>::createShared();

    CardDAO dao;
    std::list<CardDO> res;
    try {
        res = dao.queryAvailableCards();
    } catch (const std::exception& ex) {
        // TODO: 日志
        return list;
    }

    for (const auto& card : res) {
        auto dto = cardDTO::createShared();
        ZO_STAR_DOMAIN_DO_TO_DTO(dto, card,
            id, Id,
            courseId, CourseId,
            title, Title,
            quantity, Quantity,
            remainingQuantity, RemainingQuantity,
            lessonCount, LessonCount,
            expireDays, ExpireDays,
            endDate, EndDate,
            state, State,
            creator, Creator,
            editor, Editor);
        list->push_back(dto);
    }
    return list;
}

