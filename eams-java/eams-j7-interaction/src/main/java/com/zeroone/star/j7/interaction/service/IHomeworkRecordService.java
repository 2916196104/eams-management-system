package com.zeroone.star.j7.interaction.service;

import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.j7.interaction.entity.HomeworkRecord;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j7.interaction.HomeworkRecordQuery;
import com.zeroone.star.project.vo.j7.interaction.HomeworkRecordVO;

import java.util.List;

/**
 * <p>
 * homework_record 表的服务类接口
 * </p>
 * @author lvincent
 * @since 2026-03-16
 */
public interface IHomeworkRecordService extends IService<HomeworkRecord> {

    /**
     * 分页查询作业提交记录
     *
     * @param query 查询条件
     * @return 分页结果
     */
    PageDTO<HomeworkRecordVO> listRecords(HomeworkRecordQuery query);

    /**
     * 根据作业ID获取所有的提交记录
     *
     * @param homeworkId 作业ID
     * @return 记录列表
     */
    List<HomeworkRecordVO> getListByHomeworkId(Long homeworkId);
}