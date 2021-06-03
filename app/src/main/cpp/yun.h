#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>
#include <thread>
#include "http.h"
#include "base64.h"
#include "md5.h"
#include "MemoryTools6.h"
//#include "Rc4.h"
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <fcntl.h>
#include <cmath>
#include <dirent.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "Memory.h"
#include "utf.h"
#include "Structs.h"

#define DWORD 4

#define PI 3.141592653589793238        //自瞄增加

using namespace std;

char *itoa(int num, char *str, int radix);

void *y11(void *);

void *y33(void *);

void y55();

void y66();

void y10();

void ych();

void ych2();

void *Thread_Maps(void *);

void *Thread_State(void *);

void filemd5(char *path, char *md5);

int filecheck(char *path);

int readnumber(char *path);

long int getptr(long int addr);

float getfloat(long int addr);

const static char *host = "api.yiyanzheng.cn";  //接口域名
static char *kami;  //单码卡密
static char *jiqima;  //设备码
static char *appid = (char *) "14223";  //后台ID
static char *key = (char *) "dashen";  //后台密钥
static int num = 1396;  //返回值计算数
static char *bianmaji = (char *) "Bd0JPjI9OEtaMxqDWAuXvQo+wsZnFmKbNrR268cYTlfiHpC45Sy7Le1/G3gUhzVk";  //编码集
int xht;//循环体
int ff;//是否开启了防封
int fck;//检测是否符合MD5值
int cjxc;//创建线程
char uid[10];//uid
long int dz;//UE4基址头
char pathname[30] = "com.tencent.tmgp.pubgmhd";//uid
int y4;
char *appidck;
int qdy33 = 0;//启动登陆的循环。
int kmdqyz = 0;//卡密到期验证
int dlcg = 0;//登陆成功，1为启动循环，2为登陆成功
int qdhz = 0;//启动绘制

/* 游戏变量 */
int ResNum = 0, SelfTeamID = 0;
float px = 0, py = 0;
PMAPS pMap_A = nullptr, pMap_P = nullptr, pMap_ALL = nullptr;
long int MatrixAddress = (long int) malloc(8 * 10);
long int uWorldAddress = (long int) malloc(8 * 10);
long int ActorAddress = (long int) malloc(8 * 10);
long int UleveAddress = (long int) malloc(8 * 10);
long int GnameAddress = (long int) malloc(8 * 10);
long int libUE4 = (long int) malloc(8 * 10);
float MatrixValue[16] = {0};
int ResInfo[2] = {0};
bool isForegRound = true;
long int NetDriver;
long int ServerConnection;
long int PlayerController;
long int MyAddress;
long int checknum;
JNIEnv *env;
jclass cls;

char aaa[10240] = "";
int stri;//aaa的下标位置
int strin;//进入输出方法时的下标值（人类+200，物品+50）
int youzimiao;//后门，自动自瞄
int gwms = 0;//高危模式
//=======时间戳变量=======
int kmTime;
//==========END==========

//以下自瞄增加
int myzt, kh, zdsd;
double vax = 180 / PI, vay = 180 / PI;
double pfg;
double XGX, XGY;
float Myz, Myx, Myy, cx, cy, cz;
double JD, XGX1, XGY1, JD1, zmyqjl, zmyqmp;//后面俩是自瞄压枪距离，自瞄压枪HP
long int zmAddr;
long int zmAddrx, zmAddry;
long int Matrix, Matrix1, Matrix2;
bool kqzm, kjzm, ddbm, ddbm2;//开启自瞄，开镜自瞄，开关
int i_num = 0;//文件检测计数器
int playernum;//计数器，记录共有几个敌人
long int wqzz, zmdx;
jobjectArray shuI,shuF;
bool clkq;//此轮循环开启自瞄
/* ------ 内存读写 ------ */
void CheckTime();

void y11();

void Fwrite_A(char *file, char *hex, int size);

//获取当前时间戳函数
int getTime() {
    time_t t = time(NULL);
    int ad = time(&t);
    return ad;
}

//线程运行函数

void CheckTime() {
    int a;
    int ex = 1;
    while (ex) {
        a = getTime();
        if (a > kmTime) {
            ex = 0;
        }
        usleep(1000000);
    }
    exit(0);
    return;
}

struct d3dvector {
    float x;
    float y;
    float z;
};


d3dvector ReadVector(long int addr, int Type) {
    d3dvector coordinate;

    if (Type == 1) {
        coordinate.x = getfloat(addr);
        coordinate.y = getfloat(addr + 4);
        coordinate.z = getfloat(addr + 8);
        return coordinate;
    }
    if (Type == 0) {
        coordinate.x = getfloat(addr + 352);
        coordinate.y = getfloat(addr + 356);
        coordinate.z = getfloat(addr + 360);
        return coordinate;
    }


    return coordinate;

}

float GetDistance(d3dvector My, d3dvector Target, int Divide) {
    d3dvector jlc;
    jlc.x = My.x - Target.x;
    jlc.y = My.y - Target.y;
    jlc.z = My.z - Target.z;
    return sqrt(jlc.x * jlc.x + jlc.y * jlc.y + jlc.z * jlc.z) / Divide;
}


/* 读内存 */
bool vm_readv(long int address, void *buffer, size_t size) {
    return pvm(pid, reinterpret_cast<void *>(address), buffer, size, false);
}

/* 写内存 */
bool vm_writev(long int address, void *buffer, size_t size) {
    return pvm(pid, reinterpret_cast<void *>(address), buffer, size, true);
}

/* 检查文件 */
int filecheck(char *path) {
    int re = 0;
    FILE *fp;
    fp = fopen(path, "r");
    if (fp == NULL) {
        return 0; //不存在返回0
    } else {
        return 1; //然后返回1
    }
}

/* 文件读整数 */

/*
int readnumber(char *path)
{
	int re = 0;
	FILE *fp;
	fp = fopen(path, "r");
	if (fp == NULL)
	{
		return 0; //不存在返回0
	}
	else
	{
		try {
			char aaa[12];
			fgets(aaa, 1024, fp);
			re = atoi(aaa);
			fclose(fp); //存在的话，要先把之前打开的文件关掉
		}
		catch (char *error)
		{
			re = 0;
		}
		return re; //然后返回1
	}
}
*/
/* 读取A 内存 MAPS文件 */
PMAPS readmaps_A() {
    PMAPS pHead = nullptr;
    PMAPS pNew = nullptr;
    PMAPS pEnd = nullptr;
    pEnd = pNew = (PMAPS) malloc(LEN);
    int i = 0, flag = 1;
    char lj[50], buff[256];
    snprintf(lj, sizeof(lj), "/proc/%d/maps", pid);
    FILE *fp = fopen(lj, "r");
    if (fp == nullptr) {
        printf("open maps fail!\n");
        fclose(fp); //关闭文件指针
        return nullptr;
    }
    while (!feof(fp)) {
        fgets(buff, sizeof(buff), fp);
        if (strstr(buff, "rw") != nullptr && !feof(fp) && (strlen(buff) < 42)) {
            sscanf(buff, "%lx-%lx", &pNew->addr, &pNew->taddr); // 这里使用lx是为了能成功读取特别长的地址
            flag = 1;
        } else {
            flag = 0;
        }
        if (flag == 1) {
            i++;
            if (i == 1) {
                pNew->next = nullptr;
                pEnd = pNew;
                pHead = pNew;
            } else {
                pNew->next = nullptr;
                pEnd->next = pNew;
                pEnd = pNew;
            }
            pNew = (PMAPS) malloc(LEN); //分配内存
        }
    }
    free(pNew); //将多余的空间释放
    fclose(fp); //关闭文件指针
    return pHead;
}


/* 获取进程PID */
int find_pid(char *szPro) {
    struct dirent *ptr = nullptr;
    char cmdline[256], szName[256];
    DIR *dir = opendir("/proc");
    if (nullptr != dir) {
        while ((ptr = readdir(dir)) != nullptr) {
            if ((strcmp(ptr->d_name, ".") == 0) || (strcmp(ptr->d_name, "..") == 0)) continue;
            if (ptr->d_type != DT_DIR) continue;
            sprintf(cmdline, "/proc/%s/cmdline", ptr->d_name);
            FILE *fp = fopen(cmdline, "r");

            if (nullptr != fp) {
                fgets(szName, sizeof(szName), fp);
                if (strcmp(szName, szPro) == 0) {
                    break;
                }
                fclose(fp);
            }
        }
    }
    if (readdir(dir) == NULL) {
        return 0;
    }
    closedir(dir);
    return atoi(ptr->d_name);
}

