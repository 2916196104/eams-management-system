package com.zeroone.star.operation.service.impl;

import com.baomidou.mybatisplus.core.metadata.IPage;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import com.zeroone.star.operation.mapper.CreditMallMapper;
import com.zeroone.star.operation.service.ICreditMallService;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallAddDTO;
import com.zeroone.star.project.dto.j7.operation.CreditMallDTO;
import com.zeroone.star.operation.entity.CreditMall;
import com.zeroone.star.project.query.j7.operation.CreditMallListQuery;
import com.zeroone.star.project.dto.j7.operation.CreditMallDetailDTO;
import com.zeroone.star.project.vo.JsonVO;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.util.List;

@Service
public class CreditMallServiceImpl extends ServiceImpl<CreditMallMapper, CreditMall> implements ICreditMallService {

    @Resource
    private CreditMallMapper creditMallMapper;
    //领域模型转换类
    @Resource
    MsCreditMallMapper msCreditMallMapper;

    //从nacos中读取配置
    @Value("${fastdfs.nginx-servers}")
    private String urlPrefix;

    /**
     * 保存礼品
     * @param addDto
     * @return
     */
    @Transactional
    @Override
    public String saveCreditMall(CreditMallAddDTO addDto) {
        //判断materialId是否存在
        Long materialId = addDto.getMaterialId();
        Long categoryId = addDto.getCategoryId();
        if(creditMallMapper.countMaterialExists(materialId)==0 ||
                creditMallMapper.countCategoryExists(categoryId)==0) {
            return null;
        }

        String cover = addDto.getCover();
        //没有图片地址，图片时必须上传的
        if (cover == null || cover.isEmpty()) {
            return null;
        }
        CreditMall creditMall = msCreditMallMapper.addDtoToDo(addDto);
        // 如果不是相对路径（以 / 开头）或者 包含 http，直接保存
        if (cover.startsWith("http://") || cover.startsWith("https://")) {
            try {
                // 使用 URI 类自动解析，提取路径部分
                java.net.URI uri = new java.net.URI(cover);
                String path = uri.getPath();

                // 确保路径以 / 开头 (通常 getPath 会保留，但以防万一)
                if (path != null && !path.startsWith("/")) {
                    path = "/" + path;
                }
                //更新cover
                creditMall.setCover(path);
            } catch (Exception e) {
                // 如果解析出错（比如前端传了个乱码），为了数据安全，可以选择存原值或抛错
                // 这里选择存原值，避免程序崩溃
                return null;
            }
        }
        if(save(creditMall)) {
            return creditMall.getId().toString();
        }
        else {
            return null;
        }
    }

    /**
     * 获取礼品列表
     * @param query
     * @return
     */
    @Override
    public PageDTO<CreditMallDTO> listAllCreditMalls(CreditMallListQuery query) {
        // 1. 构建分页对象 (注意泛型改为 DTO)
        Page<CreditMallDTO> page = new Page<>(query.getPageIndex(), query.getPageSize());
        // 2. 构建查询条件
        IPage<CreditMallDTO> result = creditMallMapper.selectCreditMallDTOPage(page, query.getName(), query.getState());
        // 3. 转换并处理图片URL
        return PageDTO.create((Page<CreditMallDTO>) result, dto -> {
            if (dto.getCover() != null) {
                dto.setCover(concatenate(dto.getCover()));
            }
            return dto;
        });
    }

    /**
     * 获取指定id的礼品详情
     * @param id
     * @return
     */
    @Override
    public CreditMallDetailDTO getCreditMallById(String id) {
        CreditMallDetailDTO creditMallDetailDTO = creditMallMapper.selectDetailById(id);
        if (creditMallDetailDTO == null) {
            return null;
        }
        String url = concatenate(creditMallDetailDTO.getCover());
        creditMallDetailDTO.setCover(url);
        return creditMallDetailDTO;
    }

    private String concatenate(String relativePath) {
        // 3. 核心拼接逻辑
        if (relativePath != null && !relativePath.trim().isEmpty()) {
            // 清洗数据：防止配置带 / 或 路径不带 /
            String cleanPrefix = urlPrefix.endsWith("/") ? urlPrefix.substring(0, urlPrefix.length() - 1) : urlPrefix;
            String cleanPath = relativePath.startsWith("/") ? relativePath : "/" + relativePath;

            return "http://" + cleanPrefix + cleanPath;
        } else {
            return null;
        }
    }

    @Override
    public JsonVO<String> removePointsGift(List<Long> ids) {
        creditMallMapper.deleteByIdList(ids);
        return JsonVO.success("删除成功");
    }

    @Override
    public JsonVO<String> enablePointsGift(List<Long> ids, Integer state) {
        creditMallMapper.updateStatusByIdList(ids, state);
        String message = state == 1 ? "启用成功" : "禁用成功";
        return JsonVO.success(message);
    }
}
