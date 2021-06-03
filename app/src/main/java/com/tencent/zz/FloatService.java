package com.tencent.zz;

import android.*;
import android.app.*;
import android.content.*;
import android.graphics.*;
import android.os.*;
import android.view.*;
import android.view.WindowManager.*;
import android.widget.*;
import java.io.*;

import static com.tencent.zz.afff.屏幕高;

import static com.tencent.zz.afff.屏幕宽;

import static android.graphics.Typeface.BOLD;
import static android.graphics.Typeface.DEFAULT;
import android.widget.*;
import java.text.*;
import java.util.*;
import android.util.AttributeSet;

// AbdroidManifest.xml中添加以下配置:

//<!-- 悬浮窗所需权限 -->
//<uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW" />

// 注册当前悬浮窗服务
//<service
//    android:name="com.sci.FloatService"
//    android:enabled="true"
//    android:exported="true" >
//</service>

/** FloatService.java: 安卓悬浮窗 ----- 2018-6-15 上午11:49:11  */
public class FloatService extends Service
{
	private static int 屏幕宽,屏幕高;

	public static Context pp;

	private SurfaceHolder surfaceHolder;
    ActivityManager activityManager = null;
    Handler handler = new Handler();
    String activityName = null;
    String activity_last = null;
   
    private Runnable runnable;
    
	/** 显示悬浮窗 */
	public static void ShowFloat(Context context)
	{

		pp = context;
		if (Instance == null)
		{
			Intent intent = new Intent(context, FloatService.class);
			context.startService(intent);
		}
	}

	/** 关闭悬浮窗 */
	public static void HideFloat()
	{
		// Intent intent = new Intent(context, FloatService.class);
		// context.stopService(intent);

		if (Instance != null)
		{
			Instance.Hide();
		}
	}

	public static void ksi(){
		Instance.SetFloatView();
	}
	//-----------------------

	private static FloatService Instance;

	@Override
	public void onCreate()
	{
		super.onCreate();

		Instance = this;


		new afff().start(this);


        runnable = new Runnable() {


            @Override
            public void run() {
                List<ActivityManager.RunningTaskInfo> runningTaskInfo = activityManager.getRunningTasks(1);
                activityName = (runningTaskInfo.get(0).topActivity).toString();
                if (!(activityName.equals(activity_last))) {
                    activity_last += activityName+"\n";



                }
                
               // afff.写入(pp.getFilesDir()+"/vlog.log",activity_last+"\n\n\n",false);
                handler.postDelayed(runnable, 10);
            }
        };

	}

	@Override
	public IBinder onBind(Intent intent)
	{
		return null;
	}

	/** 移除悬浮窗，停止服务 */
	public void Hide()
	{
		Instance = null;

		manager.removeView(mFloatLayout);	// 移除悬浮窗
		this.stopSelf();					// 停止服务
		this.onDestroy();
	}


	WindowManager manager;

	LinearLayout mFloatLayout;
	ImageView settings;
	ImageView search;

	WindowManager.LayoutParams params;

	private void SetFloatView()
	{
		// 从布局文件，生成悬浮窗
		/*
		 LayoutInflater inflater = LayoutInflater.from(getApplicationContext());
		 mFloatLayout = (LinearLayout) inflater.inflate(R.layout.float_vie, null);
		// 添加悬浮窗至系统服务
		
		
		*/
		mFloatLayout = new LinearLayout(getApplicationContext());
		mFloatLayout.setOrientation(LinearLayout.VERTICAL);
		mFloatLayout.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.MATCH_PARENT));
		SurfaceView ax = new SurfaceView(getApplicationContext());
		 
		ax.setLayoutParams(new LayoutParams(LayoutParams.MATCH_PARENT,LayoutParams.MATCH_PARENT));
		
		mFloatLayout.addView(ax);	
		
	//	mFloatLayout.addView(文本);
	   
		
		params = getParams();
		manager = (WindowManager) getApplicationContext().getSystemService(Context.WINDOW_SERVICE);
		manager.addView(mFloatLayout, params);
	
		ax.getHolder().addCallback(new mSurfaceView(getApplicationContext(),ax.getHolder()));
		
	}

	// 拖动浮标时修改浮标位



	private WindowManager.LayoutParams getParams()
	{
		WindowManager.LayoutParams wmParams = new WindowManager.LayoutParams();
		wmParams.type =   WindowManager.LayoutParams.TYPE_SYSTEM_OVERLAY;   			// 设置window type
		wmParams.format = PixelFormat.RGBA_8888;   			// 设置图片格式，效果为背景透明
		wmParams.flags = WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE | WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE | WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL | WindowManager.LayoutParams.FLAG_FULLSCREEN | WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS | WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN; 	// 设置浮动窗口不可聚焦（实现操作除浮动窗口外的其他可见窗口的操作）
		wmParams.gravity = Gravity.LEFT | Gravity.TOP;		// 调整悬浮窗显示的停靠位置为左侧置顶

		// 以屏幕左上角为原点，设置x、y初始值（10,10），相对于gravity
		wmParams.x = 0;
		wmParams.y = 0;

		WindowManager windowManager = (WindowManager)getApplicationContext().getSystemService(WINDOW_SERVICE);
		Display display = windowManager.getDefaultDisplay();
		Point outPoint = new Point();
		display.getRealSize(outPoint);
		屏幕宽 = outPoint.x;
		屏幕高 = outPoint.y;

		// 设置悬浮窗口长宽数据
		if (屏幕宽 > 屏幕高)
		{
			wmParams.width = 屏幕宽; //(int)Float.parseFloat(afff.屏幕k());
			wmParams.height =屏幕高; //(int) Float.parseFloat(afff.屏幕g());
		}
		else if (屏幕高 > 屏幕宽)
		{
			wmParams.width = 屏幕高; //(int)Float.parseFloat(afff.屏幕k());
            wmParams.height =屏幕宽; //(int) Float.parseFloat(afff.屏幕g());

		}


		return wmParams;
	}
}

