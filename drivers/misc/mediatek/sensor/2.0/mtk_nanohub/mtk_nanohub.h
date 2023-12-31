/* SPDX-License-Identifier: GPL-2.0 */
/*
 * Copyright (C) 2020 MediaTek Inc.
 */

#ifndef SCP_SENSOR_HUB_H
#define SCP_SENSOR_HUB_H

#include <linux/ioctl.h>

#define EVT_NO_SENSOR_CONFIG_EVENT 0x00000300
#define SENSOR_RATE_ONCHANGE       0xFFFFFF01UL
#define SENSOR_RATE_ONESHOT        0xFFFFFF02UL

enum {
	CONFIG_CMD_DISABLE      = 0,
	CONFIG_CMD_ENABLE       = 1,
	CONFIG_CMD_FLUSH        = 2,
	CONFIG_CMD_CFG_DATA     = 3,
	CONFIG_CMD_CALIBRATE    = 4,
	CONFIG_CMD_SELF_TEST    = 5,
};

struct ConfigCmd {
	uint32_t evtType;
	uint64_t latency;
	uint32_t rate;
	uint8_t sensorType;
	uint8_t cmd;
	uint16_t flags;
	uint8_t data[];
} __packed;

struct SensorState {
	uint64_t latency;
	uint32_t rate;
	uint8_t sensorType;
	uint8_t alt;
	bool enable;
	int flushcnt;
	uint32_t gain;
	char name[16];
	char vendor[16];
};

#define SCP_SENSOR_HUB_SUCCESS       0
#define SCP_SENSOR_HUB_FAILURE      (-1)

#define SCP_SENSOR_HUB_X             0
#define SCP_SENSOR_HUB_Y             1
#define SCP_SENSOR_HUB_Z             2
#define SCP_SENSOR_HUB_AXES_NUM      3

/* SCP_ACTION */
#define SENSOR_HUB_ACTIVATE          0
#define SENSOR_HUB_SET_DELAY         1
#define SENSOR_HUB_GET_DATA          2
#define SENSOR_HUB_BATCH             3
#define SENSOR_HUB_SET_CONFIG        4
#define SENSOR_HUB_SET_CUST          5
#define SENSOR_HUB_NOTIFY            6
#define SENSOR_HUB_BATCH_TIMEOUT     7
#define SENSOR_HUB_SET_TIMESTAMP     8
#define SENSOR_HUB_POWER_NOTIFY      9
#define SENSOR_HUB_RAW_DATA          10

/* SCP_NOTIFY EVENT */
#define SCP_INIT_DONE                0
#define SCP_FIFO_FULL                1
#define SCP_NOTIFY                   2
#define SCP_BATCH_TIMEOUT            3
#define SCP_DIRECT_PUSH              4

enum {
	SENSOR_POWER_UP = 0,
	SENSOR_POWER_DOWN,
};

struct sensor_vec_t {
	union {
		struct {
			int32_t x;
			int32_t y;
			int32_t z;
			int32_t x_bias;
			int32_t y_bias;
			int32_t z_bias;
			int32_t reserved : 14;
			int32_t temp_result : 2;
			int32_t temperature : 16;
		};
		struct {
			int32_t azimuth;
			int32_t pitch;
			int32_t roll;
			int32_t scalar;
		};
	};
	uint32_t status;
};

struct heart_rate_event_t {
	int32_t bpm;
	int32_t status;
};

struct significant_motion_event_t {
	int32_t state;
};

struct step_counter_event_t {
	uint32_t accumulated_step_count;
};

struct step_detector_event_t {
	uint32_t step_detect;
};

struct floor_counter_event_t {
	uint32_t accumulated_floor_count;
};

enum gesture_type_t {
	GESTURE_NONE,
	SHAKE,
	TAP,
	TWIST,
	FLIP,
	SNAPSHOT,
	PICKUP,
	CHECK
};

struct gesture_t {
	int32_t probability;
};

struct pedometer_event_t {
	uint32_t accumulated_step_count;
	uint32_t accumulated_step_length;
	uint32_t step_frequency;
	uint32_t step_length;
};

struct pressure_vec_t {
	int32_t pressure;	/* Pa, i.e. hPa * 100 */
	int32_t temperature;
	uint32_t status;
};

