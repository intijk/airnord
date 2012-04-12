vim:
	vim src/main/java/org/mortbay/ijetty/hello/HelloWorld.java 
dep:build push
build:
	mvn install
push:
	adb push target/hello-3.2-SNAPSHOT.war /sdcard/jetty/webapps
index:
	vim ./src/main/webapp/index.html
