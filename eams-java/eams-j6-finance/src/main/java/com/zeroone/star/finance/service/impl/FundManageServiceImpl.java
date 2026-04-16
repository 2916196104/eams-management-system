package com.zeroone.star.finance.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.finance.service.FundManageService;
import com.zeroone.star.finance.mapper.FundManageMapper;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.FinanceRecordDTO;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.FinanceRecordVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * 款项管理服务实现类
 */
@Service
public class FundManageServiceImpl implements FundManageService {

    @Autowired
    private FundManageMapper fundManageMapper;

    @Override
    public JsonVO<PageDTO<FinanceRecordDTO>> queryPage(FinanceRecordQuery condition) {
        Page<FinanceRecordDTO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());
        IPage<FinanceRecordDTO> recordIPage = fundManageMapper.selectPageDTO(page, condition);

        PageDTO<FinanceRecordDTO> pageDTO = new PageDTO<>();
        pageDTO.setPageIndex(recordIPage.getCurrent());
        pageDTO.setPageSize(recordIPage.getSize());
        pageDTO.setTotal(recordIPage.getTotal());
        pageDTO.setPages(recordIPage.getPages());
        pageDTO.setRows(recordIPage.getRecords());

        return JsonVO.success(pageDTO);
    }

    @Override
    public JsonVO<List<Long>> confirm(List<Long> ids) {
        int count = fundManageMapper.batchConfirm(ids);
        if (count == 0) {
            return JsonVO.fail("未找到可确认的款项记录");
        }
        return JsonVO.success(ids);
    }

    @Override
    public JsonVO<List<Long>> refuse(List<Long> ids) {
        int count = fundManageMapper.batchRefuse(ids);
        if (count == 0) {
            return JsonVO.fail("未找到可拒绝的款项记录");
        }
        return JsonVO.success(ids);
    }

    @Override
    public List<FinanceRecordVO> getFinanceRecords() {
        return fundManageMapper.findAll();
    }
}
