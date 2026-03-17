package com.zeroone.star.project.j6.homework;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j6.eas.GradeManagerDto;
import com.zeroone.star.project.dto.j6.homework.HomeworkDTO;
import com.zeroone.star.project.query.j6.eas.GradeManagerQuery;
import com.zeroone.star.project.query.j6.homework.HomeworkQuery;
import com.zeroone.star.project.vo.JsonVO;

/**
 * 作业管理接口
 */
public interface HomeworkApis {

    /**
     * 查询作业列表
     * @param query
     * @return
     */
    JsonVO<PageDTO<HomeworkDTO>> queryPage(HomeworkQuery query);


    /**
     * 获取作业详情
     */
    JsonVO<HomeworkDTO> getGradeById(Integer id);


    /**
     * 保存作业
     */
    JsonVO<HomeworkDTO> saveGrade(HomeworkDTO homeworkDto);


}
