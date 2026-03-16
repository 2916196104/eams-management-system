package com.zeroone.star.student.controller;

import com.zeroone.star.project.j4.student.StudentApis;
import com.zeroone.star.student.service.IStudentService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.http.MediaType;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletResponse;

/**
 * <p>
 * 描述：学员管理及跟进记录接口实现类
 */
@RestController
@RequestMapping("/j4/student")
@Api(tags = "学员管理")
public class StudentController implements StudentApis {

    @Resource
    private IStudentService studentService;

    @ApiOperation(value = "意向学员-导出全部")
    @GetMapping(value = "/export-intention", produces = MediaType.APPLICATION_OCTET_STREAM_VALUE)
    public void exportIntentionStudent(HttpServletResponse response) throws Exception {

        studentService.exportIntentionStudent(response);
    }

    @ApiOperation(value = "意向学员-批量导入")
    @PostMapping(value = "/import-intention", consumes = MediaType.MULTIPART_FORM_DATA_VALUE, produces = MediaType.APPLICATION_OCTET_STREAM_VALUE)
    public void importIntentionStudent(@RequestPart("file") MultipartFile file, HttpServletResponse response) throws Exception {
        studentService.importIntentionStudent(file, response);
    }
}