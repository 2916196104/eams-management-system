package com.zeroone.star.stumanager.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j8.stumanager.common.StudentCourseQuery;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.stumanager.entity.StudentCourse;
import com.zeroone.star.stumanager.mapper.StudentCourseMapper;
import com.zeroone.star.stumanager.service.IStudentCourseService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

/**
 * <p>
 * 课程数据表 服务实现类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Service
public class StudentCourseServiceImpl extends ServiceImpl<StudentCourseMapper, StudentCourse> implements IStudentCourseService {
    @Resource
    private StudentCourseMapper studentCourseMapper;

    @Override
    public PageDTO<StudentCourseVO> listStudentsByCourse(StudentCourseQuery condition) {
        // 1. 构建分页
        Page<StudentCourseVO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());
        // 2. 执行查询
        Page<StudentCourseVO> result = studentCourseMapper.getList(page, condition);
        // 3. 标准返回
        return PageDTO.create(result);
    }

}
