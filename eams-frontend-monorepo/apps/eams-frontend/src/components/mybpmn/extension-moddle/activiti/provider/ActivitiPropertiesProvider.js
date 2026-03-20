/**
 * A provider with a `#getGroups(element)` method
 * that exposes groups for a diagram element.
 * @param {PropertiesPanel} propertiesPanel 属性面板
 * @param {Function} translate 翻译函数
 */
export default function ActivitiPropertiesProvider(propertiesPanel, translate) {
	// API ////////

	/**
	 * Return the groups provided for the given element.
	 * @param {DiagramElement} element
	 * @return {(Object[]) => (Object[])} groups middleware
	 */
	this.getGroups = function (element) {
		console.log(element, translate);
		/**
		 * We return a middleware that modifies
		 * the existing groups.
		 * @param {Object[]} groups
		 * @return {Object[]} modified groups
		 */
		return function (groups) {
			// FIXME: implement groups
			return groups;
		};
	};

	// registration ////////

	// Register our custom activiti properties provider.
	// Use a lower priority to ensure it is loaded after
	// the basic BPMN properties.
	propertiesPanel.registerProvider(LOW_PRIORITY, this);
}

ActivitiPropertiesProvider.$inject = ["propertiesPanel", "translate"];
