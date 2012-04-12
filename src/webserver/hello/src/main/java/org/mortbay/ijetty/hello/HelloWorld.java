package org.mortbay.ijetty.hello;
import org.json.*;
import java.io.*;
import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.ParcelFileDescriptor;
import android.util.Log;
import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.ServletOutputStream;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.android.future.usb.*;
/* ------------------------------------------------------------ */
/** Hello Servlet 
 * 
 */
public class HelloWorld extends HttpServlet 
{
    String proofOfLife = null;
   
	//////////////////////////////
	private UsbManager mUsbManager;
	private PendingIntent mPermissionIntent;
	private boolean mPermissionRequestPending;
	private static final String ACTION_USB_PERMISSION = "com.intijk.ADKDemo.USB_PERMISSION";
	private UsbAccessory mAccessory;
	private FileInputStream mInputStream;
	private FileOutputStream mOutputStream;
	private String TAG="Airnord";
	private PrintWriter pw;
	private ParcelFileDescriptor mFileDescriptor;
	private JSONObject jObjOutput,jObjInput;
	//////////////////////////////
	/////////////////////////////
	private final BroadcastReceiver mUsbReceiver=new BroadcastReceiver(){
		@Override
		public void onReceive(Context context, Intent intent) {
			// TODO Auto-generated method stub
			String action=intent.getAction();
			if(ACTION_USB_PERMISSION.equals(action)){
				synchronized(this){
					if(intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED, false)){
						UsbAccessory accessory = UsbManager.getAccessory(intent);
						if(accessory!=null){
							Log.d(TAG, "openAccessory: " + accessory);
							mFileDescriptor = mUsbManager.openAccessory(accessory);
							if(mFileDescriptor!=null){
								FileDescriptor fd=mFileDescriptor.getFileDescriptor();
								mInputStream = new FileInputStream(fd);
								mOutputStream= new FileOutputStream(fd);
								pw=new PrintWriter(mOutputStream,true);	
								/*
								try{
										pw=new PrintWriter(
											new BufferedWriter(
											new FileWriter("/sdcard/aaa")));
											
								}catch(IOException e){
										Log.e(TAG,"pw open failed" , e);
								}
								*/
							}
						}
					}else{
						Log.d(TAG,"Permission denied for accessory");
					}
				}
			}
		}
		
	};
    /* ------------------------------------------------------------ */
    public void init(ServletConfig config) throws ServletException
    {
    	super.init(config);
    	//to demonstrate it is possible
        Object o = config.getServletContext().getAttribute("org.mortbay.ijetty.contentResolver");
        android.content.ContentResolver resolver = (android.content.ContentResolver)o;
        android.content.Context androidContext = (android.content.Context)config.getServletContext().getAttribute("org.mortbay.ijetty.context");
        proofOfLife = androidContext.getApplicationInfo().packageName;
		mUsbManager = UsbManager.getInstance(androidContext);
		UsbAccessory[] accessories = mUsbManager.getAccessoryList();
		UsbAccessory accessory = (accessories == null ? null : accessories[0]);
		mPermissionIntent = PendingIntent.getBroadcast(androidContext, 0, new Intent(ACTION_USB_PERMISSION), 0);
		IntentFilter filter = new IntentFilter(ACTION_USB_PERMISSION);
		androidContext.registerReceiver(mUsbReceiver, filter);
		//发出请求
		try{
				mUsbManager.requestPermission(accessory, mPermissionIntent);
		}catch(Exception e){
				Log.e(TAG,"requestPermission Error");
		}
    }
    /* ------------------------------------------------------------ */
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        doGet(request, response);
    }
    /* ------------------------------------------------------------ */
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException
    {
        response.setContentType("text/html");
        ServletOutputStream out = response.getOutputStream();
		boolean actionDefined=true;
		jObjOutput=new JSONObject();
		String action=request.getParameter("action");	
		try{
				if(action!=null && action.length()>0){
						jObjOutput.put("action", action);
				}else{
						out.println("action did not set");
						out.flush();
						return ;
				}
				if(action.equals("Stop")){
						out.println("<h1>Stop</h1>");
						jObjOutput.put("action","Stop");
				}else if(action.equals("MoveForward")){
						jObjOutput.put("action","MoveForward");
						out.println("<h1>MoveForward</h1>");
				}else if(action.equals("MoveBackward")){
						jObjOutput.put("action","MoveBackward");
						out.println("<h1>MoveBackward</h1>");
				}else if(action.equals("MoveLeft")){
						jObjOutput.put("action","MoveLeft");
						out.println("<h1>MoveLeft</h1>");
				}else if(action.equals("MoveRight")){
						jObjOutput.put("action","MoveRight");
						out.println("<h1>MoveRight</h1>");
				}else if(action.equals("RotateLeft")){
						jObjOutput.put("action","RotateLeft");
						out.println("<h1>RotateLeft</h1>");
				}else if(action.equals("RotateRight")){
						jObjOutput.put("action","RotateRight");
						out.println("<h1>RotateRight</h1>");
				}else if(action.equals("Rotate")){
						jObjOutput.put("action","Rotate");
						int direct=Integer.parseInt(request.getParameter("direct"));
						jObjOutput.put("direct",direct);

						out.println("<h1>Rotate</h1>");
						out.println("<h1>direct)=" + direct + "</h1>");
				}else if(action.equals("MoveAngle")){
						jObjOutput.put("action","MoveAngle");
						int angle=Integer.parseInt(request.getParameter("angle"));
						float amp=Float.parseFloat(request.getParameter("amp"));
						jObjOutput.put("angle",angle);
						jObjOutput.put("amp",amp);

						out.println("<h1>MoveAngle</h1>");
						out.println("<h1>angle=" + angle + "<h1>");
						out.println("<h1>amp=" + amp + "<h1>");
				}else if(action.equals("TripodHAngle")){
						jObjOutput.put("action","TripodHAngle");
						int angle=Integer.parseInt(request.getParameter("angle"));
						jObjOutput.put("angle",angle);

						out.println("<h1>TripodHAngle</h1>");
						out.println("<h1>angle=" + angle + "</h1>");
				}else if(action.equals("TripodVAngle")){
						jObjOutput.put("action","TripodVAngle");
						int angle=Integer.parseInt(request.getParameter("angle"));
						jObjOutput.put("angle", angle);

						out.println("<h1>TripodVAngle</h1>");
						out.println("<h1>angle=" + angle + "</h1>");
				}else if(action.equals("TripodHStep")){
						jObjOutput.put("action","TripodHStep");
						int angle=Integer.parseInt(request.getParameter("angle"));
						jObjOutput.put("angle",angle);
						out.println("<h1>TripodHStep</h1>");
						out.println("<h1>angle=" + angle + "</h1>");
				}else if(action.equals("TripodVector")){
						int H=Integer.parseInt(request.getParameter("H"));
						int V=Integer.parseInt(request.getParameter("V"));
						jObjOutput.put("action","TripodVector");
						jObjOutput.put("H",H);
						jObjOutput.put("V",V);

						out.println("<h1>TripodVector</h1>");
						out.println("<h1>H=" + H + "</h1>");
						out.println("<h1>V=" + V + "</h1>");
				}else if(action.equals("TripodStepVector")){
						int H=Integer.parseInt(request.getParameter("H"));
						int V=Integer.parseInt(request.getParameter("V"));
						jObjOutput.put("action","TripodStepVector");
						jObjOutput.put("H",H);
						jObjOutput.put("V",V);

						out.println("<h1>TripodStepVector</h1>");
						out.println("<h1>H=" + H + "</h1>");
						out.println("<h1>V=" + V + "</h1>");
				}else if(action.equals("LightOn")){
						float amp=Float.parseFloat(request.getParameter("amp"));
						jObjOutput.put("action","LightOn");
						jObjOutput.put("amp",amp);

						out.println("<h1>LightOn</h1>");
						out.println("<h1>amp=" + amp + "<h1>");
				}else if(action.equals("LightOff")){
						jObjOutput.put("action","LightOff");

						out.println("<h1>LightOff</h1>");
				}else{
						actionDefined=false;
				}
		}catch(JSONException e){
				Log.e(TAG,"json add exception " + e);
		}
		if(actionDefined){
			WriteJson();
		}else{
				out.println("action " + action + " undefined");
		}
		out.flush(); //debug
		
	}
	private int d;
   	private void WriteJson(){
			if(pw==null){
					Log.e(TAG,"pw is null");
					return;
			}
			try {
					Log.e(TAG,jObjOutput.toString());
					pw.print(jObjOutput.toString()+"\003");
					/*
					if(d==0){
							d=1;
							pw.print("\077");
					}else{
							d=0;
							pw.print("\000");
					}
					*/
					pw.flush();
			} catch (Exception e) {
					// TODO Auto-generated catch block
					Log.e(TAG, "write failed", e);
			}
	}
}
