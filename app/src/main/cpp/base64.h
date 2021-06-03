
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//填入base64自定义编码集，可用群内app生成
//const char base[] = {"NrSgwsGeiX34ZzEfcdVPu8hvJjRA+TqDL2ylnmMoxOKa9pYI/5k6tF10HUbC7BQW"};
static char base[128] = {"编码集"};

static union {
	struct
	{
		unsigned long a : 6;
		unsigned long b : 6;
		unsigned long c : 6;
		unsigned long d : 6;
	} Sdata;
	unsigned char c[3];
} Udata;

char *Encbase64(char *orgdata);//base64加密

char *Decbase64(char *orgdata);//base64解密

char *toHEX(char *string);//转16进制

char* yjjm(char* data);//一键加密

void setbase(char *b);//设置base编码集


void setbase(char *b){
	strcpy(base,b);
}

char* yjjm(char* data){
	char* mw;
	data = Encbase64(data);
	mw = toHEX(data);
	free(data);
	return mw;
}

char *toHEX(char *string)
{
	char chs;
	char *ret;
	char *str;
	if (!string || (ret = str = (char *)malloc(strlen(string) * 2 + 1)) == NULL)
		return NULL;
	while (*string)
	{
		chs = (*string & 0XF0) >> 4;
		if (chs > 9)
			*str = chs - 10 + 'A'; //chs - 10 + 'A'
		else
			*str = chs + '0';
		str++;
		chs = *string & 0X0F;
		if (chs > 9)
			*str = chs - 10 + 'A'; //chs - 10 + 'A'
		else
			*str = chs + '0';
		str++;
		string++;
	}
	*str = '\0';
	return ret;
}

char *Encbase64(char *orgdata)
{
	char *p = NULL, *ret = NULL;
	int tlen = 0;
	if (orgdata == NULL)
		return NULL;
	unsigned long orglen = strlen(orgdata);
	tlen = orglen / 3;
	if (tlen % 3 != 0)
		tlen++;
	tlen = tlen * 4;
	if ((ret = (char *)malloc(tlen + 1)) == NULL)
		return NULL;
	memset(ret, 0, tlen + 1);
	p = orgdata;
	tlen = orglen;

	int i = 0, j = 0;
	while (tlen > 0)
	{
		Udata.c[0] = Udata.c[1] = Udata.c[2] = 0;
		for (i = 0; i < 3; i++)
		{
			if (tlen < 1)
				break;
			Udata.c[i] = (char)*p;
			tlen--;
			p++;
		}
		if (i == 0)
			break;
		switch (i)
		{
		case 1:
			/*ret[j++]=base[Udata.Sdata.d];
				ret[j++]=base[Udata.Sdata.c];
				ret[j++]=base[64];
				ret[j++]=base[64];*/
			ret[j++] = base[Udata.c[0] >> 2];
			ret[j++] = base[((Udata.c[0] & 0x03) << 4) | ((Udata.c[1] & 0xf0) >> 4)];
			ret[j++] = base[64];
			ret[j++] = base[64];
			break;
		case 2:
			/*ret[j++]=base[Udata.Sdata.d];
				ret[j++]=base[Udata.Sdata.c];
				ret[j++]=base[Udata.Sdata.b];
				ret[j++]=base[64];*/
			ret[j++] = base[Udata.c[0] >> 2];
			ret[j++] = base[((Udata.c[0] & 0x03) << 4) | ((Udata.c[1] & 0xf0) >> 4)];
			ret[j++] = base[((Udata.c[1] & 0x0f) << 2) | ((Udata.c[2] & 0xc0) >> 6)];
			ret[j++] = base[64];
			break;
		case 3:
			/*ret[j++]=base[Udata.Sdata.d];
				ret[j++]=base[Udata.Sdata.c];
				ret[j++]=base[Udata.Sdata.b];
				ret[j++]=base[Udata.Sdata.a];*/
			ret[j++] = base[Udata.c[0] >> 2];
			ret[j++] = base[((Udata.c[0] & 0x03) << 4) | ((Udata.c[1] & 0xf0) >> 4)];
			ret[j++] = base[((Udata.c[1] & 0x0f) << 2) | ((Udata.c[2] & 0xc0) >> 6)];
			ret[j++] = base[Udata.c[2] & 0x3f];
			break;
		default:
			break;
		}
	}
	ret[j] = '\0';
	return ret;
}

char *Decbase64(char *orgdata)
{
	char *p, *ret;
	int len;
	unsigned long orglen;
	char ch[4] = {0};
	char *pos[4];
	int offset[4];
	if (orgdata == NULL)
		return NULL;
	orglen = strlen(orgdata);
	len = orglen * 3 / 4;
	if ((ret = (char *)malloc(len + 1)) == NULL)
	{
		return NULL;
	}
	p = orgdata;
	len = orglen;
	int j = 0;

	while (len > 0)
	{
		int i = 0;
		while (i < 4)
		{
			if (len > 0)
			{
				ch[i] = *p;
				p++;
				len--;
				if ((pos[i] = (char *)strchr(base, ch[i])) == NULL)
				{
					if(ch[i] == '='){
						ret[j] = '\0';
						return ret;
					}
					return NULL;
				}
				offset[i] = pos[i] - base;
			}
			i++;
		}
		if (ch[0] == '=' || ch[1] == '=' || (ch[2] == '=' && ch[3] != '='))
		{
			return NULL;
		}
		ret[j++] = (unsigned char)(offset[0] << 2 | offset[1] >> 4);
		ret[j++] = offset[2] == 64 ? '\0' : (unsigned char)(offset[1] << 4 | offset[2] >> 2);
		ret[j++] = offset[3] == 64 ? '\0' : (unsigned char)((offset[2] << 6 & 0xc0) | offset[3]);
	}
	ret[j] = '\0';
	return ret;
}