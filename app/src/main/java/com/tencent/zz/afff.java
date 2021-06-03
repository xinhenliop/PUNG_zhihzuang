package com.tencent.zz;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;
import android.graphics.Color;
import android.graphics.PixelFormat;
import android.graphics.Point;
import android.provider.Settings;
import android.view.Display;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.ScrollView;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.ref.WeakReference;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

import android.app.Activity;


/**
 * Created by Administrator on 2021/1/31.
 */
public class afff {
       //模拟控件移动
       
    private static afff sInstance = new afff();
    private WeakReference<Activity> sCurrentActivityWeakRef;


    //计数器
    public static int mun=0;
    //基础变量
   public static int[][] add=new int[50][50];
   public static float[][] abb=new float[50][5];




    public static int bk;
        public static int bg;
        public static int 屏幕宽;
        public static int 屏幕高;
        public static  String string="";
        public static String bytestr;
        private WindowManager mwindow;
        private WindowManager.LayoutParams lparam;
        private WindowManager.LayoutParams mparam;
        private ImageButton mbutton;
        private boolean 悬浮球;
        public boolean zt;
        private boolean 是否已经打开悬浮窗;
        private double b;
       // private double w;
        private WindowManager mwMenu;
        private LinearLayout displayMenu;
        public static String 显示方框="false";
        public static String 显示射线="false";
        public static String 显示信息="false";
        public static String 绘制开关="false";
        public static String 显示骨骼="false";
        public static boolean 显示载具;
        public static boolean zm;
        public static boolean 人物透视;
        public static boolean jh;
        public static boolean dd;
        public static boolean ld;
        public static boolean zy;
        public static boolean zmk;
        private LinearLayout displayGameMenu;
        private WindowManager mwwMenu;
        private int af = WindowManager.LayoutParams.TYPE_TOAST;
        private int cf = WindowManager.LayoutParams.TYPE_SYSTEM_OVERLAY;
        private int fg = WindowManager.LayoutParams.TYPE_SYSTEM_ALERT;
        //控件列表
        //登录窗口的
        public Button 登录;
        public EditText 卡密框;
        //游戏窗口
        public TextView 关闭;

        //操作类主Context
        public static Context app;

        ///开关状态
        public boolean 按键1 = false;
        public boolean 按键2 = false;
        private boolean 按键3=false;
        private boolean 按键4=false;
        private boolean 按键5=false;
        private boolean 按键6=false;
        //开关变量
        public Switch 选项按钮1;
        public Switch 选项按钮2;
        public Switch 选项按钮3;
        public Switch 选项按钮4;
        public Switch 选项按钮5;
        public Switch 选项按钮6;
        //
        TextView 选项文本;


        public int 悬浮窗x,悬浮窗y;

        static{
            System.loadLibrary("native-lib");
        }



    //===============JNI函数===========//



    private native String login(String km,String jiqima);
    //
    private native void Start(int a);

    private native int LoadFF();
    
    //设置自瞄
    private native void setZM(int A);

    private native void INIT();
    //设置分辨率
    private native void setSwitch(int a,int b);
    
    
//===============JNI函数===========//

    public static boolean getzj(){
        return 显示载具;
    }
    public static boolean getzm(){
        return zm;
    }
    public static boolean getzy(){
        return zy;
    }
    public static boolean getjh(){
        return jh;
    }
    public static boolean getdd(){
        return dd;
    }
    public static boolean getld(){
        return false;
    }
        public static String 方框y()
        {
            // TODO: Implement this method
            return null;
        }

        public void afff()
        {

        }
        public void start(Context ao)
        {
        
            dd = false;
            ld = false;
            zm = false;
            jh = false;
            显示载具 =false;
            绘制开关 = "false";
            bytestr = "";
            app = ao;
            分辨率获取();
            setSwitch(屏幕高,屏幕宽);
            开启悬浮窗();
            INIT();
            //FloatService.ShowFloat(app);
            //写入(app.getFilesDir()+"/vb.log","1",false);
        }


    public static String getSignatureString(Signature sig) {
        byte[] hexBytes = sig.toByteArray();
        String fingerprint = "error!";
        try {
            MessageDigest digest = MessageDigest.getInstance("MD5");
            if (digest != null) {
                byte[] digestBytes = digest.digest(hexBytes);
                StringBuilder sb = new StringBuilder();
                for (byte digestByte : digestBytes) {
                    sb.append((Integer.toHexString((digestByte & 0xFF) | 0x100)), 1, 3);
                }
                fingerprint = sb.toString();
            }
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }

        return fingerprint;
    }




