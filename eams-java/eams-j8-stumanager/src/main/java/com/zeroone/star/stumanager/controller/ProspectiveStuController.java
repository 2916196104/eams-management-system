package com.zeroone.star.stumanager.controller;

import cn.hutool.core.date.DateTime;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.j8.stumanager.ProspectiveStuApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.stumanager.entity.Student;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiModelProperty;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.List;

/**
 * 意向学员
 */
@Api(tags = "意向学员")
@RequestMapping("/stu/prospective-stu")
@RestController
public class ProspectiveStuController implements ProspectiveStuApis {

    @Resource
    private EasyExcelComponent excel;

    @ApiOperation("导出意向学员Excel")
    @PostMapping("/export")
    @Override
    public ResponseEntity<byte[]> exportProspectiveStu(@ApiParam(value = "导出意向学员的id列表", example = "[1, 2, 3]", required = true) @RequestBody List<Long> ids) throws IOException {
        // 导出到文件流中
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        // excel.export("test", out, Student.class, null);
        // 响应文件
        HttpHeaders headers = new HttpHeaders();
        String filename = "rep-" + DateTime.now().toString("yyyyMMddHHmmssS") + ".xlsx";
        headers.setContentDispositionFormData("attachment", filename);
        headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
        byte[] bytes = out.toByteArray();
        out.close();
        return new ResponseEntity<>(bytes, headers, HttpStatus.CREATED);
    }

    @ApiOperation("导入意向学员")
    @PostMapping("/import")
    @Override
    public JsonVO<String> importProspectiveStu(@ApiParam(value = "意向学员excel数据", required = true) MultipartFile file) {
        return JsonVO.success("导入成功");
    }
}
