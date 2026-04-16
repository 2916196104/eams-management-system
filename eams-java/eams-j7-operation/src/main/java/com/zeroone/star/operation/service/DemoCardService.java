package com.zeroone.star.operation.service;

import com.zeroone.star.project.dto.j7.operation.DemoCardDTO;

/**
 * <p>
 * 试听卡服务接口
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-22
 */
public interface DemoCardService {
    /**
     * 保存试听卡
     * @param demoCardDTO 试听卡DTO
     * @return 保存成功的ID
     */
    Long saveDemoCard(DemoCardDTO demoCardDTO);
}
