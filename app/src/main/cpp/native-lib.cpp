#include <jni.h>
#include <stdbool.h>
//导入多线程库
void setData(JNIEnv *env,jobject obj,char data[]);
void Toast(char* str);
void Fwrite(JNIEnv *env,jobject obj,char* file,char* contex,bool a);
char* km;
char* ji;
bool KG;
int pid;
JNIEnv* QJ_JNI;
jobject QJ_OBJ;
JavaVM *g_jvm=NULL;
jobject g_obj=NULL;
#include "yun.h"


//写数据的绘制数据的

void setData(JNIEnv *env,jobject obj,char data[]){
    jclass cls = env->GetObjectClass(obj);
    jfieldID tz = env->GetStaticFieldID(cls,"bytestr","Ljava/lang/String;");
    env->SetStaticObjectField(cls,tz,env->NewStringUTF((char*)data));

}

void Toast(char* str){
    jclass cls = QJ_JNI->GetObjectClass(QJ_OBJ);
    jmethodID tz = QJ_JNI->GetStaticMethodID(cls,"Toast","(Ljava/lang/String;)V");
    QJ_JNI->CallStaticVoidMethod(cls,tz,QJ_JNI->NewStringUTF(str));
}



void Fwrite(JNIEnv *env,jobject obj,char* file,char* contex,bool a){
    jclass cls = env->GetObjectClass(obj);
    jmethodID tz = env->GetStaticMethodID(cls,"写入","(Ljava/lang/String;Ljava/lang/String;Z)V");

    if(a){
        env->CallStaticVoidMethod(cls,tz,env->NewStringUTF(file),env->NewStringUTF(contex),JNI_TRUE);
    }else{
        env->CallStaticVoidMethod(cls,tz,env->NewStringUTF(file),env->NewStringUTF(contex),JNI_FALSE);
    }

}



char* jstringTostring(JNIEnv* env, jstring jstr)
{
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0)
    {
        rtn = (char*)malloc(alen + 1);
        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}




/////下面都是JNI函数

extern "C"
JNIEXPORT jstring JNICALL
Java_com_tencent_zz_afff_login(JNIEnv *env, jobject thiz, jstring km, jstring jiqima) {
    // TODO: implement login()

    //保留这两个方便后面调用

    QJ_JNI = env;
    QJ_OBJ = thiz;

    env->GetJavaVM(&g_jvm);
    g_obj =env->NewGlobalRef(thiz);
    //登录易验证的
    jclass cls = env->GetObjectClass(thiz);
    jfieldID tz = env->GetFieldID(cls,"zt","Z");
    char* jieguo =Login(jstringTostring(env,km),jstringTostring(env,jiqima));

    if (KG){
        //控制登录框的
        env->SetBooleanField(thiz,tz,JNI_TRUE);

    }
    return env->NewStringUTF(jieguo);
}







extern "C"
JNIEXPORT jint JNICALL
Java_com_tencent_zz_afff_LoadFF(JNIEnv *env, jobject thiz) {
    // TODO: implement LoadFF()
    //写防封的
    Toast((char*)"sasac");
    return 1;
}




extern "C"
JNIEXPORT void JNICALL
Java_com_tencent_zz_afff_setSwitch(JNIEnv *env, jobject thiz, jint a, jint b) {
    // TODO: implement setSwitch()
    QJ_JNI = env;
    QJ_OBJ = thiz;
    px = (float)b/2;
    py = (float)a/2;


    if (pid == 0) {
        //printf("Get Pid fail!\n");
        getpid2();
        if (pid == 0) {
            Toast((char *) "pid错误");
            return;
        }
    }
    //自动加载防封
    thread th1(LoadNf);
    th1.detach();

   // Toast((char*)"set分辨率");
}


extern "C"
JNIEXPORT void JNICALL
Java_com_tencent_zz_afff_setZM(JNIEnv *env, jobject thiz, jint a) {
    // TODO: implement setZM()
    QJ_JNI = env;
    QJ_OBJ = thiz;
    int zm = a;
    switch(zm){
        case 0:
            kqzm = false;
            break;
        case 1:
            kqzm = true;
            break;
        case 2:
            kjzm = false;
            break;
        case 3:
            kjzm = true;
            break;
        case 4:
            ddbm = false;
            break;
        case 5:
            ddbm = true;
            break;

    }
}


extern "C"
JNIEXPORT void JNICALL
Java_com_tencent_zz_afff_Start(JNIEnv *env, jobject thiz, jint a) {
    // TODO: implement Start()
    QJ_JNI = env;
    QJ_OBJ = thiz;

    env->GetJavaVM(&g_jvm);
    g_obj =env->NewGlobalRef(thiz);
    y11();
   //
}



extern "C"
JNIEXPORT void JNICALL
Java_com_tencent_zz_afff_INIT(JNIEnv *env, jobject thiz) {
    // TODO: implement INIT()
    system("chmod 000 /data/user/0/com.tencent.tmgp.pubgmhd/files/ss_tmp");
    system("chmod 000 /data/user/0/com.tencent.tmgp.pubgmhd/files/tss_tmp");
}