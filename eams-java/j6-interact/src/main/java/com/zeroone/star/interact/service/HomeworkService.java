package com.zeroone.star.interact.service;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.interact.HomeworkDetailDto;
import com.zeroone.star.project.dto.j6.interact.HomeworkListDto;
import com.zeroone.star.project.query.j6.interact.HomeworkQuery;
import com.zeroone.star.project.vo.j6.interact.HomeworkDetailVO;

/**
 * 作业接口
 */
public interface HomeworkService {



    PageDTO<HomeworkListDto> pageQuery(HomeworkQuery homeworkQuery);


    HomeworkDetailVO getHomeworkDetail(Long id);

    Long saveHomework(HomeworkDetailDto homeworkDetailDto);
}
