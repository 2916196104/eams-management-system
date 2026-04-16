package com.zeroone.star.project.j7.interaction;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkCommentDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkDeleteDTO;
import com.zeroone.star.project.dto.j7.interaction.HomeworkSaveDTO;
import com.zeroone.star.project.query.j7.interaction.HomeworkListQuery;
import com.zeroone.star.project.query.j7.interaction.HomeworkRecordQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j7.interaction.HomeworkRecordVO;
import com.zeroone.star.project.vo.j7.interaction.HomeworkVO;
import io.swagger.annotations.Api;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.bind.annotation.RequestHeader;

/**
 * <p>
 * 描述：课后作业模块API接口定义
 * </p>
 * <p>接口范围：获取作业列表、获取作业详情、获取作业提交列表</p>
 * @author lvincent
 * @since 2026-03-15
 */
@RestController
@RequestMapping("/j7/org")
@Api(tags = "j7-作业管理接口")
public interface HomeworkApis {

    /**
     * 获取作业列表
     * <p>支持按标题模糊搜索、按班级ID/教师ID筛选，分页返回</p>
     * @param query 查询条件（title, classId, teacherId, pageIndex, pageSize）
     * @return 作业分页列表
     */
    JsonVO<PageDTO<HomeworkVO>> listHomework(HomeworkListQuery query);

    /**
     * 获取作业详情
     * <p>返回作业基本信息 + 嵌套的提交记录列表（recordList）</p>
     * @param id 作业ID
     * @return 作业详情（含提交记录）
     */
    JsonVO<HomeworkVO> getHomeworkById(Long id);

    /**
     * 获取作业提交列表
     * <p>根据作业ID查询所有提交记录，分页返回</p>
     * @param query 查询条件（homeworkId, pageIndex, pageSize）
     * @return 提交记录分页列表
     */
    JsonVO<PageDTO<HomeworkRecordVO>> listHomeworkRecords(HomeworkRecordQuery query);

    /**
     * 保存作业
     *
     * @param saveDTO 保存信息
     * @param operatorId 操作人 ID
     * @return 作业 ID
     */
    JsonVO<Long> saveHomework(@RequestBody HomeworkSaveDTO saveDTO,
                              @RequestHeader("user-id") Long operatorId);

    /**
     * 删除作业
     *
     * @param deleteDTO 删除信息
     * @param operatorId 操作人 ID
     * @return 是否删除成功
     */
    JsonVO<Void> deleteHomework(@RequestBody HomeworkDeleteDTO deleteDTO,
                                @RequestHeader("user-id") Long operatorId);

    /**
     * 点评作业
     * <p>作业评价，支持对作业进行评价，并保存评价结果</p>
     * @param commentDTO 评价信息
     * @param teacherId 教师 ID
     * @return 点评结果
     */
    JsonVO<Void> commentHomework(@RequestBody HomeworkCommentDTO commentDTO,
                                 @RequestHeader("user-id") Long teacherId);
}
