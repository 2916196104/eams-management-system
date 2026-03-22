package com.zeroone.star.finance.controller;

import com.alibaba.excel.EasyExcel;
import com.zeroone.star.finance.service.FundManageService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.j6.finance.FundManageApis;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.FinanceRecordVo;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.util.List;

@RestController
@RequestMapping("/j6/finance/fund")
@Api(tags = "Fund Manage")
public class FundManageController implements FundManageApis {

    private static final String EXPORT_NAME = "\u6b3e\u9879\u8bb0\u5f55\u8868";

    @Autowired
    private FundManageService fundManageService;

    @GetMapping
    @ApiOperation("Query fund records")
    @Override
    public JsonVO<PageDTO<FinanceRecordVo>> queryPage(FinanceRecordQuery condition) {
        return null;
    }

    @PutMapping("/confirm")
    @ApiOperation("Confirm fund records")
    @Override
    public JsonVO<List<Long>> confirm(@RequestBody List<Long> ids) {
        return null;
    }

    @PutMapping("/refuse")
    @ApiOperation("Refuse fund records")
    @Override
    public JsonVO<List<Long>> refuse(@RequestBody List<Long> ids) {
        return null;
    }

    @GetMapping("/download")
    @ApiOperation("Export all fund records")
    @Override
    public void download(HttpServletResponse response) throws IOException {
        String fileName = URLEncoder.encode(EXPORT_NAME, String.valueOf(StandardCharsets.UTF_8)).replaceAll("\\+", "%20");
        response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
        response.setCharacterEncoding("utf-8");
        response.setHeader("Content-Disposition", "attachment;filename*=UTF-8''" + fileName + ".xlsx");

        List<FinanceRecordVo> dataList = fundManageService.getFinanceRecords();
        EasyExcel.write(response.getOutputStream(), FinanceRecordVo.class)
                .sheet(EXPORT_NAME)
                .doWrite(dataList);
    }
}
