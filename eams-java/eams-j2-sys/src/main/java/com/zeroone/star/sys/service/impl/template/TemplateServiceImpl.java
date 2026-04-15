package com.zeroone.star.sys.service.impl.template;

import com.baomidou.mybatisplus.core.conditions.query.QueryWrapper;
import com.baomidou.mybatisplus.core.toolkit.StringUtils;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Template.TemplateAttachmentDTO;
import com.zeroone.star.project.dto.j2.sys.Template.TemplateDTO;
import com.zeroone.star.project.query.j2.sys.template.TemplateQuery;
import com.zeroone.star.sys.entity.Attachment;
import com.zeroone.star.sys.entity.template.SettingNotice;
import com.zeroone.star.sys.mapper.attachment.AttachmentMapper;
import com.zeroone.star.sys.mapper.template.TemplateMapper;
import com.zeroone.star.sys.service.template.ITemplateService;
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
import java.util.List;

/**
 * <p>
 * 系统设置表 服务实现类
 * </p>
 *
 * @author 斗气化码
 * @since 2026-03-27
 */
@Service
public class TemplateServiceImpl extends ServiceImpl<AttachmentMapper, Attachment> implements ITemplateService {

    @Resource
    MsTemplateMapper msTemplateMapper;

    @Resource
    AttachmentMapper attachmentMapper;

    @Resource
    TemplateMapper templateMapper;

    @SneakyThrows
    @Transactional
    @Override
    public ResponseEntity<byte[]> downloadFile(String templateId) {
        Attachment attachment = attachmentMapper.selectById(templateId);
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
    public PageDTO<TemplateAttachmentDTO> queryAll(TemplateQuery query) {
        // 构建分页查询对象
        Page<Attachment> page = new Page<>(query.getPageIndex(), query.getPageSize());
        // 构建查询条件
        QueryWrapper<Attachment> queryWrapper = new QueryWrapper<>();
        queryWrapper.like(!StringUtils.isEmpty(query.getFileName()), "name", query.getFileName());
        // 分页查询
        Page<Attachment> result = baseMapper.selectPage(page, queryWrapper);
        return PageDTO.create(result, src -> msTemplateMapper.toDTO(src));
    }

    /**
     * 新增模板列表
     * @param templateDTO
     * @return
     */
    @Override
    @Transactional
    public boolean addTemplateList(TemplateDTO templateDTO) {
        SettingNotice settingNotice = msTemplateMapper.toSettingNotice(templateDTO);
        if(templateMapper.insert(settingNotice) > 0){
            return true;
        }else {
            throw new RuntimeException("新增模版数据失败");
        }
    }

    /**
     * 删除模板列表
     * @param templateIds
     * @return
     */
    @Override
    @Transactional
    public boolean deleteTemplateList(List<String> templateIds) {
        for(String templateId : templateIds){
            if(templateMapper.deleteById(templateId) <= 0){
                throw new RuntimeException("删除模版数据失败");
            }
        }
        return true;
    }

    /**
     * 修改模板列表
     * @param templateDTO
     * @return
     */
    @Override
    @Transactional
    public boolean updateTemplateList(TemplateDTO templateDTO) {
        SettingNotice settingNotice = msTemplateMapper.toSettingNotice(templateDTO);
        if (templateMapper.updateById(settingNotice) > 0){
            return true;
        }else {
            throw new RuntimeException("修改模版数据失败");
        }
    }
}