    public static String getSgin(){
            PackageManager a =  app.getPackageManager();
            String c = app.getPackageName();
            try{
                PackageInfo d =  a.getPackageInfo(c,PackageManager.GET_SIGNATURES);
                return  getSignatureString(d.signatures[0]);
            }catch (Exception e){

            }
            return "";
        }

        public static String getbWidth()
        {
            return String.valueOf(屏幕宽);
        }

        public static String getbg()
        {
            return String.valueOf(屏幕高);
        }

        public static String 屏幕k()
        {
            return String.valueOf(屏幕宽);
        }
        public static String 屏幕g()
        {
            return String.valueOf(屏幕高);
        }


        private void 开启悬浮窗()
        {
            try
            {
                mwindow = (WindowManager)app.getSystemService(Context.WINDOW_SERVICE);
                lparam = new WindowManager.LayoutParams();

                lparam.type =2038;
                if (Settings.canDrawOverlays(app))
                {
                    mbutton = new ImageButton(app);
                    mbutton.setBackgroundResource(R.drawable.ic_launcher_background);///悬浮球的图片
                    mbutton.setOnTouchListener(new View.OnTouchListener()
                    {

                        private boolean isMove;

                        private int mTouchStartX;

                        private int mTouchStartY;

                        @Override
                        public boolean onTouch(View v, MotionEvent event)
                        {
                            switch (event.getAction())
                            {
                                case MotionEvent.ACTION_DOWN:
                                    isMove = false;

                                    mTouchStartX = (int) event.getRawX();
                                    mTouchStartY = (int) event.getRawY();
                                    break;
                                case MotionEvent.ACTION_MOVE:
                                    int nowX = (int) event.getRawX();
                                    int nowY = (int) event.getRawY();
                                    int movedX = nowX - mTouchStartX;
                                    int movedY = nowY - mTouchStartY;
                                    if (movedX > 5 || movedY > 5)
                                    {
                                        isMove = true;
                                    }
                                    mTouchStartX = nowX;
                                    mTouchStartY = nowY;
                                    lparam.x += movedX;
                                    lparam.y += movedY;
                                    悬浮窗x  = lparam.x;
                                    悬浮窗y = lparam.y;
                                    mwindow.updateViewLayout(mbutton, lparam);
                                    break;
                                case MotionEvent.ACTION_UP:
                                    break;
                                case MotionEvent.ACTION_CANCEL:
                                    break;
                            }
                            return isMove;
                        }
                    });

                    mbutton.setOnClickListener(new View.OnClickListener()//悬浮球的单击事件
                    {

                        private boolean 悬浮窗;

                        @Override
                        public void onClick(View v)
                        {
                            if(zt){
                                加载游戏窗口();
                            }else{
                                加载登陆窗口();
                            }
                            mwindow.removeView(mbutton);//关闭悬浮球
                            悬浮球 = false;
                            
                        }

                    });

                    lparam.format = PixelFormat.RGBA_8888;
                    lparam.flags = WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
                    lparam.width = 120;
                    //宽度
                    lparam.height = 120;
                    //高度
                    if(悬浮窗x != 0){
                        lparam.x = 悬浮窗x;//x
                        lparam.y = 悬浮窗y;//y
                    }else{
                        lparam.x = 0;//x
                        lparam.y = 0;//y

                    }
                    mwindow.addView(mbutton, lparam);//加载悬浮球
                    悬浮球 = true;


                }
                else
                {
                    Toast.makeText(app, "开启失败", Toast.LENGTH_LONG).show();
                }
                是否已经打开悬浮窗 = true;

            }
            catch (Exception q)
            {
                //写入("/storage/emulated/0/Android/vbb/k.log",q.toString());
                Toast.makeText(app, q.toString(), Toast.LENGTH_SHORT).show();
            }
        }

        public String 读取密码()
        {
            String 密码=读取(app.getFilesDir() + "/km");
            return 密码;
        }

