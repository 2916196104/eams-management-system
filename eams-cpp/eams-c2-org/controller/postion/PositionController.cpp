#include "stdafx.h"
//
#include "Message.h"
#include "ResultStatus.h"
#include "domain/dto/postion/PositionDTO.h"
//
#include "PositionController.h"
#include "service/position/PositionService.h"

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse>
PositionController::fetchPositionAll(const std::shared_ptr<CustomerAuthorizeObject>& auth) {

  PositionService ser;

  auto vo = ALLPositionsVO::createShared();

  auto data = ser.fetchAllPosition();
  if (data->empty()) {
    vo->init(data, RS_SERVER_BUSY);
  } else
    vo->init(data, RS_SUCCESS);

  return createDtoResponse(Status::CODE_200, vo);
};

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse>
PositionController::fetchPositionList(const std::shared_ptr<CustomerAuthorizeObject>& auth, const Int32 &pageNum,
                                      const Int32 &pageSize,
                                      const String &keyWord) {

  PositionService ser;

  auto vo = PositionListVO::createShared();
  auto empty = oatpp::Vector<PositionItemDTO::Wrapper>::createShared();

  auto page = pageNum.getValue(1);
  auto limit = pageSize.getValue(10);
  if (page <= 0 || limit <= 0) {
    vo->page = page;
    vo->limit = limit;
    vo->total = 0;
    vo->totalPages = 0;
    vo->init(empty, RS_PARAMS_INVALID);
    return createDtoResponse(Status::CODE_200, vo);
  }

  auto result = ser.pageQueryPosition(pageNum, pageSize, keyWord);

  vo->page = page;
  vo->limit = limit;
  vo->total = result.total;
  vo->totalPages = result.totalPages;
  vo->init(result.data, RS_SUCCESS);

  return createDtoResponse(Status::CODE_200, vo);
};

std::shared_ptr<oatpp::web::server::api::ApiController::OutgoingResponse>
PositionController::savePosition(const std::shared_ptr<CustomerAuthorizeObject>& auth, const PositionSaveRequestDTO::Wrapper &dto) {

  PositionService ser;

  auto vo = JsonVO<oatpp::Int64>::createShared();
  int64_t id = 0;
  if (!dto || !dto->name || dto->name->empty() || (dto->id && dto->id <= 0)) {
    vo->init(oatpp::Int64(id), RS_PARAMS_INVALID);
    return createDtoResponse(Status::CODE_200, vo);
  }

  id = ser.savePosition(dto);
  if (id < 0) {
    vo->init(oatpp::Int64(id), RS_SERVER_BUSY);
  } else {
    vo->init(oatpp::Int64(id), RS_SUCCESS);
  }

  return createDtoResponse(Status::CODE_200, vo);
}
