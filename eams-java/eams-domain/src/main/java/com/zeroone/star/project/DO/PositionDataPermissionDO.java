package com.zeroone.star.project.DO;

import com.baomidou.mybatisplus.annotation.TableField;
import com.baomidou.mybatisplus.annotation.TableId;
import com.baomidou.mybatisplus.annotation.TableName;
import lombok.Data;

import java.io.Serializable;

/**
 * 数据权限
 * @TableName data_permission
 */
@TableName(value ="data_permission")
@Data
public class PositionDataPermissionDO implements Serializable {
    /**
     * 主键
     */
    @TableId
    private Long id;

    /**
     * 岗位id
     */
    private Long positionId;

    /**
     * 权限类型
     */
    private Integer scopeType;

    /**
     * 表名(可重复)
     */
    private String entityName;

    /**
     * 数据所有人字段名
     */
    private String ownerField;

    /**
     * 备注
     */
    private String info;

    /**
     * 数据所有组织字段名
     */
    private String ownerOrgField;

    @TableField(exist = false)
    private static final long serialVersionUID = 1L;

    @Override
    public boolean equals(Object that) {
        if (this == that) {
            return true;
        }
        if (that == null) {
            return false;
        }
        if (getClass() != that.getClass()) {
            return false;
        }
        PositionDataPermissionDO other = (PositionDataPermissionDO) that;
        return (this.getId() == null ? other.getId() == null : this.getId().equals(other.getId()))
            && (this.getPositionId() == null ? other.getPositionId() == null : this.getPositionId().equals(other.getPositionId()))
            && (this.getScopeType() == null ? other.getScopeType() == null : this.getScopeType().equals(other.getScopeType()))
            && (this.getEntityName() == null ? other.getEntityName() == null : this.getEntityName().equals(other.getEntityName()))
            && (this.getOwnerField() == null ? other.getOwnerField() == null : this.getOwnerField().equals(other.getOwnerField()))
            && (this.getInfo() == null ? other.getInfo() == null : this.getInfo().equals(other.getInfo()))
            && (this.getOwnerOrgField() == null ? other.getOwnerOrgField() == null : this.getOwnerOrgField().equals(other.getOwnerOrgField()));
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + ((getId() == null) ? 0 : getId().hashCode());
        result = prime * result + ((getPositionId() == null) ? 0 : getPositionId().hashCode());
        result = prime * result + ((getScopeType() == null) ? 0 : getScopeType().hashCode());
        result = prime * result + ((getEntityName() == null) ? 0 : getEntityName().hashCode());
        result = prime * result + ((getOwnerField() == null) ? 0 : getOwnerField().hashCode());
        result = prime * result + ((getInfo() == null) ? 0 : getInfo().hashCode());
        result = prime * result + ((getOwnerOrgField() == null) ? 0 : getOwnerOrgField().hashCode());
        return result;
    }

    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append(getClass().getSimpleName());
        sb.append(" [");
        sb.append("Hash = ").append(hashCode());
        sb.append(", id=").append(id);
        sb.append(", positionId=").append(positionId);
        sb.append(", scopeType=").append(scopeType);
        sb.append(", entityName=").append(entityName);
        sb.append(", ownerField=").append(ownerField);
        sb.append(", info=").append(info);
        sb.append(", ownerOrgField=").append(ownerOrgField);
        sb.append(", serialVersionUID=").append(serialVersionUID);
        sb.append("]");
        return sb.toString();
    }
}