        public void 分辨率获取()
        {
            b = 0.314814815;
            WindowManager windowManager = (WindowManager)app.getSystemService(app.WINDOW_SERVICE);
            Display display = windowManager.getDefaultDisplay();
            Point outPoint = new Point();
            display.getRealSize(outPoint);
            屏幕宽 = outPoint.x;
            屏幕高 = outPoint.y;
            if (屏幕宽 > 屏幕高)
            {
                //w = 屏幕高 * b / 2 / 50000;
                bk = 屏幕宽 / 2;
                bg = 屏幕高 / 2;
            }
            else if (屏幕高 > 屏幕宽)
            {
                bk = 屏幕高 / 2;
                bg = 屏幕宽 / 2;
                写入("/sdcard/Android/data/.fbl", String.valueOf(屏幕宽) + "\n" + String.valueOf(屏幕高),false);
            }
        }


        public static void Toast(String a){
            Toast.makeText(app,a,Toast.LENGTH_LONG).show();
        }


        public static void 写入(String 路径, String 内容,boolean z)

        {
            try
            {

                FileWriter fw = new FileWriter(路径,z);
                fw.write(内容+"\n");
                fw.close();
            }
            catch (IOException e)
            {

                Toast.makeText(app,e.toString(),Toast.LENGTH_LONG).show();
            }
        }


        public static String 读取(String strFilePath)
        {
            String path = strFilePath;
            String content = ""; //文件内容字符串
            //打开文件
            File file = new File(path);
            //如果path是传递过来的参数，可以做一个非目录的判断
            if (file.isDirectory())
            {
            }
            else
            {
                try
                {
                    InputStream instream = new FileInputStream(file);
                    if (instream != null)
                    {
                        InputStreamReader inputreader = new InputStreamReader(instream);
                        BufferedReader buffreader = new BufferedReader(inputreader);
                        String line;
                        //分行读取
                        while ((line = buffreader.readLine()) != null)
                        {
                            content += line ;
                        }
                        instream.close();
                    }
                }
                catch (java.io.FileNotFoundException e)
                {
                }
                catch (IOException e)
                {
                }
            }
            return content;
        }

