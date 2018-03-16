/* This file has been generated from /home/michiel/paparazzi/conf/airframes/tudelft/bebop_course2018_orangeavoid.xml */
/* Version v5.13_devel-166-gae18987-dirty */
/* Please DO NOT EDIT */

#ifndef MODULES_H
#define MODULES_H

#define MODULES_IDLE  0
#define MODULES_RUN   1
#define MODULES_START 2
#define MODULES_STOP  3

#define MODULES_FREQUENCY 512

#ifdef MODULES_C
#define EXTERN_MODULES
#else
#define EXTERN_MODULES extern
#endif
#include "std.h"
#include "computer_vision/viewvideo.h"
#include "orange_avoider/orange_avoider.h"
#include "computer_vision/colorfilter.h"
#include "computer_vision/video_thread.h"
#include "loggers/file_logger.h"
#include "air_data/air_data.h"
#include "subsystems/ins/ins_int.h"
#include "subsystems/ahrs.h"
#include "stabilization/stabilization_rate.h"
#include "stabilization/stabilization_indi_simple.h"
#include "firmwares/rotorcraft/stabilization.h"
#include "stabilization/stabilization_none.h"
#include "firmwares/rotorcraft/navigation.h"
#include "guidance/guidance_h.h"
#include "guidance/guidance_v.h"
#include "subsystems/gps.h"
#include "subsystems/gps.h"
#include "subsystems/imu/imu_bebop.h"
#include "sonar/sonar_bebop.h"
#include "subsystems/imu.h"
#include "boards/bebop/actuators.h"
#include "subsystems/actuators/motor_mixing.h"
#include "subsystems/radio_control/rc_datalink.h"
#include "datalink/pprz_dl.h"

#define ORANGE_AVOIDER_PERIODIC_PERIOD 0.250000
#define ORANGE_AVOIDER_PERIODIC_FREQ 4.000000
#define VIDEO_THREAD_PERIODIC_PERIOD 1.000000
#define VIDEO_THREAD_PERIODIC_FREQ 1.000000
#define FILE_LOGGER_PERIODIC_PERIOD 0.001953
#define FILE_LOGGER_PERIODIC_FREQ 512.000000
#define AIR_DATA_PERIODIC_PERIOD 0.100000
#define AIR_DATA_PERIODIC_FREQ 10.000000
#define GPS_DATALINK_PERIODIC_CHECK_PERIOD 1.000000
#define GPS_DATALINK_PERIODIC_CHECK_FREQ 1.000000
#define IMU_BEBOP_PERIODIC_PERIOD 0.001953
#define IMU_BEBOP_PERIODIC_FREQ 512.000000

EXTERN_MODULES uint8_t video_thread_video_thread_periodic_status;
EXTERN_MODULES uint8_t logger_file_file_logger_periodic_status;
EXTERN_MODULES uint8_t gps_datalink_gps_datalink_periodic_check_status;


static inline void modules_datalink_init(void) {
  pprz_dl_init();
}

static inline void modules_default_init(void) {
  imu_init();
  sonar_bebop_init();
  imu_bebop_init();
  gps_init();
  gps_datalink_init();
  gps_datalink_gps_datalink_periodic_check_status = MODULES_START;
  guidance_h_init();
  guidance_v_init();
  nav_init();
  stabilization_init();
  stabilization_none_init();
  stabilization_indi_init();
  stabilization_rate_init();
  ins_int_init();
  air_data_init();
  logger_file_file_logger_periodic_status = MODULES_IDLE;
  video_thread_init();
  video_thread_video_thread_periodic_status = MODULES_START;
  colorfilter_init();
  orange_avoider_init();
  viewvideo_init();
}

static inline void modules_actuators_init(void) {
  motor_mixing_init();
}

static inline void modules_init(void) {
  modules_datalink_init();
  modules_default_init();
  modules_actuators_init();
}

static inline void modules_datalink_periodic_task(void) {


}

static inline void modules_default_periodic_task(void) {
  static uint8_t i1; i1++; if (i1>=1) i1=0;
  static uint8_t i51; i51++; if (i51>=51) i51=0;
  static uint8_t i128; i128++; if (i128>=128) i128=0;
  static uint16_t i512; i512++; if (i512>=512) i512=0;






  if (gps_datalink_gps_datalink_periodic_check_status == MODULES_START) {
    gps_datalink_gps_datalink_periodic_check_status = MODULES_RUN;
  }
  if (gps_datalink_gps_datalink_periodic_check_status == MODULES_STOP) {
    gps_datalink_gps_datalink_periodic_check_status = MODULES_IDLE;
  }









  if (logger_file_file_logger_periodic_status == MODULES_START) {
    file_logger_start();
    logger_file_file_logger_periodic_status = MODULES_RUN;
  }
  if (logger_file_file_logger_periodic_status == MODULES_STOP) {
    file_logger_stop();
    logger_file_file_logger_periodic_status = MODULES_IDLE;
  }

  if (video_thread_video_thread_periodic_status == MODULES_START) {
    video_thread_start();
    video_thread_video_thread_periodic_status = MODULES_RUN;
  }
  if (video_thread_video_thread_periodic_status == MODULES_STOP) {
    video_thread_stop();
    video_thread_video_thread_periodic_status = MODULES_IDLE;
  }




  imu_bebop_periodic();
  if (logger_file_file_logger_periodic_status == MODULES_RUN) {
    file_logger_periodic();
  }
  if (i51 == 0) {
    air_data_periodic();
  }
  if (i128 == 25) {
    orange_avoider_periodic();
  }
  if (i512 == 89 && gps_datalink_gps_datalink_periodic_check_status == MODULES_RUN) {
    gps_datalink_periodic_check();
  }
  else if (i512 == 259 && video_thread_video_thread_periodic_status == MODULES_RUN) {
    video_thread_periodic();
  }
}

static inline void modules_actuators_periodic_task(void) {



}

static inline void modules_periodic_task(void) {
  modules_datalink_periodic_task();
  modules_default_periodic_task();
  modules_actuators_periodic_task();
}

static inline void modules_datalink_event_task(void) {
  pprz_dl_event();
}

static inline void modules_default_event_task(void) {
  imu_bebop_event();
}

static inline void modules_actuators_event_task(void) {
}

static inline void modules_event_task(void) {
  modules_datalink_event_task();
  modules_default_event_task();
  modules_actuators_event_task();
}

#ifdef MODULES_DATALINK_C

#include "pprzlink/messages.h"
#include "generated/airframe.h"
static inline void modules_parse_datalink(uint8_t msg_id __attribute__ ((unused)),
                                          struct link_device *dev __attribute__((unused)),
                                          struct transport_tx *trans __attribute__((unused)),
                                          uint8_t *buf __attribute__((unused))) {
  if (msg_id == DL_REMOTE_GPS) { gps_datalink_parse_REMOTE_GPS(); }
  else if (msg_id == DL_REMOTE_GPS_SMALL) { gps_datalink_parse_REMOTE_GPS_SMALL(); }
  else if (msg_id == DL_REMOTE_GPS_LOCAL) { gps_datalink_parse_REMOTE_GPS_LOCAL(); }
}

#endif // MODULES_DATALINK_C

#endif // MODULES_H