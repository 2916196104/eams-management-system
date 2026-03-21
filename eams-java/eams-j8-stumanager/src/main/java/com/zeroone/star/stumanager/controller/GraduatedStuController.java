package com.zeroone.star.stumanager.controller;

import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.j8.stumanager.GraduatedStuApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import java.util.List;

/**
 * 结业学员
 */
@Api(tags = "结业学员")
@RequestMapping("/stu/graduated-stu")
@RestController
public class GraduatedStuController implements GraduatedStuApis {

    @Resource
    private EasyExcelComponent excel;

    @ApiOperation("导出结业学员")
    @PostMapping("/export")
    @Override
    public ResponseEntity<byte[]> exportPGraduatedStu(@ApiParam(value = "导出意向学员的id列表", example = "[1, 2, 3]", required = true) @RequestBody List<Long> ids) {
        return null;
    }

    @ApiOperation("导入结业学员")
    @PostMapping("/import")
    @Override
    public JsonVO<String> importGraduatedStu(@ApiParam(value = "意向学员excel数据", required = true) MultipartFile file) {
        return null;
    }
}