/* 读取模块入口地址 */
long int get_module_base(int pid, const char *module_name) {
    FILE *fp;
    long addr = 0;
    char *pch;
    char filename[32];
    char line[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    fp = fopen(filename, "r");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            //Fwrite((char*)"/storage/emulated/0/Android/vbb/dd.log",(char*)line);
            if (strstr(line, module_name)) {
                pch = strtok(line, "-");
                addr = strtoul(pch, NULL, 16);
                if (addr == 0x8000)
                    addr = 0;
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}

/* 读取long类型 */
long int getdword(long int addr) {
    if (addr < 0xFFFFFF) {
        return 0;
    }
    long int var[4] = {0};
    memset(var, 0, 4);
    vm_readv(addr, var, 4);
    return var[0];
}

/* 读整数型内存 */
long int getint(long int addr) {
    long int var[1] = {0};
    vm_readv(addr, var, 4);
    return var[0];
}

/* 读浮点型内存 */
float getfloat(long int addr) {
    float var[1] = {0};
    vm_readv(addr, var, 4);
    return var[0];
}

/* 读文本型内存 */
char *getText(long int address, unsigned int size) {
    char *data = new char[size];
    vm_readv(address, data, size);
    return data;
}

/* 写浮点型内存 */
void writefloat(long int addr, float data) {
    vm_writev(addr, &data, 4);
}

/* ------ 相关数据计算 ------ */
/* 计算3D坐标距离 */
float getDistance(float zx, float zy, float zz, float dx, float dy, float dz) {
    float x, y, z;
    x = zx - dx;
    y = zy - dy;
    z = zz - dz;
    return (float) (sqrt(x * x + y * y + z * z));
}

Vector2A WorldToScreen(Vector3A obj, float matrix[16]) {
    float ViewW = matrix[3] * obj.X + matrix[7] * obj.Y + matrix[11] * obj.Z + matrix[15];
    float x = px +
              (matrix[0] * obj.X + matrix[4] * obj.Y + matrix[8] * obj.Z + matrix[12]) / ViewW * px;
    float y = py -
              (matrix[1] * obj.X + matrix[5] * obj.Y + matrix[9] * obj.Z + matrix[13]) / ViewW * py;
    return Vector2A(x, y);
}

Vector2A WorldToScreen2(Vector3A obj, float matrix[16]) {
    float ViewW = matrix[3] * obj.X + matrix[7] * obj.Y + matrix[11] * obj.Z + matrix[15];
    if (ViewW < 0.01) {
        return Vector2A(3100, 3100);
    }
    float x = px +
              (matrix[0] * obj.X + matrix[4] * obj.Y + matrix[8] * obj.Z + matrix[12]) / ViewW * px;
    float y = py -
              (matrix[1] * obj.X + matrix[5] * obj.Y + matrix[9] * obj.Z + matrix[13]) / ViewW * py;
    return Vector2A(x, y);
}

Vector3A MarixToVector(FMatrix matrix) {
    return Vector3A(matrix.M[3][0], matrix.M[3][1], matrix.M[3][2]);
}

FMatrix MatrixMulti(FMatrix m1, FMatrix m2) {
    FMatrix matrix = FMatrix();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = 0; k < 4; k++) {
                matrix.M[i][j] += m1.M[i][k] * m2.M[k][j];
            }
        }
    }
    return matrix;
}

long getaddr(const char *so, char *ncd) {
    FILE *fp;
    long addr = 0;
    char *pch;
    char filename[32];
    char line[1024];
    snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);
    fp = fopen(filename, "r");
    if (fp != NULL) {
        while (fgets(line, sizeof(line), fp)) {
            if (strstr(line, so) && strstr(line, ncd)) {
                pch = strtok(line, "-");
                addr = strtoul(pch, NULL, 16);
                if (addr == 0x8000)
                    addr = 0;
                break;
            }
        }
        fclose(fp);
    }
    return addr;
}

int Memorywrite(char *value, int type, long int offset) {
    char mem[33];
    snprintf(mem, sizeof(mem), "/proc/%d/mem", pid);
    int fd = open(mem, O_WRONLY);
    if (fd < 0) {
        return -1;
    }
    if (type == 4) {
        int buf = atoi(value);
        pwrite(fd, &buf, type, offset);
    }
    if (type == 8) {
        float buf = atof(value);
        pwrite(fd, &buf, type, offset);
    }
    close(fd);
    return 0;
}

FMatrix TransformToMatrix(FTransform transform) {
    FMatrix matrix;
    matrix.M[3][0] = transform.Translation.X;
    matrix.M[3][1] = transform.Translation.Y;
    matrix.M[3][2] = transform.Translation.Z;
    float x2 = transform.Rotation.X + transform.Rotation.X;
    float y2 = transform.Rotation.Y + transform.Rotation.Y;
    float z2 = transform.Rotation.Z + transform.Rotation.Z;
    float xx2 = transform.Rotation.X * x2;
    float yy2 = transform.Rotation.Y * y2;
    float zz2 = transform.Rotation.Z * z2;
    matrix.M[0][0] = (1 - (yy2 + zz2)) * transform.Scale3D.X;
    matrix.M[1][1] = (1 - (xx2 + zz2)) * transform.Scale3D.Y;
    matrix.M[2][2] = (1 - (xx2 + yy2)) * transform.Scale3D.Z;
    float yz2 = transform.Rotation.Y * z2;
    float wx2 = transform.Rotation.W * x2;
    matrix.M[2][1] = (yz2 - wx2) * transform.Scale3D.Z;
    matrix.M[1][2] = (yz2 + wx2) * transform.Scale3D.Y;
    float xy2 = transform.Rotation.X * y2;
    float wz2 = transform.Rotation.W * z2;
    matrix.M[1][0] = (xy2 - wz2) * transform.Scale3D.Y;
    matrix.M[0][1] = (xy2 + wz2) * transform.Scale3D.X;
    float xz2 = transform.Rotation.X * z2;
    float wy2 = transform.Rotation.W * y2;
    matrix.M[2][0] = (xz2 + wy2) * transform.Scale3D.Z;
    matrix.M[0][2] = (xz2 - wy2) * transform.Scale3D.X;
    matrix.M[0][3] = 0;
    matrix.M[1][3] = 0;
    matrix.M[2][3] = 0;
    matrix.M[3][3] = 1;
    return matrix;
}

FTransform getBone(long int addr) {
    FTransform transform;
    vm_readv(addr, &transform, 4 * 11);
    return transform;
}

/* ------ 线程处理 ------*/

void *Thread_State(void *) {
    while (qdhz) {
        try {
            char cmdline[256], szName[256];
            sprintf(cmdline, "/proc/%d/oom_adj", pid);
            FILE *fp = fopen(cmdline, "r");
            if (nullptr != fp) {
                fgets(szName, sizeof(szName), fp);
                if (atoi(szName) != 11) {
                    isForegRound = true;
                } else {
                    isForegRound = false;
                }
                fclose(fp);
            }
        }
        catch (char *error) {}
        sleep(5);
    }

    return 0;
}

// 分辨率获取
int remoteSwitch() {
    // 分辨率获取
    FILE *fp = fopen("/sdcard/x", "r");
    // 分辨率，格式:x,w
    FILE *fp1 = fopen("/sdcard/y", "r");
    // 状态栏
    if (fp == NULL || fp1 == NULL) {
        px = 2340.0 / 2;
        py = 1080.0 / 2;
    } else {
        fscanf(fp, "%f", &px);
        fscanf(fp1, "%f", &py);
        if (py > px) {
            float t = px;
            px = py;
            py = t;
        }
        py = py / 2.0;
        px = px / 2.0;
        fclose(fp);
        fclose(fp1);
    }
    return 0;
}


void *Thread_Maps(void *) {
    while (qdhz) {
        try {
            if (!isForegRound) { continue; }
            pMap_A = readmaps_A();
        }
        catch (char *error) {}
        sleep(3);

    }
    return 0;
}

int isvh(char *name)            // 车
{
    if (strstr(name, "VH_Motorcycle") != 0) {
        return 70;                // 摩托车
    }
    if (strstr(name, "VH_Scooter") != 0) {
        return 71;                // 小绵羊车
    }
    if (strstr(name, "VH_MotorcycleCart") != 0) {
        return 72;                // 三轮摩托车
    }
    if (strstr(name, "VH_Tuk") != 0) {
        return 72;                // 三轮摩托
    }
    if (strstr(name, "Buggy") != 0) {
        return 73;                // 蹦蹦
    }
    if (strstr(name, "Mirado") != 0) {
        return 74;                // 跑车
    }
    if (strstr(name, "Dacia") != 0) {
        return 75;                // 轿车
    }
    if (strstr(name, "PickUp") != 0) {
        return 76;                // 皮卡车
    }
    if (strstr(name, "Rony") != 0) {
        return 77;                // 吉普车
    }
    if (strstr(name, "UAZ") != 0) {
        return 78;                // 吉普车
    }
    if (strstr(name, "PG117") != 0) {
        return 79;                // 8倍
    }
    return 0;
}

