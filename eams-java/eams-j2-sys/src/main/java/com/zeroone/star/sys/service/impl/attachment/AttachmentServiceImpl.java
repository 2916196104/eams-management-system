package com.zeroone.star.sys.service.impl.attachment;

import javax.annotation.Resource;
import java.util.List;
import java.util.Map;
import java.util.function.Function;

import com.alibaba.nacos.common.utils.StringUtils;
import com.baomidou.mybatisplus.core.conditions.Wrapper;
import com.baomidou.mybatisplus.core.conditions.query.LambdaQueryWrapper;
import com.baomidou.mybatisplus.core.mapper.BaseMapper;
import com.baomidou.mybatisplus.core.toolkit.support.SFunction;
import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.zeroone.star.project.components.fastdfs.FastDfsClientComponent;
import com.zeroone.star.project.components.fastdfs.FastDfsFileInfo;
import com.zeroone.star.project.dto.PageDTO;
import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentAddDTO;
import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentDTO;
import com.zeroone.star.project.dto.j2.sys.Attachment.AttachmentUpdateDTO;
import com.zeroone.star.project.query.j2.sys.attachment.AttachmentQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.j2.sys.Attachment.AttachmentUploadVO;
import com.zeroone.star.project.vo.j2.sys.Attachment.AttachmentUpdateVO;
import com.zeroone.star.sys.entity.Attachment;
import com.zeroone.star.sys.mapper.attachment.AttachmentMapper;
import com.zeroone.star.sys.service.attachment.IAttachmentService;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import java.time.LocalDateTime;
import java.util.*;

/**
 * 描述：附件服务实现类
 *
 * @author belief
 * @since 2026-03-22
 */
@Slf4j
@Service
public class AttachmentServiceImpl implements IAttachmentService {

    @Resource
    private FastDfsClientComponent fastDfsClient;

    @Resource
    private AttachmentMapper attachmentMapper;

    @Value("${fastdfs.nginx-servers}")
    private String urlPrefix;

    @Override
    @Transactional
    public AttachmentUpdateVO updateAttachment(AttachmentUpdateDTO updateDTO) {
        log.info("开始修改附件，ID: {}", updateDTO.getId());

        // 参数校验
        if (updateDTO.getId() == null) {
            throw new RuntimeException("附件ID不能为空");
        }

        // 查询附件
        Attachment attachment = attachmentMapper.selectById(updateDTO.getId());
        if (attachment == null) {
            throw new RuntimeException("附件不存在，ID: " + updateDTO.getId());
        }

        // 修改名称
        if (StringUtils.hasText(updateDTO.getName())) {
            attachment.setName(updateDTO.getName());
        }

        // 修改文件名
        if (StringUtils.hasText(updateDTO.getFileName())) {
            attachment.setFileName(updateDTO.getFileName());
            // 更新文件类型
            if (updateDTO.getFileName().contains(".")) {
                String ext = updateDTO.getFileName().substring(updateDTO.getFileName().lastIndexOf(".") + 1);
                attachment.setFileType(ext);
            }
        }

        // 保存
        int result = attachmentMapper.updateById(attachment);
        if (result <= 0) {
            throw new RuntimeException("修改附件失败");
        }

        // 返回结果
        AttachmentUpdateVO vo = new AttachmentUpdateVO();
        vo.setId(Long.valueOf(attachment.getId()));
        vo.setName(attachment.getName());
        vo.setFileName(attachment.getFileName());
        vo.setFileType(attachment.getFileType());
        return vo;
    }

