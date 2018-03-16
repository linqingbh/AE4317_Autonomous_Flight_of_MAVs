/** @file
 *  @brief PPRZLink message header for ENERGY in class telemetry
 *
 *  
 *  @see http://paparazziuav.org
 */

#ifndef _VAR_MESSAGES_telemetry_ENERGY_H_
#define _VAR_MESSAGES_telemetry_ENERGY_H_


#include "pprzlink/pprzlink_device.h"
#include "pprzlink/pprzlink_transport.h"
#include "pprzlink/pprzlink_utils.h"
#include "pprzlink/pprzlink_message.h"


#ifdef __cplusplus
extern "C" {
#endif

#if DOWNLINK

#define DL_ENERGY 37
#define PPRZ_MSG_ID_ENERGY 37

/**
 * Macro that redirect calls to the default version of pprzlink API
 * Used for compatibility between versions.
 */
#define pprzlink_msg_send_ENERGY _send_msg(ENERGY,PPRZLINK_DEFAULT_VER)

/**
 * Sends a ENERGY message (API V2.0 version)
 *
 * @param msg the pprzlink_msg structure for this message
 * @param _bat 
 * @param _amp 
 * @param _energy 
 * @param _power 
 */
static inline void pprzlink_msg_v2_send_ENERGY(struct pprzlink_msg * msg, float *_bat, float *_amp, uint16_t *_energy, float *_power) {
#if PPRZLINK_ENABLE_FD
  long _FD = 0; /* can be an address, an index, a file descriptor, ... */
#endif
  const uint8_t size = msg->trans->size_of(msg, /* msg header overhead */4+4+4+2+4);
  if (msg->trans->check_available_space(msg, _FD_ADDR, size)) {
    msg->trans->count_bytes(msg, size);
    msg->trans->start_message(msg, _FD, /* msg header overhead */4+4+4+2+4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, &(msg->sender_id), 1);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, msg->receiver_id, NULL);
    uint8_t comp_class = (msg->component_id & 0x0F) << 4 | (1 & 0x0F);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, comp_class, NULL);
    msg->trans->put_named_byte(msg, _FD, DL_TYPE_UINT8, DL_FORMAT_SCALAR, DL_ENERGY, "ENERGY");
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _bat, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _amp, 4);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_UINT16, DL_FORMAT_SCALAR, (void *) _energy, 2);
    msg->trans->put_bytes(msg, _FD, DL_TYPE_FLOAT, DL_FORMAT_SCALAR, (void *) _power, 4);
    msg->trans->end_message(msg, _FD);
  } else
        msg->trans->overrun(msg);
}

// Compatibility with the protocol v1.0 API
#define pprzlink_msg_v1_send_ENERGY pprz_msg_send_ENERGY
#define DOWNLINK_SEND_ENERGY(_trans, _dev, bat, amp, energy, power) pprz_msg_send_ENERGY(&((_trans).trans_tx), &((_dev).device), AC_ID, bat, amp, energy, power)
/**
 * Sends a ENERGY message (API V1.0 version)
 *
 * @param trans A pointer to the transport_tx structure used for sending the message
 * @param dev A pointer to the link_device structure through which the message will be sent
 * @param ac_id The id of the sender of the message
 * @param _bat 
 * @param _amp 
 * @param _energy 
 * @param _power 
 */
static inline void pprz_msg_send_ENERGY(struct transport_tx *trans, struct link_device *dev, uint8_t ac_id, float *_bat, float *_amp, uint16_t *_energy, float *_power) {
    struct pprzlink_msg msg;
    msg.trans = trans;
    msg.dev = dev;
    msg.sender_id = ac_id;
    msg.receiver_id = 0;
    msg.component_id = 0;
    pprzlink_msg_v2_send_ENERGY(&msg,_bat,_amp,_energy,_power);
}


#else // DOWNLINK

#define DOWNLINK_SEND_ENERGY(_trans, _dev, bat, amp, energy, power) {}
static inline void pprz_send_msg_ENERGY(struct transport_tx *trans __attribute__((unused)), struct link_device *dev __attribute__((unused)), uint8_t ac_id __attribute__((unused)), float *_bat __attribute__((unused)), float *_amp __attribute__((unused)), uint16_t *_energy __attribute__((unused)), float *_power __attribute__((unused))) {}

#endif // DOWNLINK


/** Getter for field bat in message ENERGY
  *
  * @param _payload : a pointer to the ENERGY message
  * @return 
  */
static inline float pprzlink_get_DL_ENERGY_bat(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 4);
}


/** Getter for field amp in message ENERGY
  *
  * @param _payload : a pointer to the ENERGY message
  * @return 
  */
static inline float pprzlink_get_DL_ENERGY_amp(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 8);
}


/** Getter for field energy in message ENERGY
  *
  * @param _payload : a pointer to the ENERGY message
  * @return 
  */
static inline uint16_t pprzlink_get_DL_ENERGY_energy(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_uint16_t(_payload, 12);
}


/** Getter for field power in message ENERGY
  *
  * @param _payload : a pointer to the ENERGY message
  * @return 
  */
static inline float pprzlink_get_DL_ENERGY_power(uint8_t * _payload __attribute__((unused)))
{
    return _PPRZ_VAL_float(_payload, 14);
}


/* Compatibility macros */
#define DL_ENERGY_bat(_payload) pprzlink_get_DL_ENERGY_bat(_payload)
#define DL_ENERGY_amp(_payload) pprzlink_get_DL_ENERGY_amp(_payload)
#define DL_ENERGY_energy(_payload) pprzlink_get_DL_ENERGY_energy(_payload)
#define DL_ENERGY_power(_payload) pprzlink_get_DL_ENERGY_power(_payload)



#ifdef __cplusplus
}
#endif // __cplusplus

#endif // _VAR_MESSAGES_telemetry_ENERGY_H_