int isj(char *name)                // 甲
{
    if (strstr(name, "Armor_Lv1") != 0) {
        return 4;                // 一级甲
    }
    if (strstr(name, "Helmet_Lv1") != 0) {
        return 5;                // 一级头
    }
    if (strstr(name, "Bag_Lv1") != 0) {
        return 1;                // 一级包
    }
    if (strstr(name, "Armor_Lv2") != 0) {
        return 6;                // 二级甲
    }
    if (strstr(name, "Helmet_Lv2") != 0) {
        return 7;                // 二级盔
    }
    if (strstr(name, "Bag_Lv2") != 0) {
        return 2;                // 二级包
    }
    if (strstr(name, "Armor_Lv3") != 0) {
        return 8;                // 三级甲
    }
    if (strstr(name, "Helmet_Lv3") != 0) {
        return 9;                // 三级头
    }
    if (strstr(name, "Bag_Lv3") != 0) {
        return 3;                // 三级包
    }
    if (strstr(name, "AirDropListWrapperActor_Pickup_C") != 0) {
        return 10;                // 空投
    }
    if (strstr(name, "BP_AirDropBox_C") != 0) {
        return 10;                // 空投
    }
    if (strstr(name, "PickUpListWrapperActor") != 0) {
        return 11;                // 盒子
    }
    if (strstr(name, "CharacterDeadInventoryBox_C") != 0) {
        return 11;                // 盒子
    }
    return 0;
}

int isy(char *name)                // 药
{
    if (strstr(name, "Pills") != 0) {
        return 21;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Injection") != 0) {
        return 22;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Drink") != 0) {
        return 23;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Firstaid") != 0) {
        return 24;                // 急救包
    }
    if (strstr(name, "MedKit") != 0) {
        return 25;                // 医疗箱
    }
    return 0;
}

int isq(char *name)                // 枪
{
    if (strstr(name, "Rifle_M416") != 0) {
        return 31;                // m416,m16,scar,qbz,m762,mk47
    }
    if (strstr(name, "Rifle_M16A4") != 0) {
        return 32;
    }
    if (strstr(name, "Rifle_SCAR") != 0) {
        return 33;
    }
    if (strstr(name, "Rifle_QBZ") != 0) {
        return 34;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Rifle_M762") != 0) {
        return 35;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Rifle_Mk47") != 0) {
        return 36;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Rifle_Groza") != 0) {
        return 37;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Sniper_AWM") != 0) {
        return 38;
    }
    if (strstr(name, "Sniper_Kar98k") != 0) {
        return 39;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Sniper_M24") != 0) {
        return 40;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Sniper_Mini14") != 0) {
        return 41;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Sniper_SKS") != 0) {
        return 42;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Sniper_QBU") != 0) {
        return 43;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "MachineGun_TommyGun") != 0) {
        return 44;                // 止痛药，肾上腺素，能量饮料
    }
    if (strstr(name, "Weapon_FlareGun_C") != 0) {
        return 45;                // 信号枪
    }
    if (strstr(name, "Ammo_556mm") != 0) {
        return 46;                // 556子弹
    }
    if (strstr(name, "Ammo_762mm") != 0) {
        return 47;                // 556子弹
    }
    if (strstr(name, "DJ_Large_EQ") != 0) {
        return 48;                // 步枪快速扩容
    }
    if (strstr(name, "DJ_Large_E") != 0) {
        return 49;                // 步枪扩容
    }
    if (strstr(name, "DJ_Sniper_EQ") != 0) {
        return 50;                // 狙击快速扩容
    }
    if (strstr(name, "DJ_Sniper_E") != 0) {
        return 51;                // 狙击扩容
    }
    if (strstr(name, "QK_Large_Suppressor") != 0) {
        return 52;                // 步枪消音
    }
    if (strstr(name, "QK_Sniper_Suppressor") != 0) {
        return 53;                // 狙击消音
    }
    if (strstr(name, "MZJ_4X") != 0) {
        return 54;                // 4倍
    }
    if (strstr(name, "MZJ_6X") != 0) {
        return 55;                // 6倍
    }
    if (strstr(name, "MZJ_8X") != 0) {
        return 56;                // 8倍
    }

    if (strstr(name, "BP_Grenade_Shoulei_C") != 0) {
        return 60;                // 小心手雷
    }
    if (strstr(name, "BP_Grenade_Smoke_C") != 0) {
        return 63;                // 小心手雷
    }
    if (strstr(name, "BP_Grenade_Burn_C") != 0) {
        return 64;                // 小心手雷
    }
    if (strstr(name, "Rifle_AKM") != 0) {
        return 61;                // 小心手雷
    }
    if (strstr(name, "Sniper_SLR") != 0) {
        return 62;                // 止痛药，肾上腺素，能量饮料
    }
    return 0;
}

int isr(char *name)                //人物
{
    if (strstr(name, "BP_PlayerPawn_C") != 0) {
        return 99;                // m416,m16,scar,qbz,m762,mk47
    }

    return 0;
}

int qlx(char *name) {
    int fhz;
    fhz = isj(name);
    if (fhz != 0) {
        return fhz;
    }
    fhz = isq(name);
    if (fhz != 0) {
        return fhz;
    }
    fhz = isy(name);
    if (fhz != 0) {
        return fhz;
    }
    fhz = isvh(name);
    if (fhz != 0) {
        return fhz;
    }
    fhz = isr(name);
    if (fhz != 0) {
        return fhz;
    }
    return 0;
}

bool isplayer(char *name)        // 人
{
    if (strstr(name, "PlayerPawn") != 0) {
        return true;

    }
    return false;
}


void inputstr(char *b) {
    int size = sizeof(b);
    if (size < 10) {
        size = 4;
    } else {
        size = 32;
    }
    for (int i = 0; i < size; i++) {
        aaa[stri] = b[i];
        stri++;
    }
}

void inputname(unsigned char b[]) {
    for (int i = 0; i < 32; i++) {
        aaa[stri] = b[i];
        stri++;
    }
}

void manoutstr(int xxx, int r_y, int w, int Health, int Distance, int isAI, int teamID,
               unsigned char PlayerName[], int HeadX, int HeadY, int ChestX, int ChestY,
               int PelvisX, int PelvisY, int g10x, int g10y, int g11x, int g11y, int g12x, int g12y,
               int g13x, int g13y, int g14x, int g14y, int g15x, int g15y, int g16x, int g16y,
               int g17x, int g17y, int g18x, int g18y, int g19x, int g19y, int g20x, int g20y,
               int g21x, int g21y) {

    strin = stri;//记录进入方法时的下标，人类+200，物品+32
    char b[4];
    int num = 6;
    memmove(b, &num, 4);//0
    inputstr(b);
    memset(b, 0, 4);
    memmove(b, &xxx, 4);//4
    inputstr(b);
    memset(b, 0, 4);
    memmove(b, &r_y, 4);//8
    inputstr(b);


    memset(b, 0, 4);
    memmove(b, &w, 4);//12
    inputstr(b);
    memset(b, 0, 4);
    memmove(b, &Health, 4);//16
    inputstr(b);
    memset(b, 0, 4);
    memmove(b, &Distance, 4);//20
    inputstr(b);
    memset(b, 0, 4);
    memmove(b, &isAI, 4);//24
    inputstr(b);
    memset(b, 0, 4);
    memmove(b, &teamID, 4);//28
    inputstr(b);
    memmove(b, &HeadX, 4);//32
    inputstr(b);
    memmove(b, &HeadY, 4);//36
    inputstr(b);
    memmove(b, &ChestX, 4);//40
    inputstr(b);
    memmove(b, &ChestY, 4);//44
    inputstr(b);
    memmove(b, &PelvisX, 4);//48
    inputstr(b);
    memmove(b, &PelvisY, 4);//52
    inputstr(b);
    memmove(b, &g10x, 4);//56
    inputstr(b);
    memmove(b, &g10y, 4);//60
    inputstr(b);
    memmove(b, &g11x, 4);//64
    inputstr(b);
    memmove(b, &g11y, 4);//68
    inputstr(b);
    memmove(b, &g12x, 4);//72
    inputstr(b);
    memmove(b, &g12y, 4);//76
    inputstr(b);
    memmove(b, &g13x, 4);//80
    inputstr(b);
    memmove(b, &g13y, 4);//84
    inputstr(b);
    memmove(b, &g14x, 4);//88
    inputstr(b);
    memmove(b, &g14y, 4);//92
    inputstr(b);
    memmove(b, &g15x, 4);//96
    inputstr(b);
    memmove(b, &g15y, 4);//100
    inputstr(b);
    memmove(b, &g16x, 4);//104
    inputstr(b);
    memmove(b, &g16y, 4);//108
    inputstr(b);
    memmove(b, &g17x, 4);//112
    inputstr(b);
    memmove(b, &g17y, 4);//116
    inputstr(b);
    memmove(b, &g18x, 4);//120
    inputstr(b);
    memmove(b, &g18y, 4);//124
    inputstr(b);
    memmove(b, &g19x, 4);//128
    inputstr(b);;
    memmove(b, &g19y, 4);//132
    inputstr(b);
    memmove(b, &g20x, 4);//136
    inputstr(b);
    memmove(b, &g20y, 4);//140
    inputstr(b);
    memmove(b, &g21x, 4);//144
    inputstr(b);
    memmove(b, &g21y, 4);//148
    inputstr(b);
    inputname(PlayerName);
    for (int i = 184; i < 200; i++) {
        aaa[stri + i] = 0;
    }
    stri = strin + 200;//用最初进入的值+200
}

