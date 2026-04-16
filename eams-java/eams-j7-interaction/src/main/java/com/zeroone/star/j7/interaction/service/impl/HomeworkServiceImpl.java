package com.zeroone.star.j7.interaction.service.impl;

import cn.hutool.core.bean.BeanUtil;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.toolkit.Wrappers;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j7.interaction.entity.Homework;
import com.zeroone.star.j7.interaction.mapper.HomeworkMapper;
import com.zeroone.star.j7.interaction.service.IHomeworkService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.vo.j7.interaction.HomeworkVO;
import com.zeroone.star.project.query.j7.interaction.HomeworkListQuery;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import com.zeroone.star.j7.interaction.entity.HomeworkRecord;
import com.zeroone.star.j7.interaction.mapper.HomeworkRecordMapper;
import com.zeroone.star.project.dto.j7.interaction.HomeworkCommentDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkDeleteDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkSaveDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkSubmitDTO;
import javax.annotation.Resource;
import java.time.LocalDateTime;
import java.util.List;

/**
 * <p>
 * homework 表的服务实现类
 * </p>
 * @author lvincent
 * @since 2026-03-16
 */
@Service
public class HomeworkServiceImpl extends ServiceImpl<HomeworkMapper, Homework> implements IHomeworkService {

    @Resource
    private HomeworkMapper homeworkMapper;

    @Resource
    private HomeworkRecordMapper homeworkRecordMapper;

    @Override
    @SuppressWarnings("unchecked")
    public PageDTO<HomeworkVO> listHomeworks(HomeworkListQuery query) {
        Page<?> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // TODO: 从上下文中获取当前登录学生 ID（如果是学生端调用），目前传 null
        Long currentStudentId = null;


        Page<HomeworkVO> resultPage = (Page<HomeworkVO>) homeworkMapper.selectHomeworkPage(page, query, currentStudentId);
        return PageDTO.create(resultPage);
    }

    @Override
    public HomeworkVO getHomeworkDetail(Long id) {
        return homeworkMapper.selectHomeworkDetail(id);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long saveHomework(HomeworkSaveDTO dto, Long operatorId) {
        Homework homeworkDO = BeanUtil.copyProperties(dto, Homework.class);
        LocalDateTime now = LocalDateTime.now();

        if (dto.getId() == null) {
            // 新增作业
            homeworkDO.setCreator(operatorId);
            homeworkDO.setAddTime(now);
            homeworkDO.setDeleted(false);
        } else {
            // 修改作业
            Homework exist = getById(dto.getId());
            if (exist == null || Boolean.TRUE.equals(exist.getDeleted())) {
                throw new RuntimeException("作业不存在或已删除");
            }
            homeworkDO.setEditor(operatorId);
            homeworkDO.setEditTime(now);
        }

        saveOrUpdate(homeworkDO);
        return homeworkDO.getId();
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public void deleteHomework(HomeworkDeleteDTO dto, Long operatorId) {
        // 校验操作人 ID 合法性
        if (operatorId == null || operatorId <= 0) {
            throw new RuntimeException("操作人 ID 无效");
        }
        List<Long> ids = dto.getIds();
        // 校验 ID 列表非空
        if (ids == null || ids.isEmpty()) {
            throw new RuntimeException("请选择要删除的作业");
        }
        for (Long id : ids) {
            Homework homeworkDO = getById(id);
            // 明确校验 ID 是否存在且未删除
            if (homeworkDO == null) {
                throw new RuntimeException("作业 ID【" + id + "】不存在");
            }
            if (Boolean.TRUE.equals(homeworkDO.getDeleted())) {
                throw new RuntimeException("作业 ID【" + id + "】已删除，请勿重复操作");
            }
            homeworkDO.setDeleted(true);
            homeworkDO.setEditor(operatorId);
            homeworkDO.setEditTime(LocalDateTime.now());
            updateById(homeworkDO);
        }
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public void commentHomework(HomeworkCommentDTO dto, Long teacherId) {
        if (teacherId == null || teacherId <= 0) {
            throw new RuntimeException("教师 ID 无效，请先登录");
        }
        // 适配你的 DTO 字段名，从 dto.getHomeworkRecordId() 取值
        Long recordId = dto.getHomeworkRecordId();
        HomeworkRecord record = homeworkRecordMapper.selectById(recordId);
        if (record == null) {
            throw new RuntimeException("作业提交记录 ID【" + recordId + "】不存在");
        }
        if (Boolean.TRUE.equals(record.getDeleted())) {
            throw new RuntimeException("该作业提交记录已删除");
        }
        if (record.getStatus() != null && record.getStatus() == 2) {
            throw new RuntimeException("该作业已被点评，请勿重复操作");
        }
        // 适配你的 DTO 字段名，从 dto.getContent() 取点评内容
        record.setComment(dto.getContent());
        record.setScore(dto.getScore());
        record.setStatus(2);
        record.setCommenter(teacherId);
        record.setCommentTime(LocalDateTime.now());
        homeworkRecordMapper.updateById(record);
    }

    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long submitHomework(HomeworkSubmitDTO dto, Long studentId) {
        // 校验学生 ID 合法性
        if (studentId == null || studentId <= 0) {
            throw new RuntimeException("学生 ID 无效，请先登录");
        }
        // 校验要提交的作业是否存在
        Long homeworkId = dto.getHomeworkId();
        Homework homeworkDO = getById(homeworkId);
        if (homeworkDO == null || Boolean.TRUE.equals(homeworkDO.getDeleted())) {
            throw new RuntimeException("作业 ID【" + homeworkId + "】不存在或已删除");
        }
        // 校验是否重复提交
        LambdaQueryWrapper<HomeworkRecord> queryWrapper = Wrappers.lambdaQuery();
        queryWrapper.eq(HomeworkRecord::getHomeworkId, homeworkId)
                .eq(HomeworkRecord::getStudentId, studentId)
                .eq(HomeworkRecord::getDeleted, false);
        if (homeworkRecordMapper.selectCount(queryWrapper) > 0) {
            throw new RuntimeException("你已提交过该作业，请勿重复提交");
        }
        // 插入提交记录
        HomeworkRecord record = new HomeworkRecord();
        record.setHomeworkId(homeworkId);
        record.setStudentId(studentId);
        record.setContent(dto.getContent());
        record.setStatus(1); // 1=待批改，2=已批改
        record.setCreator(studentId);
        record.setCreateTime(LocalDateTime.now());
        homeworkRecordMapper.insert(record);
        return record.getId();
    }

}

