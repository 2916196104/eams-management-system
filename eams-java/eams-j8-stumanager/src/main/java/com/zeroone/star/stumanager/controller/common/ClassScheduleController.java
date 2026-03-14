package com.zeroone.star.stumanager.controller.common;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.zeroone.star.project.dto.CourseStatisticsDTO;
import com.zeroone.star.project.j8.stumanager.common.ClassScheduleApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.stumanager.entity.ClassStudent;
import com.zeroone.star.stumanager.service.IClassStudentService;
import io.swagger.v3.oas.annotations.Parameter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

/**
 * 班级与课表控制器
 */
@RestController
public class ClassScheduleController implements ClassScheduleApis {

    // 仅保留实际使用的Service，消除未使用字段警告
    private final IClassStudentService classStudentService;

    @Autowired
    public ClassScheduleController(IClassStudentService classStudentService) {
        this.classStudentService = classStudentService;
    }

    /**
     * 学生加入班级
     */
    @Override
    public JsonVO<Void> joinClass(
            @RequestParam @Parameter(required = true, description = "学生ID") Long studentId,
            @RequestParam @Parameter(required = true, description = "班级ID") Long classId) {
        // 1. 参数校验
        if (studentId == null || studentId <= 0) {
            return JsonVO.fail("学生ID不能为空且必须为正整数");
        }
        if (classId == null || classId <= 0) {
            return JsonVO.fail("班级ID不能为空且必须为正整数");
        }

        // 2. 检查是否已加入
        QueryWrapper<ClassStudent> checkWrapper = new QueryWrapper<>();
        checkWrapper.eq("student_id", studentId).eq("class_id", classId);
        if (classStudentService.count(checkWrapper) > 0) {
            return JsonVO.fail("学生已加入该班级，无需重复操作");
        }

        // 3. 插入关联记录
        ClassStudent classStudent = new ClassStudent();
        classStudent.setStudentId(studentId);
        classStudent.setClassId(classId);
        boolean saveSuccess = classStudentService.save(classStudent);

        // 4. 适配JsonVO：成功返回Void类型，失败返回提示
        if (saveSuccess) {
            // 使用create方法创建Void类型的成功结果
            return JsonVO.create(null, ResultStatus.SUCCESS);
        } else {
            return JsonVO.fail("加入班级失败，请检查班级/学生是否存在");
        }
    }

    /**
     * 学生退出班级
     */
    @Override
    public JsonVO<Void> exitClass(
            @RequestParam @Parameter(required = true, description = "学生ID") Long studentId) {
        // 参数校验
        if (studentId == null || studentId <= 0) {
            return JsonVO.fail("学生ID不能为空且必须为正整数");
        }

        // 删除关联记录
        QueryWrapper<ClassStudent> deleteWrapper = new QueryWrapper<>();
        deleteWrapper.eq("student_id", studentId);
        boolean removeSuccess = classStudentService.remove(deleteWrapper);

        // 适配JsonVO
        if (removeSuccess) {
            return JsonVO.create(null, ResultStatus.SUCCESS);
        } else {
            return JsonVO.fail("退出班级失败，该学生未绑定任何班级");
        }
    }

    /**
     * 班级课程统计（
     */
    @Override
    public JsonVO<CourseStatisticsDTO> courseStatistics(
            @RequestParam(required = false) @Parameter(description = "班级ID（为空则统计所有）") Long classId) {
        // 1. 初始化DTO并填充数据
        CourseStatisticsDTO statisticsDTO = new CourseStatisticsDTO();
        if (classId != null && classId > 0) {
            // 填充指定班级的统计数据（示例）
            statisticsDTO.setCourseName("Java编程");
            statisticsDTO.setCourseCode("JAVA2026");
            statisticsDTO.setCourseType("必修课");
            statisticsDTO.setCourseTime("周一1-2节");
            statisticsDTO.setStudentName("张三");
            statisticsDTO.setStudentCode("2026001");
            statisticsDTO.setStudentType("计算机学院");
            statisticsDTO.setTeacherName("李老师");
            statisticsDTO.setTeacherCode("T2026001");
        } else {
            // 填充所有班级的汇总数据
            statisticsDTO.setCourseName("所有课程汇总");
            statisticsDTO.setCourseCode("ALL_COURSE");
            statisticsDTO.setCourseType("全类型");
            statisticsDTO.setCourseTime("全时段");
            statisticsDTO.setStudentType("全校");
        }

        // 2. 使用create方法传入CourseStatisticsDTO对象
        return JsonVO.create(statisticsDTO, ResultStatus.SUCCESS);
    }
}