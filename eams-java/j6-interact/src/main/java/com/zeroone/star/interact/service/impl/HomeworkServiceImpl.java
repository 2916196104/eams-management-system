package com.zeroone.star.interact.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.interact.entity.Homework;
import com.zeroone.star.interact.entity.HomeworkRecord;
import com.zeroone.star.interact.mapper.HomeworkMapper;
import com.zeroone.star.interact.mapper.HomeworkRecordMapper;
import com.zeroone.star.interact.service.HomeworkService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.HomeworkDetailDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkListDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkScoreDto;
import com.zeroone.star.project.query.j6.interact.HomeworkQuery;
import com.zeroone.star.project.vo.j6.interact.HomeworkDetailVO;
import com.zeroone.star.project.vo.j6.interact.HomeworkSubmissionListVo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.util.StringUtils;

import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;


@Service
public class HomeworkServiceImpl implements HomeworkService {

    @Autowired
    private HomeworkMapper homeworkMapper;

    @Autowired
    private HomeworkRecordMapper homeworkRecordMapper;

    /**
     * 获取作业列表
     * @param homeworkQuery
     * @return
     */
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

    /**
     * 获取作业详情
     * @param id
     * @return
     */
    @Override
    public HomeworkDetailVO getHomeworkDetail(Long id) {
        Homework entity = homeworkMapper.selectById(id);
        if (entity == null) {
            return null;
        }
        HomeworkDetailVO vo = new HomeworkDetailVO();
        vo.setId(entity.getId());
        vo.setClass_id(entity.getClassId());
        vo.setTitle(entity.getTitle());
        vo.setContent(entity.getContent());
        return vo;
    }


    /**
     * 保存作业
     * @param homeworkDetailDto
     * @return
     */
    @Override
    public Long saveHomework(HomeworkDetailDto homeworkDetailDto) {
        Homework entity = new Homework();
        entity.setClassId(homeworkDetailDto.getClass_id());
        entity.setTitle(homeworkDetailDto.getTitle());
        entity.setContent(homeworkDetailDto.getContent());

        // 判断是修改还是新增：id不为空且数据库中存在该记录才是修改
        boolean isUpdate = false;
        if (homeworkDetailDto.getId() != null) {
            Homework existingHomework = homeworkMapper.selectById(homeworkDetailDto.getId());
            isUpdate = (existingHomework != null);
        }

        if (isUpdate) {
            // 修改操作
            entity.setId(homeworkDetailDto.getId());
            entity.setEditTime(LocalDateTime.now());
            // TODO: 从当前登录用户获取editor
            // entity.setEditor(currentUserId);
            homeworkMapper.updateById(entity);
        } else {
            // 新增操作（不使用前端传入的id，让数据库自动生成）
            entity.setAddTime(LocalDateTime.now());
            // TODO: 从当前登录用户获取creator
            // entity.setCreator(currentUserId);
            homeworkMapper.insert(entity);
        }
        return entity.getId();
    }

    /**
     * 批量删除作业
     * @param ids 作业ID列表
     * @return 删除的ID列表
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public List<Long> deleteHomeworks(List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return new ArrayList<>();
        }
        // 逻辑删除
        homeworkMapper.deleteBatchIds(ids);
        return ids;
    }

    /**
     * 获取作业提交列表
     * @param homeworkId 作业ID
     * @return 提交列表分页数据
     */
    @Override
    public PageDTO<HomeworkSubmissionListVo> queryHomeworkSubmissionList(Long homeworkId) {
        // 创建分页对象，默认分页参数
        Page<HomeworkRecord> page = new Page<>(1, 20);

        // 构建查询条件
        LambdaQueryWrapper<HomeworkRecord> wrapper = new LambdaQueryWrapper<>();
        wrapper.eq(HomeworkRecord::getHomeworkId, homeworkId);
        // 按提交时间降序排列
        wrapper.orderByDesc(HomeworkRecord::getAddTime);

        // 执行分页查询
        Page<HomeworkRecord> resultPage = homeworkRecordMapper.selectPage(page, wrapper);

        // 转换为VO
        return PageDTO.create(resultPage, entity -> {
            HomeworkSubmissionListVo vo = new HomeworkSubmissionListVo();
            vo.setId(entity.getId());
            vo.setContent(entity.getContent());
            vo.setSubmit_time(entity.getAddTime());
            vo.setReviewer(entity.getCommentTeacher());
            vo.setScore(entity.getScore());
            vo.setComment_content(entity.getComment());
            // TODO: 需要关联查询学生表获取提交人名称
            // vo.setName(studentName);
            return vo;
        });
    }

    /**
     * 点评作业
     * @param homeworkScoreDto 点评信息（包含提交记录ID、分数、点评内容）
     * @return 提交记录ID
     */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long scoreHomework(HomeworkScoreDto homeworkScoreDto) {
        HomeworkRecord entity = homeworkRecordMapper.selectById(homeworkScoreDto.getId());
        if (entity == null) {
            return null;
        }
        // 设置点评分数和内容
        entity.setScore(homeworkScoreDto.getScore());
        entity.setComment(homeworkScoreDto.getComment());
        entity.setCommentTime(LocalDateTime.now());
        // TODO: 从当前登录用户获取点评老师ID
        // entity.setCommentTeacher(currentUserId);
        homeworkRecordMapper.updateById(entity);
        return entity.getId();
    }
}
