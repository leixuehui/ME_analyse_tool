#ifndef GLOBAL_HEADER_H
#define GLOBAL_HEADER_H
#include "ControlCAN.h"
#include <QString>
#include <QList>
#include <QColor>

#define VIDEO_FRAME_DEFAULT_WIDTH 1920.0
#define VIDEO_FRAME_DEFAULT_HEIGHT 1080.0

#ifdef WIN32  
#pragma execution_character_set("utf-8")  
#endif

/****************SOTEREA****************/
struct CanObjData
{
    QList<VCI_CAN_OBJ> objList;
};

struct DisplayAndWarningMsg
{
    QString signalName;
    QString value;
    QString unit;
};

struct DeviceInfoObj
{
    int timeInterval;
    int calibPercentage;
    int calibStatus;
    int sightlineShelter;
    int versionMain;
    int versionMinor;
    int versionPatch;
    bool valid;
};

struct ObjInfo
{
    quint8 ID ;
    float PosX ;
    float PosY ;
    float Length;
    float Width;
    float RelValY;
    quint8 type;
//    quint8 status;
};

struct ObjStatusInfo
{
    int driverStatus;
    int deviceStatus;
    float leftLaneLength;
    float rightLaneLength;
    int leftLaneStatus;
    int rightLaneStatus;
    int measCounter;
};

struct LaneAInfo
{
    bool valid;
    int quality;
    int laneType;
    float widthMarking;
    float c0;
    float c1;
};

struct LaneBInfo
{
    bool valid;
    float c2;
    float viewRange;
    int viewRangeValid;
};

struct DrawObjData
{
    QList<ObjInfo> objs;
    int frameObjCount;
    ObjStatusInfo statuInfo;
    LaneAInfo leftLaneAInfo;
    LaneBInfo leftLaneBInfo;
    LaneAInfo rightLaneAInfo;
    LaneBInfo rightLaneBInfo;
    int speedlimitSign;
    int speed;
    DeviceInfoObj deviceInfoObj;
};

struct ObjType
{
    QColor color;
    QString typeName;
    quint8 typeId;
};

/****************MOBILEYE****************/
enum TimeIndicator
{
	day      = 0,
	dusk     = 1,
	night    = 2,
	notInUse = 3
};

enum Obstacle_Type
{
	Vehicle = 0,
	Truck = 1,
	Bike = 2,
	Ped = 3,
	Bicycle=4,
	Unused=5,
	//Unused=6
};

struct GeneralInfo
{
	int     time_indicator;
	bool	headway_valid;
	double  headway_mesurement;
	bool	FCW_on;
	bool	failSafe;
	bool    PCW_PedDZ;
	int     TSR_warning_level;
	int     HW_warning_level;
	bool    Tamper_Alert;
	bool    Right_LDW_Availability;
	bool    Left_LDW_Availability;
	bool    LDW_off;
	float   Lane_Curvature;
	float	Yaw_Angle;
	float   Pitch_Angle;

	GeneralInfo() : time_indicator(0), TSR_warning_level(0), HW_warning_level(0),
		headway_valid(false), FCW_on(false), failSafe(false), PCW_PedDZ(false), headway_mesurement(0.0),
		Tamper_Alert(false), Right_LDW_Availability(false), Left_LDW_Availability(false), LDW_off(false), Lane_Curvature(0.0), Yaw_Angle(0.0), Pitch_Angle(0.0)
	{}
};

struct Obstacle_Status
{
	int	  numberOfObstacles;
	bool  LeftCloseRangCutIn;
	bool  RightCloseRangCutIn;
	bool  closeCar;
	int   failSafe;

	Obstacle_Status() : numberOfObstacles(0), failSafe(0),
		LeftCloseRangCutIn(false), RightCloseRangCutIn(false), closeCar(false)
	{}
};

struct Position
{
	double position_x;
	double position_y;


	Position() : position_x(0.0), position_y(0.0)
	{}
};

