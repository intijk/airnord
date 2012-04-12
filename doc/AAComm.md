Android and Arduino Communication specification. (AAComm)
========

Car robot motion:
========
Stop：
-----
	{
		"action":"Stop"
	}
MoveForward：
-----
	{
		"action":"MoveForward"
	}

MoveBackward：
----
	{
		"action":"MoveBackward"
	}
MoveLeft：
----
	{
		"action":"MoveLeft"
	}
MoveRight:
-----
	{
		"action":"MoveRight"
	}
RotateLeft:
----
	{
		"action":"RotateLeft"
	}
RotateRight：
-----
	{
		"action":"RotateRight"
	}
Rotate(direct=0 for anticlockwise, 1 for clockwise):
-----
	{
		"action":"Rotate",
		"direct":0
	}
MoveAngle:
-----
	{
		"action":"MoveAngle",
		"angle":-90,
		"amp":0.8
	}

CloudPlatform：
======
Move cloud platform horizontally to specified angle.
-----
	{
		"action":"TripodHAngle",
		"angle":-15
	}
Move cloud platform vertically to specified angle.
-----
	{
		"action":"TripodVAngle",
		"angle":10
	}

Step a specified angle horizontally.
------
	{
		"action":"TripodHStep",
		"angle":-10
	}

Step a specified angle vertically.
-----
	{
		"action":"TripodVStep",
		"angle":15
	}
Move to specified angle both horizontally and vertically.
-----
	{
		"action":"TripodVector",
		"H":10,
		"V":5
	}
Step a specified angle both horizontally and vertically.
------
	{
		"action":"TripodStepVector",
		"H":-5,
		"V":10
	}


Light Control
=======
Light on:
----
	{
		"action":"LightOn",
		"amp":0.6
	}

Light Off:
----
	{
		"action":"LightOff"
	}


Stop Code:
====
Sender need to append a 0x03 termination code after the json packet.
