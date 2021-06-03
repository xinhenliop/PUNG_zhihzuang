package com.tencent.zz;
import android.content.*;
import android.graphics.*;
import android.util.*;
import android.view.*;
import android.view.WindowManager.*;
import android.widget.Toast;

import java.io.*;
import java.text.*;
import java.util.*;
import java.util.Date;

import java.net.Socket;
import java.net.UnknownHostException;



import static android.graphics.Typeface.BOLD;
import static android.graphics.Typeface.DEFAULT;
import static com.tencent.zz.afff.写入;
import static com.tencent.zz.afff.绘制开关;
import static com.tencent.zz.afff.人物透视;
import static com.tencent.zz.afff.方框y;
import static com.tencent.zz.afff.bk;
import static com.tencent.zz.afff.bg;
import static com.tencent.zz.afff.string;
import static com.tencent.zz.afff.bytestr;



public class mSurfaceView extends SurfaceView implements SurfaceHolder.Callback,Runnable {
    //用于标注线程是否继续
    private boolean Flag = true;
    //SurfaceHolder
    SurfaceHolder surfaceHolder;
    //定义画笔
    Paint paint = new Paint();
    Paint paint1 = new Paint();
    Paint paint2 = new Paint();
    Paint paint3 = new Paint();
    Paint paint4 = new Paint();
    Paint paint5 = new Paint();
    Paint paint6 = new Paint();
    Paint paint7 = new Paint();
    Paint paint8 = new Paint();
    Paint paint9 = new Paint();
    Paint paint10 = new Paint();
    Paint paint11 = new Paint();
    Paint paint12 = new Paint();
    Paint paint13 = new Paint();
    Paint paint14 = new Paint();
    Paint paint15 = new Paint();
    Paint paint16 = new Paint();
    Paint paint17 = new Paint();
    Paint paint18 = new Paint();
    Paint paint19 = new Paint();
    Paint paint20 = new Paint();
    Paint paint21 = new Paint();
    Paint paint22 = new Paint();
    Paint paint23 = new Paint();
    Paint paint24 = new Paint();
    Paint paint25 = new Paint();
    Paint paint26 = new Paint();
    Paint paint27 = new Paint();
    Paint paint28 = new Paint();
    Paint paint29 = new Paint();
    Paint blue_dot = new Paint();
    Paint painttime = new Paint();
    Canvas canvas = null;
    float x = 0;
    float y = 0;
    private String bb="0";
    float x1 = 0;//左右偏移
    float Height = 0;//获取屏幕宽度、、2080
    float Width = 0;
    float SUO = 0;//获取缩放
    float w = 0;
    int h = 0;
    int m = 0;
    boolean 显示载具=false;
    boolean 简化=false;
    boolean 倒地不显 = false;
    boolean 不刷新 = false;
    boolean 雷达= false;
    boolean 自瞄= false;
    int stri=0;

    public static int 修正值 = 0;
    int n_player;
    int n_ai;
    int n_number;
    int 刷新=0;

    float hid;
    float DB = 0;
    int hp = 0;
    int xd = 0;
    float rj = 0;
    int wz = 0;
    int bh = 0;
    int db = 0;
    float dy = 0;
    float pd=0;

    int ggtzy = 0;
    int ggtgd = 0;
    int ggsbzy = 0;
    int ggsbsx = 0;
    int ggpgzy = 0;
    int ggpgsx = 0;
    int ggzjzy = 0;
    int ggzjsx = 0;
    int ggyjzy = 0;
    int ggyjsx = 0;
    int ggzszzy = 0;
    int ggzszsx = 0;
    int ggysjzy = 0;
    int ggysjsx = 0;
    int ggzswzy = 0;
    int ggzswsx = 0;
    int ggyswzy = 0;
    int ggyswsx = 0;
    int ggzdtzy = 0;
    int ggzdtsx = 0;
    int ggydtzy = 0;
    int ggydtsx = 0;
    int ggzxgzy = 0;
    int ggzxgsx = 0;
    int ggyxgzy = 0;
    int ggyxgsx = 0;
    int ggzjwzy = 0;
    int ggzjwsx = 0;
    int ggyjwzy = 0;
    int ggyjwsx = 0;

    private int hero=0;
    private float olh;

