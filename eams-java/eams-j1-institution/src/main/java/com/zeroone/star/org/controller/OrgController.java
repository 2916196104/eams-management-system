package com.zeroone.star.org.controller;

import com.zeroone.star.org.service.IOrgService;
import com.zeroone.star.project.components.user.UserHolder;
import com.zeroone.star.project.dto.j1.org.OrgSaveDTO;
import com.zeroone.star.project.j1.org.OrgApi;
import com.zeroone.star.project.query.j1.org.OrgQuery;
import com.zeroone.star.project.vo.JsonVO;
import com.zeroone.star.project.vo.ResultStatus;
import com.zeroone.star.project.vo.j1.org.OrgDetailVO;
import com.zeroone.star.project.vo.j1.org.OrgListVO;
import com.zeroone.star.project.vo.j1.org.OrgTreeVO;
import lombok.extern.slf4j.Slf4j;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.RestController;

import javax.annotation.Resource;
import javax.validation.Valid;
import java.util.List;

@RestController
@Slf4j
@Validated
public class OrgController implements OrgApi {

    @Resource
    private IOrgService orgService;

    @Resource
    private UserHolder userHolder;

    @Override
    public JsonVO<List<OrgTreeVO>> queryOrgTree(Long parentOrgId) {
        try {
            List<OrgTreeVO> treeList = orgService.queryOrgTree(parentOrgId);
            return JsonVO.success(treeList);
        } catch (Exception e) {
            log.error("查询机构树失败: {}", e.getMessage(), e);
            return JsonVO.create(null, ResultStatus.FAIL.getCode(), "查询机构树失败：" + e.getMessage());
        }
    }

    @Override
    public JsonVO<List<OrgListVO>> queryOrgList(OrgQuery query) {
        try {
            if (query == null) {
                query = new OrgQuery();
            }
            List<OrgListVO> listVO = orgService.queryOrgList(query);
            return JsonVO.success(listVO);
        } catch (Exception e) {
            log.error("查询机构列表失败: {}", e.getMessage(), e);
            return JsonVO.create(null, ResultStatus.FAIL.getCode(), "查询机构列表失败：" + e.getMessage());
        }
    }

    @Override
    public JsonVO<OrgDetailVO> queryOrgDetail(Long orgId) {
        try {
            if (orgId == null || orgId <= 0) {
                return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), "机构ID不能为空");
            }

            OrgDetailVO detailVO = orgService.queryOrgDetail(orgId);
            if (detailVO == null) {
                return JsonVO.create(null, ResultStatus.FAIL.getCode(), "机构不存在");
            }
            return JsonVO.success(detailVO);
        } catch (Exception e) {
            log.error("查询机构详情失败: orgId={}, error={}", orgId, e.getMessage(), e);
            return JsonVO.create(null, ResultStatus.FAIL.getCode(), "查询机构详情失败：" + e.getMessage());
        }
    }

    @Override
    public JsonVO<String> saveOrg(@Valid OrgSaveDTO saveDTO) {
        try {
            Long operatorId = userHolder.getCurrentUserId();
            Long operatorOrgId = userHolder.getCurrentOrgId();

            if (operatorId == null) {
                log.warn("无法获取当前用户ID，使用默认值");
                operatorId = 0L;
            }

            if (saveDTO.getOrgId() != null && saveDTO.getOrgId().equals(saveDTO.getParentOrgId())) {
                return JsonVO.create(null, ResultStatus.PARAMS_INVALID.getCode(), "不能将自己设为父机构");
            }

            Long orgId = orgService.saveOrg(saveDTO, operatorId);

            String message = saveDTO.getOrgId() == null ?
                    "新增机构成功，机构ID：" + orgId :
                    "修改机构成功，机构ID：" + orgId;
            log.info("{} - 操作人ID: {}, 所属机构ID: {}", message, operatorId, operatorOrgId);

            return JsonVO.success(message);
        } catch (Exception e) {
            log.error("保存机构失败: {}", e.getMessage(), e);
            return JsonVO.create(null, ResultStatus.FAIL.getCode(), "保存机构失败：" + e.getMessage());
        }
    }

    @Override
    public JsonVO<Boolean> removeOrg(Long orgId) {
        try {
            if (orgId == null || orgId <= 0) {
                return JsonVO.create(false, ResultStatus.PARAMS_INVALID.getCode(), "机构ID不能为空");
            }

            Long operatorId = userHolder.getCurrentUserId();
            Long operatorOrgId = userHolder.getCurrentOrgId();
            log.info("删除机构: orgId={}, 操作人ID={}, 操作人所属机构ID={}", orgId, operatorId, operatorOrgId);

            boolean result = orgService.removeOrg(orgId);
            if (result) {
                return JsonVO.success(true);
            } else {
                return JsonVO.fail("删除机构失败");
            }
        } catch (RuntimeException e) {
            log.warn("删除机构失败: orgId={}, reason={}", orgId, e.getMessage());
            return JsonVO.create(false, ResultStatus.FAIL.getCode(), e.getMessage());
        } catch (Exception e) {
            log.error("删除机构异常: orgId={}, error={}", orgId, e.getMessage(), e);
            return JsonVO.create(false, ResultStatus.FAIL.getCode(), "删除机构失败：" + e.getMessage());
        }
    }
}
