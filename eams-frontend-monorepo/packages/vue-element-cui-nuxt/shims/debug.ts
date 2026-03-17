function createDebug(namespace) {
	const logger = () => {};

	logger.namespace = namespace;
	logger.enabled = false;
	logger.extend = (suffix) => createDebug(`${namespace}:${suffix}`);
	logger.destroy = () => {};

	return logger;
}

const debugFactory = createDebug;

debugFactory.debug = debugFactory;
debugFactory.default = debugFactory;
debugFactory.coerce = (value) => value;
debugFactory.disable = () => "";
debugFactory.enable = () => {};
debugFactory.enabled = () => false;
debugFactory.humanize = (value) => String(value);
debugFactory.destroy = () => {};
debugFactory.formatters = {};
debugFactory.names = [];
debugFactory.skips = [];
debugFactory.selectColor = () => 0;

export const debug = debugFactory;
export const coerce = debugFactory.coerce;
export const disable = debugFactory.disable;
export const enable = debugFactory.enable;
export const enabled = debugFactory.enabled;
export const humanize = debugFactory.humanize;
export const destroy = debugFactory.destroy;
export const formatters = debugFactory.formatters;
export const names = debugFactory.names;
export const skips = debugFactory.skips;
export const selectColor = debugFactory.selectColor;

export default debugFactory;
