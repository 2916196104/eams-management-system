package com.zeroone.star.project.j7.operation;

import com.zeroone.star.project.dto.j7.operation.DemoCardDTO;
import com.zeroone.star.project.vo.JsonVO;

public interface DemoCardApi {
    /**
     * 新增演示卡
     * @param demoCardDTO 演示卡信息
     * @return 演示卡ID
     * @author 1
     * @version 1.0.0
     * @date 2026-3-16
     */
    JsonVO<Long> saveDemoCard(DemoCardDTO demoCardDTO);
}
