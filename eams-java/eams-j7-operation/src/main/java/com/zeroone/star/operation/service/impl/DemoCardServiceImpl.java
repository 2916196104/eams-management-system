package com.zeroone.star.operation.service.impl;

import com.baomidou.mybatisplus.core.toolkit.IdWorker;
import com.zeroone.star.operation.mapper.DemoCardMapper;
import com.zeroone.star.operation.service.DemoCardService;
import com.zeroone.star.project.dto.j7.operation.DemoCardDTO;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

/**
 * <p>
 * 试听卡服务实现类
 * </p>
 *
 * @author zeroone-star
 * @since 2026-03-22
 */
@Service
@RequiredArgsConstructor
public class DemoCardServiceImpl implements DemoCardService {
    /**
     * 试听卡Mapper
     */
    private final DemoCardMapper demoCardMapper;
    /**
    * 保存试听卡
    */
    @Override
    @Transactional(rollbackFor = Exception.class)
    public Long saveDemoCard(DemoCardDTO demoCardDTO) {
        Long id = IdWorker.getId();
        demoCardDTO.setId(id);
        demoCardMapper.insertDemoCard(demoCardDTO);
        return id;
    }
}
