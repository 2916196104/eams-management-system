package com.zeroone.star.course.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.CourseSaveDTO;
import com.zeroone.star.course.entity.CourseDO;
import com.zeroone.star.project.query.j9.course.CourseQuery;
import com.zeroone.star.project.vo.j9.course.CourseDetailVO;
import com.zeroone.star.project.vo.j9.course.CourseExportVO;
import com.zeroone.star.project.vo.j9.course.CourseListVO;

import java.util.List;

public interface ICourseService extends IService<CourseDO> {

    PageDTO<CourseListVO> listCourseList(CourseQuery query);

    CourseDetailVO getCourseDetail(Long id);

    Long saveCourse(CourseSaveDTO dto);

    int removeBatch(List<Long> ids);

    boolean updateCourseState(List<Long> ids, Integer state);

    List<CourseExportVO> listExportData(CourseQuery query);
}
