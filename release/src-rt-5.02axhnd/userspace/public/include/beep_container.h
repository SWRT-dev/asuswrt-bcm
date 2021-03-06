/***********************************************************************
 *
 * Copyright (c) 2017  Broadcom Corporation
 * All Rights Reserved
 *
 * <:label-BRCM:2017:DUAL/GPL:standard
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
 * writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
 * :>
 *
 ************************************************************************/

#ifndef CONTAINER_H
#define CONTAINER_H

#define CONT_BLKIO_MAX_ENTRIES  16
#define CONT_DEV_ACCESS_MAX_ENTRIES  16
#define CONT_DEVICES_MAX_ENTRIES  16
#define CONT_HOOK_POINT_MAX_ENTRIES  16
#define CONT_HOOK_POINT_ARGS_MAX_ENTRIES  16

#define CONT_USERNAME_LEN_MAX    32
#define CONT_CONTNAME_LEN_MAX    64

typedef enum 
{
   CONT_TOOL_LXC = 0,
   CONT_TOOL_DOCKER,
   CONT_TOOL_MAX,
} ContContainerToolType_t;

typedef enum 
{
   CONT_BLKIO_READ_BPS_DEV = 0,
   CONT_BLKIO_WRITE_BPS_DEV,
   CONT_BLKIO_READ_IOPS_DEV,
   CONT_BLKIO_WRITE_IOPS_DEV
} ContBlockIoType_t;

typedef struct
{
   ContBlockIoType_t type;
   long long major;
   long long minor;
   unsigned long long rate;
} ContBlockIo_t;

typedef struct
{
   int allow;
   long long major;
   long long minor;
   char devType[8];
   char accessType[8];
} ContDevAccessList_t;

typedef struct
{
   char type[8];
   char path[32];
   long long major;
   long long minor;
} ContDevicesList_t;

typedef struct contResource_t
{
   unsigned long long cpu;
   long long realtimeRuntime;
   char cpus[64];
   unsigned long long memory;
   unsigned long long flash;
   ContBlockIo_t blkio[CONT_BLKIO_MAX_ENTRIES];
   ContDevAccessList_t devAccess[CONT_DEV_ACCESS_MAX_ENTRIES];
} ContResource_t;

typedef struct
{
   char path[1024];
   char args[CONT_HOOK_POINT_ARGS_MAX_ENTRIES][1024];
   unsigned long long timeout;
} ContHookPoint_t;

typedef struct
{
   ContHookPoint_t presetup[CONT_HOOK_POINT_MAX_ENTRIES];
   ContHookPoint_t prestart[CONT_HOOK_POINT_MAX_ENTRIES];
   ContHookPoint_t poststart[CONT_HOOK_POINT_MAX_ENTRIES];
   ContHookPoint_t poststop[CONT_HOOK_POINT_MAX_ENTRIES];
   int presetupHookEntries;
   int prestartHookEntries;
   int poststartHookEntries;
   int poststopHookEntries;
} ContHooks_t;

typedef struct
{
   ContContainerToolType_t toolType;
   char containerName[CONT_CONTNAME_LEN_MAX];
   char path[1024];
   char appName[64];
   char library[1024];
   char username[CONT_USERNAME_LEN_MAX+1];
   int uid;
   int maxUser;
   int isPrivileged;
   char ntwkBridge[32];
   char ntwkDns[64];
   char ntwkMac[32];
   int fullFS;
   ContResource_t resource;
   ContDevicesList_t devices[CONT_DEVICES_MAX_ENTRIES];
   ContHooks_t hooks;
} ContainerSetup_t;

typedef enum
{
   CONT_MEDIA_TYPE_EXECUTABLE  = 0,   
   CONT_MEDIA_TYPE_TARBALL,
   CONT_MEDIA_TYPE_LAST,
} contMediaType;

typedef enum
{
   CONTRET_SUCCESS = 0,      /**<Success. */
   CONTRET_INTERNAL_ERROR ,  /**< Internal error. */
   CONTRET_SYSTEM_RESOURCE_EXCEEDED ,/**< System resources exceeded */
} ContRet;

int contCreateContainerDir(const char *path, ContContainerToolType_t tool,
                           contMediaType mediaType, char *unpackPath,
                           int unpackPathLen, int limitFlash, int fullFS);
ContRet contSetupContainer(const ContainerSetup_t *conf);
int contRestoreContainer(const char *container_name, const char *path,
                         int isPrivileged, const char *username, 
                         int limitFlash, int fullFS);
int contStopContainer(const char *container_name);
int contStartContainer(const char *path, const char *container_name,
                       int needCMS, int isRoot, int needNetwork);
int contDestroyContainer(const char *container_name, const char *path,
                         int limitFlash, int fullFS);
int contNetworkAddress(const char *container_name, char *addr, int addrLen);
int contGetContainerDataDir(const char *path, int limitFlash, int isEE,
                            char *dataDir, int dataDirLen, int fullFS);
int contGetEeContainerDuDir(const char *path, int limitFlash, int isEE,
                            char *duDir, int duDirLen);
int contCleanupContainerMountPoint(const char *container_name, const char *path,
                                   int limitFlash, int fullFS);

/*****************************************************************************
*  FUNCTION:  contGetContainerNameByPid
*  DESCRIPTION:
*     Get the container name by PID. If pid is 0, the container name of the
*     caller will be returned.  If failed, containerName will be an
*     empty string.
*  PARAMETERS:
*     pid (IN) PID
*     containerName (OUT) container name buffer
*     containerNameSize (IN) container name buffer size
*  RETURNS:
*     void
******************************************************************************
*/
void contGetContainerNameByPid(unsigned int pid,
                               char *containerName, int containerNameSize);

#endif /* #ifndef CONTAINER_H */
