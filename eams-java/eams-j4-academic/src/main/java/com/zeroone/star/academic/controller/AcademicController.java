package com.zeroone.star.academic.controller;

import com.zeroone.star.academic.service.IAcademicFinanceService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.StudentDTO;
import com.zeroone.star.project.j4.academic.AcademicApis;
import com.zeroone.star.project.query.j4.student.StudentQuery;
import com.zeroone.star.project.vo.JsonVO;
import io.swagger.annotations.Api;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

/**
 * <p>
 * 描述：学员模块缴欠费与退费控制器
 * </p>
 */
@Validated
@RestController
@RequestMapping("/j4/academic")
@Api(tags = "学员模块财务接口")
public class AcademicController implements AcademicApis {
//    @Resource
    private IAcademicFinanceService academicFinanceService;

    @Override
    public JsonVO<PageDTO<StudentDTO>> queryPage(StudentQuery condition) {
        return null;
    }

    @Override
    public JsonVO<Long> saveStudents(StudentDTO studentDTO) {
        return null;
    }

    @Override
    public JsonVO<Long> deleteStudents(Long id) {
        return null;
    }

    @Override
    public JsonVO<Long> updateStudents(StudentDTO studentDTO) {
        return null;
    }

    @Override
    public JsonVO<StudentDTO> queryStudents(Long id) {
        return null;
    }

    @Override
    public JsonVO<List<StudentDTO>> queryStudents() {
        return null;
    }
}
