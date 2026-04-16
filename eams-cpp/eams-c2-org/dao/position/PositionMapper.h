#ifndef _POSITIONMAPPER_H_
#define _POSITIONMAPPER_H_
#include "Mapper.h"
#include "domain/do/position/PositionDO.h"

class PositionItemMapper : public Mapper<PositionItemDO> {

public:
  PositionItemDO mapper(ResultSet *resultSet) const override {
    PositionItemDO item;
    item.setId(resultSet->getInt("id"));
    item.setname(resultSet->getString("name"));
    return item;
  }
};
#endif
