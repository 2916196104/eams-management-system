package com.zeroone.star.j7.interaction.service;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.service.IService;
import com.zeroone.star.j7.interaction.entity.Homework;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.query.j7.interaction.HomeworkListQuery;
import com.zeroone.star.project.vo.j7.interaction.HomeworkVO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkCommentDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkDeleteDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkSaveDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkSubmitDTO;
import com.zeroone.star.project.query.j7.interaction.HomeworkListQuery;
import com.zeroone.star.project.vo.j7.interaction.HomeworkVO;
/**
 * <p>
 * homework 表的服务类接口
 * </p>
 * @author lvincent
 * @since 2026-03-16
 */
public interface IHomeworkService extends IService<Homework> {

    /**
     * 分页查询作业列表
     * @param query 查询条件
     * @return 分页结果
     */
    PageDTO<HomeworkVO> listHomeworks(HomeworkListQuery query);

    /**
     * 获取作业详情（内部不包含 recordList）
     * @param id 作业ID
     * @return 作业 VO
     */
    HomeworkVO getHomeworkDetail(Long id);
    /**
     * 保存（提交）作业
     * @param dto 作业保存参数
     * @param operatorId 操作人ID（教师ID）
     * @return 作业ID
     */
    Long saveHomework(HomeworkSaveDTO dto, Long operatorId);

    /**
     * 删除作业
     * @param dto 作业删除参数
     * @param operatorId 操作人ID
     */
    void deleteHomework(HomeworkDeleteDTO dto, Long operatorId);

    /**
     * 点评作业
     * @param dto 作业点评参数
     * @param teacherId 点评教师ID
     */
    void commentHomework(HomeworkCommentDTO dto, Long teacherId);
    /**
     * 学生提交作业
     * @param dto 提交作业参数
     * @param studentId 学生ID（从请求头获取）
     * @return 作业提交记录ID
     */
    Long submitHomework(HomeworkSubmitDTO dto, Long studentId);

}
