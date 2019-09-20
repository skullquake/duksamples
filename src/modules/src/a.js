/* -------------------------------------------------------------------------- */
Duktape.modSearch = function (id) {
	res = readFile('./lib/' + id);
	res = new TextDecoder("utf-8").decode(res);
	if (typeof res === 'string') {
		return res;
	}
}
/* -------------------------------------------------------------------------- */
var ES5Class=require('es5class.js')
/* -------------------------------------------------------------------------- */
var Rectangle=ES5Class({
	constructor:function (width, height) {
		this.width = width;
		this.height = height;
	},
	area: function () {
		return this.width * this.height;
	}
});
/* -------------------------------------------------------------------------- */
var r=new Rectangle(2,3);
console.log(r.area());
