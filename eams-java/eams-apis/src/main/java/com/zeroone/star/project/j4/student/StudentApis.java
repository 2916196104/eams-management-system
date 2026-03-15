package com.zeroone.star.project.j4.student;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j4.student.ChangeCreditDTO;
import com.zeroone.star.project.dto.j4.student.CreditLogDTO;
import com.zeroone.star.project.dto.j4.student.LessonCountDTO;
import com.zeroone.star.project.query.j4.student.CreditSelectQuery;
import com.zeroone.star.project.vo.JsonVO;

public interface StudentApis {
    /**
     * 获取消课记录（条件+分页）
     * 查询对应学员的消课记录
     * @return 分页的消课记录
     * @author MRME39
     */
    JsonVO<PageDTO<LessonCountDTO>> queryOmyLessonCount(String StudentID);

    /**
     * 获取积分记录（条件+分页）
     * 查询条件下的积分记录
     * @return 分页的积分记录
     * @author MRME39
     */
    JsonVO<PageDTO<CreditLogDTO>> queryCreditLog(CreditSelectQuery creditSelectQuery);

    /**
     * 调整积分
     * @author MRME39
     */
    JsonVO<Long> saveCreditLog(ChangeCreditDTO changeCreditDTO);
}
