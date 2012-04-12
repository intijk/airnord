var isdown=false;
var centerX=200,centerY=200;
var bigR=100;smallR=20;
var angle=0;
var lastSendTime=Date.now();


$("canvas").drawEllipse({
  strokeStyle: "#69f",
  strokeWidth: 3,
  x: centerX, y: centerY,
  width: bigR*2, height: bigR*2,
  fromCenter: true
});


$("canvas")
  .bind('mousedown',function(){
	isdown=true;
})
  .bind('mouseup',function(){
  	isdown=false;
})
  .bind('mousemove',function(e){
    if(isdown){
    	$("canvas")
          .clearCanvas()
          .drawEllipse({
  		strokeStyle: "#69f",
  		strokeWidth: 3,
  		x: centerX, y: centerY,
  		width: bigR*2, height: bigR*2,
  		fromCenter: true
	})
          .drawArc({
 		strokeStyle: "#69f",
  		strokeWidth: 2,
  		x: e.offsetX, y: e.offsetY,
  		radius: smallR,
  		start: 0, end: 359.9
	})
          .drawLine({
  		strokeStyle: "#69f",
  		strokeWidth: 3,
  		x1: e.offsetX, y1: e.offsetY,
  		x2: centerX, y2: centerY,
	})
    deltaY=centerY-e.offsetY;
    deltaX=e.offsetX-centerX;
    if(Math.abs(deltaX)<0.02){
      if(e.offsetY>=centerY){
      	angle=-90;
      }else{
      	angle=90;
      }
    }else{
    	angle=Math.atan(deltaY/deltaX);
	angle=angle*360/2/Math.PI;
	if(deltaX<0){
		if(deltaY>=0){
			angle+=180;		
		}else{
			angle-=180;		
		}
	}
    }
    angle=Math.round(angle);
    amp=Math.sqrt(deltaX*deltaX+deltaY*deltaY)/bigR;
    if(amp>1)amp=1;
    console.log(angle);
    console.log(amp);
    if(Date.now()-lastSendTime>600){
        $.get("http://192.168.1.151:8080/hello-3.2-SNAPSHOT/sayit?action=MoveAngle&angle=" + angle + "&amp=" + amp,null,function(){
	console.log("success!");
});
	lastSendTime=Date.now();
    }
    }
	
  })