    @Override
    @Transactional
    public void removeAttachment(Long id) {
        log.info("开始删除附件，ID: {}", id);

        // 参数校验
        if (id == null) {
            throw new RuntimeException("附件ID不能为空");
        }

        // 查询附件
        Attachment attachment = attachmentMapper.selectById(id);
        if (attachment == null) {
            log.warn("附件不存在，ID: {}", id);
            throw new RuntimeException("附件不存在，ID: " + id);
        }

        // 删除FastDFS文件
        if (StringUtils.hasText(attachment.getSavePath())) {
            try {
                String savePath = attachment.getSavePath();
                String group = null;
                String storageId = null;

                // 方式1: 从 savePath 解析（格式: group1/M00/00/00/xxx.png）
                if (savePath.contains("/")) {
                    String[] parts = savePath.split("/", 2);
                    if (parts.length == 2 && parts[0].startsWith("group")) {
                        group = parts[0];
                        storageId = parts[1];
                        log.info("从savePath解析到 group: {}, storageId: {}", group, storageId);
                    }
                }

                // 方式2: 如果 savePath 解析失败，从 URL 解析
                if (group == null && StringUtils.hasText(attachment.getUrl())) {
                    String url = attachment.getUrl();
                    // 解析 URL: http://ip:port/group1/M00/00/00/xxx.png?token=...
                    int pathStart = url.indexOf("/", url.indexOf("://") + 3);
                    int queryStart = url.indexOf("?");
                    String path = queryStart > 0 ? url.substring(pathStart, queryStart) : url.substring(pathStart);

                    if (path.startsWith("/")) {
                        path = path.substring(1);
                    }

                    String[] parts = path.split("/", 2);
                    if (parts.length == 2) {
                        group = parts[0];
                        storageId = parts[1];
                        log.info("从URL解析到 group: {}, storageId: {}", group, storageId);
                    }
                }

                // 方式3: 如果还是解析失败，使用默认 group
                if (group == null) {
                    group = "group1";
                    storageId = savePath;
                    log.info("使用默认 group: {}, storageId: {}", group, storageId);
                }

                if (group != null && storageId != null) {
                    FastDfsFileInfo fileInfo = FastDfsFileInfo.builder()
                            .group(group)
                            .storageId(storageId)
                            .build();
                    int result = fastDfsClient.deleteFile(fileInfo);
                    if (result == 0) {
                        log.info("删除FastDFS文件成功，ID: {}", id);
                    } else {
                        log.warn("删除FastDFS文件返回非0，可能文件不存在或已删除，result: {}", result);
                    }
                } else {
                    log.warn("无法解析FastDFS文件路径，跳过删除，savePath: {}", savePath);
                }
            } catch (Exception e) {
                log.error("删除FastDFS文件失败，ID: {}", id, e);
                // 不抛出异常，继续删除数据库记录
            }
        }

        // 删除数据库记录
        int result = attachmentMapper.deleteById(id);
        if (result > 0) {
            log.info("附件删除成功，ID: {}", id);
        } else {
            log.warn("删除数据库记录失败，ID: {}", id);
            throw new RuntimeException("删除数据库记录失败");
        }
    }

    @Override
    @Transactional
    public void removeAttachmentsBatch(List<Long> ids) {
        if (ids == null || ids.isEmpty()) {
            log.warn("附件ID列表为空");
            return;
        }

        log.info("开始批量删除附件，IDs: {}", ids);

        // 批量查询所有附件
        List<Attachment> attachments = attachmentMapper.selectBatchIds(ids);
        if (attachments.isEmpty()) {
            log.warn("未找到要删除的附件，IDs: {}", ids);
            return;
        }

        // 批量删除FastDFS文件
        for (Attachment attachment : attachments) {
            if (StringUtils.hasText(attachment.getSavePath())) {
                try {
                    String savePath = attachment.getSavePath();
                    String group = null;
                    String storageId = null;

                    // 从 savePath 解析
                    if (savePath.contains("/")) {
                        String[] parts = savePath.split("/", 2);
                        if (parts.length == 2 && parts[0].startsWith("group")) {
                            group = parts[0];
                            storageId = parts[1];
                        }
                    }

                    // 从 URL 解析
                    if (group == null && StringUtils.hasText(attachment.getUrl())) {
                        String url = attachment.getUrl();
                        int pathStart = url.indexOf("/", url.indexOf("://") + 3);
                        int queryStart = url.indexOf("?");
                        String path = queryStart > 0 ? url.substring(pathStart, queryStart) : url.substring(pathStart);

                        if (path.startsWith("/")) {
                            path = path.substring(1);
                        }

                        String[] parts = path.split("/", 2);
                        if (parts.length == 2) {
                            group = parts[0];
                            storageId = parts[1];
                        }
                    }

                    if (group == null) {
                        group = "group1";
                        storageId = savePath;
                    }

                    FastDfsFileInfo fileInfo = FastDfsFileInfo.builder()
                            .group(group)
                            .storageId(storageId)
                            .build();
                    fastDfsClient.deleteFile(fileInfo);
                    log.info("删除FastDFS文件成功，ID: {}", attachment.getId());
                } catch (Exception e) {
                    log.error("删除FastDFS文件失败, id: {}", attachment.getId(), e);
                }
            }
        }

        // 批量删除数据库记录
        int result = attachmentMapper.deleteBatchIds(ids);
        log.info("批量删除附件完成，成功删除 {} 条记录", result);
    }

