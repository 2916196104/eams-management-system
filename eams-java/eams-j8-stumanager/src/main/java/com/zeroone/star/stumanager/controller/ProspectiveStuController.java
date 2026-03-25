package com.zeroone.star.stumanager.controller;

import cn.hutool.core.date.DateTime;
import com.alibaba.excel.EasyExcel;
import com.alibaba.excel.ExcelWriter;
import com.alibaba.excel.write.metadata.WriteSheet;
import com.zeroone.star.project.components.easyexcel.EasyExcelComponent;
import com.zeroone.star.project.j8.stumanager.ProspectiveStuApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.ProspectiveStuVO;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.entity.User;
import com.zeroone.star.stumanager.service.IStudentService;
import com.zeroone.star.stumanager.service.IUserService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import io.swagger.annotations.ApiParam;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletResponse;
import java.io.ByteArrayOutputStream;
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
    public void exportProspectiveStu(HttpServletResponse response, @ApiParam(value = "导出意向学员的id列表", example = "[1, 2, 3]", required = true) @RequestBody List<Long> ids) throws IOException {

        List<ProspectiveStuVO> list = studentService.queryStudents(ids);

        String filename = "student-" + DateTime.now().toString("yyyyMMddHHmmssS") + ".xlsx";
        response.setContentType("application/vnd.openxmlformats-officedocument.spreadsheetml.sheet");
        response.setCharacterEncoding("UTF-8");
//        response.setHeader("Content-Disposition", "attachment;filename=" + URLEncoder.encode(filename, "UTF-8"));
        response.setHeader("Content-Disposition", "attachment;filename*=UTF-8''" + URLEncoder.encode(filename, StandardCharsets.UTF_8.name()));
        try {
            export("student", response.getOutputStream(), ProspectiveStuVO.class, list);
        } catch (Exception e) {
            e.printStackTrace();
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
    public JsonVO<String> importProspectiveStu(@ApiParam(value = "意向学员excel数据", required = true) MultipartFile file) throws IOException {
        InputStream input = file.getInputStream();
        List<ProspectiveStuVO> list = excel.parseExcel(input, "student", ProspectiveStuVO.class);
        if(list != null && list.size() > 0) {

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

            studentService.saveBatch(students);

            return JsonVO.success("导入成功");
        } else {
            return JsonVO.fail("导入失败");
        }
    }
}
