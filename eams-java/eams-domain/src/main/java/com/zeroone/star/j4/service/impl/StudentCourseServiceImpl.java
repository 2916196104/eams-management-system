package com.zeroone.star.j4.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j4.entity.Course;
import com.zeroone.star.j4.entity.Student;
import com.zeroone.star.j4.entity.StudentCourse;
import com.zeroone.star.j4.mapper.CourseMapper;
import com.zeroone.star.j4.mapper.StudentCourseMapper;
import com.zeroone.star.j4.mapper.StudentMapper;
import com.zeroone.star.j4.service.IStudentCourseService;
import com.zeroone.star.project.dto.ExtendPageDTO;
import com.zeroone.star.project.dto.j4.student.EnrollmentDTO;
import org.springframework.beans.BeanUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

@Service
public class StudentCourseServiceImpl extends ServiceImpl<StudentCourseMapper, StudentCourse>
        implements IStudentCourseService {

    @Autowired
    private StudentMapper studentMapper;

    @Autowired
    private CourseMapper courseMapper;

    @Override
    public IPage<EnrollmentDTO> getEnrollmentList(ExtendPageDTO extendPageDTO) {
        // 获取分页参数（使用 pageIndex 和 pageSize）
        Long pageIndex = extendPageDTO.getPageIndex() != null ? extendPageDTO.getPageIndex() : 1L;
        Long pageSize = extendPageDTO.getPageSize() != null ? extendPageDTO.getPageSize() : 10L;

        // 创建分页对象（注意：Page 需要的是 long 类型）
        Page<StudentCourse> page = new Page<>(pageIndex, pageSize);

        // 构建查询条件
        LambdaQueryWrapper<StudentCourse> wrapper = new LambdaQueryWrapper<>();
        wrapper.orderByDesc(StudentCourse::getAddTime);

        // 执行分页查询
        IPage<StudentCourse> pageResult = this.page(page, wrapper);

        // 如果查询结果为空，返回空分页
        if (pageResult.getRecords().isEmpty()) {
            Page<EnrollmentDTO> emptyPage = new Page<>(pageIndex, pageSize);
            emptyPage.setTotal(0);
            return emptyPage;
        }

        // 收集所有 studentId 和 courseId
        List<Long> studentIds = pageResult.getRecords().stream()
                .map(StudentCourse::getStudentId)
                .distinct()
                .collect(Collectors.toList());

        List<Long> courseIds = pageResult.getRecords().stream()
                .map(StudentCourse::getCourseId)
                .distinct()
                .collect(Collectors.toList());

        // 批量查询关联数据
        Map<Long, Student> studentMap = studentMapper.selectBatchIds(studentIds).stream()
                .collect(Collectors.toMap(Student::getId, s -> s));

        Map<Long, Course> courseMap = courseMapper.selectBatchIds(courseIds).stream()
                .collect(Collectors.toMap(Course::getId, c -> c));

        // 转换为 DTO
        List<EnrollmentDTO> dtoList = pageResult.getRecords().stream()
                .map(sc -> {
                    EnrollmentDTO dto = new EnrollmentDTO();
                    BeanUtils.copyProperties(sc, dto);

                    Student student = studentMap.get(sc.getStudentId());
                    if (student != null) {
                        dto.setStudentName(student.getName());
                    }

                    Course course = courseMap.get(sc.getCourseId());
                    if (course != null) {
                        dto.setCourseName(course.getName());
                    }

                    return dto;
                })
                .collect(Collectors.toList());

        // 封装返回结果
        Page<EnrollmentDTO> resultPage = new Page<>(pageIndex, pageSize);
        resultPage.setRecords(dtoList);
        resultPage.setTotal(pageResult.getTotal());

        return resultPage;
    }
}
