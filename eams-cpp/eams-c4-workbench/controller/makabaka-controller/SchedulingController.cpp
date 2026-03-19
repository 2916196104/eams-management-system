#include "SchedulingController.h"
#include"Macros.h"

/**
 * 创建重复排课
 */
oatpp::Object<JsonVO<SchedulingVO::Wrapper>>
SchedulingController::execCreateRepeat(const RepeatedSchedulingQuery::Wrapper& query) {

    auto vo = SchedulingVO::createShared();
    vo->scheduleId = 1001;
    vo->message = ZH_WORDS_GETTER("test.repeat");

    auto result = JsonVO<SchedulingVO::Wrapper>::createShared();
    result->success(vo);

    return result;
}


/**
 * 创建自由排课
 */
oatpp::Object<JsonVO<SchedulingVO::Wrapper>>
SchedulingController::execCreateFree(const FreeSchedulingQuery::Wrapper& query) {

    auto vo = SchedulingVO::createShared();
    vo->scheduleId = 2001;
    vo->message = ZH_WORDS_GETTER("test.free");

    auto result = JsonVO<SchedulingVO::Wrapper>::createShared();
    result->success(vo);

    return result;
}