package com.zeroone.star.stumanager.controller;

import cn.hutool.core.date.DateTime;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.j8.stumanager.GraduatedStuApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.project.vo.j8.stumanager.GraduatedStuVO;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.entity.User;
import com.zeroone.star.stumanager.service.IStudentService;
import com.zeroone.star.stumanager.service.IUserService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.InputStream;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.stream.Collectors;

/**
 * 结业学员控制器
 */
@Api(tags = "结业学员")
@RequestMapping("/stu/graduated-stu")
@RestController
public class GraduatedStuController implements GraduatedStuApis {

    @Resource
    private IStudentService studentService;
    
    @Resource
    private IUserService userService;
    
    @Resource
    private EasyExcelComponent excel;

    /**
     * 导出结业学员列表
     */
    @GetMapping("/export")
    @ApiOperation(value = "导出结业学员列表", notes = "导出Excel格式的结业学员列表")
    @Override
    public void exportGraduatedStudents(HttpServletResponse response) {
        try {
            // 查询所有结业学员（stage = 2 表示结业）
            List<Student> students = studentService.list();
            
            // 转换为VO对象
            List<GraduatedStuVO> list = students.stream()
                    .filter(student -> student.getStage() == 2) // 只导出结业学员
                    .map(student -> {
                        GraduatedStuVO vo = new GraduatedStuVO();
                        vo.setId(student.getId());
                        vo.setName(student.getName());
                        // vo.setPhone(student.getPhone());
                        vo.setSex(student.getGender() == 0 ? "男" : "女");
                        vo.setBirthday(student.getBirthday());
                        // 这里可以根据实际情况设置其他字段
                        return vo;
                    })
                    .collect(Collectors.toList());

            String filename = "graduated-student-" + DateTime.now().toString("yyyyMMddHHmmssS") + ".xlsx";
            response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
            response.setCharacterEncoding("UTF-8");
            response.setHeader("Content-Disposition", "attachment;filename*=UTF-8''" + URLEncoder.encode(filename, StandardCharsets.UTF_8.name()));
            
            excel.export("graduated-student", response.getOutputStream(), GraduatedStuVO.class, list);
        } catch (Exception e) {
            // 如果流还未提交，可重置响应返回错误；否则只能记录日志
            if (!response.isCommitted()) {
                try {
                    response.reset();
                    response.sendError(HttpStatus.INTERNAL_SERVER_ERROR.value(), "导出失败");
                } catch (IOException ex) {
                    ex.printStackTrace();
                }
            }
        }
    }

    /**
     * 导入结业学员
     */
    @PostMapping("/import")
    @ApiOperation(value = "导入结业学员", notes = "通过Excel文件批量导入结业学员")
    @Override
    public JsonVO<String> importGraduatedStudents(@ApiParam(value = "结业学员excel数据", required = true) @RequestParam("file") MultipartFile file) {
        String fileName = file.getOriginalFilename();
        if(fileName == null || !fileName.endsWith(".xlsx") && !fileName.toLowerCase().endsWith(".xls")) {
            return JsonVO.fail("文件类型错误，仅支持.xlsx和.xls文件的解析");
        }

        try {
            InputStream input = file.getInputStream();
            List<GraduatedStuVO> list = excel.parseExcel(input, "graduated-student", GraduatedStuVO.class);
            if(list == null || list.isEmpty()) {
                return JsonVO.create("文件内容为空", ResultStatus.FAIL.getCode(), "文件没有数据");
            }
            
            List<Student> students = list.stream().map(
                    item -> {
                        User user = new User();
                        user.setName(item.getParentName());
                        user.setMobile(item.getPhone());
                        userService.save(user);

                        Student student = new Student();
                        student.setId(item.getId());
                        student.setName(item.getName());
                        student.setGender(item.getSex().equals("男") ? 0 : 1);
                        student.setBirthday(item.getBirthday());
                        // student.setPhone(item.getPhone());
                        student.setUserId(user.getId());
                        student.setStage(2); // 设置为结业状态
                        student.setFamilyRel(item.getFamilyRel().equals("非直系亲属") ? 1 : 0);
                        return student;
                    }
            ).collect(Collectors.toList());

            int success = 0;
            int fail = 0;
            for (Student student : students) {
                if (studentService.save(student)) {
                    success++;
                } else {
                    fail++;
                }
            }
            return JsonVO.success("导入完成, 成功: " + success + "条, 失败: " + fail + "条");
        } catch (Exception e) {
            return JsonVO.create("导入学员失败", ResultStatus.FAIL.getCode(), e.getMessage());
        }
    }
}
