{
	var ES5Class=function(obj){
		var constructor=obj.hasOwnProperty('constructor')?
			obj.constructor
			:
			function(){}
		;
		Object.getOwnPropertyNames(obj).forEach(
			function(key){
				var descriptor=Object.getOwnPropertyDescriptor(obj,key);
				descriptor.enumerable=false;
				Object.defineProperty(constructor.prototype,key,descriptor);
			}
		);
		return constructor;
	}
	module.exports=ES5Class;
}
