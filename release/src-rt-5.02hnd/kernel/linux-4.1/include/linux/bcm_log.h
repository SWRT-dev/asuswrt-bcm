#if defined(CONFIG_BCM_KF_LOG)
/*
* <:copyright-BRCM:2012:DUAL/GPL:standard
* 
*    Copyright (c) 2012 Broadcom 
*    All Rights Reserved
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
:>
*/
#ifndef _BCM_LOG_SERVICES_
#define _BCM_LOG_SERVICES_

#if !defined(__KERNEL__)
#include <stdint.h>             /**< ISO C99 7.18 Integer Types */
#include <stdio.h>
#include <string.h>
#endif

#include <linux/bcm_log_mod.h>

#if defined(__KERNEL__)
#define bcmPrint            printk
#else
#define bcmPrint            printf
#define BUG()               do { } while(0)
#define EXPORT_SYMBOL(sym)
#endif

/*********
 *********
 * Private:
 *********
 *********/


#define IN /*Input parameters*/
#define OUT /*Output parameters*/
#define INOUT /*Input/Output parameters*/

/*
 * This block of defines selects supported functionality for everything
 * that includes bcm_log.h.  Selection of functionality will eventually
 * be moved to make menuconfig.  CONFIG_BRCM_COLORIZE_PRINTS is already
 * in make menuconfig, but it is locally disabled here.
 */
#ifdef CONFIG_BCM_LOG
#undef CONFIG_BRCM_COLORIZE_PRINTS
#define BCM_ASSERT_SUPPORTED
#define BCM_LOG_SUPPORTED
#define BCM_DATADUMP_SUPPORTED
#define BCM_ERROR_SUPPORTED
#undef BCM_SNAPSHOT_SUPPORTED
#endif /* CONFIG_BCM_LOG */

#include <linux/bcm_colors.h>

#if defined(BCM_ASSERT_SUPPORTED)
#define BCM_ASSERTCODE(code)    code
#else
#define BCM_ASSERTCODE(code)
#endif /*defined(BCM_ASSERT_SUPPORTED)*/

#if defined(BCM_LOG_SUPPORTED)
#define BCM_LOGCODE(code)    code
#else
#define BCM_LOGCODE(code)
#endif /*defined(BCM_LOG_SUPPORTED)*/

#if defined(BCM_ERROR_SUPPORTED)
#define BCM_ERRORCODE(code)    code
#else
#define BCM_ERRORCODE(code)
#endif /*defined(BCM_ERROR_SUPPORTED)*/

#if defined(BCM_DATADUMP_SUPPORTED)
#define BCM_DATADUMPCODE(code)    code
#else
#define BCM_DATADUMPCODE(code) 0
#endif /*defined(BCM_DATADUMP_SUPPORTED)*/

#if defined(BCM_SNAPSHOT_SUPPORTED)
#define BCM_SNAPSHOTCODE(code)    code
#else
#define BCM_SNAPSHOTCODE(code) 0
#endif /*defined(BCM_SNAPSHOT_SUPPORTED)*/

typedef enum {
    BCM_LOG_DD_IMPORTANT=0,
    BCM_LOG_DD_INFO,
    BCM_LOG_DD_DETAIL,
    BCM_LOG_DD_MAX
} bcmLogDataDumpLevel_t;

typedef void (*bcmLogLevelChangeCallback_t)(bcmLogId_t logId, bcmLogLevel_t level, void *ctx);

typedef struct {
    bcmLogId_t logId;
    char *name;
    bcmLogLevel_t logLevel;
    bcmLogDataDumpLevel_t ddLevel;
    bcmLogLevelChangeCallback_t lcCallback;
    void * lcCallbackCtx;
} bcmLogModuleInfo_t;

typedef struct
{
    int (*reserveSlave)(int busNum, int slaveId, int maxFreq);
    int (*syncTrans)(unsigned char *txBuf, unsigned char *rxBuf, int prependcnt, int nbytes, int busNum, int slaveId);
    int (*kerSysSlaveWrite)(int dev, unsigned int addr, unsigned int data, unsigned int len);
    int (*kerSysSlaveRead)(int dev, unsigned int addr, unsigned int *data, unsigned int len);
    int (*bpGet6829PortInfo)( unsigned char *portInfo6829 );
    
} bcmLogSpiCallbacks_t;


/********
 ********
 * Public: service API offered by LOGdriver to other drivers
 ********
 ********/

/**
 * Logging API: Activate by #defining BCM_LOG_SUPPORTED
 **/

#if defined(BCM_LOG_SUPPORTED)
bcmLogModuleInfo_t *bcmLog_logIsEnabled(bcmLogId_t logId, bcmLogLevel_t logLevel);
#else
#define bcmLog_logIsEnabled(arg1, arg2) 0
#endif

