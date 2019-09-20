{
	var ES3Class=function(obj){
		var constructor=obj.hasOwnProperty('constructor')?obj.constructor:function(){};
		var key;
		for(key in obj){
			if(obj.hasOwnProperty(key)&&key!=='constructor'){
				constructor.prototype[key]=obj[key];
			}
		}
		return constructor;
	};
	module.exports=ES3Class;
}
