#include "telem.c"
#include <dotenv-c/dotenv.c>

int main(void) {

  /*
   *
   * Setup the wrapper
   *
   */
  env_load(".", false); // Load .env file from current directory

  char *client_tty =
      getenv("CLIENT_TTY"); // Load the CLIENT_TTY environment variable

  // Display the initialization messages
  printf("Initializing Telem wrapper\n");
  printf("Using tty: %s\n", client_tty);

  /*
   *
   * Setup the krpc system
   *
   */
  krpc_connection_t conn;
  krpc_schema_Status status;
  krpc_error_t err;
  krpc_SpaceCenter_Vessel_t vessel;

  /*
   *
   * Connect to krpc
   *
   *  NOTE: Use SOCAT to create a pseudo terminal, then you can connect to it.
   * Ensure that KRPC server is setup to be /dev/pts/n+1 and the client is
   * /dev/pts/n
   *
   */
  err = krpc_open(&conn, client_tty);

  if (err != KRPC_OK) {
    fprintf(stderr, "%s\n", krpc_get_error(err));
    return err;
  }

  err = krpc_connect(conn, "Prototype flight computer");

  if (err != KRPC_OK) {
    fprintf(stderr, "%s\n", krpc_get_error(err));
    return err;
  }

  krpc_KRPC_GetStatus(conn, &status);
  printf("Connected to kRPC server version %s\n", status.version);

  /*
   *
   * Initialize the Vessel and Flight Data
   *
   */
  err = krpc_SpaceCenter_ActiveVessel(conn, &vessel);
  if (err != KRPC_OK) {
    fprintf(stderr, "%s\n", krpc_get_error(err));
    return err;
  }

  telem_instance_t telem;
  krpc_init_telem(&telem, &conn, &vessel);

  telem_frame_t frame;

  printf("SIZE OF FRAME: %lu\n", sizeof(telem_frame_t));
  // krpc_poll_telem(&telem, &frame);
  // krpc_dump_telem_frame(&frame);
}