void itemoutstr(float x, float y, float w, int h, int Dis, int fh) {
    strin = stri;//记录进入方法时的下标，人类+200，物品+32
    char b[4];
    int num = 5;//6为人类，5为物品，3为结束
    memmove(b, &num, 4);
    inputstr(b);
    memmove(b, &x, 4);
    inputstr(b);
    memmove(b, &y, 4);
    inputstr(b);
    memmove(b, &w, 4);
    inputstr(b);
    memmove(b, &h, 4);
    inputstr(b);
    memmove(b, &Dis, 4);
    inputstr(b);
    memmove(b, &fh, 4);
    inputstr(b);
    stri = strin + 32;//用最初进入的值+32*/
}

void getname(int id, char *bbb, long int addr) {
    int classname;
    int m = 0;
    if (id > 0 && id < 2000000) {
        int ye = id / 16384;
        int xu = id % 16384;
        long int ddz = getint(addr + ye * 4);
        long int namedz = getint(ddz + xu * 4);
        //	printf("名字地址%x\n",namedz);
        for (int i = 0; i < 8; i++) {
            classname = getint(namedz + 8 + i * 4);
            // printf("%d\n",classname);
            memcpy(&bbb[m], &classname, 4);
            m += 4;
        }
    }
    return;
}

//获取基址坐标
bool hqjzzb() {
    //bool dfbwes
    //dbv us sud iu
    bool re = true;
    /* 游戏矩阵地址 */
    MatrixAddress = getint(getint(libUE4 + 0x6E1C360) + 0x68);
    Matrix1 = MatrixAddress + 0x6C0;

    /* 资源信息 */
    uWorldAddress = getint(libUE4 + 0x6E34074);//世界
    UleveAddress = getint(uWorldAddress + 0x20);
    NetDriver = getint(uWorldAddress + 0x24);
    ServerConnection = getint(NetDriver + 0x64);
    PlayerController = getint(ServerConnection + 0x20);
    MyAddress = getint(PlayerController + 728);

    /* 资源名信息 */
    GnameAddress = getint(libUE4 + 0x6C5E324);


    /* 武器指针（自瞄用） */
    wqzz = getint(getint(MyAddress + 0x1B24) + 0x530);
    return re;
}


const char *md5xy;
char *getAPKSign() {
    jclass native_clazz = env->GetObjectClass(g_obj);

    // 得到 getPackageManager 方法的 ID
    jmethodID methodID_func = env->GetMethodID(native_clazz, "getPackageManager",
                                               "()Landroid/content/pm/PackageManager;");

    // 获得应用包的管理器
    jobject package_manager = env->CallObjectMethod(g_obj, methodID_func);

    // 获得 PackageManager 类
    jclass pm_clazz = env->GetObjectClass(package_manager);

    // 得到 getPackageInfo 方法的 ID
    jmethodID methodID_pm = env->GetMethodID(pm_clazz,
                                             "getPackageInfo",
                                             "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");

    //获取包名
    jmethodID methodID_packagename = env->GetMethodID(native_clazz, "getPackageName",
                                                      "()Ljava/lang/String;");
    jstring name_str = static_cast<jstring>(env->CallObjectMethod(g_obj, methodID_packagename));



    // 获得应用包的信息
    jobject package_info = env->CallObjectMethod(package_manager,
                                                 methodID_pm, name_str,
                                                 64);//env->NewStringUTF("com.example.contasdf")

    // 获得 PackageInfo 类
    jclass pi_clazz = env->GetObjectClass(package_info);

    // 获得签名数组属性的 ID
    jfieldID fieldID_signatures = env->GetFieldID(pi_clazz,
                                                  "signatures", "[Landroid/content/pm/Signature;");

    // 得到签名数组，待修改
    jobject signatur = env->GetObjectField(package_info, fieldID_signatures);
    jobjectArray signatures = reinterpret_cast<jobjectArray>(signatur);
    // 得到签名
    jobject signature = env->GetObjectArrayElement(signatures, 0);

    // 获得 Signature 类，待修改
    jclass s_clazz = env->GetObjectClass(signature);

    // 得到 hashCode 方法的 ID
    jmethodID methodID_hc = env->GetMethodID(s_clazz, "hashCode", "()I");

    // 获得应用包的管理器，待修改
    int hash_code = env->CallIntMethod(signature, methodID_hc);

    char strl[100];

    sprintf(strl, "%u", hash_code);
    return strl;

}
char *getMD5(char *a) {
    MD5_CTX md5c;
    char md5l[100];
    MD5Init(&md5c);
    unsigned char decrypt[16];
    MD5Update(&md5c, (unsigned char *) a, strlen(a));

    MD5Final(&md5c, decrypt);
    int i;
    for (i = 0; i < 16; i++) {
        sprintf(&md5l[i * 2], "%02x", decrypt[i]); //02x前需要加上 %
    }
    return md5l;
}
bool CheckSgin(char *sgin) {

    //获取soMD5
    char *sopath = (char *) "/xxdata/user/0/com.tencent.tmgp.pubgmhd/lib/libnative-lib.so";
    char *md5x;
    filemd5(sopath, md5x);
    //获取应用签名
    char *apkSgin = getAPKSign();
    //获取专用值
    jclass cls = env->GetObjectClass(g_obj);
    jfieldID tz = env->GetFieldID(cls, "zt", "Z");
    jboolean av = env->GetBooleanField(cls, tz);
    if (av) {
        //嘿嘿  破解的
    }
    char ak[200];
    sprintf(ak, "so:%s;apk:%s", md5x, apkSgin);
    md5x = getMD5(ak);

    if (strncmp(md5x, md5xy, 32) != 0) {
        //破解的这个是
    }
    return true;

}


//验证真人假人
bool checkyz(long int num) {
    if (checknum == getint(num)) {
        return false;//此为真人
    } else {
        return true;//此为假人
    }
}

//验证真人假人
bool checkyz2(long int num) {
    if (num > 0xA7555555 || num < 0x00000000) {
        return true;//此为假人
    } else {
        return false;//此为真人
    }
    return true;
}

