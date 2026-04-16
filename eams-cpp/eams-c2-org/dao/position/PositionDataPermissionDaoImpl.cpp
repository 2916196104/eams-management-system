
#include <vector>
#include "../../domain/do/position/PositionDataPermissionDO.h"

class PositionDataPermissionDao {
public:
    virtual ~PositionDataPermissionDao() = default;
    virtual int64_t countByPositionId(int positionId) = 0;
    virtual std::vector<PositionDataPermissionDO> selectByPositionId(int positionId, int offset, int limit) = 0;
};