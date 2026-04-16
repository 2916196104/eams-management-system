package com.zeroone.star.interact.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.HomeworkDetailDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkListDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkScoreDto;
import com.zeroone.star.project.query.j6.interact.HomeworkQuery;
import com.zeroone.star.project.vo.j6.interact.HomeworkDetailVO;
import com.zeroone.star.project.vo.j6.interact.HomeworkSubmissionListVo;

import java.util.List;

/**
 * 作业接口
 */
public interface HomeworkService {

    /**
     * 分页查询作业列表
     * @param homeworkQuery 查询条件
     * @return 分页数据
     */
    PageDTO<HomeworkListDto> pageQuery(HomeworkQuery homeworkQuery);

    /**
     * 根据ID获取作业详情
     * @param id 作业ID
     * @return 作业详情
     */
    HomeworkDetailVO getHomeworkDetail(Long id);

    /**
     * 保存作业（新增或修改）
     * @param homeworkDetailDto 作业信息
     * @return 作业ID
     */
    Long saveHomework(HomeworkDetailDto homeworkDetailDto);

    /**
     * 批量删除作业
     * @param ids 作业ID列表
     * @return 删除的ID列表
     */
    List<Long> deleteHomeworks(List<Long> ids);

    /**
     * 获取作业提交列表
     * @param homeworkId 作业ID
     * @return 提交列表分页数据
     */
    PageDTO<HomeworkSubmissionListVo> queryHomeworkSubmissionList(Long homeworkId);

    /**
     * 点评作业
     * @param homeworkScoreDto 点评信息（包含提交记录ID、分数、点评内容）
     * @return 提交记录ID
     */
    Long scoreHomework(HomeworkScoreDto homeworkScoreDto);
}
