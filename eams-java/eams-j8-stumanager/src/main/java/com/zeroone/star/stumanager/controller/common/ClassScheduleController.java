package com.zeroone.star.stumanager.controller.common;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.zeroone.star.project.dto.CourseStatisticsDTO;
import com.zeroone.star.project.j8.stumanager.common.ClassScheduleApis;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.stumanager.entity.ClassStudent;
import com.zeroone.star.stumanager.entity.Course;
import com.zeroone.star.stumanager.service.IClassStudentService;
import com.zeroone.star.stumanager.service.ICourseService;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

/**
 * 班级与课表控制器（已修复所有报错）
 */
@RestController
public class ClassScheduleController implements ClassScheduleApis {

    // 仅注入已使用的Service，消除警告
    private final IClassStudentService classStudentService;
    private final ICourseService courseService;

    // 构造函数注入
    public ClassScheduleController(IClassStudentService classStudentService,
                                   ICourseService courseService) {
        this.classStudentService = classStudentService;
        this.courseService = courseService;
    }

    /**
     * 学生加入班级
     */
    @Override
    public JsonVO<Void> joinClass(
            @RequestParam Long studentId,
            @RequestParam Long classId) {
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

        return saveSuccess ? JsonVO.create(null, ResultStatus.SUCCESS) : JsonVO.fail("加入班级失败");
    }

    /**
     * 学生退出班级
     */
    @Override
    public JsonVO<Void> exitClass(
            @RequestParam Long studentId) {
        if (studentId == null || studentId <= 0) {
            return JsonVO.fail("学生ID不能为空且必须为正整数");
        }

        QueryWrapper<ClassStudent> deleteWrapper = new QueryWrapper<>();
        deleteWrapper.eq("student_id", studentId);
        boolean removeSuccess = classStudentService.remove(deleteWrapper);

        return removeSuccess ? JsonVO.create(null, ResultStatus.SUCCESS) : JsonVO.fail("退出班级失败");
    }

    /**
     * 班级课程统计（✅ 已适配真实Course实体，无报错）
     */
    @Override
    public JsonVO<CourseStatisticsDTO> courseStatistics(
            @RequestParam(required = false) Long classId) {
        CourseStatisticsDTO dto = new CourseStatisticsDTO();

        if (classId != null && classId > 0) {
            // 查询班级课程
            QueryWrapper<Course> courseQuery = new QueryWrapper<>();
            courseQuery.eq("class_id", classId);
            Course course = courseService.getOne(courseQuery);

            if (course != null) {
                // 匹配Course实体的真实字段
                dto.setCourseName(course.getName()); // 课程名：实体有name字段
                dto.setCourseCode(""); // 实体无课程代码，设为空
                // 课堂类型转换：1大课 2小班课 3 1v1
                if (course.getLessonType() != null) {
                    switch (course.getLessonType()) {
                        case 1: dto.setCourseType("大课"); break;
                        case 2: dto.setCourseType("小班课"); break;
                        case 3: dto.setCourseType("1v1"); break;
                        default: dto.setCourseType("未知类型");
                    }
                } else {
                    dto.setCourseType("");
                }
                dto.setCourseTime(""); // 实体无课程时间，设为空
                dto.setTeacherName(course.getTeacherInfo()); // 师资信息
                dto.setTeacherCode(""); // 实体无教师代码，设为空
            }

            // 简化：无学生/教师关联表，清空冗余赋值
            dto.setStudentName("");
            dto.setStudentCode("");
            dto.setStudentType("");
        } else {
            // 汇总数据
            dto.setCourseName("全部课程统计");
            dto.setCourseCode("ALL");
            dto.setCourseType("全类型");
            dto.setCourseTime("全时段");
            dto.setStudentType("全校");
        }

        return JsonVO.create(dto, ResultStatus.SUCCESS);
    }
}