package com.zeroone.star.j7.interaction.service.impl;

import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.j7.interaction.entity.HomeworkRecord;
import com.zeroone.star.j7.interaction.mapper.HomeworkRecordMapper;
import com.zeroone.star.j7.interaction.service.IHomeworkRecordService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j7.interaction.HomeworkRecordQuery;
import com.zeroone.star.project.vo.j7.interaction.HomeworkRecordVO;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

/**
 * <p>
 * homework_record 表的服务实现类
 * </p>
 * @author lvincent
 * @since 2026-03-16
 */
@Service
public class HomeworkRecordServiceImpl extends ServiceImpl<HomeworkRecordMapper, HomeworkRecord> implements IHomeworkRecordService {

    @Resource
    private HomeworkRecordMapper homeworkRecordMapper;

    @Override
    public PageDTO<HomeworkRecordVO> listRecords(HomeworkRecordQuery query) {
        // 构建分页对象
        Page<HomeworkRecord> page = new Page<>(query.getPageIndex(), query.getPageSize());

        // 调用 Mapper 查询
        Page<HomeworkRecordVO> resultPage = (Page<HomeworkRecordVO>) homeworkRecordMapper.selectHomeworkRecordPage(page, query);

        return PageDTO.create(resultPage);
    }

    @Override
    public List<HomeworkRecordVO> getListByHomeworkId(Long homeworkId) {
        return homeworkRecordMapper.selectListByHomeworkId(homeworkId);
    }
}