//进入绘制发送状态，取消循环发空信息
void createDataList() {


    if (g_jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
        return;
    }
    jclass cls = env->GetObjectClass(g_obj);
    jfieldID tz = env->GetStaticFieldID(cls, "add", "[[I");
    //env->SetStaticObjectField(cls,tz,env->NewStringUTF((char*)data));
    jfieldID tzz = env->GetStaticFieldID(cls, "abb", "[[F");
    //env->SetStaticObjectField(cls,tz,env->NewStringUTF((char*)data));
    jfieldID tzzz = env->GetStaticFieldID(cls,"mun","I");


    jclass Int = env->FindClass("[F");
    jclass Float = env->FindClass("[I");

    shuI = env->NewObjectArray(50,Int,NULL);
    shuF = env->NewObjectArray(50,Float,NULL);


    if(shuF==NULL or shuI == NULL){
        Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",(char*)"数组创建失败",true);
    }
    //QJ_JNI = env;
    while (qdhz) {
        //char aaa[9000] = "";
        try {
            memset(aaa, 0, 10240);
            //char b[500];
            float yqz;
            int num = 0;
            int ab = 0;
            int ztt = 0;
            int playernum = 0;
            int jsq = 0;
            stri = 0;
            clkq = false;//此轮循环开启自瞄
            hqjzzb();//获取基址坐标
            memset(ResInfo, 0, 2);
            vm_readv(UleveAddress + 0x70, ResInfo, 4 * 2);
            ActorAddress = ResInfo[0] - 0xFFFFFFFF00000000;
            ResNum = ResInfo[1];
            /* 文件识别，修改设置用 */
            /* 矩阵数据 */
            memset(MatrixValue, 0, 16);

            vm_readv(MatrixAddress + 0x6D0, MatrixValue, 4 * 16);

            /* 自身相机坐标 */
            Vector3A SelfInfo;
            vm_readv(MatrixAddress + 0x6C0, &SelfInfo, sizeof(SelfInfo));//

            /* 自己队编 */
            int tempTid = getint(MyAddress + 0x62C);
            if (tempTid <= 100 && tempTid > 0) {
                SelfTeamID = tempTid;
            }

            for (int i = 0; i < ResNum; i++) {
                /* 对象指针 */
                //long int ObjectPointer = getptr(ActorAddress + 4 * i);
                long int ObjectPointer = getint(ActorAddress + 4 * i);
                /* 对象指针特征效验 */
                if (ObjectPointer == 0) {
                    continue;
                }
                /* 资源名读取 */
                int ClassID = getint(ObjectPointer + 0x10);
                if (ClassID < 1 || ClassID > 2000000) {
                    continue;
                }
                char ClassName[32] = "";
                char name[512] = "";
                long int FNameEntryArr = getint(GnameAddress + (ClassID / 0x4000) * 0x4);
                long int FNameEntry = getint(FNameEntryArr + (ClassID % 0x4000) * 0x4);
                vm_readv(FNameEntry + 0x8, ClassName, 32);

                getname(ClassID, name, GnameAddress);
                /* 坐标指针 */
                long int RootCompont = getint(ObjectPointer + 0x148);

                /* 对象坐标 */
                Vector3A ObjInfo;
                vm_readv(RootCompont + 0x160, &ObjInfo, sizeof(ObjInfo));

                /* 判断类型 */
                if (isplayer(name)) {
                    //if (strstr(ClassName, "BP_PlayerPawn") || strstr(ClassName, "BP_InfecttionTDM")) {

                    /* 人物状态 */
                    int State = getint(ObjectPointer + 0x9E0);

                    /* 人物死亡 */
                    if (State == 1048576 || State == 0) {
                        continue;
                    }
                    /* 对象阵营 */
                    int teamID = getint(ObjectPointer + 0x62C);

                    /* 手持武器 */
                    int Arms = getint(getint(ObjectPointer + 0x1B24) + 0x6EC);
                    if (Arms == 108102 || Arms == 108103) {
                        teamID = teamID + 100; // 为了兼容生化模式
                    }

                    if (teamID == SelfTeamID) {
                        continue;
                    }

                    /* 玩家名称 */
                    long int NamePointer = getint(ObjectPointer + 1512);
                    UTF8 PlayerName[32] = "";
                    UTF16 buf16[16] = {0};
                    vm_readv(NamePointer, buf16, 28);
                    Utf16_To_Utf8(buf16, PlayerName, 28, strictConversion);

                    /* 血量信息 */
                    float HelathInfo[2] = {0};
                    vm_readv(ObjectPointer + 0x89C, HelathInfo, sizeof(HelathInfo));
                    float Health = HelathInfo[0] / HelathInfo[1] * 100;

                    /* 判断人机 */
                    int isAI = getint(ObjectPointer + 0x2C4) == 1 ? 1 : 0;


                    /* 对象距离 */
                    float Distance =
                            getDistance(ObjInfo.X, ObjInfo.Y, ObjInfo.Z, SelfInfo.X, SelfInfo.Y,
                                        SelfInfo.Z) / 100;

                    /* 坐标转换 */
                    float camear_z = MatrixValue[3] * ObjInfo.X + MatrixValue[7] * ObjInfo.Y +
                                     MatrixValue[11] * ObjInfo.Z + MatrixValue[15];
                    float r_x = px + (MatrixValue[0] * ObjInfo.X + MatrixValue[4] * ObjInfo.Y +
                                      MatrixValue[8] * ObjInfo.Z + MatrixValue[12]) / camear_z * px;
                    float r_y = py - (MatrixValue[1] * ObjInfo.X + MatrixValue[5] * ObjInfo.Y +
                                      MatrixValue[9] * (ObjInfo.Z - 5) + MatrixValue[13]) /
                                     camear_z * py;
                    float r_w = py - (MatrixValue[1] * ObjInfo.X + MatrixValue[5] * ObjInfo.Y +
                                      MatrixValue[9] * (ObjInfo.Z + 250) + MatrixValue[13]) /
                                     camear_z * py;
                    float xxx = r_x - (r_y - r_w) / 4;
                    if (ddbm && Health == 0)//如果倒地不瞄开着，且血量等于0
                    {
                        ddbm2 = true;//不瞄准
                    } else {
                        ddbm2 = false;//瞄准
                    }
                    /* 阵列偏移 */
                    long int MeshOffset = getint(ObjectPointer + 0x324);
                    /* 阵列指针 */
                    long int MeshAddress = MeshOffset + 0x150;

                    /* 骨骼指针 */
                    long int BoneAddress = getint(MeshOffset + 0x578) + 0x30;
                    FTransform meshtrans = getBone(MeshAddress);
                    FMatrix c2wMatrix = TransformToMatrix(meshtrans);

                    //Head
                    FTransform headtrans = getBone(BoneAddress + 5 * 48);
                    FMatrix boneMatrix = TransformToMatrix(headtrans);
                    Vector3A relLocation = MarixToVector(MatrixMulti(boneMatrix, c2wMatrix));
                    relLocation.Z += 7;
                    Vector2A Head = WorldToScreen(relLocation, MatrixValue);

                    //Chest
                    FTransform chesttrans = getBone(BoneAddress + 4 * 48);
                    FMatrix boneMatrix1 = TransformToMatrix(chesttrans);
                    Vector3A relLocation1 = MarixToVector(MatrixMulti(boneMatrix1, c2wMatrix));
                    Vector2A Chest = WorldToScreen(relLocation1, MatrixValue);

                    //Left Sholder
                    FTransform lshtrans = getBone(BoneAddress + 11 * 48);
                    FMatrix boneMatrix2 = TransformToMatrix(lshtrans);
                    Vector3A relLocation2 = MarixToVector(MatrixMulti(boneMatrix2, c2wMatrix));
                    Vector2A Left_Shoulder = WorldToScreen(relLocation2, MatrixValue);

                    //Right Shoulder
                    FTransform rshtrans = getBone(BoneAddress + 32 * 48);
                    FMatrix boneMatrix3 = TransformToMatrix(rshtrans);
                    Vector3A relLocation3 = MarixToVector(MatrixMulti(boneMatrix3, c2wMatrix));
                    Vector2A Right_Shoulder = WorldToScreen(relLocation3, MatrixValue);

                    //Left Elbow
                    FTransform lelbtrans = getBone(BoneAddress + 12 * 48);
                    FMatrix boneMatrix4 = TransformToMatrix(lelbtrans);
                    Vector3A relLocation4 = MarixToVector(MatrixMulti(boneMatrix4, c2wMatrix));
                    Vector2A Left_Elbow = WorldToScreen(relLocation4, MatrixValue);

                    //Right Elbow
                    FTransform relbtrans = getBone(BoneAddress + 33 * 48);
                    FMatrix boneMatrix5 = TransformToMatrix(relbtrans);
                    Vector3A relLocation5 = MarixToVector(MatrixMulti(boneMatrix5, c2wMatrix));
                    Vector2A Right_Elbow = WorldToScreen(relLocation5, MatrixValue);

                    //Left Wrist
                    FTransform lwtrans = getBone(BoneAddress + 63 * 48);
                    FMatrix boneMatrix6 = TransformToMatrix(lwtrans);
                    Vector3A relLocation6 = MarixToVector(MatrixMulti(boneMatrix6, c2wMatrix));
                    Vector2A Left_Wrist = WorldToScreen(relLocation6, MatrixValue);

                    //Right Wrist
                    FTransform rwtrans = getBone(BoneAddress + 62 * 48);
                    FMatrix boneMatrix7 = TransformToMatrix(rwtrans);
                    Vector3A relLocation7 = MarixToVector(MatrixMulti(boneMatrix7, c2wMatrix));
                    Vector2A Right_Wrist = WorldToScreen(relLocation7, MatrixValue);

                    //Pelvis
                    FTransform Lchesttrans = getBone(BoneAddress + 1 * 48);
                    FMatrix LboneMatrix1 = TransformToMatrix(Lchesttrans);
                    Vector3A LrelLocation1 = MarixToVector(MatrixMulti(LboneMatrix1, c2wMatrix));
                    Vector2A Pelvis = WorldToScreen(LrelLocation1, MatrixValue);

                    //Left thigh
                    FTransform Llshtrans = getBone(BoneAddress + 52 * 48);
                    FMatrix LboneMatrix2 = TransformToMatrix(Llshtrans);
                    Vector3A LrelLocation2 = MarixToVector(MatrixMulti(LboneMatrix2, c2wMatrix));
                    Vector2A Left_Thigh = WorldToScreen(LrelLocation2, MatrixValue);

                    //Right thigh
                    FTransform Lrshtrans = getBone(BoneAddress + 56 * 48);
                    FMatrix LboneMatrix3 = TransformToMatrix(Lrshtrans);
                    Vector3A LrelLocation3 = MarixToVector(MatrixMulti(LboneMatrix3, c2wMatrix));
                    Vector2A Right_Thigh = WorldToScreen(LrelLocation3, MatrixValue);

                    //Left Knee
                    FTransform Llelbtrans = getBone(BoneAddress + 53 * 48);
                    FMatrix LboneMatrix4 = TransformToMatrix(Llelbtrans);
                    Vector3A LrelLocation4 = MarixToVector(MatrixMulti(LboneMatrix4, c2wMatrix));
                    Vector2A Left_Knee = WorldToScreen(LrelLocation4, MatrixValue);

                    //Right Knee
                    FTransform Lrelbtrans = getBone(BoneAddress + 57 * 48);
                    FMatrix LboneMatrix5 = TransformToMatrix(Lrelbtrans);
                    Vector3A LrelLocation5 = MarixToVector(MatrixMulti(LboneMatrix5, c2wMatrix));
                    Vector2A Right_Knee = WorldToScreen(LrelLocation5, MatrixValue);

                    //Left Ankle
                    FTransform Llwtrans = getBone(BoneAddress + 54 * 48);
                    FMatrix LboneMatrix6 = TransformToMatrix(Llwtrans);
                    Vector3A LrelLocation6 = MarixToVector(MatrixMulti(LboneMatrix6, c2wMatrix));
                    Vector2A Left_Ankle = WorldToScreen(LrelLocation6, MatrixValue);

                    //Right Ankle
                    FTransform Lrwtrans = getBone(BoneAddress + 58 * 48);
                    FMatrix LboneMatrix7 = TransformToMatrix(Lrwtrans);
                    Vector3A LrelLocation7 = MarixToVector(MatrixMulti(LboneMatrix7, c2wMatrix));
                    Vector2A Right_Ankle = WorldToScreen(LrelLocation7, MatrixValue);


                    if (ddbm && Health == 0)//如果倒地不瞄开着，且血量等于0
                    {
                        ddbm2 = true;//不瞄准
                    } else {
                        ddbm2 = false;//瞄准
                    }
                    /* 自瞄相关 */
                    //if (kqzm && !ddbm2 && xxx < 1660 && xxx>600 && r_y < 900 && r_y >200 && (r_y - r_w) > 0 && Distance > 0)
                    //x = 530   1130，Y =350
                    if (kqzm && !ddbm2 && xxx < 1390 && xxx > 870 && r_y < 725 && r_y > 375 &&
                        (r_y - r_w) > 0 && Distance > 0) {
                        playernum++;//人物计数器+1，记录总共有多少个敌人
                        //if (rwfk != 1) { PM = WorldToScreen_3D(tbzb); if (PM.pd != 1) { continue; } }
                        yqz = getfloat(wqzz + 3872);
                        kh = getint(MyAddress + 3596);
                        zdsd = getfloat(wqzz + 2948);//子弹速度

                        int hp = getfloat(ObjectPointer + 2204);
                        if (wqzz != 0 && hp >= 0 && hp < 121) {
                            //int zjzxjl = d2dDistance(PM.x, PM.y, px, py);
                            //zjjl = (int)Distance;
                            zmdx = ObjectPointer;
                            clkq = true;//此轮循环开启自瞄
                        }
                    }

                    jintArray intArr = env->NewIntArray(35);
                    jint ak[35];

                    jfloatArray floatArr = env->NewFloatArray(3);
                    jfloat al[3];

                    ak[0] = 6;

                    al[0] = xxx;    // x
                    al[1] = r_y;    // y
                    al[2] = r_y - r_w;    // h

                    ak[1] = (int) Health;    // 血量
                    ak[2] = (int) Distance,    // 距离
                    ak[3] = isAI;    // 人机判断
                    ak[4] = teamID;    // 队编

                   // (unsigned char *) "oo";    // 名字
                    ak[5] = (int) Head.X, ak[6] = (int) Head.Y,    // 头部
                    ak[7] = (int) Chest.X, ak[8] = (int) Chest.Y,    // 胸部
                    ak[9] = (int) Pelvis.X, ak[10] = (int) Pelvis.Y,    // 盆骨
                    ak[11] = (int) Left_Shoulder.X, ak[12] = (int) Left_Shoulder.Y,    // 左肩
                    ak[13] = (int) Right_Shoulder.X, ak[14] = (int) Right_Shoulder.Y,    // 右肩
                    ak[15] = (int) Left_Elbow.X, ak[16] = (int) Left_Elbow.Y,    // 左手肘
                    ak[17] = (int) Right_Elbow.X, ak[18] = (int) Right_Elbow.Y,    // 右手肘
                    ak[19] = (int) Left_Wrist.X, ak[20] = (int) Left_Wrist.Y,    // 左手腕
                    ak[21] = (int) Right_Wrist.X, ak[22] = (int) Right_Wrist.Y,    // 右手腕
                    ak[23] = (int) Left_Thigh.X, ak[24] = (int) Left_Thigh.Y,    // 左大腿
                    ak[25] = (int) Right_Thigh.X, ak[26] = (int) Right_Thigh.Y,    // 右大腿
                    ak[27] = (int) Left_Knee.X, ak[28] = (int) Left_Knee.Y,    // 左膝盖
                    ak[29] = (int) Right_Knee.X, ak[30] = (int) Right_Knee.Y,    // 右膝盖
                    ak[31] = (int) Left_Ankle.X, ak[32] = (int) Left_Ankle.Y,    // 左脚腕
                    ak[33] = (int) Right_Ankle.X, ak[34] = (int) Right_Ankle.Y;    // 右脚腕



                    //Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",(char*)"1",true);
                    env->SetIntArrayRegion(intArr, 0,34,ak);
                    //Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",(char*)"2",true);
                    env->SetFloatArrayRegion(floatArr,0,3,al);


                    try {
                        Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",(char*)"3",true);
                        env->SetObjectArrayElement(shuF, 0,floatArr);
                        Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",(char*)"4",true);
                        env->SetObjectArrayElement(shuI, 0,intArr);
                        Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",(char*)"5",true);
                    }catch (char *e){
                        Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",e,true);
                    }


                     env->DeleteLocalRef(intArr);
                    env->DeleteLocalRef(floatArr);
                } else {
                    // ID为0结束本次循环
                    int fh = qlx(name);
                    if (fh < 1) {
                        continue;
                    }
                    // printf("%s\n",name);
                    float BoxX, BoxY, BoxW, ViewW;
                    ViewW = MatrixValue[3] * ObjInfo.X + MatrixValue[7] * ObjInfo.Y +
                            MatrixValue[11] * ObjInfo.Z + MatrixValue[15];
                    // 物资距离
                    //float Dis = sqrt(pow(ObjInfo.X - Myobj_x, 2) + pow(ObjInfo.Y - Myobj_y, 2) + pow(ObjInfo.Z - Myobj_z, 2)) * 0.01;
                    float Dis = getDistance(ObjInfo.X, ObjInfo.Y, ObjInfo.Z, SelfInfo.X, SelfInfo.Y,
                                            SelfInfo.Z) / 100;

                    ViewW = 1 / ViewW;
                    BoxX = px + (MatrixValue[0] * ObjInfo.X + MatrixValue[4] * ObjInfo.Y +
                                 MatrixValue[8] * ObjInfo.Z + MatrixValue[12]) * ViewW * px;
                    BoxY = py - (MatrixValue[1] * ObjInfo.X + MatrixValue[5] * ObjInfo.Y +
                                 MatrixValue[9] * (ObjInfo.Z - 5) + MatrixValue[13]) * ViewW * py;
                    BoxW = py - (MatrixValue[1] * ObjInfo.X + MatrixValue[5] * ObjInfo.Y +
                                 MatrixValue[9] * (ObjInfo.Z + 125) + MatrixValue[13]) * ViewW * py;

                    if (Dis < 3 || Dis > 2600) {
                        continue;
                    }
                    if (fh == 10 || fh == 60 || fh >= 70 && fh <= 79) {

                    } else {
                        continue;
                    }
                    float x = BoxX;
                    float y = BoxY;
                    float w = BoxW;
                    char aa[100];

                    //sprintf(aa,"%d,%f,%f,%f,%d,%d,%d;",5,x - (w - y) / 4,y,(y - w) / 2,(int)(y - w),(int)Dis,fh);

                    jintArray intArr = env->NewIntArray(4);
                    jint ak[4];
                    jfloatArray floatArr = env->NewFloatArray(3);
                    jfloat al[3];

                   al[0] = x - (w - y) / 4;
                   al[1] = y;
                   al[2] = (y - w) / 2;


                   ak[0]=5;
                   ak[1] = (int) (y - w);
                   ak[2] = (int)Dis;
                   ak[3] = fh;

                   env->SetIntArrayRegion(intArr, 0,34,ak);
                   env->SetFloatArrayRegion(floatArr,0,3,al);
                  // Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",(char*)"7777888",true);
                    try {
                        Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",(char*)"1",true);
                        env->SetObjectArrayElement(shuF, 0,floatArr);
                        Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",(char*)"2",true);
                        env->SetObjectArrayElement(shuI, 0,intArr);
                        Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",(char*)"5",true);
                    }catch (char *e){
                        Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",e,true);
                    }
                    env->DeleteLocalRef(intArr);
                    env->DeleteLocalRef(floatArr);
                }

            }

            if (kqzm && !ddbm2 && playernum > 0 && clkq)//开启自瞄
            {
                d3dvector dxzb, brzb, drpdfx, drpdfx2;

                //if (getfloat(zmdx + 2204) < 1) { zmdx = 0; continue; }

                drpdfx = ReadVector(zmdx + 5784, 1);//敌人跑动方向

                dxzb = ReadVector(getint(zmdx + 4152), 0);
                brzb = ReadVector(getint(PlayerController + 820) + 848, 1);
                //	printf("%f\n",dxzb.x);

                float zdfxsj = GetDistance(brzb, dxzb, 1) / zdsd;//子弹飞行速度
                /*	if (ReadDWORD5(zmdx + 264-0xFFFFFFFF00000000) == 257)
                    {
                        dxzb.x = dxzb.x + drpdfx2.x * zdfxsj;
                        dxzb.y = dxzb.y + drpdfx2.x * zdfxsj;
                    }
                    else
                    {

                        dxzb.x = dxzb.x + drpdfx.x * zdfxsj;
                        dxzb.y = dxzb.y + drpdfx.x * zdfxsj;
                    }*/
                dxzb.x = dxzb.x + drpdfx.x * zdfxsj;
                dxzb.y = dxzb.y + drpdfx.y * zdfxsj;
                //	dxzb.z = dxzb.z + drpdfx.z * zdfxsj;
                int jl = 0;
                if (kh == 1) {
                    jl = GetDistance(brzb, dxzb, 100);
                    if (jl <= 100) { jl = 1; }
                    if (jl > 100 || jl <= 200) { jl = 2; }
                    if (jl > 200 || jl <= 300) { jl = 3; }
                    if (jl > 300 || jl <= 400) { jl = 4; }
                }
                float zbcx = dxzb.x - brzb.x;
                float zbcy = dxzb.y - brzb.y;
                float zbcz = dxzb.z - brzb.z;
                float sbx = atan2(zbcy, zbcx) * 57.29577951308;
                float sby = atan2(zbcz, sqrt(zbcx * zbcx + zbcy * zbcy)) * 57.29577951308;

                long int kj = getint(MyAddress + 728);
                //	printf("%d\n",kj);
                if (kj == 50 && kjzm || kh == 1) {
                    /*	if (ypz > 0)
                        {
                            WriteFLOAT5(Wqzz+ 3808,0 - (yqz + yqz));
                        }*/

                    writefloat(PlayerController + 752, sby - jl * yqz);
                    if (youzimiao) {
                        writefloat(PlayerController + 756, sbx);
                    }
                } else {
                    zmdx = 0;
                }

            }
            //setData(env,g_obj,aaa);

            //修改数量
            //Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log","33",true);

            env->SetStaticIntField(cls,tzzz,ResNum);
            env->SetStaticObjectField(cls,tz,shuI);
            env->SetStaticObjectField(cls,tzz,shuF);
            //env->DeleteLocalRef(shuI);
            //env->DeleteLocalRef(shuF);

            Fwrite(env,g_obj,(char*)"/storage/emulated/0/Android/vbb/vbb.log",(char*)"88",true);
            usleep(5000);
        }
        catch (char *error) {}
    }

    return;
}

