package com.zeroone.star.j7.interaction.mapper;

import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.j7.interaction.entity.HomeworkRecord;
import com.zeroone.star.project.query.j7.interaction.HomeworkRecordQuery;
import com.zeroone.star.project.vo.j7.interaction.HomeworkRecordVO;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * <p>
 * homework_record 表的 Mapper 接口
 * </p>
 * @author lvincent
 * @since 2026-03-16
 */
@Mapper
public interface HomeworkRecordMapper extends BaseMapper<HomeworkRecord> {

    /**
     * 分页查询作业提交记录（含学生姓名、点评教师姓名）
     * @param page 分页参数
     * @param query 查询条件
     * @return 提交记录 VO 列表
     */
    IPage<HomeworkRecordVO> selectHomeworkRecordPage(Page<?> page, @Param("query") HomeworkRecordQuery query);

    /**
     * 查询某个作业下的所有提交记录
     * @param homeworkId 作业ID
     * @return 提交记录 VO 列表
     */
    List<HomeworkRecordVO> selectListByHomeworkId(@Param("homeworkId") Long homeworkId);
}
