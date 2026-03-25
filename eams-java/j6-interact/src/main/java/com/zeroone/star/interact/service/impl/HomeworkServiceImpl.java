package com.zeroone.star.interact.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.interact.entity.Homework;
import com.zeroone.star.interact.mapper.HomeworkMapper;
import com.zeroone.star.interact.service.HomeworkService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.HomeworkDetailDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkListDto;
import com.zeroone.star.project.query.j6.interact.HomeworkQuery;
import com.zeroone.star.project.vo.j6.interact.HomeworkDetailVO;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.util.StringUtils;

import java.time.LocalDateTime;


@Service
public class HomeworkServiceImpl implements HomeworkService {

    @Autowired
    private HomeworkMapper homeworkMapper;

    @Override
    public PageDTO<HomeworkListDto> pageQuery(HomeworkQuery homeworkQuery) {
        // 创建分页对象
        Page<Homework> page = new Page<>(homeworkQuery.getPageIndex(), homeworkQuery.getPageSize());

        // 构建查询条件
        LambdaQueryWrapper<Homework> wrapper = new LambdaQueryWrapper<>();
        // 标题模糊查询
        if (StringUtils.hasText(homeworkQuery.getTitle())) {
            wrapper.like(Homework::getTitle, homeworkQuery.getTitle());
        }
        // 班级精确查询
        if (homeworkQuery.getClass_id() != null) {
            wrapper.eq(Homework::getClassId, homeworkQuery.getClass_id());
        }
        // 按添加时间降序排列
        wrapper.orderByDesc(Homework::getAddTime);

        // 执行分页查询
        Page<Homework> resultPage = homeworkMapper.selectPage(page, wrapper);

        // 转换为DTO
        return PageDTO.create(resultPage, entity -> {
            HomeworkListDto dto = new HomeworkListDto();
            dto.setId(entity.getId());
            dto.setTitle(entity.getTitle());
            dto.setClass_id(entity.getClassId());
            dto.setAdd_time(entity.getAddTime());
            // TODO: 需要关联查询用户表获取发布者名称
            // dto.setCreator(creatorName);
            // TODO: 需要统计提交数
            // dto.setSubmit_data(submitCount);
            return dto;
        });
    }

    @Override
    public HomeworkDetailVO getHomeworkDetail(Long id) {
        return homeworkMapper.selectById(id);
    }


    @Override
    public Long saveHomework(HomeworkDetailDto homeworkDetailDto) {
        Homework homework = new Homework();

        // 修改作业
        if (homeworkDetailDto.getId() != null) {
            homework.setId(homeworkDetailDto.getId());
            homework.setClassId(homeworkDetailDto.getClass_id());
            homework.setTitle(homeworkDetailDto.getTitle());
            homework.setContent(homeworkDetailDto.getContent());
            homework.setEditTime(LocalDateTime.now());

            homeworkMapper.updateById(homework);

            return homework.getId();
        }
        // 新增作业
        else {
            homework.setClassId(homeworkDetailDto.getClass_id());
            homework.setTitle(homeworkDetailDto.getTitle());
            homework.setContent(homeworkDetailDto.getContent());
            homework.setCreator(homeworkDetailDto.getCreator());
            homework.setAddTime(LocalDateTime.now());
            homework.setEditTime(LocalDateTime.now());

            homeworkMapper.insert(homework);

            return homework.getId();
        }
    }


}