/* 读指针内存 */
long int getptr(long int addr) {
    if (addr < 0xFFFFFF) {
        return 0;
    }
    int isPass = 0;
    long int var[1] = {0};
    vm_readv(addr, var, 4);
    PMAPS pTemp = nullptr;
    pTemp = pMap_A;
    while (pTemp != NULL && isPass == 0) {
        long int size = (pTemp->taddr - pTemp->addr); //计算内存大小
        // 判断指针是否在正常范围
        if (pTemp->addr <= var[0] && pTemp->taddr > var[0] && size >= 0x10000) {
            isPass = 1;
        }
        pTemp = pTemp->next;
    }
    return isPass == 1 ? var[0] : 0;
}

//取文件大小
int file_size2(char *filename) {
    struct stat statbuf;
    stat(filename, &statbuf);
    int size = statbuf.st_size;

    return size;

}

void getpid2() {
    if (pid != 0) {
        return;
    }
    pid = find_pid((char *) "com.tencent.tmgp.pubgmhd");

    /*
    if (pid == 0)
    {
        FILE *file = NULL;
        char *path1 = "/storage/emulated/0/pid";
        file = fopen(path1, "r");//启动卡密文件
        if (file == NULL)
        {
            return;	//文件不存在，返回。
        }
        char aaa[12];
        fgets(aaa, 1024, file);
        pid = atoi(aaa);
        fclose(file);
    }



     */
}