struct ObstacleData_A
{
	int obstacleID;
	Position obstaclePosition;
	int blinkerInfo;
	int cutInAndOut;
	double obstacleRelvel_X;
	int obstacleStatus;
	bool obstacleBrakeLights;
	int obstacle_Type;


	ObstacleData_A() : obstacleID(0), blinkerInfo(0), cutInAndOut(0), obstacleStatus(0),
		obstacleRelvel_X(0.0), obstacleBrakeLights(false), obstacle_Type(6)
	{}
};

struct ObstacleData_B
{
	double obstacleLength;
	double obstacleWidth;
	int	   obstacleLane;
	bool   CIPVFlags;

	ObstacleData_B() : obstacleLength(0.0), obstacleWidth(0.0),
		obstacleLane(0), CIPVFlags(false)
	{}
};

struct ObstacleData_C
{
	double obstacleAngleRate;
	double obstacleScaleChange;
	double objectAccel_X;
	double obstacleAngle;

	ObstacleData_C() : obstacleAngleRate(0.0), obstacleScaleChange(0.0),
		objectAccel_X(0.0), obstacleAngle(0.0)
	{}
};

struct Lane_Status
{
	bool LDW_availability_right;
	bool LDW_availability_left ;	  
	int	Lane_type_left		  ;
	int	Lane_type_right		  ;
	double	distance_to_alne_L	  ;
	double	distance_to_alne_R	  ;
	int	Lane_conf_right		  ;
	int	Lane_conf_left		  ;

	Lane_Status() : LDW_availability_right(false), LDW_availability_left(false), Lane_type_left(0),
		Lane_type_right(0), distance_to_alne_L(0.0), distance_to_alne_R(0.0), Lane_conf_right(0), Lane_conf_left(0)
	{}

};

struct Left_Status
{
	int	Lane_Type_L                 ;
	int	Quality_L					;
	double	Curvature_L					;
	double	Position_L					;
	double	Width_left_marking			;
	double	Heading_Angle_L				;
	double	View_Range_L				;
	bool	View_Rang_Availability_L	;

	Left_Status() : Lane_Type_L(0), Quality_L(0), Curvature_L(0.0), Position_L(0.0), Width_left_marking(0.0),
		Heading_Angle_L(0.0), View_Range_L(0.0), View_Rang_Availability_L(false)
	{}

};

struct Right_Status
{
	int	Lane_Type_R;
	int	Quality_R;
	double	Curvature_R;
	double	Position_R;
	double	Width_right_marking;
	double	Heading_Angle_R;
	double	View_Range_R;
	bool	View_Rang_Availability_R	 ;

	Right_Status() : Lane_Type_R(0), Quality_R(0), Curvature_R(0.0), Position_R(0.0), Width_right_marking(0.0),
		Heading_Angle_R(0.0), View_Range_R(0.0), View_Rang_Availability_R(false)
	{}
};

struct ObjInfo_ME
{
	double position_x;
	double position_y;

	ObjInfo_ME() : position_x(0.0), position_y(0.0)
	{}
};

struct ME_DeviceData
{
	int					       selfSpeed;
	GeneralInfo			       generalInfo;
	Obstacle_Status		       obstacleStatus;   
	QMap<int, ObstacleData_A>  mapObstacleDataA;
	QMap<int, ObstacleData_B>  mapObstacleDataB;
	QMap<int, ObstacleData_C>  mapObstacleDataC;
	//line
	Lane_Status   lane_Status;
	Left_Status  left_Status;
	Right_Status right_Status;

	QList<Position> objs;
	//mapObstacleDataA::obstaclePosition at(int numberOfObstacles);
	//Position obstaclePosition
	ME_DeviceData() : selfSpeed(0)
	{
		mapObstacleDataA.clear();
		mapObstacleDataB.clear();
		mapObstacleDataC.clear();
	}


};

#endif // GLOBAL_HEADER_H
