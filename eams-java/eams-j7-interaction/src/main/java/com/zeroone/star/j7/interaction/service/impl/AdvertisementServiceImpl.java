package com.zeroone.star.j7.interaction.service.impl;

import com.baomidou.mybatisplus.core.toolkit.IdWorker;
import com.zeroone.star.j7.interaction.controller.AdvertisementController;
import com.zeroone.star.j7.interaction.mapper.AdvertisementMapper;
import com.zeroone.star.j7.interaction.service.AdvertisementService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.interaction.AdvertisementDTO;
import com.zeroone.star.project.entity.Advertisement;
import com.zeroone.star.project.query.j7.interaction.AdvertisementQuery;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.Date;
import java.util.List;

@Slf4j
@Service
public class AdvertisementServiceImpl implements AdvertisementService {

    @Resource
    private AdvertisementMapper advertisementMapper;
    @Autowired
    private AdvertisementController advertisement;

    @Override
    public PageDTO<Advertisement> queryPage(AdvertisementQuery advertisementQuery) {
        List<Advertisement> data = advertisementMapper.queryPage(advertisementQuery);

        Long pageIndex = advertisementQuery.getPageIndex();
        Long pageSize = advertisementQuery.getPageSize();
        long total = data.size();
        Long pages = (total + pageSize - 1) / pageSize;

        PageDTO<Advertisement> pageDTO = new PageDTO<>(pageIndex, pageSize, total, pages, data);
        return pageDTO;
    }

    @Override
    public Advertisement getAdvertisementDetail(Long id) {
        Advertisement advertisement = advertisementMapper.queryAdvertisementDetail(id);
        if (advertisement != null) {
            Advertisement advertisement_new = new Advertisement();
            advertisement_new.setTitle(advertisement.getTitle());
            advertisement_new.setContent(advertisement.getContent());
            advertisement_new.setType(advertisement.getType());

            return advertisement_new;
        }

        return null;
    }

    @Override
    public Long saveAdvertisement(AdvertisementDTO advertisementDTO) {
        Advertisement res = advertisementMapper.findAdvertisement(advertisementDTO);
        if(res == null){
            Advertisement check = advertisementMapper.findAdvertisementByCode(advertisementDTO.getCode());
            if(check != null){
                return null;
            }
            advertisementDTO.setId(String.valueOf(IdWorker.getId()));
            advertisementDTO.setAddTime(new Date());
            advertisementDTO.setEditTime(new Date());
            Long result = advertisementMapper.insertAdvertisement(advertisementDTO);
            if(result == null || result == 0){
                return null;
            }
            return 1L;

        }else{
            advertisementDTO.setEditTime(new Date());
            Long result = advertisementMapper.updateAdvertisement(advertisementDTO);
            if(result == null || result == 0){
                return null;
            }
            return 1L;
        }
    }

    @Override
    public boolean removeNotice(List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            return false;
        }
        return false;
    }

    @Override
    public boolean modifyNotice(Long id, Integer status) {
        if (id == null || status == null || (status != 0 && status != 1)) {
            log.error("参数无效：id={}, status={}", id, status);
            return false;
        }

        return false;
    }
}
