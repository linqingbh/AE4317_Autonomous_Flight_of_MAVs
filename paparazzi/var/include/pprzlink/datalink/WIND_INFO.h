/** @file
 *  @brief PPRZLink message header for WIND_INFO in class datalink
 *
 *  
        Wind information.
        The wind is reported as a vector, it gives the direction the wind is blowing to.
        This can be comming from the ground wind estimator
        or from an embedded algorithm.
        Flags field definition:
        - bit 0: horizontal wind is valid (east and north fields)
        - bit 1: vertical wind is valid (up field)
        - bit 2: airspeed is valid
      
 *  @see http://paparazziuav.org
 */

#ifndef _VAR_MESSAGES_datalink_WIND_INFO_H_
#define _VAR_MESSAGES_datalink_WIND_INFO_H_


#include "pprzlink/pprzlink_device.h"
#include "pprzlink/pprzlink_transport.h"
#include "pprzlink/pprzlink_utils.h"
#include "pprzlink/pprzlink_message.h"


#ifdef __cplusplus
extern "C" {
#endif

#if DOWNLINK

#define DL_WIND_INFO 3
#define PPRZ_MSG_ID_WIND_INFO 3

/**
 * Macro that redirect calls to the default version of pprzlink API
 * Used for compatibility between versions.
 */
#define pprzlink_msg_send_WIND_INFO _send_msg(WIND_INFO,PPRZLINK_DEFAULT_VER)

/**
 * Sends a WIND_INFO message (API V2.0 version)
 *
 * @param msg the pprzlink_msg structure for this message
 * @param _ac_id 
 * @param _flags bit 0: horizontal wind, bit 1: vertical wind: bit 2: airspeed
 * @param _east east component of the wind
 * @param _north north component of the wind
 * @param _up vertical component of the wind
 * @param _airspeed local airspeed norm
 */
static inline void pprzlink_msg_v2_send_WIND_INFO(struct pprzlink_msg * msg, uint8_t *_ac_id, uint8_t *_flags, float *_east, float *_north, float *_up, float *_airspeed) {
#if PPRZLINK_ENABLE_FD
  long _FD = 0; /* can be an address, an index, a file descriptor, ... */
#endif
  const uint8_t size = msg->trans->size_of(msg, /* msg header overhead */4+1+1+4+4+4+4);
  if (msg->trans->check_available_space(msg, _FD_ADDR, size)) {
    msg->trans->count_bytes(msg, size);
    msg->trans->start_message(msg, _FD, /* msg header overhead */4+1+1+4+4+4+4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, &(msg->sender_id), 1);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, msg->receiver_id, NULL);
    uint8_t comp_class = (msg->component_id & 0x0F) << 4 | (2 & 0x0F);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, comp_class, NULL);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, DL_WIND_INFO, "WIND_INFO");
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, (void *) _ac_id, 1);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, (void *) _flags, 1);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _east, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _north, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _up, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _airspeed, 4);
    msg->trans->end_message(msg, _FD);
  } else
        msg->trans->overrun(msg);
}

// Compatibility with the protocol v1.0 API
#define pprzlink_msg_v1_send_WIND_INFO pprz_msg_send_WIND_INFO
#define DOWNLINK_SEND_WIND_INFO(_trans, _dev, ac_id, flags, east, north, up, airspeed) pprz_msg_send_WIND_INFO(&((_trans).trans_tx), &((_dev).device), AC_ID, ac_id, flags, east, north, up, airspeed)
/**
 * Sends a WIND_INFO message (API V1.0 version)
 *
 * @param trans A pointer to the transport_tx structure used for sending the message
 * @param dev A pointer to the link_device structure through which the message will be sent
 * @param ac_id The id of the sender of the message
 * @param _ac_id 
 * @param _flags bit 0: horizontal wind, bit 1: vertical wind: bit 2: airspeed
 * @param _east east component of the wind
 * @param _north north component of the wind
 * @param _up vertical component of the wind
 * @param _airspeed local airspeed norm
 */
static inline void pprz_msg_send_WIND_INFO(struct transport_tx *trans, struct link_device *dev, uint8_t ac_id, uint8_t *_ac_id, uint8_t *_flags, float *_east, float *_north, float *_up, float *_airspeed) {
    struct pprzlink_msg msg;
    msg.trans = trans;
    msg.dev = dev;
    msg.sender_id = ac_id;
    msg.receiver_id = 0;
    msg.component_id = 0;
    pprzlink_msg_v2_send_WIND_INFO(&msg,_ac_id,_flags,_east,_north,_up,_airspeed);
}


#else // DOWNLINK

#define DOWNLINK_SEND_WIND_INFO(_trans, _dev, ac_id, flags, east, north, up, airspeed) {}
static inline void pprz_send_msg_WIND_INFO(struct transport_tx *trans __attribute__((unused)), struct link_device *dev __attribute__((unused)), uint8_t ac_id __attribute__((unused)), uint8_t *_ac_id __attribute__((unused)), uint8_t *_flags __attribute__((unused)), float *_east __attribute__((unused)), float *_north __attribute__((unused)), float *_up __attribute__((unused)), float *_airspeed __attribute__((unused))) {}

#endif // DOWNLINK


/** Getter for field ac_id in message WIND_INFO
  *
  * @param _payload : a pointer to the WIND_INFO message
  * @return 
  */
static inline uint8_t pprzlink_get_DL_WIND_INFO_ac_id(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_uint8_t(_payload, 4);
}


/** Getter for field flags in message WIND_INFO
  *
  * @param _payload : a pointer to the WIND_INFO message
  * @return bit 0: horizontal wind, bit 1: vertical wind: bit 2: airspeed
  */
static inline uint8_t pprzlink_get_DL_WIND_INFO_flags(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_uint8_t(_payload, 5);
}


/** Getter for field east in message WIND_INFO
  *
  * @param _payload : a pointer to the WIND_INFO message
  * @return east component of the wind
  */
static inline float pprzlink_get_DL_WIND_INFO_east(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 6);
}


/** Getter for field north in message WIND_INFO
  *
  * @param _payload : a pointer to the WIND_INFO message
  * @return north component of the wind
  */
static inline float pprzlink_get_DL_WIND_INFO_north(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 10);
}


/** Getter for field up in message WIND_INFO
  *
  * @param _payload : a pointer to the WIND_INFO message
  * @return vertical component of the wind
  */
static inline float pprzlink_get_DL_WIND_INFO_up(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 14);
}


/** Getter for field airspeed in message WIND_INFO
  *
  * @param _payload : a pointer to the WIND_INFO message
  * @return local airspeed norm
  */
static inline float pprzlink_get_DL_WIND_INFO_airspeed(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 18);
}


/* Compatibility macros */
#define DL_WIND_INFO_ac_id(_payload) pprzlink_get_DL_WIND_INFO_ac_id(_payload)
#define DL_WIND_INFO_flags(_payload) pprzlink_get_DL_WIND_INFO_flags(_payload)
#define DL_WIND_INFO_east(_payload) pprzlink_get_DL_WIND_INFO_east(_payload)
#define DL_WIND_INFO_north(_payload) pprzlink_get_DL_WIND_INFO_north(_payload)
#define DL_WIND_INFO_up(_payload) pprzlink_get_DL_WIND_INFO_up(_payload)
#define DL_WIND_INFO_airspeed(_payload) pprzlink_get_DL_WIND_INFO_airspeed(_payload)



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _VAR_MESSAGES_datalink_WIND_INFO_H_
