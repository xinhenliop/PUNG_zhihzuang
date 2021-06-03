package com.tencent.zz;

final public class EasyConfig
{
	final public static String HOST="http://api.yiyanzheng.cn/";//这是接口地址不用改
	final public static String TOKEN="39246";//改成你的自定义密钥
	private EasyConfig(){}
	
	
}





/*

以下是需要在后台配置的东西：

1.在后台的用户管理-返回值配置:

返回值计算方式设置为-加法

返回值单向加密设为-md5

返回值动态方式设置为-年月日时分

返回值全局加密设置为-自定义BASE64

动态秘钥加密设置为-不启用



2.在后台的基本管理-加密校验配置:

全局数据提交加密-开启

全局签名加密验证-关闭

传输加密转换方式-转16进制

全局参数变量加密-不开启
*/
