package com.zeroone.star.project.j6.interact;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.HomeworkDetailDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkListDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkScoreDto;
import com.zeroone.star.project.query.j6.interact.HomeworkQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j6.interact.HomeworkDetailVO;
import com.zeroone.star.project.vo.j6.interact.HomeworkSubmissionListVo;

import java.util.List;

/**
 * 课后作业apis
 */
public interface HomeworkApis {
    /**
     * 获取作业列表（条件+分页）
     */
   JsonVO<PageDTO<HomeworkListDto>> queryHomeworkList(HomeworkQuery homeworkQuery);

    /**
     * 获取作业详情
     */
    JsonVO<HomeworkDetailVO> homeworkDetails(Long id);

    /**
     * 保存作业,新增和编辑作业是调用这个接口
     * todo 返回值该用do?
     */
    JsonVO<Long>saveHomework(HomeworkDetailDto homeworkDetailDto);

    /**
     * 删除作业
     */
    JsonVO<List<Long>>deleteHomeworks(List<Long> ids);

    /**
     * 获取作业提交列表（条件+分页）
     */
    JsonVO<PageDTO<HomeworkSubmissionListVo>>queryHomeworkSubmissionList(Long homeworkId);
    /**
     * 点评作业
     * @param homeworkScoreDto 点评信息（包含提交记录ID、分数、点评内容）
     * @return 提交记录ID
     */
    JsonVO<Long> scoreHomework(HomeworkScoreDto homeworkScoreDto);
}
