package com.zeroone.star.finance.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.finance.mapper.FinanceRecordMapper;
import com.zeroone.star.finance.service.FinanceRecordService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.FinanceRecordVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class FinanceRecordServiceImpl implements FinanceRecordService {

    @Autowired
    private FinanceRecordMapper financeRecordMapper;

    @Override
    public JsonVO<PageDTO<FinanceRecordVO>> queryPage(FinanceRecordQuery condition) {
        Page<FinanceRecordVO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());
        IPage<FinanceRecordVO> recordIPage = financeRecordMapper.selectPageVO(page, condition);

        PageDTO<FinanceRecordVO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(recordIPage.getCurrent());
        pageDTO.setPageSize(recordIPage.getSize());
        pageDTO.setTotal(recordIPage.getTotal());
        pageDTO.setRows(recordIPage.getRecords());

        return JsonVO.success(pageDTO);
    }

    @Override
    public JsonVO<List<Long>> confirm(List<Long> ids) {
        int count = financeRecordMapper.batchConfirm(ids);
        if(count == 0) {
            return JsonVO.fail("未找到可确认的款项记录");
        }
        return JsonVO.success(ids);
    }

    @Override
    public JsonVO<List<Long>> refuse(List<Long> ids) {
        int count = financeRecordMapper.batchRefuse(ids);
        if(count == 0) {
            return JsonVO.fail("未找到可拒绝的款项记录");
        }
        return JsonVO.success(ids);
    }
}
