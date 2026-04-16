package com.zeroone.star.stumanager.service.impl;

import com.alibaba.cloud.commons.lang.StringUtils;
import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuChooseCourseDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuChooseStaffDTO;
import com.zeroone.star.project.dto.j8.stumanager.common.StuSignCourseDTO;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.CourseQuery;
import com.zeroone.star.project.query.j8.StuSignCourseQuery.StaffQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.stumanager.entity.Course;
import com.zeroone.star.stumanager.entity.Staff;
import com.zeroone.star.project.query.j8.stumanager.common.StudentCourseQuery;
import com.zeroone.star.project.vo.j8.stumanager.StudentCourseVO;
import com.zeroone.star.stumanager.entity.StudentCourse;
import com.zeroone.star.stumanager.mapper.CourseMapper;
import com.zeroone.star.stumanager.mapper.StaffMapper;
import com.zeroone.star.stumanager.mapper.StudentCourseMapper;
import com.zeroone.star.stumanager.service.IStudentCourseService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;

/**
 * <p>
 * 报名签约表 服务实现类
 * </p>
 *
 * @author dabidai
 * @since 2026-03-14
 */
@Service
public class StudentCourseServiceImpl extends ServiceImpl<StudentCourseMapper, StudentCourse> implements IStudentCourseService {
    @Resource
    private StudentCourseMapper studentCourseMapper;

    @Resource
    StaffMapper staffMapper;

    @Resource
    CourseMapper courseMapper;

    @Resource
    MsStuCouMapper msStuCouMapper;

    @Override
    public PageDTO<StudentCourseVO> listStudentsByCourse(StudentCourseQuery condition) {
        // 1. 构建分页
        Page<StudentCourseVO> page = new Page<>(condition.getPageIndex(), condition.getPageSize());
        // 2. 执行查询
        Page<StudentCourseVO> result = studentCourseMapper.getList(page, condition);
        // 3. 标准返回
        return PageDTO.create(result);
    }

    /**
     * 学生课程报名接口实现
     *
     * @param stuSignCourseDTO 报名签单新增DTO（含前端传入的学生ID、课程ID等参数）
     * @return 包含报名结果的JSON响应对象
     */
    @Override
    @Transactional(rollbackFor = Exception.class) // 事务控制，异常回滚
    public JsonVO<StuSignCourseDTO> enrollCourse(StuSignCourseDTO stuSignCourseDTO) {
        // 1. DTO转换为实体对象
        StudentCourse studentCourse = msStuCouMapper.addDtoToStudentCourse(stuSignCourseDTO);

        // 2. 补充业务字段（前端未传但实体需要的字段）
        studentCourse.setAddTime(LocalDateTime.now()); // 创建时间
        studentCourse.setEditTime(LocalDateTime.now()); // 更新时间

        // 3. 执行业务操作：保存报名信息到数据库
        int insertCount = studentCourseMapper.insert(studentCourse);

        // 4. 校验保存结果，封装返回数据
        if (insertCount > 0) {
            // 实体转换为DTO（返回给前端）
            StuSignCourseDTO resultDTO = msStuCouMapper.studentCourseToStuSignCourseDto(studentCourse);
            // 返回成功响应（包含DTO数据）
            return JsonVO.success(resultDTO);
        } else {
            // 返回失败响应
            return JsonVO.fail("课程报名失败，请重试");
        }
    }


    @Override
    @Transactional(rollbackFor = Exception.class)
    public JsonVO<PageDTO<StuChooseCourseDTO>> CourseSelect(CourseQuery query) {
        // 1. 构建分页对象（页码、页大小）
        Page<Course> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 2. 构建查询条件：课程名称模糊搜索 + 排序
        QueryWrapper<Course> queryWrapper = new QueryWrapper<>();
        // 课程名称模糊查询
        queryWrapper.like(!StringUtils.isEmpty(query.getCourseName()), "name", query.getCourseName());
        // 排序：优先按更新时间/创建时间降序，再按ID降序
        queryWrapper.orderBy(true, false, "IFNULL(edit_time, add_time)");
        queryWrapper.orderBy(true, false, "id");

        // 3. 执行分页查询
        Page<Course> pageResult = courseMapper.selectPage(page, queryWrapper);

        // 4. 转换为DTO并封装为JsonVO
        PageDTO<StuChooseCourseDTO> pageDTO = PageDTO.create(pageResult, msStuCouMapper::courseToStuChooseCourseDto);
        // 返回完整分页对象
        return JsonVO.success(pageDTO);
    }

    /**
     * 分页+模糊查询经手人列表
     * @param query 分页+姓名模糊查询条件
     * @return 分页结果
     */
    @Override
    @Transactional(rollbackFor = Exception.class) // 事务控制，异常回滚
    public JsonVO<PageDTO<StuChooseStaffDTO>> StaffSelect(StaffQuery query) {
        // 1. 构建分页对象（页码、页大小）
        Page<Staff> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 2. 构建查询条件：员工姓名模糊搜索 + 排序
        QueryWrapper<Staff> queryWrapper = new QueryWrapper<>();
        // 员工姓名模糊查询（非空才拼接条件）
        queryWrapper.like(!StringUtils.isEmpty(query.getName()), "name", query.getName());
        // 排序：优先按更新时间/创建时间降序，再按ID降序（适配Staff表字段）
        queryWrapper.orderBy(true, false, "IFNULL(edit_time, add_time)");
        queryWrapper.orderBy(true, false, "id");

        // 3. 执行分页查询
        Page<Staff> pageResult = staffMapper.selectPage(page,queryWrapper);

        // 4. 转换为DTO并封装为JsonVO
        // 先映射为StuChooseStaffDTO，再向上转型为StuChooseStaffAddDTO（因StuChooseStaffDTO继承自AddDTO）
        PageDTO<StuChooseStaffDTO> pageDTO = PageDTO.create(pageResult,
                staff -> msStuCouMapper.staffToStuChooseStaffDto(staff));

        // 返回完整分页对象
        return JsonVO.success(pageDTO);
    }

}
