package com.tencent.zz;

import android.app.*;
import android.os.*;
import android.content.*;
import android.provider.*;
import android.widget.*;
import android.graphics.*;
import android.net.*;





//主操作类








public class MainActivity extends Activity 
{
    
    private void 执行(String shell)
    {
        String s=shell;
        try
        {
            Runtime.getRuntime().exec(s,null,null);//执行
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
    
    
	@Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(黑屏窗());
		检查悬浮窗权限();



执行("su");
		//初始化操作
		//new afff().start(getApplicationContext());
		FloatService.ShowFloat(this);
		///=====跳转游戏首界面
		Intent ad = new Intent(this, Assrs.class);
	
	startActivity(ad);

		//关闭当前界面
	finish();
    }



	public void 检查悬浮窗权限()
	{
		if (!Settings.canDrawOverlays(getApplicationContext()))//如果不可以绘制悬浮窗
		{
			Toast.makeText(getApplicationContext(), "请开启悬浮窗权限", Toast.LENGTH_LONG).show();
			startActivityForResult(new Intent(Settings.ACTION_MANAGE_OVERLAY_PERMISSION, Uri.parse("package:" + getPackageName())), 0);
		}
	}

	private LinearLayout 黑屏窗()
	{
		//基础布局


		LinearLayout	displayMenu = new LinearLayout(getApplicationContext());


		displayMenu.setBackgroundColor(Color.rgb(0, 0, 0));
		displayMenu.setOrientation(LinearLayout.VERTICAL);


		return displayMenu;
		// TODO: Implement this method
	}


}
