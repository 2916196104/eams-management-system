package com.zeroone.star.course.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.conditions.update.LambdaUpdateWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.course.entity.*;
import com.zeroone.star.course.mapper.*;
import com.zeroone.star.course.service.ICourseService;
import com.zeroone.star.project.components.user.UserDTO;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.course.CourseDTO;
import com.zeroone.star.project.dto.j9.course.CourseSaveDTO;
import com.zeroone.star.project.dto.j9.course.CourseImageDTO;
import com.zeroone.star.project.dto.j9.course.CourseSectionDTO;
import com.zeroone.star.project.query.j9.course.CoursePageQuery;
import com.zeroone.star.project.query.j9.course.CourseQuery;
import com.zeroone.star.project.vo.j9.course.*;
import lombok.Data;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.Collections;
import java.util.Date;
import java.util.List;
import java.util.stream.Collectors;

/**
 * 课程 Service 实现
 * @author yangxiao
 */
@Service
public class CourseServiceImpl extends ServiceImpl<CourseMapper, CourseDO> implements ICourseService {

    @Resource
    private CourseMapper courseMapper;

    @Resource
    private SubjectMapper subjectMapper;

    @Resource
    private CourseImageMapper courseImageMapper;

    @Resource
    private UserHolder userHolder;

    @Override
    public PageDTO<CourseListVO> listCourseList(CourseQuery query) {
        Page<CourseListVO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        courseMapper.selectCourseList(page, query);
        PageDTO<CourseListVO> result = new PageDTO<>();
        result.setPageIndex(page.getCurrent());
        result.setPageSize(page.getSize());
        result.setTotal(page.getTotal());
        result.setPages(page.getPages());
        result.setRows(page.getRecords());
        return result;
    }

    @Override
    public CourseDetailVO getCourseDetail(Long id) {
        CourseDO courseDO = baseMapper.selectById(id);
        if (courseDO == null) {
            return null;
        }
        CourseDetailVO courseDetailVO = BeanUtil.copyProperties(courseDO, CourseDetailVO.class);
        //获取学科名称
        courseDetailVO.setSubjectName(subjectMapper.selectNameById(courseDO.getSubjectId()));

        //获取图集
        LambdaQueryWrapper<CourseImageDO> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(CourseImageDO::getCourseId, id);
        List<CourseImageDO> courseImageDOList = courseImageMapper.selectList(wrapper);
        List<CourseImageVO> courseImageVOList = courseImageDOList
                .stream()
                .map(courseImageDO -> BeanUtil.copyProperties(courseImageDO, CourseImageVO.class))
                .collect(Collectors.toList());
        courseDetailVO.setImages(courseImageVOList);

        return courseDetailVO;
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long saveCourse(CourseSaveDTO dto) {
        //获取当前时间
        LocalDateTime now = LocalDateTime.now();
        //判断是新增还是更新
        CourseDO courseDO = BeanUtil.copyProperties(dto, CourseDO.class);
        //获取当前用户ID
        Long userId = null;
        try {
            UserDTO currentUser = userHolder.getCurrentUser();
            userId = Long.valueOf(currentUser.getId());
        } catch (Exception e) {
            // 获取用户失败不影响主流程
        }

        if(dto.getId() != null){
            //更新
            courseDO.setEditTime(now);
            courseDO.setEditor(userId);
            courseMapper.updateById(courseDO);
        }else{
            courseDO.setAddTime(now);
            courseDO.setCreator(userId);
            courseMapper.insert(courseDO);
        }
        Long id = courseDO.getId();

        //更新图集（先删除旧图集，再新增新图集）
        LambdaUpdateWrapper<CourseImageDO> wrapper = new LambdaUpdateWrapper<>();
        wrapper.eq(CourseImageDO::getCourseId, id);
        courseImageMapper.delete(wrapper);
        List<CourseImageDTO> images = dto.getImages();
        if(images != null){
            images.forEach(image -> {
                CourseImageDO courseImageDo = BeanUtil.copyProperties(image, CourseImageDO.class);
                courseImageMapper.insert(courseImageDo);
            });
        }

        return id;
    }

    @Override
    public int removeBatch(List<Long> ids) {
        return baseMapper.deleteBatchIds(ids);
    }

    @Override
    public boolean updateCourseState(List<Long> ids, Integer state) {
        LambdaUpdateWrapper<CourseDO> wrapper = new LambdaUpdateWrapper<>();
        wrapper.in(CourseDO::getId, ids)
               .set(CourseDO::getState, state)
               .set(CourseDO::getEditTime, LocalDateTime.now());
        return update(wrapper);
    }

    @Override
    public List<CourseExportVO> listExportData(CourseQuery query) {
        return courseMapper.selectCourseExportList(query);
    }
}
