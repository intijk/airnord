Android and Arduino Communication specification. (AAComm)
========

小车运动相关：
========
停止：
-----
	{
		"action":"Stop"
	}
向前移动：
-----
	{
		"action":"MoveForward"
	}

向后移动：
----
	{
		"action":"MoveBackward"
	}
向左移动：
----
	{
		"action":"MoveLeft"
	}
向右移动:
-----
	{
		"action":"MoveRight"
	}
向左旋转:
----
	{
		"action":"RotateLeft"
	}
向右旋转：
-----
	{
		"action":"RotateRight"
	}
旋转（direct为0代表逆时针，为1代表顺时针）:
-----
	{
		"action":"Rotate",
		"direct":0
	}
角度运动:
-----
	{
		"action":"MoveAngle",
		"angle":-90,
		"amp":0.8
	}

云台控制：
======
水平运动到角度：
-----
	{
		"action":"TripodHAngle",
		"angle":-15
	}
垂直运动到角度：
-----
	{
		"action":"TripodVAngle",
		"angle":10
	}

水平步进一段：
------
	{
		"action":"TripodHStep",
		"angle":-10
	}

垂直步进一段：
-----
	{
		"action":"TripodVStep",
		"angle":15
	}
移动到角度：
-----
	{
		"action":"TripodVector",
		"H":10,
		"V":5
	}
步进一个角度：
------
	{
		"action":"TripodStepVector",
		"H":-5,
		"V":10
	}

灯控:
=======
亮灯：
----
	{
		"action":"LightOn",
		"amp":0.6
	}

灭灯：
----
	{
		"action":"LightOff"
	}


终止码：
====
发送方需要在每个数据包之后添加0x03的ETX终止码，标志一个数据包发送的完成。
