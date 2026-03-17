package com.zeroone.star.project.j6.interact;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.HomeworkRecordDTO;
import com.zeroone.star.project.query.j6.interact.HomeworkRecordQuery;
import com.zeroone.star.project.vo.JsonVO;

import java.util.List;

/**
 * 课后作业apis
 */
public interface HomeworkApis {

    /**
     * 删除作业
     * @param ids 作业ID
     * @return 删除结果
     */
    JsonVO<List<Long>> deleteHomework(List<Long>ids);

    /**
     * 分页查询作业提交列表
     *
     * @param condition 查询条件
     * @return 作业列表
     */
    JsonVO<PageDTO<HomeworkRecordDTO>> queryPage(HomeworkRecordQuery condition);
}
