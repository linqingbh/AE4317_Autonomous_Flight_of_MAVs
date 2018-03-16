/* This file has been generated by gen_radio from /home/michiel/paparazzi/conf/radios/dummy.xml */
/* Version v5.13_devel-166-gae18987-dirty */
/* Please DO NOT EDIT */

#ifndef RADIO_H
#define RADIO_H

#define RADIO_NAME "cockpitMM"

#define RADIO_CTL_NB 1

#define RADIO_FILTER 7

#define RADIO_CTL_A 0
#define RADIO_THROTTLE RADIO_CTL_A

#define RADIO_THROTTLE_NEUTRAL 1120
#define RADIO_THROTTLE_MIN 1120
#define RADIO_THROTTLE_MAX 2000

#define PPM_PULSE_TYPE PPM_PULSE_TYPE_POSITIVE
#define PPM_DATA_MIN_LEN (900ul)
#define PPM_DATA_MAX_LEN (2100ul)
#define PPM_SYNC_MIN_LEN (5000ul)
#define PPM_SYNC_MAX_LEN (15000ul)

#define NormalizePpmFIR(_ppm, _rc) {\
  static uint8_t avg_cpt = 0; /* Counter for averaging */\
  int16_t tmp_radio;\
  tmp_radio = _ppm[RADIO_THROTTLE] - RC_PPM_TICKS_OF_USEC(1120);\
  _rc.values[RADIO_THROTTLE] = tmp_radio * (MAX_PPRZ / (float)(RC_PPM_SIGNED_TICKS_OF_USEC(2000-1120)));\
  Bound(_rc.values[RADIO_THROTTLE], 0, MAX_PPRZ); \
\
  avg_cpt++;\
  if (avg_cpt == RC_AVG_PERIOD) {\
    avg_cpt = 0;\
 }\
}

#define NormalizePpmIIR(_ppm, _rc) {\
  int32_t tmp_radio;\
  int32_t tmp_value;\
\
  tmp_radio = _ppm[RADIO_THROTTLE] - RC_PPM_TICKS_OF_USEC(1120);\
  tmp_value = (tmp_radio * MAX_PPRZ) / (RC_PPM_SIGNED_TICKS_OF_USEC(2000-1120));\
  Bound(tmp_value, 0, MAX_PPRZ); \
  _rc.values[RADIO_THROTTLE] = (pprz_t)(tmp_value);\
\
}


#endif // RADIO_H
