package com.zeroone.star.finance.controller;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.FinanceRecordDTO;
import com.zeroone.star.project.j6.finance.FundManageApis;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import java.util.List;

@RestController
@RequestMapping("/j6/finance/fund")
@Api(tags = "款项管理")
public class FundManageController implements FundManageApis {


    /**
     * 获取款项列表（条件+分页）
     *
     * @param condition 查询条件
     * @return 款项信息
     */
    @GetMapping
    @ApiOperation("获取款项列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<FinanceRecordDTO>> queryPage(FinanceRecordQuery condition) {
        return null;
    }

    /**
     * 批量确认
     *
     * @param ids 财务记录id
     * @return 修改款项信息
     */
    @PutMapping("/confirm")
    @ApiOperation("批量确认")
    @Override
    public JsonVO<List<Long>> confirm(@RequestBody List<Long> ids) {
        return null;
    }

    /**
     * 批量拒绝
     *
     * @param ids 财务记录id
     * @return 修改款项信息
     */
    @PutMapping("/refuse")
    @ApiOperation("批量拒绝")
    @Override
    public JsonVO<List<Long>> refuse(@RequestBody List<Long> ids) {
        return null;
    }
}
