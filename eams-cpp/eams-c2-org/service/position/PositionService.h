#ifndef _POSITIONSERVICE_H_
#define _POSITIONSERVICE_H_

#include "../../domain/dto/position/PositionDTO.h"

class PositionService {

public:
  struct PageQueryResult {
    oatpp::Vector<PositionItemDTO::Wrapper> data;
    int32_t total;
    int32_t totalPages;
  };

  oatpp::Vector<PositionItemDTO::Wrapper> fetchAllPosition();
  PageQueryResult pageQueryPosition(const oatpp::Int32 &pageNum,
                                    const oatpp::Int32 &pageSize,
                                    const oatpp::String &keyWord);

  int64_t savePosition(const PositionSaveRequestDTO::Wrapper &dto);
  bool deletePositions(const std::vector<int64_t>& ids);
};

#endif