#define BCM_LOG_FUNC(logId)                     \
    BCM_LOG_DEBUG((logId), " ")

#define BCM_LOG_DEBUG(logId, fmt, arg...)                               \
    BCM_LOGCODE( do { bcmLogModuleInfo_t *_pModInfo = bcmLog_logIsEnabled(logId, BCM_LOG_LEVEL_DEBUG); \
                      if (_pModInfo)                                              \
                          bcmPrint(CLRm "[DBG " "%s" "] %-10s: " fmt CLRnl, \
                                 _pModInfo->name, __FUNCTION__, ##arg); } while(0) )

#define BCM_LOG_INFO(logId, fmt, arg...)                               \
    BCM_LOGCODE( do { bcmLogModuleInfo_t *_pModInfo = bcmLog_logIsEnabled(logId, BCM_LOG_LEVEL_INFO); \
                      if (_pModInfo)                                              \
                          bcmPrint(CLRg "[INF " "%s" "] %-10s: " fmt CLRnl, \
                                 _pModInfo->name, __FUNCTION__, ##arg); } while(0) )

#define BCM_LOG_NOTICE(logId, fmt, arg...)                               \
    BCM_LOGCODE( do { bcmLogModuleInfo_t *_pModInfo = bcmLog_logIsEnabled(logId, BCM_LOG_LEVEL_NOTICE); \
                      if (_pModInfo)                                              \
                          bcmPrint(CLRb "[NTC " "%s" "] %-10s: " fmt CLRnl, \
                                 _pModInfo->name, __FUNCTION__, ##arg); } while(0) )


/**
 * Error Reporting API: Activate by #defining BCM_ERROR_SUPPORTED
 **/

#define BCM_LOG_ERROR(logId, fmt, arg...)                                \
    BCM_ERRORCODE( do { bcmLogModuleInfo_t *_pModInfo = bcmLog_logIsEnabled(logId, BCM_LOG_LEVEL_ERROR); \
                      if (_pModInfo)                                              \
                          bcmPrint(CLRerr "[ERROR " "%s" "] %-10s,%d: " fmt CLRnl, \
                                 _pModInfo->name, __FUNCTION__, __LINE__, ##arg); } while(0) )


/**
 * Assert API: Activate by #defining BCM_ASSERT_SUPPORTED
 **/

#define BCM_ASSERT(cond)                                         \
    BCM_ASSERTCODE( if ( !(cond) ) {                                    \
                        bcmPrint(CLRerr "[ASSERT " "%s" "] %-10s,%d: " #cond CLRnl, \
                               __FILE__, __FUNCTION__, __LINE__); \
                        BUG();                                          \
                     } )


/**
 * Datadump API: Activate by #defining BCM_DATADUMP_SUPPORTED
 **/

/*
 * Prototype of datadump print functions.
 * Note: parse functions must be exported (EXPORT_SYMBOL)
 */
typedef int (Bcm_DataDumpPrintFunc)(uint32_t dataDumpId, IN void* dataPtr, uint32_t numDataBytes,
                                    OUT char* buf, uint32_t bufSize);

#if defined(BCM_DATADUMP_SUPPORTED)
bcmLogModuleInfo_t *bcmLog_ddIsEnabled(bcmLogId_t logId, bcmLogDataDumpLevel_t ddLevel);
void bcm_dataDumpRegPrinter(uint32_t qId, uint32_t dataDumpId, Bcm_DataDumpPrintFunc *printFun);
void bcm_dataDump(uint32_t qID, uint32_t dataDumpID, const char* dataDumpName, void *ptr, uint32_t numBytes);
uint32_t bcm_dataDumpCreateQ(const char* qName);
void bcm_dataDumpDeleteQ(uint32_t qid);
#endif

/*
 * Create a DataDump queue. Different modules can share a queue.
 * Returns a queue ID (uint32_t).
 */
#define BCM_DATADUMP_CREATE_Q(qName) BCM_DATADUMPCODE(bcm_dataDumpCreateQ(qName))

/*
 * Delete a DataDump queue.
 */
#define BCM_DATADUMP_DELETE_Q(qID) BCM_DATADUMPCODE(bcm_dataDumpDeleteQ(qID))

/*
 * Dump data
 */
#define BCM_DATADUMP_IMPORTANT(logId, qID, dataDumpID, ptr, numBytes) \
    BCM_DATADUMPCODE( do { bcmLogModuleInfo_t *_pModInfo = bcmLog_ddIsEnabled(logId, BCM_LOG_DD_IMPORTANT); \
                      if (_pModInfo)                                              \
                          bcm_dataDump(qID, dataDumpID, #dataDumpID, (void*)(ptr), numBytes); } while(0) )
#define BCM_DATADUMP_INFO(logId, qID, dataDumpID, ptr, numBytes) \
    BCM_DATADUMPCODE( do { bcmLogModuleInfo_t *_pModInfo = bcmLog_ddIsEnabled(logId, BCM_LOG_DD_INFO); \
                      if (_pModInfo)                                              \
                          bcm_dataDump(qID, dataDumpID, #dataDumpID, (void*)(ptr), numBytes); } while(0) )
#define BCM_DATADUMP_DETAIL(logId, qID, dataDumpID, ptr, numBytes) \
    BCM_DATADUMPCODE( do { bcmLogModuleInfo_t *_pModInfo = bcmLog_ddIsEnabled(logId, BCM_LOG_DD_DETAIL); \
                      if (_pModInfo)                                              \
                          bcm_dataDump(qID, dataDumpID, #dataDumpID, (void*)(ptr), numBytes); } while(0) )
#define BCM_DATADUMP_MAX(logId, qID, dataDumpID, ptr, numBytes) \
    BCM_DATADUMPCODE( do { bcmLogModuleInfo_t *_pModInfo = bcmLog_ddIsEnabled(logId, BCM_LOG_DD_MAX); \
                      if (_pModInfo)                                              \
                          bcm_dataDump(qID, dataDumpID, #dataDumpID, (void*)(ptr), numBytes); } while(0) )

/*
 * Register a printer for a certain DataDump ID.
 * Datadumps for which no printer is registered will use a default printer.
 * The default printer will print the data as an array of bytes.
 */
#define BCM_DATADUMP_REG_PRINTER(qId, dataDumpId, printFun)             \
    BCM_DATADUMPCODE(bcm_dataDumpRegPrinter(qId, dataDumpId, printFun))

/* A helper macro for datadump printers */
#define DDPRINTF(buf, len, bufSize, arg...)                             \
    ({len += snprintf((buf)+(len), max_t(uint32_t, 0, (bufSize)-80-(len)), ##arg); \
        if ((len) >= (bufSize)-80) snprintf((buf)+(len), 80, "---BUFFER FULL---\n");})


/**
 * Snapshot API: Commit all logs to the Snapshot queue
 **/

#define BCM_LOG_SNAPSHOT() BCM_SNAPSHOTCODE() /*TBD*/


/**
 * API Function Prototypes
 **/

#ifdef CONFIG_BCM_LOG

void __init bcmLog_init( void );

void bcmLog_setGlobalLogLevel(bcmLogLevel_t logLevel);
bcmLogLevel_t bcmLog_getGlobalLogLevel(void);

void bcmLog_setLogLevel(bcmLogId_t logId, bcmLogLevel_t logLevel);
bcmLogLevel_t bcmLog_getLogLevel(bcmLogId_t logId);

char *bcmLog_getModName(bcmLogId_t logId);

void bcmLog_registerSpiCallbacks(bcmLogSpiCallbacks_t callbacks);

typedef int (bcmFun_t)(void *);

/*Register a function with the bcmLog driver*/
void bcmFun_reg(bcmFunId_t funId, bcmFun_t *f);

/*De-Register a function with the bcmLog driver*/
void bcmFun_dereg(bcmFunId_t funId);

/*Look up a function by FunId. Returns NULL if the function is not
 *registered.*/
bcmFun_t* bcmFun_get(bcmFunId_t funId);

void bcmLog_registerLevelChangeCallback(bcmLogId_t logId, bcmLogLevelChangeCallback_t callback, void *ctx);

#else

/* BCM LOG not configured: create empty stubs for all functions */
static inline void bcmLog_init( void )                                           {}
static inline void bcmLog_setGlobalLogLevel(bcmLogLevel_t loglevel)              {}
static inline bcmLogLevel_t bcmLog_getGlobalLogLevel(void)                       { return 0; }
static inline char *bcmLog_getModName(bcmLogId_t logId)                          { return NULL; }
static inline void bcmLog_registerSpiCallbacks(bcmLogSpiCallbacks_t callbacks)   {}
static inline void bcmLog_setLogLevel(bcmLogId_t logId, bcmLogLevel_t logLevel)  {}
static inline bcmLogLevel_t bcmLog_getLogLevel(bcmLogId_t logId)                 { return 0; }
typedef int (bcmFun_t)(void *);
static inline void bcmFun_reg(bcmFunId_t funId, bcmFun_t f)                      {}
static inline void bcmFun_dereg(bcmFunId_t funId)                                {}
static inline bcmFun_t* bcmFun_get(bcmFunId_t funId)                             { return NULL; }
static inline void bcmLog_registerLevelChangeCallback(bcmLogId_t logId, bcmLogLevelChangeCallback_t callback, void *ctx) {}


#endif /* CONFIG_BCM_LOG */
#endif /*_BCM_LOG_SERVICES_*/
#endif /* CONFIG_BCM_KF_LOG */