    Context qq;
    String[] color = new String[]{"#FFC0FF00","#FFFEFF5D","#FFFFCB2F","#FFFF7F00","#FFFF3416","#FFFF5D86","#FFD65DFF","#FFAE5EFF","#FF5C46FF","#FF2E63FF","#FF17A9FF","#FF00FFFF","#FF47B9FF","#FF16FFE2","#FF00FEBD","#FF75FFA9","#FF17FF6F","#FF5CFF46","#FFFF8BE3","#FFC6FFA1","#FFFFA88C","#FFFEA3C6","#FFFF0080","#FFFF642E","#FF8BFF46"};

    public mSurfaceView(Context context,SurfaceHolder ad) {
        super(context);
        //getWindow().setFlags(LayoutParams.FLAG_SECURE, LayoutParams.FLAG_SECURE);
        // 禁止截屏
        //activity.getWindow().addFlags(WindowManager.LayoutParams.FLAG_SECURE);
        //activity.getWindow().addFlags(WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE | WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE | WindowManager.LayoutParams.FLAG_NOT_TOUCH_MODAL | WindowManager.LayoutParams.FLAG_FULLSCREEN | WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS | WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN);


        surfaceHolder = ad;

        qq = context;
        surfaceHolder.addCallback(this);
        this.setZOrderOnTop(true);
        surfaceHolder.setFormat(PixelFormat.TRANSLUCENT);
    }

    private Bitmap getBitmapFromPath(String path) {
        if (!new File(path).exists()) {
            System.err.println("getBitmapFromPath: file not exists");
            return null;
        }
        byte[] buf = new byte[1024 * 1024];// 1M
        Bitmap bitmap = null;
        try {
            FileInputStream fis = new FileInputStream(path);
            int len = fis.read(buf, 0, buf.length);
            bitmap = BitmapFactory.decodeByteArray(buf, 0, len);
            int bw = bitmap.getWidth();
            int bh = bitmap.getHeight();
            float scale = Math.min(1f * 43 / bw, 1f * 43 / bh);
            bitmap = scaleBitmap(bitmap, scale);
            if (bitmap == null) {
                System.out.println("len= " + len);
                System.err
                        .println("path: " + path + "  could not be decode!!!");
            }
        } catch (Exception e) {
            e.printStackTrace();

        }
        return bitmap;
    }

    /**
     * 根据给定的宽和高进行拉伸
     *
     * @param origin 原图
     * @param scale  缩放比例
     * @return new Bitmap
     */

    private Bitmap scaleBitmap(Bitmap origin, float scale) {
        if (origin == null) {
            return null;
        }
        int height = origin.getHeight();
        int width = origin.getWidth();
        Matrix matrix = new Matrix();
        matrix.postScale(scale, scale);// 使用后乘
        Bitmap newBM = Bitmap.createBitmap(origin, 0, 0, width, height, matrix, false);
        if (!origin.isRecycled()) {
            origin.recycle();
        }
        return newBM;
    }

    public static String getFileContent(File file) {
        String content = "";
        if (!file.isDirectory()) {
            try {
                InputStream instream = new FileInputStream(file);
                if (instream != null) {
                    InputStreamReader inputreader
                            = new InputStreamReader(instream, "UTF-8");
                    BufferedReader buffreader = new BufferedReader(inputreader);
                    String line = "";
                    while ((line = buffreader.readLine()) != null) {
                        content += line;
                    }
                    instream.close();//关闭输入流
                }
            } catch (FileNotFoundException e) {
            } catch (IOException e) {
            }
        }
        return content;
    }

    @Override
    public void surfaceCreated(SurfaceHolder surfaceHolder) {
        //初始化画笔
        init();
        Flag = true;
        new Thread(this).start();
    }

