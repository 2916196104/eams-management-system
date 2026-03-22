package com.zeroone.star.finance.service.impl;

import com.zeroone.star.finance.mapper.FundManageMapper;
import com.zeroone.star.finance.service.FundManageService;
import com.zeroone.star.project.vo.j6.finance.FinanceRecordVo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class FundManageServiceImpl implements FundManageService {

    @Autowired
    private FundManageMapper fundManageMapper;

    public List<FinanceRecordVo> getFinanceRecords() {
        // 从数据库获取数据
        return fundManageMapper.findAll(); // 或者你可以写自定义查询
    }

}
