package com.zeroone.star.sys.service.impl;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.core.toolkit.StringUtils;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Template.TemplateDTO;
import com.zeroone.star.project.query.j2.sys.template.TemplateQuery;
import com.zeroone.star.sys.entity.Attachment;
import com.zeroone.star.sys.mapper.MsTemplateMapper;
import com.zeroone.star.sys.mapper.TemplateMapper;
import com.zeroone.star.sys.service.ITemplateService;
import com.baomidou.mybatisplus.extension.service.impl.ServiceImpl;
import lombok.SneakyThrows;
import org.springframework.http.HttpHeaders;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import javax.annotation.Resource;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.net.URL;
import java.net.URLEncoder;
import java.time.LocalDate;

/**
 * <p>
 * 系统设置表 服务实现类
 * </p>
 *
 * @author 斗气化码
 * @since 2026-03-27
 */
@Service
public class TemplateServiceImpl extends ServiceImpl<TemplateMapper, Attachment> implements ITemplateService {

    @Resource
    MsTemplateMapper msTemplateMapper;

    @Resource
    TemplateMapper templateMapper;

    @SneakyThrows
    @Transactional
    @Override
    public ResponseEntity<byte[]> downloadFile(String templateId) {
        Attachment attachment = templateMapper.selectById(templateId);
        String fileUrl = attachment.getUrl();
        String name = attachment.getName();

        URL url = new URL(fileUrl);

        // 读取远程文件到字节数组
        try (InputStream in = url.openStream();
             ByteArrayOutputStream out = new ByteArrayOutputStream()) {

            byte[] buffer = new byte[8192];
            int len;
            while ((len = in.read(buffer)) != -1) {
                out.write(buffer, 0, len);
            }
            byte[] data = out.toByteArray();

            // 构建下载响应头
            HttpHeaders headers = new HttpHeaders();
            headers.setContentType(MediaType.APPLICATION_OCTET_STREAM);
            String currentDate = LocalDate.now().toString();
            String fileName = URLEncoder.encode(name + currentDate + ".xlsx", "UTF-8");
            headers.setContentDispositionFormData("attachment", fileName);

            return new ResponseEntity<>(data, headers, HttpStatus.OK);
        }
    }

    @Transactional
    @Override
    public PageDTO<TemplateDTO> queryAll(TemplateQuery query) {
        // 构建分页查询对象
        Page<Attachment> page = new Page<>(query.getPageIndex(), query.getPageSize());
        // 构建查询条件
        QueryWrapper<Attachment> queryWrapper = new QueryWrapper<>();
        queryWrapper.like(!StringUtils.isEmpty(query.getFileName()), "name", query.getFileName());
        // 分页查询
        Page<Attachment> result = baseMapper.selectPage(page, queryWrapper);
        return PageDTO.create(result, src -> msTemplateMapper.toDTO(src));
    }
}