struct proximity_vec_t {
	uint32_t steps;
	int32_t oneshot;
};

struct relative_humidity_vec_t {
	int32_t relative_humidity;
	int32_t temperature;
	uint32_t status;
};

struct sleepmonitor_event_t {
	int32_t state;		/* sleep, restless, awake */
};

enum fall_type {
	FALL_NONE,
	FALL,
	FLOP,
	FALL_MAX
};

struct fall_t {
	uint8_t probability[FALL_MAX];	/* 0~100 */
};

struct tilt_event_t {
	int32_t state;		/* 0,1 */
};

struct in_pocket_event_t {
	int32_t state;		/* 0,1 */
};

struct geofence_event_t {
	uint32_t state;  /* geofence [source, result, operation_mode] */
};

struct sar_event_t {
	struct {
		int32_t data[3];
		int32_t x_bias;
		int32_t y_bias;
		int32_t z_bias;
	};
	uint32_t status;
};

enum activity_type_t {
	STILL,
	STANDING,
	SITTING,
	LYING,
	ON_FOOT,
	WALKING,
	RUNNING,
	CLIMBING,
	ON_BICYCLE,
	IN_VEHICLE,
	TILTING,
	UNKNOWN,
	ACTIVITY_MAX
};

struct activity_t {
	uint8_t probability[ACTIVITY_MAX];	/* 0~100 */
};

struct data_unit_t {
	uint8_t sensor_type;
	uint8_t flush_action;
	uint8_t reserve[2];
	uint64_t time_stamp;
	union {
		struct sensor_vec_t accelerometer_t;
		struct sensor_vec_t gyroscope_t;
		struct sensor_vec_t magnetic_t;
		struct sensor_vec_t orientation_t;
		struct sensor_vec_t pdr_event;

		int32_t light;
		struct proximity_vec_t proximity_t;
		int32_t temperature;
		struct pressure_vec_t pressure_t;
		struct relative_humidity_vec_t relative_humidity_t;

		struct sensor_vec_t uncalibrated_acc_t;
		struct sensor_vec_t uncalibrated_mag_t;
		struct sensor_vec_t uncalibrated_gyro_t;

		struct pedometer_event_t pedometer_t;

		struct heart_rate_event_t heart_rate_t;
		struct significant_motion_event_t smd_t;
		struct step_detector_event_t step_detector_t;
		struct step_counter_event_t step_counter_t;
		struct floor_counter_event_t floor_counter_t;
		struct activity_t activity_data_t;
		struct gesture_t gesture_data_t;
		struct fall_t fall_data_t;
		struct tilt_event_t tilt_event;
		struct in_pocket_event_t inpocket_event;
		struct geofence_event_t geofence_data_t;
		struct sar_event_t sar_event;
/* begin, prize-lifenfen-20181126, add for sensorhub hardware info */
#ifdef CONFIG_SENSORHUB_PRIZE_HARDWARE_INFO
#ifdef CONFIG_SENSORHUB_PRIZE_HARDWARE_INFO_SIZE
		int32_t data[14];
#else
		int32_t data[8];
#endif
#else
		int32_t data[8];
#endif
/* end, prize-lifenfen-20181126, add for sensorhub hardware info */
	};
} __packed;

struct sensor_fifo {
	uint32_t rp;
	uint32_t wp;
	uint32_t fifo_size;
	uint32_t reserve;
	struct data_unit_t data[0];
};

struct SCP_SENSOR_HUB_REQ {
	uint8_t sensorType;
	uint8_t action;
	uint8_t reserve[2];
/* begin, prize-lifenfen-20181126, add for sensorhub hardware info */
#ifdef CONFIG_SENSORHUB_PRIZE_HARDWARE_INFO
#ifdef CONFIG_SENSORHUB_PRIZE_HARDWARE_INFO_SIZE
	uint32_t data[17];
#else
	uint32_t data[11];
#endif
#else
	uint32_t data[11];
#endif
/* end, prize-lifenfen-20181126, add for sensorhub hardware info */
};

struct SCP_SENSOR_HUB_RSP {
	uint8_t sensorType;
	uint8_t action;
	int8_t errCode;
	uint8_t reserve[1];
	/* uint32_t    reserved[9]; */
};

