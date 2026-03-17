package com.zeroone.star.finance.controller;

import com.alibaba.excel.EasyExcel;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.FinanceRecordDTO;
import com.zeroone.star.project.j6.finance.FundManageApis;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.net.URLEncoder;
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

    /**
     * 导出Excel（下载数据模板或报表）
     * GET /api/excel/download
     */
    @GetMapping("/download")
    @ApiOperation("导出")
    @Override
    public void download(HttpServletResponse response) throws IOException {
        // 1. 设置响应头
        String fileName = URLEncoder.encode("用户列表", "UTF-8").replaceAll("\\+", "%20");
        response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
        response.setCharacterEncoding("utf-8");
        response.setHeader("Content-Disposition", "attachment;filename=" + fileName + ".xlsx");
        //todo
        // 2. 准备数据
        List<FinanceRecordDTO> dataList = null;

        // 3. 使用EasyExcel写入数据并输出到响应流
        EasyExcel.write(response.getOutputStream(), FinanceRecordDTO.class)
                .sheet("项款记录表") // 设置Sheet名称
                .doWrite(dataList); // 写入数据
    }
}
