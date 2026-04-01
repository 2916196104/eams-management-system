package com.zeroone.star.finance.controller;

import com.alibaba.excel.EasyExcel;
import com.zeroone.star.finance.service.FundManageService;
import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsFileInfo;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.finance.FinanceRecordDTO;
import com.zeroone.star.project.j6.finance.FundManageApis;
import com.zeroone.star.project.query.j6.finance.FinanceRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.finance.FinanceRecordVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletResponse;
import java.io.ByteArrayOutputStream;
import java.util.List;

/**
 * 款项管理Controller
 */
@RestController
@RequestMapping("/j6-finance/fund")
@Api(tags = "款项管理")
public class FundManageController implements FundManageApis {

    private static final String EXPORT_NAME = "款项记录表";

    @Autowired
    private FundManageService fundManageService;

    @Autowired
    private FastDfsClientComponent fastDfsClient;

    @Value("${fastdfs.nginx-servers}")
    private String fastDfsNginxHost;

    @GetMapping("/list")
    @ApiOperation("获取款项列表（条件+分页）")
    @Override
    public JsonVO<PageDTO<FinanceRecordDTO>> queryPage(FinanceRecordQuery condition) {
        return fundManageService.queryPage(condition);
    }

    @PutMapping("/confirm")
    @ApiOperation("批量确认款项")
    @Override
    public JsonVO<List<Long>> confirm(@RequestBody List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要确认的款项");
        }
        return fundManageService.confirm(ids);
    }

    @PutMapping("/refuse")
    @ApiOperation("批量拒绝款项")
    @Override
    public JsonVO<List<Long>> refuse(@RequestBody List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return JsonVO.fail("请选择要拒绝的款项");
        }
        return fundManageService.refuse(ids);
    }

    @GetMapping("/download")
    @ApiOperation("导出款项记录，返回下载链接")
    @Override
    public JsonVO<String> download(HttpServletResponse response) {
        // 获取数据
        List<FinanceRecordVO> dataList = fundManageService.getFinanceRecords();

        // 使用 EasyExcel 生成 Excel 到内存
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        EasyExcel.write(out, FinanceRecordVO.class)
                .sheet(EXPORT_NAME)
                .doWrite(dataList);

        // 上传到 FastDFS
        FastDfsFileInfo fileInfo = null;
        try {
            fileInfo = fastDfsClient.uploadFile(out.toByteArray(), "xlsx");
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        // 获取下载链接
        String downloadUrl = fastDfsClient.fetchUrl(fileInfo, fastDfsNginxHost, true);

        return JsonVO.success(downloadUrl);
    }
}