struct SCP_SENSOR_HUB_ACTIVATE_REQ {
	uint8_t sensorType;
	uint8_t action;
	uint8_t reserve[2];
	uint32_t enable;	/* 0 : disable ; 1 : enable */
	/* uint32_t    reserved[9]; */
};

#define SCP_SENSOR_HUB_ACTIVATE_RSP SCP_SENSOR_HUB_RSP
/* typedef SCP_SENSOR_HUB_RSP SCP_SENSOR_HUB_ACTIVATE_RSP; */

struct SCP_SENSOR_HUB_SET_DELAY_REQ {
	uint8_t sensorType;
	uint8_t action;
	uint8_t reserve[2];
	uint32_t delay;		/* ms */
	/* uint32_t    reserved[9]; */
};

#define SCP_SENSOR_HUB_SET_DELAY_RSP  SCP_SENSOR_HUB_RSP
/* typedef SCP_SENSOR_HUB_RSP SCP_SENSOR_HUB_SET_DELAY_RSP; */

struct SCP_SENSOR_HUB_GET_DATA_REQ {
	uint8_t sensorType;
	uint8_t action;
	uint8_t reserve[2];
	/* uint32_t    reserved[10]; */
};

struct SCP_SENSOR_HUB_GET_DATA_RSP {
	uint8_t sensorType;
	uint8_t action;
	int8_t errCode;
	uint8_t reserve[1];
	/* struct data_unit_t data_t; */
	union {
		int8_t int8_Data[0];
		int16_t int16_Data[0];
		int32_t int32_Data[0];
	} data;
};

struct SCP_SENSOR_HUB_BATCH_REQ {
	uint8_t sensorType;
	uint8_t action;
	uint8_t flag;
	uint8_t reserve[1];
	uint32_t period_ms;	/* batch reporting time in ms */
	uint32_t timeout_ms;	/* sampling time in ms */
	/* uint32_t    reserved[7]; */
};

#define SCP_SENSOR_HUB_BATCH_RSP SCP_SENSOR_HUB_RSP
/* typedef SCP_SENSOR_HUB_RSP SCP_SENSOR_HUB_BATCH_RSP; */

struct SCP_SENSOR_HUB_SET_CONFIG_REQ {
	uint8_t sensorType;
	uint8_t action;
	uint8_t reserve[2];
	/* struct sensorFIFO   *bufferBase; */
	uint32_t bufferBase;/* use int to store buffer DRAM base LSB 32 bits */
	uint32_t bufferSize;
	uint64_t ap_timestamp;
	uint64_t arch_counter;
	/* uint32_t    reserved[8]; */
};

#define SCP_SENSOR_HUB_SET_CONFIG_RSP  SCP_SENSOR_HUB_RSP
/* typedef SCP_SENSOR_HUB_RSP SCP_SENSOR_HUB_SET_CONFIG_RSP; */

enum CUST_ACTION {
	CUST_ACTION_SET_CUST = 1,
	CUST_ACTION_SET_CALI,
	CUST_ACTION_RESET_CALI,
	CUST_ACTION_SET_TRACE,
	CUST_ACTION_SET_DIRECTION,
	CUST_ACTION_SHOW_REG,
	CUST_ACTION_GET_RAW_DATA,
	CUST_ACTION_SET_PS_THRESHOLD,
	CUST_ACTION_SHOW_ALSLV,
	CUST_ACTION_SHOW_ALSVAL,
	CUST_ACTION_SET_FACTORY,
	CUST_ACTION_GET_SENSOR_INFO,
/* begin, prize-lifenfen-20181126, add for sensorhub hardware info,begin */
#ifdef CONFIG_SENSORHUB_PRIZE_HARDWARE_INFO
	CUST_ACTION_GET_PRIZE_HARDWARE_INFO,
#endif
/* begin, prize-lifenfen-20181126, add for sensorhub hardware info,end */
/* prize modified by gongtaitao for send lcm param to light sensor 20221031 start */
	CUST_ACTION_SET_ALS_PARAM,
/* prize modified by gongtaitao for send lcm param to light sensor 20221031 end */
};

struct SCP_SENSOR_HUB_CUST {
	enum CUST_ACTION action;
};

struct SCP_SENSOR_HUB_SET_CUST {
	enum CUST_ACTION action;
	int32_t data[0];
};

