import assigneeProp from "./parts/AssigneeProp";
import conExpPorp from "./parts/ConditionExpProp";
import { is } from "bpmn-js/lib/util/ModelUtil";
const LOW_PRIORITY = 500;
/**
 * 创建Flowable自定义属性组
 * @param {Function} translate 翻译函数
 * @param {Object[]} entries 属性组数据
 */
function createFlowableCustomerGroup(translate, entries) {
	const flowableGroup = {
		id: "flowable",
		label: translate("Flowable properties"),
		entries,
		tooltip: translate("Settings for flowable properties"),
	};
	return flowableGroup;
}

/**
 * A provider with a `#getGroups(element)` method
 * that exposes groups for a diagram element.
 * @param {PropertiesPanel} propertiesPanel 属性面板
 * @param {Function} translate 翻译函数
 */
export default function FlowablePropertiesProvider(propertiesPanel, translate) {
	// API ////////

	/**
	 * Return the groups provided for the given element.
	 * @param {DiagramElement} element
	 * @return {(Object[]) => (Object[])} groups middleware
	 */
	this.getGroups = function (element) {
		/**
		 * We return a middleware that modifies
		 * the existing groups.
		 * @param {Object[]} groups
		 * @return {Object[]} modified groups
		 */
		return function (groups) {
			// UserTask
			if (is(element, "bpmn:UserTask")) {
				groups.push(createFlowableCustomerGroup(translate, [assigneeProp(element)]));
			}
			// SequenceFlow
			if (is(element, "bpmn:SequenceFlow")) {
				groups.push(createFlowableCustomerGroup(translate, [conExpPorp(element)]));
			}
			return groups;
		};
	};

	// registration ////////

	// Register our custom flowable properties provider.
	// Use a lower priority to ensure it is loaded after
	// the basic BPMN properties.
	propertiesPanel.registerProvider(LOW_PRIORITY, this);
}

FlowablePropertiesProvider.$inject = ["propertiesPanel", "translate"];