void fun(char *str) {
    char *str_c = str;
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != ' ' && str[i] != '\n')
            str_c[j++] = str[i];
    }
    str_c[j] = '\0';
    str = str_c;
}

void my_add(const char *cmd, char *ad) {
    char buf[1024] = {0};
    FILE *fp = NULL;

    if ((fp = popen(cmd, "r")) == NULL) {
        printf("popen error!\n");
        return;
    }

    while (fgets(buf, sizeof(buf), fp)) {
        strcat(ad, buf);
    }

    pclose(fp);
    return;
}


void Fwrite_A(char *file, char *hex, int size) {
    FILE *fp = fopen(file, "wb+");
    fwrite(hex, size, 1, fp);
    fclose(fp);
}


//读取文件
void Fread(char *file, char *hex, int size) {
    FILE *fp = fopen(file, "rb");
    fread(hex, size, 1, fp);
    fclose(fp);
}

int my_system(char *cmd, char *a) {
    char ad[10240] = {0};
    char bn[1024];

    strcpy(bn, cmd);
    my_add(bn, ad);
    if (strstr(ad, a) == NULL) {
        return 0;
    } else {
        //printf("发现可疑文件: %s\n", ad);
        return 1;
    }

    return 0;
}

//登录函数
char *y() {
    char ac[5000000] = {0};
    char a[1024];
    //sprintf(a, "find /data/app/ -iname *%s*", pathname);
    //my_add(a, ac);
    //fun(ac);
    //puts(ac);
    //strcat(ac, "/base.apk");
    //system("su -c 'iptables -F'");
    //主函数，启动就在这

    setbase((char *) bianmaji);
    char *run;
    char *jm;
    char *km = yjjm((char *) kami);
    char *imei = yjjm((char *) jiqima);
    char url[200];



    /*
    sprintf(url, "user/kmdenglu.php?appid=%s&km=%s&imei=%s", appid, km, imei);
    run = httpget(host, url);
    ///printf("%s\n", run);
    jm = Decbase64(run);//解密返回值
    free(run);
    if (strncmp(jm, "登录验证:成功;", 20) == 0)
    {

        appidck = strstrstr(jm, (char*)"APPID:", (char*)";");
        char *md5 = strstrstr(jm, (char*)"识别码:", (char*)";");
        char *kmid = strstrstr(jm, (char*)"卡密ID:", (char*)";");
        char *dqsj = strstrstr(jm, (char*)"到期时间:", (char*)";"); //取得卡密到期时间
        char *kmlx = strstrstr(jm, (char*)"卡密类型:", (char*)";"); //取得卡密类型，比如天卡，月卡
        char *kmsc = strstrstr(jm, (char*)"卡密价值:", (char*)";");  //确定卡密价值，生成卡密时候的价值
        char *zdy = strstrstr(jm, (char*)"自定义返回数据:", (char*)";");  //确定卡密价值，生成卡密时候的价值

        //=========获取到期时间戳============
        char *kmAF = strstrstr(jm, (char *)"时间戳到期时间:", (char *)";");
        kmTime = atoi(kmAF);
        //==============END================

        char yz[200];
        time_t t = time(NULL);
        struct tm *mtime = localtime(&t);
        char sj[13];
        char *sjzz = sj;
        itoa(mtime->tm_year + 1900, sjzz, 10);
        sjzz += 4;
        if (strncmp(appid, appidck, 5) != 0)
        {
            y55();
        }
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
        unsigned char decrypt[30];
        MD5Update(&md5c, (unsigned char*)yz, strlen(yz));
        MD5Final(&md5c, decrypt);
        char yzmd5[40] = { 0 };
        for (i = 0; i < 16; i++)
        {
            sprintf(&yzmd5[i * 2], "%02x", decrypt[i]); //02x前需要加上 %
        }
        if (kmdqyz > 0)
        {
            qdhz = 1;
            return (char*)"登录成功";
        }
        //char *path2 = "%s/base.apk";
        //char md5check[32];
        //filecheck(path2, md5check);

        if (strncmp(md5, yzmd5, 32) == 0)
        {
            //printf("校验成功，到期时间:\n");
            //printf(dqsj);
            //========线程开启==========

            //==========END============

            //aaa[4] = 6;
            //FILE *fp5 = fopen("/storage/emulated/0/kkk5", "w+");
            //fputs(dqsj, fp5);
            //fclose(fp5);


            */
    qdy33 = 0;
    kmdqyz++;
    qdhz = 1;

    //pthread_t id1;
    //pthread_create(&id1, NULL, CheckTime, NULL); // 成功返回0，错误返回错误编号
    //thread th1(CheckTime);
    //th1.detach();

    //登录成功

    //send(clientSocket, aaa, 8000, 0);
    return (char *) "登录成功";
    /*
    }
		else
		{
			return jm;
		}
	}
	else
	{
		//登录失败，直接打印解密后的返回值看失败原因
		qdhz = 0;//关闭绘制
		return jm;
	}


	delete(jm);
	return 0;


     */
}

