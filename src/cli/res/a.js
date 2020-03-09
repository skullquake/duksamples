alert("./res/a.js: starting server");
try{
	var s=new Server(8080);
	s.setOption("enable_directory_listing","yes");
	s.setOption("document_root","./pub");
	s.start();
	//s.poll();
}catch(e){
	console.log(e);
}