    @Override
    public AttachmentUploadVO uploadAttachment(AttachmentAddDTO addDto) throws Exception {
        log.info("开始上传附件，文件名: {}", addDto.getFile().getOriginalFilename());

        String fileName = addDto.getFile().getOriginalFilename();

        String extName = (fileName != null && fileName.contains("."))
                ? fileName.substring(fileName.lastIndexOf(".") + 1)
                : "";

        // 上传文件
        FastDfsFileInfo info = fastDfsClient.uploadFile(addDto.getFile().getBytes(), extName);

        if (info == null) {
            throw new RuntimeException("文件上传失败");
        }

        log.info("文件上传成功，group: {}, storageId: {}", info.getGroup(), info.getStorageId());

        // 构建URL
        String url = fastDfsClient.fetchUrl(info, urlPrefix, true);

        // 保存完整的存储路径（group + storageId）
        String fullSavePath = info.getGroup() + "/" + info.getStorageId();

        // 插入数据库
        Attachment attachment = new Attachment();
        attachment.setFileName(fileName);
        attachment.setFileSize((int) addDto.getFile().getSize());
        attachment.setName(addDto.getName());
        attachment.setFileType(extName);
        attachment.setUrl(url);
        attachment.setSavePath(fullSavePath);  // 保存完整路径，如 "group1/M00/00/00/xxx.png"
        attachment.setCreator(addDto.getCreator());
        attachment.setAddTime(LocalDateTime.now());

        int result = attachmentMapper.insert(attachment);
        if (result <= 0) {
            throw new RuntimeException("保存附件信息到数据库失败");
        }

        log.info("附件信息保存成功，ID: {}, savePath: {}", attachment.getId(), fullSavePath);

        // 返回结果
        AttachmentUploadVO uploadVO = new AttachmentUploadVO();
        uploadVO.setId(attachment.getId());
        uploadVO.setFileName(fileName);
        uploadVO.setFileSize((int) addDto.getFile().getSize());
        uploadVO.setFileSizeReadable(digitalSize(addDto.getFile().getSize()));
        uploadVO.setFileType(extName);
        uploadVO.setName(addDto.getName());
        uploadVO.setUrl(url);
        uploadVO.setSavePath(fullSavePath);
        uploadVO.setAddTime(attachment.getAddTime());
        uploadVO.setCreator(addDto.getCreator());
        uploadVO.setUploadStatus("success");
        uploadVO.setMessage("文件上传成功");
        return uploadVO;
    }

    public static String digitalSize(long size) {
        if (size <= 0) {
            return "0 B";
        }
        String[] units = new String[]{"B", "KB", "MB", "GB", "TB"};
        int unitIndex = 0;

        double dSize = size;

        while (dSize >= 1024 && unitIndex < units.length - 1) {
            dSize /= 1024;
            unitIndex++;
        }
        return String.format("%.2f %s", dSize, units[unitIndex]);
    }

