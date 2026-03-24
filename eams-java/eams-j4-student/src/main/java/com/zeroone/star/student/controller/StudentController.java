package com.zeroone.star.student.controller;

import com.zeroone.star.project.dto.j4.student.StudentQueryCondition;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.student.service.StudentGraduationService;
import io.swagger.annotations.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;
import javax.servlet.http.HttpServletResponse;
import java.net.URLEncoder;

/**
 * <p>
 * 学生表 前端控制器
 * </p>
 * @author gintoki
 * @since 2026-03-23
 */
@RestController
@RequestMapping("/student")
@Api(tags = "结业学员导入导出")
public class StudentController {
    @Autowired
    private StudentGraduationService studentGraduationService;
    /**
     * 结业学员导入（Excel文件）
     * @param file Excel文件（非空校验）
     */
    @PostMapping("/graduation/import")
    @ApiOperation("结业学员导入Excel")
    @ApiImplicitParam(name = "file", value = "上传Excel", dataType = "__file", paramType = "formData")
    public JsonVO<String> importExcel(@RequestParam("file") MultipartFile file) {
        studentGraduationService.importGraduationStudent(file);
        return JsonVO.success("导入成功");
    }
    @GetMapping("/graduation/export")
    @ApiOperation("结业学员导出Excel")
    public void export(
            // 关键：去掉 @RequestBody！！！
            StudentQueryCondition condition,
            HttpServletResponse response) {
        try {
            // 设置下载头（自动弹出保存）
            response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
            response.setCharacterEncoding("utf-8");
            String fileName = URLEncoder.encode("结业学员列表", "UTF-8");
            response.setHeader("Content-Disposition", "attachment;filename=" + fileName + ".xlsx");
            // 执行导出
            studentGraduationService.exportGraduationStudent(condition, response);
        } catch (Exception e) {
            throw new RuntimeException("导出失败");
        }
    }
}