        private void 加载登陆窗口()
        {
            mwMenu = (WindowManager)app.getSystemService(Context.WINDOW_SERVICE);
            mparam = new WindowManager.LayoutParams();

            mparam.type =2038;
            初始化登陆框();
            mparam.format = PixelFormat.RGBA_8888;
            mparam.gravity = Gravity.CENTER;
            mparam.flags = WindowManager.LayoutParams.FLAG_SHOW_WALLPAPER;
            mparam.width = 600;
            //宽度
            mparam.height = WindowManager.LayoutParams.WRAP_CONTENT;
            //高度
            mparam.x = 0;//x
            mparam.y = 0;//y

            mwMenu.addView(displayMenu, mparam);

            //悬浮窗长按监听
            displayMenu.setOnTouchListener(new View.OnTouchListener()
            {

                private boolean 移动;

                private int 按下X;

                private int 按下Y;
                @Override
                public boolean onTouch(View v, MotionEvent event)
                {
                    switch (event.getAction())
                    {
                        case MotionEvent.ACTION_DOWN://单击
                            移动 = false;
                            按下X = (int) event.getRawX();
                            按下Y = (int) event.getRawY();
                            break;
                        case MotionEvent.ACTION_MOVE://拖动
                            int nowX = (int) event.getRawX();
                            int nowY = (int) event.getRawY();
                            int movedX = nowX - 按下X;
                            int movedY = nowY - 按下Y;
                            if (movedX > 5 || movedY > 5)
                            {
                                移动 = true;
                            }
                            按下X = nowX;
                            按下Y = nowY;
                            lparam.x += movedX;
                            lparam.y += movedY;
                            mwindow.updateViewLayout(displayMenu, mparam);
                            break;
                        case MotionEvent.ACTION_UP://抬起
                            break;
                        case MotionEvent.ACTION_CANCEL:
                            break;
                    }
                    return 移动;
                }
            });



        }
        private void 初始化登陆框()
        {
        //基础布局


        displayMenu = new LinearLayout(app);
        displayMenu.setBackgroundColor(Color.rgb(83, 134, 139));
        displayMenu.setOrientation(LinearLayout.VERTICAL);
        displayMenu.setGravity(Gravity.CENTER_VERTICAL);
        卡密框 = new EditText(app);
        卡密框.setHint("输入购买的单码卡密");
        卡密框.setWidth(dip2px(app, 150));
        卡密框.setTextSize(15);
        displayMenu.addView(卡密框);
        登录 = new Button(app);
        登录.setText("登录卡密");
        登录.setWidth(dip2px(app, 100));
        登录.setOnClickListener(new View.OnClickListener(){

            @Override
            public void onClick(View p1)
            {

                String a="";
                try{
                    a = login(卡密框.getText().toString(),EggUtil.getImei(app));
                    //写入("/storage/emulated/0/Android/vbb/m.log0",a);
                }catch (Exception e ){
                    a = e.toString();
                }
                Toast.makeText(app, a, Toast.LENGTH_SHORT).show();
                
                if(zt){
                    开启悬浮窗();//显示主悬浮窗
                    mwMenu.removeView(displayMenu);//移除菜单
                    FloatService.ksi();
                }
             }


        });

        displayMenu.addView(登录);
        Button 关闭b = new Button(app);
        关闭b.setText("返回悬浮窗");
        登录.setWidth(dip2px(app, 100));
        关闭b.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View p1)
            {
                开启悬浮窗();//显示主悬浮窗
                mwMenu.removeView(displayMenu);//移除菜单
            }
        });

        displayMenu.addView(关闭b);
        // TODO: Implement this method
    }

        private void 加载游戏窗口()
        {

            try{
            mwwMenu = (WindowManager)app.getSystemService(Context.WINDOW_SERVICE);
            mparam = new WindowManager.LayoutParams();

            mparam.type = 2038;
            初始化游戏框();
            mparam.format = PixelFormat.RGBA_8888;
            mparam.gravity = Gravity.CENTER;
            mparam.flags = WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE;
            mparam.width = 600;
            //宽度
            mparam.height = WindowManager.LayoutParams.WRAP_CONTENT;


            if(悬浮窗x>0){
                mparam.x = 悬浮窗x;//x
                mparam.y = 悬浮窗y;//y
            }else{
                mparam.x = 0;//x
                mparam.y = 0;//y

            }


            mwwMenu.addView(displayGameMenu, mparam);

            //悬浮窗长按监听
            displayGameMenu.setOnTouchListener(new View.OnTouchListener()
            {

                private boolean 移动;

                private int 按下X;

                private int 按下Y;
                @Override
                public boolean onTouch(View v, MotionEvent event)
                {
                    switch (event.getAction())
                    {
                        case MotionEvent.ACTION_DOWN://单击
                            移动 = false;
                            按下X = (int) event.getRawX();
                            按下Y = (int) event.getRawY();
                            break;
                        case MotionEvent.ACTION_MOVE://拖动
                            int nowX = (int) event.getRawX();
                            int nowY = (int) event.getRawY();
                            int movedX = nowX - 按下X;
                            int movedY = nowY - 按下Y;
                            if (movedX > 5 || movedY > 5)
                            {
                                移动 = true;
                            }
                            按下X = nowX;
                            按下Y = nowY;
                            lparam.x += movedX;
                            lparam.y += movedY;
                            mwwMenu.updateViewLayout(displayMenu, mparam);
                            break;
                        case MotionEvent.ACTION_UP://抬起
                            break;
                        case MotionEvent.ACTION_CANCEL:
                            break;
                    }
                    return 移动;
                }
            });

            }catch(Exception a){
                写入("/storage/emulated/0/Android/vbb/k.log",a.toString(),false);
                //Toast.makeText(app, a.toString(), Toast.LENGTH_LONG).show();
            }



        }
        private void 初始化游戏框()
        {
            LinearLayout aga;
            LinearLayout agb;
            LinearLayout agc;
            LinearLayout agd;


            //留有空白的布局一定要创建监听否则会闪退
            //布局
            displayGameMenu = new LinearLayout(app);
            displayGameMenu.setBackgroundColor(Color.rgb(83, 134, 139));
            displayGameMenu.setOrientation(LinearLayout.VERTICAL);


            //标题布局
            TextView 文本 = new TextView(app);
            文本.setWidth(dip2px(app, 250));
            文本.setGravity(Gravity.CENTER);
            文本.setText("     云    诺   \n    单击关闭  ");
            文本.setHeight(dip2px(app, 55));
            文本.setTextSize(20);
            文本.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View p1)
                {
                    开启悬浮窗();//显示主悬浮窗
                    mwwMenu.removeView(displayGameMenu);//移除菜单
                }
            });
            displayGameMenu.addView(文本);

            //这里给布局框加监听是防止点到他闪退
            displayGameMenu.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View p1)
                {
                }
            });
            //列表布局
            ScrollView list_XX = new ScrollView(app);
            list_XX.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View p1)
                {
                }
            });
            //主布局空间
            LinearLayout zhu = new LinearLayout(app);
            zhu.setOrientation(LinearLayout.VERTICAL);
            zhu.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View p1)
                {
                }
            });



