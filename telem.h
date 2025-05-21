/*
 * telem.h
 *
 * Stores function prototypes and constants for the telem.c file.
 *
 * Date Created: 2025-05-10
 * Date Modified: 2025-05-10
 *
 */
#ifndef KRPC_TELEM_H
#define KRPC_TELEM_H

#include <krpc_cnano.h>
#include <krpc_cnano/services/krpc.h>
#include <krpc_cnano/services/space_center.h>

#include <stdint.h>

/*
 *
 * This structure is used as a 'singleton' for telemetry or allows the use of
 * multiple telemetry captures.
 *
 * Current Static Size of the telem_instance_t struct: 16 Bytes
 *
 * This calulations is based on common sizes. For platform specific sizes,
 * please use sizeof on each type on the desired platform.
 *
 */
typedef struct telem_instance_t {
  krpc_connection_t *conn;           // KRPC connection (Size = 8 Bytes)
  krpc_SpaceCenter_Vessel_t *vessel; // KRPC vessel (Size = 8 Bytes)
} telem_instance_t;

/*
 *
 * This structure is used to store the telemetry data from the KRPC for a
 * specific snapshot in time. We are calling it a frame.
 *
 * Current Static Size of the telem_frame_t struct: 100 Bytes
 *
 * This calulations is based on common sizes. For platform specific sizes,
 * please use sizeof on each type on the desired platform.
 * If we sampled the telemetry 60 times persecond, this would be 6.00 KB/s of
 * data. This means 360 KB/minute of data, 21.60 MB/hour of data, and 518.40
 * MB/day
 */
typedef struct telem_frame_t {
  time_t time;            // Time of the telemetry frame (Size = 8 Bytes)
  bool sas;               // SAS Enabled Flag (Size = 1 Byte)
  int sas_mode;           // What mode the SAS in from 0-7 (Size = 1 Byte)
  bool rcs;               // RCS Enabled Flag (Size = 1 Byte)
  double met;             // Mission Elapsed Time (Size = 8 Bytes)
  float thrust;           // Current thrust of the vessel (Size = 4 Bytes)
  float specific_impulse; // Current specific impulse of the vessel (Size = 4
                          // Bytes)
  float g_force;          // Current g-force of the vessel (Size = 4 Bytes)
  float mean_altitude;    // Mean altitude of the vessel (Size = 4 Bytes)
  float surface_altitude; // Surface altitude of the vessel (Size = 4 Bytes)
  float orbit_speed;   // Current speed of the vessel in orbit (Size = 4 Bytes)
  float surface_speed; // Current speed of the vessel (Size = 4 Bytes)
  float rotation;      // Current rotation of the vessel (Size = 4 Bytes)
  float direction;     // Current direction of the vessel (Size = 4 Bytes)
  float pitch;         // Current pitch of the vessel (Size = 4 Bytes)
  float heading;       // Current heading of the vessel (Size = 4 Bytes)
  bool abort;          // Abort flag (Size = 1 Byte)
  float throttle;      // Current throttle of the vessel (SIze = 4 Bytes)
  int32_t stage;       // Current stage of the vessel (Size = 32 Bytes)
} telem_frame_t;

/*
 *
 * Init assumes either a pointer to stack variable, or a point to a heap
 * variable that is allocated.
 */
void krpc_init_telem(telem_instance_t *telem, krpc_connection_t *conn,
                     krpc_SpaceCenter_Vessel_t *vessel);
/*
 *
 * Poll the Vessel and Flight data from KRPC and store it in the telem_frame_t
 */
krpc_error_t krpc_poll_telem(telem_instance_t *telem, telem_frame_t *frame);

/*
 *
 * Dump the telemetry frame to the console.
 */
void krpc_dump_telem_frame(telem_frame_t *frame);

#endif // KRPC_TELEM_H
