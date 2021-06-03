#ifndef STRUCTSCOMM_H
#define STRUCTSCOMM_H

//using namespace std;

#define MaxPlayerCount 30
#define MaxVehicleCount 20
#define MaxItemsCount 20
#define MaxGrenadeCount 20
#define MaxAirBoxCount 20

struct Vector2A {
	float X;
	float Y;

	Vector2A() {
		this->X = 0;
		this->Y = 0;
	}

	Vector2A(float x, float y) {
		this->X = x;
		this->Y = y;
	}
};

struct Vector3A {
	float X;
	float Y;
	float Z;

	Vector3A() {
		this->X = 0;
		this->Y = 0;
		this->Z = 0;
	}

	Vector3A(float x, float y, float z) {
		this->X = x;
		this->Y = y;
		this->Z = z;
	}

};

struct Vector4A {
	float x;
	float y;
	float h;
	float w;

	Vector4A() {
		this->x = 0;
		this->y = 0;
		this->h = 0;
		this->w = 0;
	}


	Vector4A (float x, float y, float h, float w) {
		this->x = x;
		this->y = y;
		this->h = h;
		this->w = w;
	}
};

enum Mode {
	InitMode = 1,
	ESPMode = 2,
	HackMode = 3,
	StopMode = 4,
};

struct Request {
	int Mode;
	int ScreenWidth;
	int ScreenHeight;
	bool isSpeed;
	bool isBone;
	bool isItems;
	bool isVehicle;
};

struct BoneData {
	Vector2A Head;
	Vector2A Chest;
	Vector2A Pelvis;
	Vector2A Left_Shoulder;
	Vector2A Right_Shoulder;
	Vector2A Left_Elbow;
	Vector2A Right_Elbow;
	Vector2A Left_Wrist;
	Vector2A Right_Wrist;
	Vector2A Left_Thigh;
	Vector2A Right_Thigh;
	Vector2A Left_Knee;
	Vector2A Right_Knee;
	Vector2A Left_Ankle;
	Vector2A Right_Ankle;
};

struct PlayerData {
	bool isAI;
	int TeamID;
	float Health;
	float Angle;
	int State;
	float AimedYawDiff;
	float Distance;
	char PlayerName[32];
	Vector4A Location;
	Vector2A RadarLocation;
	Vector2A Head;
	Vector2A Chest;
	Vector2A Pelvis;
	Vector2A Left_Shoulder;
	Vector2A Right_Shoulder;
	Vector2A Left_Elbow;
	Vector2A Right_Elbow;
	Vector2A Left_Wrist;
	Vector2A Right_Wrist;
	Vector2A Left_Thigh;
	Vector2A Right_Thigh;
	Vector2A Left_Knee;
	Vector2A Right_Knee;
	Vector2A Left_Ankle;
	Vector2A Right_Ankle;
};

struct ItemData {
	float Distance;
	char ItemName[32];
	Vector2A Location;
};

struct Response {
	bool Success; //状态
	bool isHall; //大厅
	int PlayerCount; //人
	int GrenadeCount; //投掷物
	int VehicleCount; //车
	int ItemsCount; //物资
	int AirBoxCount; //空投盒子飞机
	PlayerData Players[MaxPlayerCount];
	ItemData Grenades[MaxGrenadeCount];
	ItemData Vehicle[MaxVehicleCount];
	ItemData Items[MaxItemsCount];
	ItemData AirBox[MaxAirBoxCount];
};

struct FMatrix {
	float M[4][4];
};

struct Quat {
	float X;
	float Y;
	float Z;
	float W;
};

struct FTransform {
	Quat Rotation;
	Vector3A Translation;
	float chunk;
	Vector3A Scale3D;
};

struct MAPS {
	long int addr;
	long int taddr;
	int type;
	struct MAPS *next;
};

typedef struct MAPS *PMAPS;

#define LEN sizeof(struct MAPS)

#endif