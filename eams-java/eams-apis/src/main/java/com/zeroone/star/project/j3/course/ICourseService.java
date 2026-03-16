package com.zeroone.star.project.j3.course;
import javax.servlet.http.HttpServletResponse;

public interface ICourseService {
    /**
     * 导出所有课程数据
     * @param response 响应对象
     */
    void exportAllCourses(HttpServletResponse response);
}