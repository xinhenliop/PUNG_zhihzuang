#include <stdio.h>
#include <time.h>

#include "http.h"
#include "base64.h"
#include "md5.h"


char *itoa(int num, char *str, int radix);

const static char *host = "api.yiyanzheng.cn";  //接口域名
const static char *appid = "14104";  //后台ID
const static char *key = "39246";  //后台密钥
const static int num = 46;  //返回值计算数
const static char *kami="14G592UHPKTC3468F8JO";  //单码卡密
const static char *jiqima="79833b81c384d691";  //设备码
const static char *bianmaji="IjQmL2OpZsMd70BwcvXH8SGa6eK+UTnR9CFyr5fu/gWlo4P1NhEiAkD3zqVJxbYt";  //编码集

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

char* Login(char* ka,char* ji,bool KGG)
{
	//主函数，启动就在这
	setbase((char*)bianmaji);
	char *run;
	char *jm;
	kami = ka;
	jiqima = ji;
	char *km = yjjm((char*)kami);
	char *imei = yjjm((char*)jiqima);
	char url[128];
	sprintf(url, "user/kmdenglu.php?appid=%s&km=%s&imei=%s", appid, km, imei);
	run = httpget(host, url);
	jm = Decbase64(run);//解密返回值
	free(run);
	//printf("%s\n", jm);//打印返回值解密后的
	if (strncmp(jm, "登录验证:成功;", 20) == 0)
	{
		char *md5 = strstrstr(jm, (char*)"识别码:", (char*)";");
		char *kmid = strstrstr(jm, (char*)"卡密ID:", (char*)";");
		char *dqsj=strstrstr(jm, (char*)"到期时间:", (char*)";"); //取得卡密到期时间
		char *kmlx=strstrstr(jm, (char*)"卡密类型:", (char*)";"); //取得卡密类型，比如天卡，月卡
		char *kmsc=strstrstr(jm, (char*)"卡密价值:", (char*)";");  //确定卡密价值，生成卡密时候的价值
		char *yz;
		time_t t = time(NULL);
		struct tm *mtime = localtime(&t);
		char sj[13];
		char *sjzz = sj;
		itoa(mtime->tm_year + 1900, sjzz, 10);
		sjzz += 4;
		if (mtime->tm_mon + 1 < 10)
		{ //月
			*sjzz = '0';
			sjzz++;
			itoa(mtime->tm_mon + 1, sjzz, 10);
			sjzz++;
		}
		else
		{
			itoa(mtime->tm_mon + 1, sjzz, 10);
			sjzz += 2;
		}
		if (mtime->tm_mday < 10)
		{ //日
			*sjzz = '0';
			sjzz++;
			itoa(mtime->tm_mday, sjzz, 10);
			sjzz++;
		}
		else
		{
			itoa(mtime->tm_mday, sjzz, 10);
			sjzz += 2;
		}
		if (mtime->tm_hour < 10)
		{ //小时
			*sjzz = '0';
			sjzz++;
			itoa(mtime->tm_hour, sjzz, 10);
			sjzz++;
		}
		else
		{
			itoa(mtime->tm_hour, sjzz, 10);
			sjzz += 2;
		}
		if (mtime->tm_min < 10)
		{ //分钟
			*sjzz = '0';
			sjzz++;
			itoa(mtime->tm_min, sjzz, 10);
			sjzz++;
		}
		else
		{
			itoa(mtime->tm_min, sjzz, 10);
			sjzz += 2;
		}
		sprintf(yz, "%d%s%s%s%s", atoi(kmid) + num, key, kami, kmid, sj);

		MD5_CTX md5c;
		MD5Init(&md5c);
		int i;
		unsigned char decrypt[16];
		MD5Update(&md5c, (unsigned char*)yz, strlen(yz));
		MD5Final(&md5c, decrypt);
		char yzmd5[32] = {0};
		for (i = 0; i < 16; i++)
		{
			sprintf(&yzmd5[i * 2], "%02x", decrypt[i]); //02x前需要加上 %
		}
		if (strncmp(md5, yzmd5, 32) == 0)
		{
			KGG = true;
			return dqsj;
		}
		else
		{
			 KGG = false;
			return (char *)"校验失败，数据异常\n";
		}
	}
	else
	{
		//登录失败，直接打印解密后的返回值看失败原因

	}
	KGG = false;
	free(jm);
	return jm;
}

char *itoa(int num, char *str, int radix)
{
	char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //索引表
	unsigned unum;										   //存放要转换的整数的绝对值,转换的整数可能是负数
	int i = 0, j, k;									   //i用来指示设置字符串相应位，转换之后i其实就是字符串的长度；转换后顺序是逆序的，有正负的情况，k用来指示调整顺序的开始位置;j用来指示调整顺序时的交换。

	//获取要转换的整数的绝对值
	if (radix == 10 && num < 0) //要转换成十进制数并且是负数
	{
		unum = (unsigned)-num; //将num的绝对值赋给unum
		str[i++] = '-';		   //在字符串最前面设置为'-'号，并且索引加1
	}
	else
		unum = (unsigned)num; //若是num为正，直接赋值给unum

	//转换部分，注意转换后是逆序的
	do
	{
		str[i++] = index[unum % (unsigned)radix]; //取unum的最后一位，并设置为str对应位，指示索引加1
		unum /= radix;							  //unum去掉最后一位

	} while (unum); //直至unum为0退出循环

	str[i] = '\0'; //在字符串最后添加'\0'字符，c语言字符串以'\0'结束。

	//将顺序调整过来
	if (str[0] == '-')
		k = 1; //如果是负数，符号不用调整，从符号后面开始调整
	else
		k = 0; //不是负数，全部都要调整

	char temp;						   //临时变量，交换两个值时用到
	for (j = k; j <= (i - 1) / 2; j++) //头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1
	{
		temp = str[j];				 //头部赋值给临时变量
		str[j] = str[i - 1 + k - j]; //尾部赋值给头部
		str[i - 1 + k - j] = temp;	 //将临时变量的值(其实就是之前的头部值)赋给尾部
	}

	return str; //返回转换后的字符串
}