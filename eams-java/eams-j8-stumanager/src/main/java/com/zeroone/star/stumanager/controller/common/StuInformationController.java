package com.zeroone.star.stumanager.controller.common;

import com.alibaba.cloud.commons.lang.StringUtils;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.ChangeStuStageDTO;
import com.zeroone.star.project.dto.j8.stumanager.SaveStu.SaveStuDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuChooseCourseDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuChooseStaffDTO;
import com.zeroone.star.project.dto.j8.stumanager.StudentHeadImgDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuSignCourseDTO;
import com.zeroone.star.project.j8.stumanager.common.StuInformationApis;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.CourseQuery;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.StaffQuery;
import com.zeroone.star.project.query.j8.stumanager.StudentQuery;
import com.zeroone.star.project.query.j8.stumanager.common.StudentCourseQuery;
import com.zeroone.star.project.query.j8.stumanager.common.StudentListQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentListVO;
import com.zeroone.star.project.vo.j8.stumanager.StudentVO;
import com.zeroone.star.stumanager.entity.Student;
import com.zeroone.star.stumanager.mapper.StudentMapper;
import com.zeroone.star.project.vo.j8.SaveStu.DictVO;
import com.zeroone.star.stumanager.mapper.StudentMapper;
import com.zeroone.star.stumanager.service.IStudentCourseService;
import com.zeroone.star.stumanager.service.IStudentService;
import com.zeroone.star.stumanager.service.impl.MsStuMapper;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiOperation;
import org.springframework.beans.BeanUtils;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;
import java.util.List;
import java.time.LocalDate;
import java.util.List;

/**
 * 学员信息
 */
@Api(tags = "共用接口-学员信息")
@RequestMapping("/stu/common/stuInformation")
@RestController
@Validated
public class StuInformationController implements StuInformationApis {

    @Resource
    private IStudentService iStudentService;

    @Resource
    MsStuMapper msStuMapper;

    @Resource
    private IStudentCourseService studentCourseService;

    @Resource
    IStudentCourseService iStudentCourseService;


    /**
     * 修改学生信息（适配模板风格）
     * @param saveStuDTO 学生修改DTO（JSON格式，含ID和修改后的信息）
     * @return 包含修改结果的JSON响应
     */
    @Resource
    StudentMapper studentMapper;

    //保存学员控制器
    @PostMapping("/save-student")
    @ApiOperation("修改学生信息")
    @Override
    public JsonVO<SaveStuDTO> saveStudent(@Validated @RequestBody SaveStuDTO saveStuDTO) {
        return iStudentService.saveStudent(saveStuDTO);
    }

    @PostMapping("/save-student/update-stage")
    @ApiOperation("修改学生状态")
    @Override
    public JsonVO<ChangeStuStageDTO> updateStudentStage(@Validated @RequestBody ChangeStuStageDTO changeStuStageDTO) {

        return iStudentService.updateStudentStage(changeStuStageDTO);
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
        return iStudentService.listFamilyRel();
    }

    @Override
    @GetMapping("/get-studentDetail")
    @ApiOperation(value = "查询学员详细信息")
    public JsonVO<StudentVO> getStudentDetail(StudentQuery query) {
        if (query == null || query.getId() == null) {
            return JsonVO.fail("学员ID不能为空");
        }
        LambdaQueryWrapper<Student> queryWrapper = new LambdaQueryWrapper<>();
        queryWrapper.eq(Student::getId, query.getId());
        queryWrapper.like(StringUtils.isNotEmpty(query.getName()), Student::getName, query.getName());
        queryWrapper.eq(StringUtils.isNotEmpty(query.getBranchSchool()), Student::getSchoolId, query.getBranchSchool());
        queryWrapper.eq(StringUtils.isNotEmpty(query.getGrade()), Student::getGrade, query.getGrade());
        queryWrapper.like(StringUtils.isNotEmpty(query.getTeacherName()), Student::getCounselor, query.getTeacherName());//StudentVo:counselor,StudentQuery:teacherName;
        Student student=iStudentService.getOne(queryWrapper);
        if(student == null){
            return JsonVO.fail("未找到该学员信息");
        }
        StudentVO studentVO=new StudentVO();
        BeanUtils.copyProperties(student,studentVO);
        return JsonVO.success(studentVO);
    }

    @Override
    @PutMapping("/update-studentHeadImg")
    @ApiOperation(value = "修改学员头像")
    public JsonVO<String> updateStudentHeadImg(@Validated @RequestBody StudentHeadImgDTO studentHeadImgDTO ) {
        LambdaUpdateWrapper<Student> updateWrapper = new LambdaUpdateWrapper<>();
        updateWrapper.eq(Student::getId,studentHeadImgDTO.getId());
        updateWrapper.set(Student::getHeadImg,studentHeadImgDTO.getId());//Student:headImg
        boolean success = iStudentService.update(updateWrapper);
        if(!success){
            return JsonVO.fail("修改头像失败");
        }
//        StudentHeadImgVO studentHeadImgVO=new StudentHeadImgVO();
//        studentHeadImgVO.setId(studentHeadImgDTO.getId());
//        studentHeadImgVO.setHeadImg(studentHeadImgDTO.getHeadImg());
        return JsonVO.success("修改头像成功");
    }


    @GetMapping("/query-studentlist")
    @ApiOperation(value = "获取学员列表")
    public  JsonVO<PageDTO<StudentListVO>> queryStudents(@Validated StudentListQuery query) {
        PageDTO<StudentListVO> pageDTO= iStudentService.listStudents(query);
        if (pageDTO.getTotal() == 0) {
            return JsonVO.create(pageDTO, 10000, "未找到相关数据");
        }
        return JsonVO.success(pageDTO);
    }

    @GetMapping("/query-listByCourse")
    @ApiOperation(value = "获取学员课程数据列表")
    @Override
    public JsonVO<PageDTO<StudentCourseVO>> queryStudentsByCourse(@Validated StudentCourseQuery condition) {
        PageDTO<StudentCourseVO> pageDTO = iStudentCourseService.listStudentsByCourse(condition);
        if (pageDTO.getTotal() == 0) {
            return JsonVO.create(pageDTO, 10000, "未找到相关数据");
        }
        return JsonVO.success(pageDTO);
    }

    @GetMapping("/dict/grade")
    @ApiOperation("获取年级字典下拉列表")
    public JsonVO<List<DictVO>> listGradeDict() {
        return iStudentService.listGradeDict();
    }

    @GetMapping("/dict/source")
    @ApiOperation("获取来源字典列表")
    @Override
    public JsonVO<List<DictVO>> listJoinWayDict() {
        return iStudentService.listJoinWayDict();
    }
}