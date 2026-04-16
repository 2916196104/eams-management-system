package com.zeroone.star.operation.service.impl;

import com.zeroone.star.operation.mapper.PointsRecordMapper;
import com.zeroone.star.operation.service.IPointsRecordService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.PointsRecordUpdateDTO;
import com.zeroone.star.project.dto.j7.operation.PointsRecordDTO;
import com.zeroone.star.project.query.j7.operation.PointsRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

@Service
public class IPointsRecordServiceImpl implements IPointsRecordService {

    @Resource
    private PointsRecordMapper pointsRecordMapper;

    @Override
    public JsonVO<PageDTO<PointsRecordDTO>> queryAllPointsRecord(PointsRecordQuery condition) {
        long pageNum = 1L;
        long pageSize = 10L;

        if (condition != null) {
            if (condition.getPageIndex() > 0) {
                pageNum = condition.getPageIndex();
            }
            if (condition.getPageSize() > 0) {
                pageSize = Math.min(condition.getPageSize(), 100);
            }
        }

        int offset = (int) ((pageNum - 1) * pageSize);

        List<PointsRecordDTO> records = pointsRecordMapper.selectPointsRecordList(condition, offset, (int) pageSize);
        Long total = (long) pointsRecordMapper.countPointsRecord(condition);

        PageDTO<PointsRecordDTO> pageResult = new PageDTO<>();
        pageResult.setRows(records);
        pageResult.setTotal(total);
        pageResult.setPageIndex(pageNum);
        pageResult.setPageSize(pageSize);

        return JsonVO.success(pageResult);
    }


    @Override
    public JsonVO<String> updatePointsRecord(List<PointsRecordUpdateDTO> updateDtos) {
        try {
            if (updateDtos == null || updateDtos.isEmpty()) {
                return JsonVO.fail("调整数据不能为空");
            }
            for (PointsRecordUpdateDTO dto : updateDtos) {
                pointsRecordMapper.updatePointsRecord(dto);
            }
            return JsonVO.success("积分调整成功");
        } catch (Exception e) {
            return JsonVO.fail("调整失败：" + e.getMessage());
        }
    }

}
