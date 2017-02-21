#ifndef _VELOC_H
#define _VELOC_H

/*---------------------------------------------------------------------------
                                  Defines
---------------------------------------------------------------------------*/

/** Token returned if a VEOC function succeeds.                             */
#define VELOC_SUCCESS (0)
#define VELOC_FAILURE (1)

#define VELOC_MAX_NAME (1024)

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------
                                  New types
---------------------------------------------------------------------------*/

/** @typedef    VELOCT_type
 *  @brief      Type recognized by VELOC.
 *
 *  This type allows handling data structures.
 */
typedef struct VELOCT_type {            /** VELOC type declarator.         */
    int             id;                 /** ID of the data type.           */
    int             size;               /** Size of the data type.         */
} VELOCT_type;

/*---------------------------------------------------------------------------
                                  Global variables
---------------------------------------------------------------------------*/

/** VELOC data type for chars.                                               */
extern VELOCT_type VELOC_CHAR;
/** VELOC data type for short integers.                                      */
extern VELOCT_type VELOC_SHRT;
/** VELOC data type for integers.                                            */
extern VELOCT_type VELOC_INTG;
/** VELOC data type for long integers.                                       */
extern VELOCT_type VELOC_LONG;
/** VELOC data type for unsigned chars.                                      */
extern VELOCT_type VELOC_UCHR;
/** VELOC data type for unsigned short integers.                             */
extern VELOCT_type VELOC_USHT;
/** VELOC data type for unsigned integers.                                   */
extern VELOCT_type VELOC_UINT;
/** VELOC data type for unsigned long integers.                              */
extern VELOCT_type VELOC_ULNG;
/** VELOC data type for single floating point.                               */
extern VELOCT_type VELOC_SFLT;
/** VELOC data type for double floating point.                               */
extern VELOCT_type VELOC_DBLE;
/** VELOC data type for long doble floating point.                           */
extern VELOCT_type VELOC_LDBE;

/*---------------------------------------------------------------------------
                            VELOC public functions
---------------------------------------------------------------------------*/

/**************************
 * Init / Finalize
 *************************/

// initialize the library
//   IN config - specify path to config file, pass NULL if no config file
int VELOC_Init(char *config);

// shut down the library
int VELOC_Finalize();

/**************************
 * Memory registration
 *************************/

// define new memory type for use in VELOC_Mem_protect
//   OUT type - defines a VELOC type for use in calls to Mem_protect (handle)
//   IN  size - size of type in bytes
int VELOC_Mem_type(VELOCT_type* type, int size);

// registers a memory region for checkpoint/restart
//   IN id    - application defined integer label for memory region
//   IN ptr   - pointer to start of memory region
//   IN count - number of consecutive elements in memory region
//   IN type  - type of element in memory region
int VELOC_Mem_protect(int id, void* ptr, long count, VELOCT_type type);

/**************************
 * File registration
 *************************/

// Informs application about path to open a file
// This must either be called between VELOC_Start_restart/VELOC_Complete_restart
// or between VELOC_Start_checkpoint/VELOC_Complete_checkpoint
//   IN  name       - file name of checkpoint file
//   OUT veloc_name - full path application should use when opening the file
int VELOC_Route_file(const char* name, char* veloc_name);

/**************************
 * Restart routines
 *************************/

// determine whether application has checkpoint to read on restart
//   OUT flag - flag returns 1 if there is a checkpoint available to read, 0 otherwise
int VELOC_Have_restart(int* flag);

// mark start of restart phase
int VELOC_Start_restart();

// read checkpoint file contents into registered memory regions
// must be called between VELOC_Start_restart/VELOC_Complete_restart
int VELOC_Mem_restart();

// mark end of restart phase
int VELOC_Complete_restart();

/**************************
 * Checkpoint routines
 *************************/

// determine whether application should checkpoint
//   OUT flag - flag returns 1 if checkpoint should be taken, 0 otherwise
int VELOC_Need_checkpoint(int* flag);

// mark start of a new checkpoint
int VELOC_Start_checkpoint();

// write registered memory regions into a checkpoint file
// must be called between VELOC_Start_checkpoint/VELOC_Complete_checkpoint
int VELOC_Mem_checkpoint();

// mark end of current checkpoint
//   IN valid - calling process should set this flag to 1 if it wrote all checkpoint data successfully
int VELOC_Complete_checkpoint(int valid);

/**************************
 * convenience functions for existing FTI users
 * (implemented with combinations of above functions)
 ************************/

// substitute for FTI_Checkpoint
int VELOC_Mem_save();

// substitute for FTI_Recover
int VELOC_Mem_recover();

// substitute for FTI_Snapshot
int VELOC_Mem_snapshot();

#ifdef __cplusplus
}
#endif

#endif /* ----- #ifndef _VELOC_H  ----- */