//选项布局    ============
            //主的LinearLayout布局Toast.makeText(app,"开启透视成功",Toast.LENGTH_SHORT).show();

            aga = new LinearLayout(app);
            aga.setPadding(dip2px(app, 5), dip2px(app, 5), dip2px(app, 5), dip2px(app, 5));
            aga.setOrientation(LinearLayout.HORIZONTAL);
            aga.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View p1)
                {
                }
            });
            aga.setBackgroundColor(Color.rgb(211, 211, 211));

            //选项名称文本
            选项文本 = new TextView(app);
            选项文本.setText("开启透视");
            选项文本.setWidth(dip2px(app, 165));
            选项文本.setTextColor(Color.rgb(25, 25, 25));
            aga.addView(选项文本);
            //开关选项的控件
            选项按钮1 = new Switch(app);
            选项按钮1.setWidth(dip2px(app, 50));
            选项按钮1.setHeight(dip2px(app, 40));
            //这里为了刷新控件的状态
            选项按钮1.setChecked(按键1);
            //这里好像没法写开关的监听，就用的点击监听
            选项按钮1.setOnClickListener(new View.OnClickListener(){

                                         @Override
                                         public void onClick(View p1)
                                         {

                                             try{
                                                 if (选项按钮1.isChecked())
                                                 {
                                                     //关闭改选项
                                                     选项按钮1.setChecked(true);
                                                     //选项1设置状态已便下次创建控件时的状态\
                                                    // Toast.makeText(app,"开启透视",Toast.LENGTH_SHORT).show();
                                                      final int ak;
                                                     Toast.makeText(app, "开启透视成功", Toast.LENGTH_SHORT).show();


//                                                   //  public void run() {
                                                             Start(0);
                                                      // }
                                                     //.start();


                                                     按键1 = true;
                                                     人物透视 = true;
                                                     绘制开关 = "true";



                                                     //
                                                 }
                                                 else
                                                 {
                                                     //开启选项
                                                     选项按钮1.setChecked(false);
                                                     按键1 = false;
                                                     人物透视 = false;
                                                     绘制开关 = "false";
                                                     //

                                                 }
                                             }catch (Exception e)
                                             {
                                                 Toast.makeText(app,e.toString(),Toast.LENGTH_SHORT).show();
                                             }
                                             // TODO: Implement this method

                                         }
                                     }
            );

            //添加
            aga.addView(选项按钮1);

            zhu.addView(aga);




            agb = new LinearLayout(app);
            agb.setPadding(dip2px(app, 5), dip2px(app, 5), dip2px(app, 5), dip2px(app, 5));
            agb.setOrientation(LinearLayout.HORIZONTAL);
            agb.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View p1)
                {
                }
            });
            //agb.setBackgroundColor(Color.rgb(211,211,211));
            选项文本 = new TextView(app);
            选项文本.setText("显示载具");
            选项文本.setWidth(dip2px(app, 165));
            选项文本.setTextColor(Color.rgb(25, 25, 25));
            agb.addView(选项文本);
            选项按钮2 = new Switch(app);
            选项按钮2.setWidth(dip2px(app, 50));
            选项按钮2.setHeight(dip2px(app, 40));
            选项按钮2.setChecked(按键2);
            选项按钮2.setOnClickListener(new View.OnClickListener(){
                                         @Override
                                         public void onClick(View p1)
                                         {
                                             // TODO: Implement this method
                                             if (选项按钮2.isChecked())
                                             {
                                                 //关闭改选项
                                                 选项按钮2.setChecked(true);
                                                 按键2 = true;
                                                 显示载具 = true;
                                                 Toast.makeText(app, "载具显示", Toast.LENGTH_SHORT).show();
                                                 
                                              }
                                             else
                                             {
                                                 //开启选项
                                                 选项按钮2.setChecked(false);
                                                 按键2 = false;
                                                 显示载具 = false;
                                                 Toast.makeText(app, "关闭载具显示", Toast.LENGTH_SHORT).show();

                                             }
                                         }
                                     }
            );
            agb.addView(选项按钮2);
            zhu.addView(agb);



            aga = new LinearLayout(app);
            aga.setPadding(dip2px(app, 5), dip2px(app, 5), dip2px(app, 5), dip2px(app, 5));
            aga.setOrientation(LinearLayout.HORIZONTAL);
            aga.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View p1)
                {
                }
            });
            aga.setBackgroundColor(Color.rgb(211, 211, 211));
            选项文本 = new TextView(app);
            选项文本.setText("开启自瞄");
            选项文本.setWidth(dip2px(app, 165));
            选项文本.setTextColor(Color.rgb(25, 25, 25));
            aga.addView(选项文本);
            选项按钮3 = new Switch(app);
            选项按钮3.setWidth(dip2px(app, 50));
            选项按钮3.setHeight(dip2px(app, 40));
            选项按钮3.setChecked(按键3);
            选项按钮3.setOnClickListener(new View.OnClickListener(){
                                         @Override
                                         public void onClick(View p1)
                                         {
                                             // TODO: Implement this method
                                             if (选项按钮3.isChecked())
                                             {
                                                 //关闭改选项
                                                 选项按钮3.setChecked(true);
                                                 按键3 = true;
                                                 Toast.makeText(app, "开启自瞄", Toast.LENGTH_SHORT).show();
                                                 zm = true;
                                                 setZM(1);
                                             }
                                             else
                                             {
                                                 //开启选项
                                                 选项按钮3.setChecked(false);
                                                 按键3 = false;
                                                 zm = false;
                                                 Toast.makeText(app, "关闭自瞄", Toast.LENGTH_SHORT).show();
                                                 setZM(0);
                                             }
                                         }
                                     }
            );

            aga.addView(选项按钮3);
            zhu.addView(aga);


            agb = new LinearLayout(app);
            agb.setPadding(dip2px(app, 5), dip2px(app, 5), dip2px(app, 5), dip2px(app, 5));
            agb.setOrientation(LinearLayout.HORIZONTAL);
            agb.setOnClickListener(new View.OnClickListener(){
                @Override
                public void onClick(View p1)
                {
                }
            });
            选项文本 = new TextView(app);
            选项文本.setText("开镜自瞄");
            选项文本.setWidth(dip2px(app, 165));
            选项文本.setTextColor(Color.rgb(25, 25, 25));
            agb.addView(选项文本);
            选项按钮6 = new Switch(app);
            选项按钮6.setWidth(dip2px(app, 50));
            选项按钮6.setHeight(dip2px(app, 40));
            选项按钮6.setChecked(按键6);
            选项按钮6.setOnClickListener(new View.OnClickListener(){
                                         @Override
                                         public void onClick(View p1)
                                         {
                                             // TODO: Implement this method
                                             if (选项按钮6.isChecked())
                                             {
                                                 //关闭改选项
                                                 选项按钮6.setChecked(true);
                                                 按键6 = true;
                                                 zmk = true;
                                                 Toast.makeText(app, "开启开镜自瞄", Toast.LENGTH_SHORT).show();
                                                setZM(3);
                                             }
                                             else
                                             {
                                                 //开启选项
                                                 选项按钮6.setChecked(false);
                                                 按键6 = false;
                                                 zmk =false;
                                                 Toast.makeText(app, "关闭开镜自瞄", Toast.LENGTH_SHORT).show();
                                                 setZM(2);
                                             }
                                         }
                                     }
            );
            agb.addView(选项按钮6);
            zhu.addView(agb);
            list_XX.addView(zhu);
            displayGameMenu.addView(list_XX);
        }

        //=====游戏布局完

        public static int dip2px(Context context, float dpValue)
        {
            final float scale = context.getResources().getDisplayMetrics().density;
            return (int) (dpValue * scale + 0.5f);
        }

        public static int dip2sp(Context context, float dpValue)
        {
            final float scale = context.getResources().getDisplayMetrics().density /
                    context.getResources().getDisplayMetrics().scaledDensity;
            return (int) (dpValue * scale + 0.5f);
        }

        /**
         * 根据手机的分辨率从 px(像素) 的单位 转成为 dp
         */
        public static int px2dip(Context context, float pxValue)
        {
            final float scale = context.getResources().getDisplayMetrics().density;
            return (int) (pxValue / scale + 0.5f);
        }

        /**
         * 将px值转换为sp值，保证文字大小不变
         */
        public static int px2sp(Context context, float pxValue)
        {
            final float fontScale = context.getResources().getDisplayMetrics().scaledDensity;
            return (int) (pxValue / fontScale + 0.5f);
        }

        /**
         * 将sp值转换为px值，保证文字大小不变
         */
        public static int sp2px(Context context, float spValue)
        {
            final float fontScale = context.getResources().getDisplayMetrics().scaledDensity;
            return (int) (spValue * fontScale + 0.5f);
        }



        //===登陆布局


}
