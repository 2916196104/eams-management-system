package com.zeroone.star.stumanager.controller;

import cn.hutool.core.date.DateTime;
import com.alibaba.excel.EasyExcel;
import com.alibaba.excel.ExcelWriter;
import com.alibaba.excel.write.metadata.WriteSheet;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.j8.stumanager.ProspectiveStuApis;
import com.zeroone.star.project.query.j8.stumanager.ProspectiveStuQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.project.vo.j8.stumanager.ProspectiveStuVO;
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
import java.io.OutputStream;
import java.net.URLEncoder;
import java.nio.charset.StandardCharsets;
import java.util.List;
import java.util.stream.Collectors;

/**
 * 意向学员
 */
@Api(tags = "意向学员")
@RequestMapping("/stu/prospective-stu")
@RestController
public class ProspectiveStuController implements ProspectiveStuApis {

    @Resource
    private IStudentService studentService;
    @Resource
    private IUserService userService;

    @Resource
    private EasyExcelComponent excel;

    @ApiOperation("导出意向学员Excel")
    @PostMapping("/export")
    @Override
    public void exportProspectiveStu(HttpServletResponse response,
                                     @RequestBody ProspectiveStuQuery prospectiveStuQuery) throws IOException {

        List<ProspectiveStuVO> list = studentService.queryStudents(prospectiveStuQuery.getIds());

        String filename = "student-" + DateTime.now().toString("yyyyMMddHHmmssS") + ".xlsx";
        response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
        response.setCharacterEncoding("UTF-8");
//        response.setHeader("Content-Disposition", "attachment;filename=" + URLEncoder.encode(filename, "UTF-8"));
        response.setHeader("Content-Disposition", "attachment;filename*=UTF-8''" + URLEncoder.encode(filename, StandardCharsets.UTF_8.name()));
        try {
            export("student", response.getOutputStream(), ProspectiveStuVO.class, list);
        } catch (Exception e) {
            // 如果流还未提交，可重置响应返回错误；否则只能记录日志
            if (!response.isCommitted()) {
                response.reset();
                response.sendError(HttpStatus.INTERNAL_SERVER_ERROR.value(), "导出失败");
            }
        }
    }

    private static final int MAX_COUNT_PER_SHEET = 1000;

    public <T> void export(String sheetName, OutputStream os, Class<T> clazz, List<T> dataList) throws IOException {
        ExcelWriter writer = EasyExcel.write(os, clazz)
                .autoCloseStream(false)
                .build();

        int sheetCount = dataList.isEmpty() ? 1 :
                (dataList.size() + MAX_COUNT_PER_SHEET - 1) / MAX_COUNT_PER_SHEET;

        for (int i = 0; i < sheetCount; i++) {
            WriteSheet sheet = EasyExcel.writerSheet(i, sheetName + (i + 1)).build();
            int start = i * MAX_COUNT_PER_SHEET;
            int end = Math.min((i + 1) * MAX_COUNT_PER_SHEET, dataList.size());
            writer.write(dataList.subList(start, end), sheet);
        }

        writer.finish();
        os.flush();
    }

    @ApiOperation("导入意向学员")
    @PostMapping("/import")
    @Override
    public JsonVO<String> importProspectiveStu(@ApiParam(value = "意向学员excel数据", required = true) MultipartFile file) {

        String fileName = file.getOriginalFilename();
        if(fileName == null || !fileName.endsWith(".xlsx") || !fileName.toLowerCase().endsWith(".xls")) {
            return JsonVO.fail("文件类型错误，仅支持.xlsx和.xls文件的解析");
        }

        try {
            InputStream input = file.getInputStream();
            List<ProspectiveStuVO> list = excel.parseExcel(input, "student", ProspectiveStuVO.class);
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
                        student.setUserId(user.getId());
                        student.setStage(0);
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
