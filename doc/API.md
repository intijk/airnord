-----------------  
  
#Move Action  
  
-----------------  
  
**GET action** *http://example.org/action*    
  
Parameters:  
  
+ action  *http://example.org/action?action=\[value\]*    
    
  Values:  
	- **Stop**    
	  Example: http://example.org/action?action=Stop         
  
	- **MoveForward**    
	  Example: http://example.org/action?action=MoveForward       
  
	- **MoveBackward**    
	  Example: http://example.org/action?action=MoveBackward  
  
	- **MoveLeft**    
      In truth, as Airnord using pedrail car,it is 'Rotate anticlockwise', example:    
	  *http://example.org/action?action=MoveLeft*  
  
	- **MoveRight**    
      In truth, as Airnord using pedrail car,it is 'Rotate clockwise', example:    
	  *http://example.org/action?action=MoveRight*  
  
	- **RotateLeft**    
	  The same as 'MoveLeft', example:  
	  *http://example.org/action?action=RotateLeft*  
  
	- **RotateRight**    
	  The same as 'MoveRight', example:  
	  *http://example.org/action?action=RotateRight*  
  
	- **Rotate**    
	  Should append parameter 'direct', example:    
	  *http://example.org/action?action=Rotate?direct=0*  
	  Where 0 indicate anticlockwise rotate, 1 for clockwise.  
	  
    - **MoveAngle**    
      Move in direction, append parameter 'angle' and 'amp', where amp is [0,1] for speed control. The angle is in the math cartesian coordinate type, ie. MoveForward is the same as angle=90, the angle ascend anticlockwisely. example:  
	  *http://example.org/action?action=MoveAngle&angle=90&amp=0.9*  
  
-----------------------  
  
#Cloud platform action  
  
----------------------  
  
**GET action** http://example.org/action  
  
Parameters:  
  
+ action  
  
	- **TripodHAngle**    
	  Move cloud platform horizontally to specified angle.  
	  Should append parameter 'angle'.  
	  Example:  
	  *http://example.org/action?action=TripodHAngle&angle=10*  
  
	- **TripodVAngle**    
	  Move cloud platform vertically to specified angle.  
	  Should append parameter 'angle'.  
	  Example:  
	  *http://example.org/action?action=TripodVAngle&angle=10*  
  
	- **TripodHStep**    
	  Step cloud platform a specified angle horizontally.  
	  Should append parameter 'angle'.  
	  Example:  
	  *http://example.org/action?action=TripodHStep&angle=10*  
	  
  
	- **TripodVStep**    
	  Step cloud platform a specified angle vertically.  
	  Should append parameter 'angle'.  
	  Example:  
	  *http://example.org/action?action=TripodVStep&angle=10*  
	   
	- **TripodVector**    
	  Move cloud platform to specified angle both horizontally and vertically.   
	  Should append parameter 'H' and 'V'.  
	  Example:  
	  *http://example.org/action?action=TripodVector&H=10&V=5*  
  
	- **TripodVector**    
	  Step cloud platform a specified angle both horizontally and vertically.   
	  Should append parameter 'H' and 'V'.  
	  Example:  
	  *http://example.org/action?action=TripodStepVector&H=10&V=5*  

---------------

#Light

----------------  

**GET action** *http://example.org/action*

Parameters:

+ action  *http://example.org/action?action=\[value\]*
	   
	- **LightOn**    
      Light on.  
	  Should appedn parameter 'amp', which indicate the amplitude of the light.  
	  Example:  
	  *http://example.org/action?action=LightOn&amp=0.8*  

	- **LightOff**    
	  Light Off.  
	  Example:  
	  *http://example.org/action?action=LightOff*  
	  
----------------------  