struct SCP_SENSOR_HUB_SET_TRACE {
	enum CUST_ACTION action;
	int trace;
};

struct SCP_SENSOR_HUB_SET_DIRECTION {
	enum CUST_ACTION action;
	int direction;
};

struct SCP_SENSOR_HUB_SET_FACTORY {
	enum CUST_ACTION	action;
	unsigned int	factory;
};

struct SCP_SENSOR_HUB_SET_CALI {
	enum CUST_ACTION action;
	union {
		int8_t int8_data[0];
		uint8_t uint8_data[0];
		int16_t int16_data[0];
		uint16_t uint16_data[0];
		int32_t int32_data[0];
		uint32_t uint32_data[SCP_SENSOR_HUB_AXES_NUM];
	};
};

#define SCP_SENSOR_HUB_RESET_CALI   SCP_SENSOR_HUB_CUST
/* typedef SCP_SENSOR_HUB_CUST SCP_SENSOR_HUB_RESET_CALI; */

struct SCP_SENSOR_HUB_SETPS_THRESHOLD {
	enum CUST_ACTION action;
	int32_t threshold[2];
};

#define SCP_SENSOR_HUB_SHOW_REG    SCP_SENSOR_HUB_CUST
#define SCP_SENSOR_HUB_SHOW_ALSLV  SCP_SENSOR_HUB_CUST
#define SCP_SENSOR_HUB_SHOW_ALSVAL SCP_SENSOR_HUB_CUST
/*
 * typedef SCP_SENSOR_HUB_CUST SCP_SENSOR_HUB_SHOW_REG;
 * typedef SCP_SENSOR_HUB_CUST SCP_SENSOR_HUB_SHOW_ALSLV;
 * typedef SCP_SENSOR_HUB_CUST SCP_SENSOR_HUB_SHOW_ALSVAL;
 */

struct SCP_SENSOR_HUB_GET_RAW_DATA {
	enum CUST_ACTION action;
	union {
		int8_t int8_data[0];
		uint8_t uint8_data[0];
		int16_t int16_data[0];
		uint16_t uint16_data[0];
		int32_t int32_data[0];
		uint32_t uint32_data[SCP_SENSOR_HUB_AXES_NUM];
	};
};

struct mag_dev_info_t {
	char libname[16];
	int8_t layout;
	int8_t deviceid;
};

struct sensorInfo_t {
	char name[16];
	struct mag_dev_info_t mag_dev_info;
};

struct scp_sensor_hub_get_sensor_info {
	enum CUST_ACTION action;
	union {
		int32_t int32_data[0];
		struct sensorInfo_t sensorInfo;
	};
};
/* begin, prize-lifenfen-20181126, add for sensorhub hardware info*/
#ifdef CONFIG_SENSORHUB_PRIZE_HARDWARE_INFO
#ifdef CONFIG_SENSORHUB_PRIZE_HARDWARE_INFO_SIZE
struct sensor_hardware_info_t {
	char chip[16];
	char vendor[16];
	char id[16];
	char more[16];
};
#else
struct sensor_hardware_info_t {
	char chip[8];
	char vendor[8];
	char id[8];
	char more[8];
};
#endif
struct scp_sensor_hub_get_sensor_hardware_info {
	enum CUST_ACTION action;
	union {
		int32_t int32_data[0];
		struct sensor_hardware_info_t hardwareInfo;
	};
};
#endif
/* end, prize-lifenfen-20181126, add for sensorhub hardware info */

/* prize modified by gongtaitao for send lcm param to light sensor 20221031 start */
struct SCP_SENSOR_HUB_SET_ALS_PARAM {
	enum CUST_ACTION action;
	uint16_t lcm_param[4];
};
/* prize modified by gongtaitao for send lcm param to light sensor 20221031 end */

enum {
	USE_OUT_FACTORY_MODE = 0,
	USE_IN_FACTORY_MODE
};

