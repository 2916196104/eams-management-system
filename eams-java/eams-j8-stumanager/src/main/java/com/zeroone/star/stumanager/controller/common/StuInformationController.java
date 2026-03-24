package com.zeroone.star.stumanager.controller.common;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.SaveStu.ChangeStuStageDTO;
import com.zeroone.star.project.dto.j8.SaveStu.SaveStuDTO;
import com.zeroone.star.project.dto.j8.StuSignCourse.*;
import com.zeroone.star.project.j8.stumanager.common.StuInformationApis;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.CourseQuery;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.SaveStu.DictVO;
import com.zeroone.star.stumanager.service.IStudentCourseService;
import com.zeroone.star.stumanager.service.IStudentService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;

/**
 * <p>
 * 描述：学员信息管理控制器
 * </p>
 * <p>版权：&copy;01星球</p>
 * <p>地址：01星球总部</p>
 * @author tsfmn
 * @version 1.0.0
 */
@RestController
@RequestMapping("/StuInformation")
@Api(tags = "学员信息管理")
@Validated
public class StuInformationController implements StuInformationApis {

    @Resource
    private IStudentService studentService;

    @Resource
    private IStudentCourseService studentCourseService;


    /**
     * 修改学生信息（适配模板风格）
     * @param saveStuDTO 学生修改DTO（JSON格式，含ID和修改后的信息）
     * @return 包含修改结果的JSON响应
     */
    @PostMapping("/save-student")
    @ApiOperation("修改学生信息")
    @Override
    public JsonVO<SaveStuDTO> saveStudent(@Validated @RequestBody SaveStuDTO saveStuDTO) {
        return studentService.saveStudent(saveStuDTO);
    }

    @PostMapping("/save-student/update-stage")
    @ApiOperation("修改学生状态")
    @Override
    public JsonVO<ChangeStuStageDTO> updateStudentStage(@Validated @RequestBody ChangeStuStageDTO changeStuStageDTO) {

        return studentService.updateStudentStage(changeStuStageDTO);
    }

    /**
     * 学员报名课程
     */
    @PostMapping("/enroll-course")
    @ApiOperation(value = "学员报名课程")
    @Override
    public JsonVO<StuSignCourseDTO> enrollCourse(@RequestBody StuSignCourseDTO stuSignCourseDTO) {
        return studentCourseService.enrollCourse(stuSignCourseDTO);
    }


    @GetMapping("/enroll-course/select-course")
    @ApiOperation("获取分页选择课程信息")
    @Override
    public JsonVO<PageDTO<StuChooseCourseDTO>> CourseSelect(CourseQuery courseQuery) {

        return studentCourseService.CourseSelect(courseQuery);
    }

    @GetMapping("/enroll-course/select-staff")
    @ApiOperation("获取分页经手人信息")
    @Override
    public JsonVO<PageDTO<StuChooseStaffDTO>> StaffSelect(StaffQuery query) {
        // 直接调用service实现
        return studentCourseService.StaffSelect(query);
    }

    @GetMapping("/dict/family-relation")
    @ApiOperation("获取亲属关系字典列表")
    @Override
    public JsonVO<List<DictVO>> listFamilyRel() {
        return studentService.listFamilyRel();
    }

    @GetMapping("/dict/grade")
    @ApiOperation("获取年级字典下拉列表")
    public JsonVO<List<DictVO>> listGradeDict() {
        return studentService.listGradeDict();
    }

    @GetMapping("/dict/source")
    @ApiOperation("获取来源字典列表")
    @Override
    public JsonVO<List<DictVO>> listJoinWayDict() {
        return studentService.listJoinWayDict();
    }


}