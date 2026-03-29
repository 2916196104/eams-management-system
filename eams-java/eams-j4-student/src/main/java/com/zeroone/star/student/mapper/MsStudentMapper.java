package com.zeroone.star.student.mapper;

import com.zeroone.star.project.vo.j4.student.CourseCounterVO;
import com.zeroone.star.student.entity.StudentCourse;
import org.mapstruct.AfterMapping;
import org.mapstruct.Mapper;
import org.mapstruct.Mapping;
import org.mapstruct.MappingTarget;

import java.math.BigDecimal;
import java.util.List;

@Mapper(componentModel = "spring")
public interface MsStudentMapper {

    @Mapping(source = "courseId", target = "courseName")
    @Mapping(source = "subjectId", target = "subjectName")
    CourseCounterVO toCourseCounterVO(StudentCourse studentCourse);
    @AfterMapping
    default void toCourseCounterVOAfter(StudentCourse source, @MappingTarget CourseCounterVO target){
        // 转换课程名和科目名

        // 计算购买课次
        Integer countLessonTotal = source.getCountLessonTotal();
        Integer countLessonRefund = source.getCountLessonRefund();
        target.setTotalCount(countLessonTotal-countLessonRefund);

        // 计算剩余课次
        int countLessonComplete = target.getCountLessonComplete();
        int totalCount = target.getTotalCount();
        target.setRemainingCount(totalCount-countLessonComplete);

        // 计算剩余金额
        BigDecimal unitPrice = target.getUnitPrice();
        int remainingCount = target.getRemainingCount();
        target.setRemainingAmount(unitPrice.multiply(BigDecimal.valueOf(remainingCount)));
    }
    List<CourseCounterVO> toCourseCounterVOList(List<StudentCourse> studentCourseDOList);
}
