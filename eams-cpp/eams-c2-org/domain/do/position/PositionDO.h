#ifndef _POSITIONDO_H_
#define _POSITIONDO_H_

#include "BaseDO.h"
#include "SqlHelper.h"
#include <memory>
class PositionItemDO : public BaseDO {

public:
  MYSQL_SYNTHESIZE(int, id, Id);
  MYSQL_SYNTHESIZE(std::string, name, name);

  PositionItemDO() : BaseDO("position") {
    MYSQL_ADD_FIELD_PK("id", "i", id);
    MYSQL_ADD_FIELD_NULLABLE("name", "s", name, true);
  }
};

#endif