struct SCP_SENSOR_HUB_SET_CUST_REQ {
	uint8_t sensorType;
	uint8_t action;
	uint8_t reserve[2];
	union {
		uint32_t custData[11];
		struct SCP_SENSOR_HUB_CUST cust;
		struct SCP_SENSOR_HUB_SET_CUST setCust;
		struct SCP_SENSOR_HUB_SET_CALI setCali;
		struct SCP_SENSOR_HUB_RESET_CALI resetCali;
		struct SCP_SENSOR_HUB_SET_TRACE setTrace;
		struct SCP_SENSOR_HUB_SET_DIRECTION setDirection;
		struct SCP_SENSOR_HUB_SHOW_REG showReg;
		struct SCP_SENSOR_HUB_GET_RAW_DATA getRawData;
		struct SCP_SENSOR_HUB_SETPS_THRESHOLD setPSThreshold;
		struct SCP_SENSOR_HUB_SHOW_ALSLV showAlslv;
		struct SCP_SENSOR_HUB_SHOW_ALSVAL showAlsval;
		struct SCP_SENSOR_HUB_SET_FACTORY setFactory;
		struct scp_sensor_hub_get_sensor_info getInfo;
/* begin, prize-lifenfen-20181126, add for sensorhub hardware info */
#ifdef CONFIG_SENSORHUB_PRIZE_HARDWARE_INFO
		struct scp_sensor_hub_get_sensor_hardware_info gethardwareInfo;
#endif
/* end, prize-lifenfen-20181126, add for sensorhub hardware info*/
/* prize modified by gongtaitao for send lcm param to light sensor 20221031 start */
		struct SCP_SENSOR_HUB_SET_ALS_PARAM setAlsData;
/* prize modified by gongtaitao for send lcm param to light sensor 20221031 end */
	};
};

struct SCP_SENSOR_HUB_SET_CUST_RSP {
	uint8_t sensorType;
	uint8_t action;
	uint8_t errCode;
	uint8_t reserve[1];
	union {
		uint32_t custData[11];
		struct SCP_SENSOR_HUB_GET_RAW_DATA getRawData;
		struct scp_sensor_hub_get_sensor_info getInfo;
/* begin, prize-lifenfen-20181126, add for sensorhub hardware info */
#ifdef CONFIG_SENSORHUB_PRIZE_HARDWARE_INFO
		struct scp_sensor_hub_get_sensor_hardware_info gethardwareInfo;
#endif
/* end, prize-lifenfen-20181126, add for sensorhub hardware info */
	};
};

struct SCP_SENSOR_HUB_NOTIFY_RSP {
	uint8_t sensorType;
	uint8_t action;
	uint8_t event;
	uint8_t reserve[1];
	union {
		int8_t		int8_Data[0];
		int16_t		int16_Data[0];
		int32_t		int32_Data[0];
		struct {
			uint32_t	currWp;
			uint64_t	scp_timestamp;
			uint64_t	arch_counter;
		};
	};
};

union SCP_SENSOR_HUB_DATA {
	struct SCP_SENSOR_HUB_REQ req;
	struct SCP_SENSOR_HUB_RSP rsp;
	struct SCP_SENSOR_HUB_ACTIVATE_REQ activate_req;
	struct SCP_SENSOR_HUB_ACTIVATE_RSP activate_rsp;
	struct SCP_SENSOR_HUB_SET_DELAY_REQ set_delay_req;
	struct SCP_SENSOR_HUB_SET_DELAY_RSP set_delay_rsp;
	struct SCP_SENSOR_HUB_GET_DATA_REQ get_data_req;
	struct SCP_SENSOR_HUB_GET_DATA_RSP get_data_rsp;
	struct SCP_SENSOR_HUB_BATCH_REQ batch_req;
	struct SCP_SENSOR_HUB_BATCH_RSP batch_rsp;
	struct SCP_SENSOR_HUB_SET_CONFIG_REQ set_config_req;
	struct SCP_SENSOR_HUB_SET_CONFIG_RSP set_config_rsp;
	struct SCP_SENSOR_HUB_SET_CUST_REQ set_cust_req;
	struct SCP_SENSOR_HUB_SET_CUST_RSP set_cust_rsp;
	struct SCP_SENSOR_HUB_NOTIFY_RSP notify_rsp;
};

/* prize modified by gongtaitao for send lcm param to light sensor 20221207 start */
typedef struct {
    int16_t brightness;
    int16_t pixelR;
    int16_t pixelG;
    int16_t pixelB;
} send_pixel_data;
/* prize modified by gongtaitao for send lcm param to light sensor 20221207 end */
#endif
