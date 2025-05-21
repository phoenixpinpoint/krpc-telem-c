#include "telem.h"
#include <krpc_cnano/error.h>

// Initialize a specific telemetry instance.
void krpc_init_telem(telem_instance_t *telem, krpc_connection_t *conn,
                     krpc_SpaceCenter_Vessel_t *vessel) {
  telem->conn = conn;
  telem->vessel = vessel;
}

krpc_error_t krpc_poll_telem(telem_instance_t *telem, telem_frame_t *frame) {

  krpc_error_t err = KRPC_OK;
  krpc_SpaceCenter_Flight_t obt_flight;
  krpc_SpaceCenter_Flight_t srf_flight;
  krpc_SpaceCenter_Control_t control;
  krpc_SpaceCenter_SASMode_t sas_mode;
  krpc_SpaceCenter_CelestialBody_t celestial_body;
  // krpc_SpaceCenter_ReferenceFrame_t ref_frame;
  krpc_SpaceCenter_ReferenceFrame_t obt_frame;
  krpc_SpaceCenter_ReferenceFrame_t srf_frame;

  // Initialize the Reference Frames
  krpc_SpaceCenter_CelestialBody_NonRotatingReferenceFrame(
      *telem->conn, &obt_frame, celestial_body);
  krpc_SpaceCenter_CelestialBody_ReferenceFrame(*telem->conn, &srf_frame,
                                                celestial_body);

  // Get the Vessel Control
  err = krpc_SpaceCenter_Vessel_Control(*telem->conn, &control, *telem->vessel);
  if (err != KRPC_OK) {
    return err;
  }

  err = krpc_SpaceCenter_Control_SAS(*telem->conn, &frame->sas, control);
  if (err != KRPC_OK) {
    return err;
  }

  err = krpc_SpaceCenter_Control_SASMode(*telem->conn, &sas_mode, control);
  if (err != KRPC_OK) {
    return err;
  }
  frame->sas_mode = (int)sas_mode;

  err = krpc_SpaceCenter_Control_RCS(*telem->conn, &frame->rcs, control);
  if (err != KRPC_OK) {
    return err;
  }

  // Get the Vessel Mission Elapsed Time
  err = krpc_SpaceCenter_Vessel_MET(*telem->conn, &frame->met, *telem->vessel);
  if (err != KRPC_OK) {
    return err;
  }

  // Get the Vessel SAS Status
  err = krpc_SpaceCenter_Control_SAS(*telem->conn, &frame->sas, control);
  if (err != KRPC_OK) {
    return err;
  }

  // Get the Vessel SAS Mode
  err = krpc_SpaceCenter_Control_SASMode(*telem->conn, &sas_mode, control);
  if (err != KRPC_OK) {
    return err;
  }

  // Get the Vessel RCS Status
  err = krpc_SpaceCenter_Control_RCS(*telem->conn, &frame->rcs, control);
  if (err != KRPC_OK) {
    return err;
  }

  // Get the Vessel Thrust
  err = krpc_SpaceCenter_Vessel_Thrust(*telem->conn, &frame->thrust,
                                       *telem->vessel);
  if (err != KRPC_OK) {
    return err;
  }

  // Get the Vessel Specific Impulse
  err = krpc_SpaceCenter_Vessel_SpecificImpulse(
      *telem->conn, &frame->specific_impulse, *telem->vessel);
  if (err != KRPC_OK) {
    return err;
  }

  // Get the Vessel G-Force
  err =
      krpc_SpaceCenter_Flight_GForce(*telem->conn, &frame->g_force, srf_flight);
  if (err != KRPC_OK) {
    return err;
  }

  /*

  krpc_SpaceCenter_Vessel_Flight(conn, &flight, vessel, obt_frame);

  krpc_SpaceCenter_Flight_Speed(conn, &obt_speed, flight);
  krpc_SpaceCenter_Vessel_Flight(conn, &flight, vessel, srf_frame);
  krpc_SpaceCenter_Flight_Speed(conn, &srf_speed, flight);
  krpc_SpaceCenter_Flight_GForce(conn, &g_force, flight);
  krpc_SpaceCenter_Flight_MeanAltitude(conn, &alt_msl, flight);
  krpc_SpaceCenter_Flight_SurfaceAltitude(conn, &alt_surf, flight);
  krpc_SpaceCenter_Vessel_Position(conn, &orbit_pos, vessel, obt_frame);
  krpc_SpaceCenter_Vessel_Position(conn, &srf_pos, vessel, srf_frame);

  */

  return err;
}

void krpc_dump_telem_frame(telem_frame_t *frame) {
  printf("Time: %ld\n", frame->time);
  printf("SAS: %d\n", frame->sas);
  printf("SAS Mode: %d\n", frame->sas_mode);
  printf("RCS: %d\n", frame->rcs);
  printf("MET: %f\n", frame->met);
  printf("Thrust: %f\n", frame->thrust);
  printf("Specific Impulse: %f\n", frame->specific_impulse);
  printf("G-Force: %f\n", frame->g_force);
  printf("Mean Altitude: %f\n", frame->mean_altitude);
  printf("Surface Altitude: %f\n", frame->surface_altitude);
  printf("Orbit Speed: %f\n", frame->orbit_speed);
  printf("Surface Speed: %f\n", frame->surface_speed);
  printf("Rotation: %f\n", frame->rotation);
  printf("Direction: %f\n", frame->direction);
  printf("Pitch: %f\n", frame->pitch);
  printf("Heading: %f\n", frame->heading);
  printf("Abort: %d\n", frame->abort);
  printf("Throttle: %f\n", frame->throttle);
  printf("Stage: %d\n", frame->stage);
}