    @Override
    public JsonVO<PageDTO<AttachmentDTO>> queryAttachmentList(AttachmentQuery query) {
        log.info("查询附件列表，查询条件: {}", query);

        // 构建分页对象
        Page<Attachment> page = new Page<>(query.getPageIndex(), query.getPageSize());
        // 构建条件
        LambdaQueryWrapper<Attachment> wrapper = new LambdaQueryWrapper<>();
        // 模糊查询：附件名称
        wrapper.like(StringUtils.hasText(query.getName()),
                Attachment::getName, query.getName());
        // 模糊查询：文件原名
        wrapper.like(StringUtils.hasText(query.getFileName()),
                Attachment::getFileName, query.getFileName());
        // 精确查询：文件类型
        wrapper.eq(StringUtils.hasText(query.getFileType()),
                Attachment::getFileType, query.getFileType());
        // 精确查询：创建人
        wrapper.eq(query.getCreator() != null,
                Attachment::getCreator, query.getCreator());
        // 时间范围
        wrapper.ge(query.getAddTimeStart() != null,
                Attachment::getAddTime, query.getAddTimeStart());
        wrapper.le(query.getAddTimeEnd() != null,
                Attachment::getAddTime, query.getAddTimeEnd());
        // 排序
        if ("asc".equalsIgnoreCase(query.getOrderDirection())) {
            wrapper.orderByAsc(getColumn(query.getOrderBy()));
        } else {
            wrapper.orderByDesc(getColumn(query.getOrderBy()));
        }
        // 执行查询
        Page<Attachment> resultPage = attachmentMapper.selectPage(page, wrapper);
        PageDTO<AttachmentDTO> pageDTO = PageDTO.create(resultPage, AttachmentDTO.class);
        return JsonVO.success(pageDTO);
    }

    private SFunction<Attachment, ?> getColumn(String column) {
        switch (column) {
            case "add_time":
                return Attachment::getAddTime;
            case "file_size":
                return Attachment::getFileSize;
            default:
                return Attachment::getAddTime;
        }
    }

    @Override
    public AttachmentDTO queryAttachmentById(Long id) {
        if (id == null) {
            return null;
        }
        Attachment attachment = attachmentMapper.selectById(id);
        if (attachment == null) {
            return null;
        }
        // 转换为DTO
        AttachmentDTO dto = new AttachmentDTO();
        dto.setId(Long.valueOf(attachment.getId()));
        dto.setFileName(attachment.getFileName());
        dto.setFileSize(attachment.getFileSize());
        dto.setFileType(attachment.getFileType());
        dto.setName(attachment.getName());
        dto.setUrl(attachment.getUrl());
        dto.setSavePath(attachment.getSavePath());
        dto.setAddTime(attachment.getAddTime());
        dto.setCreator(Long.valueOf(attachment.getCreator()));
        return dto;
    }

    @Override
    public String getDownloadUrl(Long id) {
        return "";
    }

    @Override
    public void incrementDownloadCount(Long id) {
    }

    @Override
    public Boolean validateAttachmentAccess(Long id) {
        return null;
    }

    @Override
    public boolean saveBatch(Collection<Attachment> entityList, int batchSize) {
        return false;
    }

    @Override
    public boolean saveOrUpdateBatch(Collection<Attachment> entityList, int batchSize) {
        return false;
    }

    @Override
    public boolean updateBatchById(Collection<Attachment> entityList, int batchSize) {
        return false;
    }

    @Override
    public boolean saveOrUpdate(Attachment entity) {
        return false;
    }

    @Override
    public Attachment getOne(Wrapper<Attachment> queryWrapper, boolean throwEx) {
        return null;
    }

    @Override
    public Map<String, Object> getMap(Wrapper<Attachment> queryWrapper) {
        return Collections.emptyMap();
    }

    @Override
    public <V> V getObj(Wrapper<Attachment> queryWrapper, Function<? super Object, V> mapper) {
        return null;
    }

    @Override
    public BaseMapper<Attachment> getBaseMapper() {
        return null;
    }

    @Override
    public Class<Attachment> getEntityClass() {
        return null;
    }
}
