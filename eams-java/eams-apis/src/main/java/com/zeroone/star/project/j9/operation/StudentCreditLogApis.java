package com.zeroone.star.project.j9.operation;

import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j9.operation.StudentCreditAdjustDTO;
import com.zeroone.star.project.query.j9.operation.StudentCreditLogQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j9.operation.StudentCreditAdjustVO;
import com.zeroone.star.project.vo.j9.operation.StudentCreditLogVO;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.RequestBody;

public interface StudentCreditLogApis {

    /**
     * 查询学生积分记录列表（条件+分页）
     * @param condition
     * @return
     */
    JsonVO<PageDTO<StudentCreditLogVO>> queryCreditLogList(StudentCreditLogQuery condition);

    /**
     * 调整学生积分
     * @param adjustDTO
     * @return
     */
    JsonVO<StudentCreditAdjustVO> modifyCredit(@Validated @RequestBody StudentCreditAdjustDTO adjustDTO);
}