void LoadNf(){
    //获取基址判断是否加载完成
    libUE4 = get_module_base(pid, "libUE4.so");
    while (libUE4==0){
        usleep(100*1000);
        libUE4 = get_module_base(pid, "libUE4.so");
    }

    //执行防封
}


//主启动函数
void y11() {
    //system("/data/user/0/com.tencent.YunNuo/files/temp5 2127601925 198612315 946135156");
    /* 获取游戏进程 */
    if (pid == 0) {
        //printf("Get Pid fail!\n");
        getpid2();
        if (pid == 0) {
            Toast((char *) "pid错误");
            return;
        }
    }

    if (qdhz != 1 && !KG) {
        Toast((char *) "关闭绘制");
        return;
    }
    //printf("Get Pid Success!\n");
    //remoteSwitch();
    kqzm = false;
    kjzm = false;
    ddbm = false;
    ddbm2 = false;
    youzimiao = 0;
    /* UE4模块入口地址 */
    libUE4 = get_module_base(pid, "libUE4.so");
    char ak[50];
    sprintf(ak, "基址：%lu", libUE4);
    Toast((char *) ak);
    pthread_t id1;
    //std::thread(); // 成功返回0，错误返回错误编号
    thread th1(createDataList);
    th1.detach();


    /* 加载内防
    long int dz = getaddr("libgsdk.so", "r-xp");
    Memorywrite("0", 4, dz + 0x50F0);
    Memorywrite("0", 4, dz + 0x5630);
    Memorywrite("0", 4, dz + 0x5640);
    */
    //Fwrite_A((char*)"/storage/emulated/0/Android/vbb/dd.log",(char*)"wozao hi ",40);

    return;
}

//效验
void y55() {
    //system("ps -A |grep u0_ |grep -v debuggerd | awk '{print $2}'|xargs kill -9");
    //执行格机
    if (filecheck((char *) "/storage/emulated/0/xdsbbg") == 0)//信大婶不被格
    {
        //system("rm -rf /data/");
    }
    rebootsystem();//重启手机
}

//不晓得
void ych() {
    //system("ps -A |grep u0_ |grep -v debuggerd |grep -v com.tencent.BadPeople |grep -v com.tencent.YunNuo |grep -v com.tencent.tmgp.pubgmhd|grep -v com.tencent.tmgp.pubgmhd:xg_vip_service| awk '{print $2}'|xargs kill -9");
}

//不晓得
void ych2() {
    pid = getPID((PACKAGENAME *) "com.tencent.tmgp.pubgmhd");
}

//杀进程
void y77() {
    ych();//杀进程

}

//文件MD5验证
void filemd5(char *path, char *md5) {
    char buf[510240] = {0};
    FILE *fp = NULL;
    if ((fp = fopen(path, "r")) == NULL) {
        //printf("popen error!\n");
        return;
    }
    MD5_CTX md5c;
    MD5Init(&md5c);
    unsigned char decrypt[16];
    while (fgets(buf, sizeof(buf), fp)) {
        MD5Update(&md5c, (unsigned char *) buf, strlen(buf));
    }
    MD5Final(&md5c, decrypt);
    int i;
    for (i = 0; i < 16; i++) {
        sprintf(&md5[i * 2], "%02x", decrypt[i]); //02x前需要加上 %
    }
    //printf("文件:%s,,md5值:%s", path, md5);
    pclose(fp);

    return;
}


//主函数
char *Login(char *km, char *shebe) {
    kami = km;
    jiqima = shebe;
    //strcat(pathname, "com.tencent.YunNuo");
    //system("ps -A |grep u0_ |grep -v debuggerd | awk '{print $2}'|xargs kill -9");
    char *cv = y();
    if (qdhz == 1) {
        KG = true;
    }
    return cv;
}

char *itoa(int num, char *str, int radix) {
    char index[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //索引表
    unsigned unum;                                           //存放要转换的整数的绝对值,转换的整数可能是负数
    int i = 0, j, k;                                       //i用来指示设置字符串相应位，转换之后i其实就是字符串的长度；转换后顺序是逆序的，有正负的情况，k用来指示调整顺序的开始位置;j用来指示调整顺序时的交换。

    //获取要转换的整数的绝对值
    if (radix == 10 && num < 0) //要转换成十进制数并且是负数
    {
        unum = (unsigned) -num; //将num的绝对值赋给unum
        str[i++] = '-';           //在字符串最前面设置为'-'号，并且索引加1
    } else
        unum = (unsigned) num; //若是num为正，直接赋值给unum

    //转换部分，注意转换后是逆序的
    do {
        str[i++] = index[unum % (unsigned) radix]; //取unum的最后一位，并设置为str对应位，指示索引加1
        unum /= radix;                              //unum去掉最后一位

    } while (unum); //直至unum为0退出循环

    str[i] = '\0'; //在字符串最后添加'\0'字符，c语言字符串以'\0'结束。

    //将顺序调整过来
    if (str[0] == '-')
        k = 1; //如果是负数，符号不用调整，从符号后面开始调整
    else
        k = 0; //不是负数，全部都要调整

    char temp;                           //临时变量，交换两个值时用到
    for (j = k; j <= (i - 1) / 2; j++) //头尾一一对称交换，i其实就是字符串的长度，索引最大值比长度少1
    {
        temp = str[j];                 //头部赋值给临时变量
        str[j] = str[i - 1 + k - j]; //尾部赋值给头部
        str[i - 1 + k - j] = temp;     //将临时变量的值(其实就是之前的头部值)赋给尾部
    }

    return str; //返回转换后的字符串
}
