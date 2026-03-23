package com.zeroone.star.stumanager.controller;

import com.zeroone.star.project.j8.stumanager.GraduatedStuApis;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpServletResponse;

/**
 * 结业学员控制器
 */
@Api(tags = "结业学员")
@RequestMapping("/stu/graduated-stu")
@RestController
public class GraduatedStuController implements GraduatedStuApis {

    /**
     * 导出结业学员列表
     */
    @GetMapping("/export")
    @ApiOperation(value = "导出结业学员列表", notes = "导出Excel格式的结业学员列表")
    @Override
    public void exportGraduatedStudents(HttpServletResponse response) {
        // 导出功能实现
    }

    /**
     * 导入结业学员
     */
    @PostMapping("/import")
    @ApiOperation(value = "导入结业学员", notes = "通过Excel文件批量导入结业学员")
    @Override
    public JsonVO<String> importGraduatedStudents(@RequestParam("file") MultipartFile file) {
        JsonVO<String> jsonVO = new JsonVO<>();
        jsonVO.setData("导入成功");
        jsonVO.setCode(10000);
        jsonVO.setMessage("success");
        return jsonVO;
    }
}