    public String hqcl(int paramInt) {
        String str = "";
        switch (paramInt)
        {
            case 10:
            {
                str = "✈空投✈";
                break;
            }
            case 60:
            {
                str = "小心手雷";
                break;
            }
            case 70:
            {
                str = "【摩托车】";
                break;
            }
            case 71:
            {
                str = "【小绵羊】";
                break;
            }
            case 72:
            {
                str = "【三轮摩托】";
                break;
            }
            case 73:
            {
                str = "【蹦蹦车】";
                break;
            }
            case 74:
            {
                str = "【跑车】";
                break;
            }
            case 75:
            {
                str = "【小轿车】";
                break;
            }
            case 76:
            {
                str = "【皮卡车】";
                break;
            }
            case 77:
            {
                str = "【皮卡车】";
                break;
            }
            case 78:
            {
                str = "【吉普车】";
                break;
            }
            case 79:
            {
                str = "【游艇】";
                break;
            }
            default:
            {
                str = "【载具】";
                break;
            }
        }
        return str;
    }
    private void init() {
        //红点
        paint.setColor(Color.rgb(255,0,0));         //改过这里
        paint.setStyle(Paint.Style.FILL);
        paint.setStrokeWidth(3.5f);
        //射线
        paint1.setColor(Color.parseColor("#d7fff1"));
        paint1.setStyle(Paint.Style.FILL);
        paint1.setStyle(Paint.Style.STROKE);
        paint1.setStrokeWidth(2.5f);
        //距离描边
        paint2.setColor(Color.parseColor("#000000"));
        paint2.setStyle(Paint.Style.FILL);
        paint2.setStrokeWidth(1.5f);
        //距离
        paint3.setColor(Color.parseColor("#FF7777"));      //名字上的血量
        paint3.setTextSize(18);//字体大小
        paint3.setStrokeWidth(2f);

        paint16.setColor(Color.rgb(255,0,0));      //名字上的血量，玩家繁化时显示
        paint16.setTextSize(18);//字体大小

        //射线圆点
        paint4.setColor(Color.rgb(255, 255, 255));
        paint4.setStyle(Paint.Style.FILL);
        paint4.setTextSize(10);
        //血条边框
        paint5.setColor(Color.rgb(0,0,0));
        paint5.setStyle(Paint.Style.STROKE);  //边框
        paint5.setStrokeWidth(1.5f);
        //血条实心
        paint6.setColor(Color.parseColor("#00ffff"));
        paint6.setStyle(Paint.Style.FILL);
        //paint6.setAlpha(80);//透明性
        paint6.setStrokeWidth(10f);

        paint25.setColor(Color.parseColor("#11FF70"));      //名字上的字
        paint25.setTextSize(25);//字体大小
        paint25.setStrokeWidth(6f);

        paint20.setColor(Color.parseColor("#505050ff"));
        paint20.setStyle(Paint.Style.FILL);
        paint20.setStrokeWidth(10f);

        //方框实心
        paint7.setColor(Color.rgb(255, 255, 255));
        paint7.setStyle(Paint.Style.FILL);
        paint7.setAlpha(0);
        //方框边框
        paint8.setColor(Color.rgb(248,248,255));
        paint8.setStyle(Paint.Style.STROKE);
        paint8.setStrokeWidth(3.5f);
        //运行时间
        painttime.setColor(Color.rgb(255, 0, 0));//字体颜色
        //Typeface font = Typeface.create(Typeface.SANS_SERIF, BOLD);//加载字体
        //painttime.setTypeface(font);//设置字体
        painttime.setStrokeWidth(7);
        painttime.setTextSize(20);//字体大0小
        //背敌距离
        paint9.setColor(Color.rgb(255,255,0));
        paint9.setStyle(Paint.Style.FILL);
        paint9.setTextSize(25);
        paint9.setAlpha(205);
        //背敌
        paint10.setColor(Color.rgb(255, 0, 0));
        paint10.setStyle(Paint.Style.FILL);
        paint10.setTextSize(15);
        paint10.setAlpha(130);
        //队编背景
        paint11.setColor(Color.rgb(0,0,0));
        paint11.setStyle(Paint.Style.FILL);
        paint11.setAlpha(160);
        //队编-人机
        paint12.setColor(Color.parseColor("#00ffff"));//字体颜色       //预警人数，淡蓝色
        Typeface font = Typeface.create(Typeface.SANS_SERIF, BOLD);//加载字体
        paint12.setTypeface(font);//设置字体
        paint12.setStrokeWidth(10);
        paint12.setTextSize(35);//字体大0小
        //队编-玩家
        paint17.setColor(Color.parseColor("#ff0033"));//字体颜色       //预警人数，淡红色
        paint17.setTypeface(font);//设置字体
        paint17.setStrokeWidth(10);
        paint17.setTextSize(35);//字体大0小

        paint18.setColor(Color.parseColor("#7CFBFB"));//字体颜色       //空投显示
        paint18.setTypeface(font);//设置字体
        paint18.setStrokeWidth(5);
        paint18.setTextSize(28);//字体大0小

        paint19.setColor(Color.parseColor("#F8F82A"));//字体颜色       //载具显示
        paint19.setTypeface(font);//设置字体
        paint19.setStrokeWidth(5);
        paint19.setTextSize(28);//字体大0小

        paint22.setColor(Color.rgb(255,0,0));//字体颜色       //红色文字，小心手雷
        paint22.setTypeface(font);//设置字体
        paint22.setStrokeWidth(5);
        paint22.setTextSize(28);//字体大0小

        blue_dot.setStyle(Paint.Style.FILL);    //雷达相关
        blue_dot.setStrokeWidth(12);


        paint13.setColor(Color.parseColor("#ff00ff73"));
        paint13.setStyle(Paint.Style.FILL);
        paint13.setAlpha(160);


        paint14.setColor(Color.rgb(255,0,0));            //玩家骨骼颜色
        paint14.setStyle(Paint.Style.STROKE);
        paint14.setStrokeWidth(1.5f);

        paint15.setColor(Color.parseColor("#33ff66"));
        paint15.setStyle(Paint.Style.STROKE);
        paint15.setStrokeWidth(2.5f);



        paint21.setColor(Color.rgb(255,0,0));           //改过这里，大红色
        paint21.setStyle(Paint.Style.STROKE);
        paint21.setStrokeWidth(10f);


    }
    public void sleep()
    {
        try {
            Thread.sleep(5);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }



    /*
    public static int tryint(String str)//异常处理，int转换
    {
        int re = 0;
        try {
            re = Integer.parseInt(str);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return re;

    }
    public static float tryfloat(String str)//异常处理，float转换
    {
        float re = 0;
        try {
            re = Float.parseFloat(str);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return re;
    }
    public static int bytegetInt(byte[] bytes)
    {
        int re = 0;
        try {
            re = (0xff & bytes[0]) | (0xff00 & (bytes[1] << 8)) | (0xff0000 & (bytes[2] << 16)) | (0xff000000 & (bytes[3] << 24));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return (re);
    }
    public static float getfloat(int num)
    {
        float re = 0;
        try {
            byte[] b = new byte[4];
            b[0] = bytestr[num];
            b[1] = bytestr[num+1];
            b[2] = bytestr[num+2];
            b[3] = bytestr[num+3];
            re = Float.intBitsToFloat(bytegetInt(b));
        } catch (Exception e) {
            e.printStackTrace();
        }
        //Float.floatToIntBits(data)
        //afff.写入("/sdcard/Yunai/zhi",str);
        //Float.intBitsToFloat(getInt(b));
        return(re);
    }
    public static int getint(int num)
    {
        int re = 0;
        try {
            byte[] b = new byte[4];
            b[0] = bytestr[num];
            b[1] = bytestr[num+1];
            b[2] = bytestr[num+2];
            b[3] = bytestr[num+3];
            re = bytegetInt(b);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return(re);
    }
    public static String getplayername(int num)
    {
        String re = "";
        try {
            byte[] b = new byte[32];
            for(int i=0;i<32;i++)
            {
                b[i] = bytestr[num+i];
            }
            re = new String(b);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return re;
    }


     */
    public static boolean deleteFile(String fileName) {
        File file = new File(fileName);
        if (file.isFile() && file.exists()) {
            file.delete();
            //System.out.println("删除单个文件" + fileName + "成功！");
            return true;
        } else {
            //System.out.println("删除单个文件" + fileName + "失败！");
            return false;
        }
    }
    @Override
    public void surfaceChanged(SurfaceHolder surfaceHolder, int i, int i1, int i2) {
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder surfaceHolder) {
        Flag = false;
    }
    @Override
    public void run() {
        Thread syncTask = new Thread(new Runnable() {
            @Override

            public void run() {
                while (Flag) {
                    try {
                        canvas = surfaceHolder.lockCanvas();
                        canvas.drawColor(Color.TRANSPARENT, PorterDuff.Mode.CLEAR);

                    } catch (Exception e) {
                        break;
                    }
                    //循环打印运行时间
                    //开始执行
                    float x2;

                    float x3;
                    float xu;
                    Width=Float.parseFloat(afff.getbWidth());
                    Height=Float.parseFloat(afff.getbg());
                    if (绘制开关.equals("true")) {
                        //           deleteFile("/sdcard/Yunai/桩5");
                        //           afff.写入("/sdcard/Yunai/桩1","1");

                        //x1=Float.parseFloat(方框y());
                        //x1=-100;
                        显示载具=afff.getzj();
                        倒地不显 = afff.getdd();
                        简化 = afff.getjh();//读取时否简化
                        自瞄 = afff.getzm();//读取时否简化

                        //File file = new File("/storage/emulated/0/bo.log");//坐标输出必须和cpp的路径一致
                        //String b = getFileContent(file);
                        //String bb = b.replace(",,", ",");
                        //String[] concent = bb.split(";");
                        //afff.写入("/sdcard/Yunai/桩1",string);
                        //String[] str1 = string.split("$");
                        //afff.写入("/sdcard/Yunai/桩2",str1[0]);
                        //String[] concent = str1[0].split(";");
                        // int left = string.indexOf("end;") + 4;
                        //String[] concent = string.substring(0,left).split(";");
                        //String[] concent = string.split(";");
                        //afff.写入("/sdcard/Yunai/坐标",string);
                        //string = new String(bytestr);

                        //afff.写入("/sdcard/Yunai/坐标2",string);
                        n_player = 0;
                        n_ai = 0;
                        n_number = 0;
                        stri = 0;
                        int count = 0;
                        String name = "";
                        boolean human = true;
                        boolean goon = false;
                        不刷新= false;
                        //String[] list_sj = bytestr.split(";");
                        int num = afff.mun;
                        afff.写入("/sdcard/vvv",String.valueOf(num),true);
                        while (num>0)
                        {
                            try {

                              //int type = Integer.parseInt(shuju[0]);
                                int type = afff.add[num][0];
                                //afff.写入("/sdcard/Yunai/桩12",new String(bytestr));
                                if(type!=5 && type != 6)
                                {
                                    goon = true;
                                    continue;
                                }


                                x = afff.abb[num][0];
                                y =afff.abb[num][1];
                                w = afff.abb[num][2];
                                hp = afff.add[num][1];
                                m = afff.add[num][2];
                                xd = afff.add[num][3];

                                if(type == 5)
                                {
                                    human = false;
                                }
                                else
                                {
                                    if (xd == 0) {
                                        n_ai += 1;
                                    } else {
                                        n_player += 1;
                                    }
                                    n_number++;
                                    human = true;
                                }
                                x1=修正值;
                                if (human) {
                                  db = afff.add[num][4];//队标
                                  ggtzy = afff.add[num][5];//骨骼头左右
                                  ggtgd = afff.add[num][6];//骨骼头高度
                                  ggsbzy = afff.add[num][7];//骨骼胸部左右
                                  ggsbsx = afff.add[num][8];//骨骼胸部上下
                                  ggpgzy = afff.add[num][9];//骨骼盆骨左右
                                  ggpgsx = afff.add[num][10];//骨骼盆骨上下
                                  ggzjzy = afff.add[num][11];//骨骼左肩左右
                                  ggzjsx = afff.add[num][12];//骨骼左肩上下
                                  ggyjzy = afff.add[num][13];//骨骼右肩左右
                                  ggyjsx = afff.add[num][14];//骨骼右肩上下
                                  ggzszzy = afff.add[num][15];//骨骼左手肘左右
                                  ggzszsx = afff.add[num][16];//骨骼左手肘上下
                                  ggysjzy = afff.add[num][17];//骨骼右手肘左右
                                  ggysjsx = afff.add[num][18];//骨骼右手肘上下
                                  ggzswzy = afff.add[num][19];//骨骼左手腕左右
                                  ggzswsx = afff.add[num][20];//骨骼左手腕上下
                                  ggyswzy = afff.add[num][21];//骨骼右手腕左右
                                  ggyswsx = afff.add[num][22];//骨骼右手腕上下
                                  ggzdtzy = afff.add[num][23];//骨骼左大腿左右
                                  ggzdtsx = afff.add[num][24];//骨骼左大腿上下
                                  ggydtzy = afff.add[num][25];//骨骼右大腿左右
                                  ggydtsx = afff.add[num][26];//骨骼右大腿上下
                                  ggzxgzy = afff.add[num][27];//骨骼左膝盖左右
                                  ggzxgsx = afff.add[num][28];//骨骼左膝盖上下
                                  ggyxgzy =afff.add[num][29];//骨骼右膝盖左右
                                  ggyxgsx = afff.add[num][30];//骨骼右膝盖上下
                                  ggzjwzy = afff.add[num][31];//骨骼左脚腕左右
                                  ggzjwsx = afff.add[num][32];//骨骼左脚腕上下
                                  ggyjwzy = afff.add[num][33];//骨骼右脚腕左右
                                  ggyjwsx = afff.add[num][34];//骨骼右脚腕上下
                                   name="玩家";
                                }

                            } catch (Exception v) {
                                //Toast.makeText(mSurfaceView.this,"异常数："+Integer.toString(zb.length),Toast.LENGTH_LONG).show();
                                v.printStackTrace();
                                continue;
                            }
                            x2=w/4.0f;
                            x3=x2+x+x1;
                            xu = ggtzy+x1;
                            if (m > 1&& x>0 && y > 0 && w>0  && human == false) {
                                if(xd ==10) {
                                    canvas.drawText(hqcl(xd), x -30 +x1, y, paint18);//空投
                                    canvas.drawText( m +"M",  x +x1, y+30, paint3);
                                }
                                if(xd ==60) {
                                    canvas.drawText(hqcl(xd), x -30 +x1, y, paint22);//空投
                                    canvas.drawText( m +"M",  x +x1, y+30, paint3);
                                }
                                if(xd < 99 && xd >= 70 && 显示载具==true)
                                {
                                    canvas.drawText(hqcl(xd), x -30  +x1, y, paint19);//载具
                                    canvas.drawText( m +"M",  x +x1, y+30, paint3);
                                }
                            }
                            else {
                                雷达 = afff.getld();
                                if (雷达 && human == true) {
                                    canvas.drawLine(100 + 450 / 2 - 200, 100 + 450 / 2, 100 + 450 / 2 + 200, 100 + 450 / 2, paint5);
                                    canvas.drawLine(100 + 450 / 2, 100 + 450 / 2 - 200, 100 + 450 / 2, 100 + 450 / 2 + 200, paint5);
                                    canvas.drawCircle(100 + 450 / 2, 100 + 450 / 2, 180, paint5);
                                    canvas.drawCircle(100 + 450 / 2, 100 + 450 / 2, 120, paint5);
                                    canvas.drawCircle(100 + 450 / 2, 100 + 450 / 2, 80, paint5);
                                    canvas.drawRect(100 + 850 / 2, 100 + 850 / 2, 124, 124, paint5);
                                    {
                                        if (x < 3100 && y < 3100 && w > -90 && x > -890 && y > -3100 && w < 310 && hp != 0) {
                                            canvas.drawCircle(100 + 230 / 2 + x / 10, 100 + 230 / 2 + w, 5, blue_dot);
                                            if (xd == 0) {
                                                canvas.drawLine(100 + 180 / 2 + x / 10, 100 + 180 / 2 + w, 100 + 280 / 2 + x / 10, 100 + 280 / 2 + w, paint15);
                                                canvas.drawLine(100 + 280 / 2 + x / 10, 100 + 180 / 2 + w, 100 + 180 / 2 + x / 10, 100 + 280 / 2 + w, paint15);
                                                canvas.drawText("[AI]" + m + "M", 80 + 180 / 2 + x / 10, 100 + 245 / 2 + w, paint3);
                                            } else {
                                                canvas.drawLine(100 + 180 / 2 + x / 10, 100 + 180 / 2 + w, 100 + 280 / 2 + x / 10, 100 + 280 / 2 + w, paint14);
                                                canvas.drawLine(100 + 280 / 2 + x / 10, 100 + 180 / 2 + w, 100 + 180 / 2 + x / 10, 100 + 280 / 2 + w, paint14);
                                                canvas.drawText("[玩家]" + m + "M", 65 + 180 / 2 + x / 10, 100 + 245 / 2 + w, paint3);
                                            }
                                        }
                                    }
                                }
                                if (hp == 0 && 倒地不显) {
                                    surfaceHolder.unlockCanvasAndPost(canvas);
                                    continue;
                                }
                                if(自瞄)
                                {
                                    canvas.drawCircle(Width / 2, Height/2, 550, paint14);//头部
                                }
                                if (m > 1 && x > 0 && y > 0 && w > 0 && 人物透视) {
                                    //canvas.drawText("["+D+"队"+"]"+"[HP:"+HP+"]"+"[距离:"+M+"米]", ggtzy-150+x1, ggtgd-20, paint3);


                                    //canvas.drawRect(x-x2+x1,y,x3,y+w,paint15);//方框
                                    float bkxz = (ggzjwsx - ggtgd)/5;
                                    简化 = afff.getjh();//读取时否简化
                                    if (简化 == false) {
                                        canvas.drawLine(Width / 2, 130, ggtzy + x1, ggtgd, paint1);//射线
                                        canvas.drawRect(ggpgzy - x2 + x1, ggtgd - bkxz, ggpgzy + x2 + x1, ggzjwsx+bkxz, paint15);//方框
                                        //canvas.drawRect(xu - 120, ggtgd - bkxz -60, xu + 120, ggtgd - bkxz -6, paint20); //血条框
                                        canvas.drawRect(ggpgzy - 81, ggtgd - bkxz -15, ggpgzy + 80, ggtgd - bkxz -6, paint5); //血条框

                                        canvas.drawRect(ggpgzy - 80, ggtgd - bkxz -14, (ggpgzy - 80) + (hp * 1.6f), ggtgd - bkxz -7, paint6); //血条框
                                        if (xd == 0) {
                                            canvas.drawText("[" + db + "队] 电脑 [" + m + "M]", ggpgzy - 93, ggtgd - bkxz - 23, paint25);
                                            //canvas.drawText(Integer.toString(hp) + "HP", xu - 20, ggtgd - bkxz-10, paint3);
                                        } else {
                                            canvas.drawText("[" + db + "队] 玩家 [" + m + "M]", ggpgzy - 93, ggtgd - bkxz - 23, paint25);
                                            //canvas.drawText(Integer.toString(hp) + "HP", xu - 20, ggtgd - bkxz - 10, paint16);
                                        }

                                    } else {
                                        canvas.drawText("[" + db + "队] " + Integer.toString(hp) + "HP [" + m + "M]", xu - 90, ggtgd - bkxz - 10, paint3);
                                        if (xd == 0) {
                                            canvas.drawRect(ggpgzy - x2 + x1, ggtgd - bkxz, ggpgzy + x2 + x1, ggzjwsx+bkxz, paint15);//方框
                                        }else
                                        {
                                            canvas.drawRect(ggpgzy - x2 + x1, ggtgd - bkxz, ggpgzy + x2 + x1, ggzjwsx+bkxz, paint14);//方框
                                        }
                                    }

                                    //骨骼
                                    if (hp < 120 && m > 3 && m < 300 && ggtgd < Height && ggtzy < Width && db > 0 && ggtgd > 0 && ggtzy > 0 && !简化) {
                                        if (xd == 0) {
                                            if(m<60) {
                                                canvas.drawCircle(ggtzy + x1, ggtgd, 5, paint15);//头部
                                            }
                                            canvas.drawLine(ggtzy + x1, ggtgd, ggsbzy + x1, ggsbsx, paint15);//骨骼头
                                            canvas.drawLine(ggsbzy + x1, ggsbsx, ggpgzy + x1, ggpgsx, paint15);//骨骼身体
                                            canvas.drawLine(ggsbzy + x1, ggsbsx, ggzjzy + x1, ggzjsx, paint15);//骨骼左肩
                                            canvas.drawLine(ggzjzy + x1, ggzjsx, ggzszzy + x1, ggzszsx, paint15);//骨骼左手肘
                                            canvas.drawLine(ggzszzy + x1, ggzszsx, ggzswzy + x1, ggzswsx, paint15);//骨骼左手腕
                                            canvas.drawLine(ggsbzy + x1, ggsbsx, ggyjzy + x1, ggyjsx, paint15);//骨骼右肩
                                            canvas.drawLine(ggyjzy + x1, ggyjsx, ggysjzy + x1, ggysjsx, paint15);//骨骼右手肘
                                            canvas.drawLine(ggysjzy + x1, ggysjsx, ggyswzy + x1, ggyswsx, paint15);//骨骼右手腕
                                            canvas.drawLine(ggpgzy + x1, ggpgsx, ggzdtzy + x1, ggzdtsx, paint15);//骨骼左大腿
                                            canvas.drawLine(ggzdtzy + x1, ggzdtsx, ggzxgzy + x1, ggzxgsx, paint15);//骨骼左膝盖
                                            canvas.drawLine(ggzxgzy + x1, ggzxgsx, ggzjwzy + x1, ggzjwsx, paint15);//骨骼左脚腕
                                            canvas.drawLine(ggpgzy + x1, ggpgsx, ggydtzy + x1, ggydtsx, paint15);//骨骼右大腿
                                            canvas.drawLine(ggydtzy + x1, ggydtsx, ggyxgzy + x1, ggyxgsx, paint15);//骨骼右膝盖
                                            canvas.drawLine(ggyxgzy + x1, ggyxgsx, ggyjwzy + x1, ggyjwsx, paint15);//骨骼右脚腕
                                        } else if (xd == 1) {
                                            if(m<60) {
                                                canvas.drawCircle(ggtzy + x1, ggtgd, 5, paint14);//头部
                                            }
                                            canvas.drawLine(ggtzy + x1, ggtgd, ggsbzy + x1, ggsbsx, paint14);//骨骼头
                                            canvas.drawLine(ggsbzy + x1, ggsbsx, ggpgzy + x1, ggpgsx, paint14);//骨骼身体
                                            canvas.drawLine(ggsbzy + x1, ggsbsx, ggzjzy + x1, ggzjsx, paint14);//骨骼左肩
                                            canvas.drawLine(ggzjzy + x1, ggzjsx, ggzszzy + x1, ggzszsx, paint14);//骨骼左手肘
                                            canvas.drawLine(ggzszzy + x1, ggzszsx, ggzswzy + x1, ggzswsx, paint14);//骨骼左手腕
                                            canvas.drawLine(ggsbzy + x1, ggsbsx, ggyjzy + x1, ggyjsx, paint14);//骨骼右肩
                                            canvas.drawLine(ggyjzy + x1, ggyjsx, ggysjzy + x1, ggysjsx, paint14);//骨骼右手肘
                                            canvas.drawLine(ggysjzy + x1, ggysjsx, ggyswzy + x1, ggyswsx, paint14);//骨骼右手腕
                                            canvas.drawLine(ggpgzy + x1, ggpgsx, ggzdtzy + x1, ggzdtsx, paint14);//骨骼左大腿
                                            canvas.drawLine(ggzdtzy + x1, ggzdtsx, ggzxgzy + x1, ggzxgsx, paint14);//骨骼左膝盖
                                            canvas.drawLine(ggzxgzy + x1, ggzxgsx, ggzjwzy + x1, ggzjwsx, paint14);//骨骼左脚腕
                                            canvas.drawLine(ggpgzy + x1, ggpgsx, ggydtzy + x1, ggydtsx, paint14);//骨骼右大腿
                                            canvas.drawLine(ggydtzy + x1, ggydtsx, ggyxgzy + x1, ggyxgsx, paint14);//骨骼右膝盖
                                            canvas.drawLine(ggyxgzy + x1, ggyxgsx, ggyjwzy + x1, ggyjwsx, paint14);//骨骼右脚腕
                                        }
                                    }

                                }

                            }
                            //if结束


                            num--;
                        }
                    }
                    canvas.drawText("🎅🏻真人:" + Integer.toString(n_player),Width / 2 -170,120, paint17);
                    canvas.drawText("🤖电脑:" + Integer.toString(n_ai),Width / 2 +30,120, paint12);
                    surfaceHolder.unlockCanvasAndPost(canvas);

                }
            }
        });
        syncTask.start();
    }
}
