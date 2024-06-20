/**
 * @file regstr.h
 * Copyright 2012, 2013 MinGW.org project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
#ifndef _REGSTR_H
#define _REGSTR_H
#pragma GCC system_header
#include <_mingw.h>

#ifdef __cplusplus
extern "C" {
#endif

#define REGSTR_KEY_CLASS TEXT("Class")
#define REGSTR_KEY_CONFIG TEXT("Config")
#define REGSTR_KEY_ENUM TEXT("Enum")
#define REGSTR_KEY_ROOTENUM TEXT("Root")
#define REGSTR_KEY_BIOSENUM TEXT("BIOS")
#define REGSTR_KEY_PCMCIAENUM TEXT("PCMCIA")
#define REGSTR_KEY_PCIENUM TEXT("PCI")
#define REGSTR_KEY_LOGCONFIG	TEXT("LogConfig")
#define REGSTR_KEY_SYSTEMBOARD	TEXT("*PNP0C01")
#define REGSTR_KEY_APM	TEXT("*PNP0C05")
#define REGSTR_KEY_INIUPDATE	TEXT("IniUpdate")
#define REG_KEY_INSTDEV TEXT("Installed")
#define REGSTR_KEY_DOSOPTCDROM	TEXT("CD-ROM")
#define REGSTR_KEY_DOSOPTMOUSE	TEXT("MOUSE")
#define REGSTR_DEFAULT_INSTANCE TEXT("0000")
#define REGSTR_PATH_MOTHERBOARD REGSTR_KEY_SYSTEMBOARD TEXT("\\" REGSTR_DEFAULT_INSTANCE
#define REGSTR_PATH_SETUP	TEXT("Software\\Microsoft\\Windows\\CurrentVersion")
#define REGSTR_PATH_PIFCONVERT TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\PIFConvert")
#define REGSTR_PATH_MSDOSOPTS	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\MS-DOSOptions")
#define REGSTR_PATH_MSDOSEMU	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\MS-DOS Emulation")
#define REGSTR_PATH_NEWDOSBOX	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\MS-DOS Emulation\\AppCompat")
#define REGSTR_PATH_RUNONCE	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunOnce")
#define REGSTR_PATH_RUN	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Run")
#define REGSTR_PATH_RUNSERVICESONCE	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunServicesOnce")
#define REGSTR_PATH_RUNSERVICES	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\RunServices")

#ifndef REGSTR_PATH_EXPLORER /* also in shlobj.h */
#define REGSTR_PATH_EXPLORER	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer")
#endif

#define REGSTR_PATH_DETECT	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Detect")
#define REGSTR_PATH_APPPATHS	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\App Paths")
#define REGSTR_PATH_UNINSTALL TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall")
#define REGSTR_PATH_REALMODENET TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Network\\Real Mode Net")
#define REGSTR_PATH_NETEQUIV TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Network\\Equivalent")
#define REGSTR_PATH_CVNETWORK TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Network")
#define REGSTR_PATH_IDCONFIGDB	TEXT("System\\CurrentControlSet\\Control\\IDConfigDB")
#define REGSTR_PATH_CLASS	TEXT("System\\CurrentControlSet\\Services\\Class")
#define REGSTR_PATH_DISPLAYSETTINGS TEXT("Display\\Settings")
#define REGSTR_PATH_FONTS	TEXT("Display\\Fonts")
#define REGSTR_PATH_ENUM	TEXT("Enum")
#define REGSTR_PATH_ROOT	TEXT("Enum\\Root")
#define REGSTR_PATH_SERVICES	TEXT("System\\CurrentControlSet\\Services")
#define REGSTR_PATH_VXD TEXT("System\\CurrentControlSet\\Services\\VxD")
#define REGSTR_PATH_IOS TEXT("System\\CurrentControlSet\\Services\\VxD\\IOS")
#define REGSTR_PATH_VMM TEXT("System\\CurrentControlSet\\Services\\VxD\\VMM")
#define REGSTR_PATH_VPOWERD TEXT("System\\CurrentControlSet\\Services\\VxD\\VPOWERD")
#define REGSTR_PATH_VNETSUP TEXT("System\\CurrentControlSet\\Services\\VxD\\VNETSUP")
#define REGSTR_PATH_NWREDIR TEXT("System\\CurrentControlSet\\Services\\VxD\\NWREDIR")
#define REGSTR_PATH_NCPSERVER TEXT("System\\CurrentControlSet\\Services\\NcpServer\\Parameters")
#define REGSTR_PATH_IOARB	TEXT("System\\CurrentControlSet\\Services\\Arbitrators\\IOArb")
#define REGSTR_PATH_ADDRARB	TEXT("System\\CurrentControlSet\\Services\\Arbitrators\\AddrArb")
#define REGSTR_PATH_DMAARB	TEXT("System\\CurrentControlSet\\Services\\Arbitrators\\DMAArb")
#define REGSTR_PATH_IRQARB	TEXT("System\\CurrentControlSet\\Services\\Arbitrators\\IRQArb")
#define REGSTR_PATH_CODEPAGE	TEXT("System\\CurrentControlSet\\Control\\Nls\\Codepage")
#define REGSTR_PATH_FILESYSTEM	TEXT("System\\CurrentControlSet\\Control\\FileSystem")
#define REGSTR_PATH_FILESYSTEM_NOVOLTRACK	TEXT("System\\CurrentControlSet\\Control\\FileSystem\\NoVolTrack")
#define REGSTR_PATH_CDFS	TEXT("System\\CurrentControlSet\\Control\\FileSystem\\CDFS")
#define REGSTR_PATH_WINBOOT	TEXT("System\\CurrentControlSet\\Control\\WinBoot")
#define REGSTR_PATH_INSTALLEDFILES	TEXT("System\\CurrentControlSet\\Control\\InstalledFiles")
#define REGSTR_PATH_VMM32FILES	TEXT("System\\CurrentControlSet\\Control\\VMM32Files")
#define REGSTR_MAX_VALUE_LENGTH 256
#define REGSTR_VAL_BITSPERPIXEL	TEXT("BitsPerPixel")
#define REGSTR_VAL_RESOLUTION TEXT("Resolution")
#define REGSTR_VAL_DPILOGICALX	TEXT("DPILogicalX")
#define REGSTR_VAL_DPILOGICALY	TEXT("DPILogicalY")
#define REGSTR_VAL_DPIPHYSICALX	TEXT("DPIPhysicalX")
#define REGSTR_VAL_DPIPHYSICALY TEXT("DPIPhysicalY")
#define REGSTR_VAL_REFRESHRATE TEXT("RefreshRate")
#define REGSTR_VAL_DISPLAYFLAGS TEXT("DisplayFlags")
#define REGSTR_PATH_CONTROLPANEL TEXT("Control Panel")
#define REGSTR_PATH_CONTROLSFOLDER TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Controls Folder")
#define REGSTR_VAL_DOSCP	TEXT("OEMCP")
#define REGSTR_VAL_WINCP	TEXT("ACP")
#define REGSTR_PATH_DYNA_ENUM	TEXT("Config Manager\\Enum")
#define	REGSTR_VAL_HARDWARE_KEY	TEXT("HardWareKey")
#define	REGSTR_VAL_ALLOCATION	TEXT("Allocation")
#define	REGSTR_VAL_PROBLEM	TEXT("Problem")
#define	REGSTR_VAL_STATUS	TEXT("Status")
#define REGSTR_VAL_DONTUSEMEM	TEXT("DontAllocLastMem")
#define REGSTR_VAL_SYSTEMROOT TEXT("SystemRoot")
#define REGSTR_VAL_BOOTCOUNT	TEXT("BootCount")
#define REGSTR_VAL_REALNETSTART	TEXT("RealNetStart")
#define	REGSTR_VAL_MEDIA	TEXT("MediaPath")
#define	REGSTR_VAL_CONFIG	TEXT("ConfigPath")
#define REGSTR_VAL_DEVICEPATH	TEXT("DevicePath")
#define REGSTR_VAL_SRCPATH	TEXT("SourcePath")
#define REGSTR_VAL_OLDWINDIR	TEXT("OldWinDir")
#define REGSTR_VAL_SETUPFLAGS	TEXT("SetupFlags")
#define REGSTR_VAL_REGOWNER TEXT("RegisteredOwner")
#define REGSTR_VAL_REGORGANIZATION TEXT("RegisteredOrganization")
#define REGSTR_VAL_LICENSINGINFO TEXT("LicensingInfo")
#define REGSTR_VAL_OLDMSDOSVER TEXT("OldMSDOSVer")
#define REGSTR_VAL_FIRSTINSTALLDATETIME TEXT("FirstInstallDateTime")
#define REGSTR_VAL_INSTALLTYPE	TEXT("InstallType")
#define REGSTR_VAL_WRAPPER	TEXT("Wrapper")
#define IT_COMPACT 0
#define IT_TYPICAL 1
#define IT_PORTABLE 2
#define IT_CUSTOM 3
#define REGSTR_KEY_SETUP	TEXT("\\Setup")
#define REGSTR_VAL_BOOTDIR TEXT("BootDir")
#define REGSTR_VAL_WINBOOTDIR TEXT("WinbootDir")
#define REGSTR_VAL_WINDIR	TEXT("WinDir")
#define REGSTR_VAL_APPINSTPATH	TEXT("AppInstallPath")
#define REGSTR_PATH_EBD REGSTR_PATH_SETUP REGSTR_KEY_SETUP TEXT("\\EBD")
#define REGSTR_KEY_EBDFILESLOCAL TEXT("EBDFilesLocale")
#define REGSTR_KEY_EBDFILESKEYBOARD TEXT("EBDFilesKeyboard")
#define REGSTR_KEY_EBDAUTOEXECBATLOCAL TEXT("EBDAutoexecBatLocale")
#define REGSTR_KEY_EBDAUTOEXECBATKEYBOARD TEXT("EBDAutoexecBatKeyboard")
#define REGSTR_KEY_EBDCONFIGSYSLOCAL TEXT("EBDConfigSysLocale")
#define REGSTR_KEY_EBDCONFIGSYSKEYBOARD TEXT("EBDConfigSysKeyboard")
#define REGSTR_VAL_MSDOSMODE TEXT("MSDOSMode")
#define REGSTR_VAL_MSDOSMODEDISCARD TEXT("Discard")
#define REGSTR_VAL_DOSOPTGLOBALFLAGS	TEXT("GlobalFlags")
#define DOSOPTGF_DEFCLEAN 1
#define REGSTR_VAL_DOSOPTFLAGS	TEXT("Flags")
#define REGSTR_VAL_OPTORDER	TEXT("Order")
#define REGSTR_VAL_CONFIGSYS	TEXT("Config.Sys")
#define REGSTR_VAL_AUTOEXEC	TEXT("Autoexec.Bat")
#define REGSTR_VAL_STDDOSOPTION TEXT("StdOption")
#define REGSTR_VAL_DOSOPTTIP	TEXT("TipText")
#define DOSOPTF_DEFAULT 1
#define DOSOPTF_SUPPORTED 2
#define DOSOPTF_ALWAYSUSE 4
#define DOSOPTF_USESPMODE 8
#define DOSOPTF_PROVIDESUMB 16
#define DOSOPTF_NEEDSETUP 32
#define DOSOPTF_INDOSSTART 64
#define DOSOPTF_MULTIPLE 128
#define SUF_FIRSTTIME 1
#define SUF_EXPRESS 2
#define SUF_BATCHINF 4
#define SUF_CLEAN 8
#define SUF_INSETUP 16
#define SUF_NETSETUP 32
#define SUF_NETHDBOOT 64
#define SUF_NETRPLBOOT 128
#define SUF_SBSCOPYOK 256
#define REGSTR_VAL_DOSPAGER	TEXT("DOSPager")
#define REGSTR_VAL_VXDGROUPS	TEXT("VXDGroups")
#define REGSTR_VAL_VPOWERDFLAGS TEXT("Flags")
#define VPDF_DISABLEPWRMGMT 1
#define VPDF_FORCEAPM10MODE 2
#define VPDF_SKIPINTELSLCHECK 4
#define VPDF_DISABLEPWRSTATUSPOLL 8
#define REGSTR_VAL_WORKGROUP TEXT("Workgroup")
#define REGSTR_VAL_DIRECTHOST TEXT("DirectHost")
#define REGSTR_VAL_FILESHARING TEXT("FileSharing")
#define REGSTR_VAL_PRINTSHARING	TEXT("PrintSharing")
#define REGSTR_VAL_FIRSTNETDRIVE TEXT("FirstNetworkDrive")
#define REGSTR_VAL_MAXCONNECTIONS	TEXT("MaxConnections")
#define REGSTR_VAL_APISUPPORT	TEXT("APISupport")
#define REGSTR_VAL_MAXRETRY	TEXT("MaxRetry")
#define REGSTR_VAL_MINRETRY	TEXT("MinRetry")
#define REGSTR_VAL_SUPPORTLFN	TEXT("SupportLFN")
#define REGSTR_VAL_SUPPORTBURST	TEXT("SupportBurst")
#define REGSTR_VAL_SUPPORTTUNNELLING	TEXT("SupportTunnelling")
#define REGSTR_VAL_FULLTRACE	TEXT("FullTrace")
#define REGSTR_VAL_READCACHING	TEXT("ReadCaching")
#define REGSTR_VAL_SHOWDOTS	TEXT("ShowDots")
#define REGSTR_VAL_GAPTIME	TEXT("GapTime")
#define REGSTR_VAL_SEARCHMODE	TEXT("SearchMode")
#define REGSTR_VAL_SHELLVERSION TEXT("ShellVersion")
#define REGSTR_VAL_MAXLIP TEXT("MaxLIP")
#define REGSTR_VAL_PRESERVECASE TEXT("PreserveCase")
#define REGSTR_VAL_OPTIMIZESFN TEXT("OptimizeSFN")
#define REGSTR_VAL_NCP_BROWSEMASTER TEXT("BrowseMaster")
#define	REGSTR_VAL_NCP_USEPEERBROWSING	TEXT("Use_PeerBrowsing")
#define REGSTR_VAL_NCP_USESAP TEXT("Use_Sap")
#define	REGSTR_VAL_WIN31FILESYSTEM	TEXT("Win31FileSystem")
#define REGSTR_VAL_PRESERVELONGNAMES	TEXT("PreserveLongNames")
#define REGSTR_VAL_DRIVEWRITEBEHIND	TEXT("DriveWriteBehind")
#define REGSTR_VAL_ASYNCFILECOMMIT	TEXT("AsyncFileCommit")
#define REGSTR_VAL_PATHCACHECOUNT	TEXT("PathCache")
#define REGSTR_VAL_NAMECACHECOUNT	TEXT("NameCache")
#define REGSTR_VAL_CONTIGFILEALLOC	TEXT("ContigFileAllocSize")
#define REGSTR_VAL_VOLIDLETIMEOUT	TEXT("VolumeIdleTimeout")
#define REGSTR_VAL_BUFFIDLETIMEOUT	TEXT("BufferIdleTimeout")
#define REGSTR_VAL_BUFFAGETIMEOUT	TEXT("BufferAgeTimeout")
#define	REGSTR_VAL_NAMENUMERICTAIL TEXT("NameNumericTail")
#define	REGSTR_VAL_READAHEADTHRESHOLD	TEXT("ReadAheadThreshold")
#define	REGSTR_VAL_DOUBLEBUFFER TEXT("DoubleBuffer")
#define	REGSTR_VAL_SOFTCOMPATMODE TEXT("SoftCompatMode")
#define REGSTR_VAL_DRIVESPINDOWN	TEXT("DriveSpinDown")
#define	REGSTR_VAL_FORCEPMIO	TEXT("ForcePMIO")
#define REGSTR_VAL_FORCERMIO	TEXT("ForceRMIO")
#define REGSTR_VAL_LASTBOOTPMDRVS	TEXT("LastBootPMDrvs")
#define REGSTR_VAL_VIRTUALHDIRQ	TEXT("VirtualHDIRQ")
#define REGSTR_VAL_SRVNAMECACHECOUNT	TEXT("ServerNameCacheMax")
#define REGSTR_VAL_SRVNAMECACHE	TEXT("ServerNameCache")
#define REGSTR_VAL_SRVNAMECACHENETPROV	TEXT("ServerNameCacheNumNets")
#define	REGSTR_VAL_AUTOMOUNT	TEXT("AutoMountDrives")
#define	REGSTR_VAL_COMPRESSIONMETHOD	TEXT("CompressionAlgorithm")
#define	REGSTR_VAL_COMPRESSIONTHRESHOLD	TEXT("CompressionThreshold")
#define REGSTR_VAL_CDCACHESIZE	TEXT("CacheSize")
#define REGSTR_VAL_CDPREFETCH	TEXT("Prefetch")
#define REGSTR_VAL_CDPREFETCHTAIL TEXT("PrefetchTail")
#define REGSTR_VAL_CDRAWCACHE	TEXT("RawCache")
#define REGSTR_VAL_CDEXTERRORS	TEXT("ExtendedErrors")
#define REGSTR_VAL_CDSVDSENSE	TEXT("SVDSense")
#define REGSTR_VAL_CDSHOWVERSIONS TEXT("ShowVersions")
#define REGSTR_VAL_CDCOMPATNAMES TEXT("MSCDEXCompatNames")
#define REGSTR_VAL_CDNOREADAHEAD TEXT("NoReadAhead")
#define REGSTR_VAL_SCSI	TEXT("SCSI\\")
#define REGSTR_VAL_ESDI	TEXT("ESDI\\")
#define REGSTR_VAL_FLOP TEXT("FLOP\\")
#define	REGSTR_VAL_DISK	TEXT("GenDisk")
#define	REGSTR_VAL_CDROM	TEXT("GenCD")
#define	REGSTR_VAL_TAPE	TEXT("TAPE")
#define	REGSTR_VAL_SCANNER TEXT("SCANNER")
#define	REGSTR_VAL_FLOPPY	TEXT("FLOPPY")
#define	REGSTR_VAL_SCSITID TEXT("SCSITargetID")
#define	REGSTR_VAL_SCSILUN TEXT("SCSILUN")
#define	REGSTR_VAL_REVLEVEL TEXT("RevisionLevel")
#define	REGSTR_VAL_PRODUCTID TEXT("ProductId")
#define	REGSTR_VAL_PRODUCTTYPE TEXT("ProductType")
#define	REGSTR_VAL_DEVTYPE TEXT("DeviceType")
#define	REGSTR_VAL_REMOVABLE TEXT("Removable")
#define REGSTR_VAL_CURDRVLET TEXT("CurrentDriveLetterAssignment")
#define	REGSTR_VAL_USRDRVLET TEXT("UserDriveLetterAssignment")
#define	REGSTR_VAL_SYNCDATAXFER TEXT("SyncDataXfer")
#define	REGSTR_VAL_AUTOINSNOTE	TEXT("AutoInsertNotification")
#define	REGSTR_VAL_DISCONNECT TEXT("Disconnect")
#define	REGSTR_VAL_INT13 TEXT("Int13")
#define	REGSTR_VAL_PMODE_INT13 TEXT("PModeInt13")
#define	REGSTR_VAL_USERSETTINGS TEXT("AdapterSettings")
#define	REGSTR_VAL_NOIDE TEXT("NoIDE")
#define	REGSTR_VAL_DISKCLASSNAME	TEXT("DiskDrive")
#define	REGSTR_VAL_CDROMCLASSNAME	TEXT("CDROM")
#define	REGSTR_VAL_FORCELOAD	TEXT("ForceLoadPD")
#define	REGSTR_VAL_FORCEFIFO TEXT("ForceFIFO")
#define	REGSTR_VAL_FORCECL TEXT("ForceChangeLine")
#define REGSTR_VAL_NOUSECLASS TEXT("NoUseClass")
#define REGSTR_VAL_NOINSTALLCLASS TEXT("NoInstallClass")
#define REGSTR_VAL_NODISPLAYCLASS TEXT("NoDisplayClass")
#define REGSTR_VAL_SILENTINSTALL TEXT("SilentInstall")
#define REGSTR_KEY_PCMCIA_CLASS TEXT("PCMCIA")
#define REGSTR_KEY_SCSI_CLASS TEXT("SCSIAdapter")
#define REGSTR_KEY_PORTS_CLASS TEXT("ports")
#define REGSTR_KEY_MEDIA_CLASS TEXT("MEDIA")
#define REGSTR_KEY_DISPLAY_CLASS TEXT("Display")
#define REGSTR_KEY_KEYBOARD_CLASS TEXT("Keyboard")
#define REGSTR_KEY_MOUSE_CLASS TEXT("Mouse")
#define REGSTR_KEY_MONITOR_CLASS TEXT("Monitor")
#define REGSTR_VAL_PCMCIA_OPT	TEXT("Options")
#define PCMCIA_OPT_HAVE_SOCKET	1
#define PCMCIA_OPT_AUTOMEM	4
#define PCMCIA_OPT_NO_SOUND	8
#define PCMCIA_OPT_NO_AUDIO	16
#define PCMCIA_OPT_NO_APMREMOVE 32
#define REGSTR_VAL_PCMCIA_MEM	TEXT("Memory")
#define PCMCIA_DEF_MEMBEGIN	0xC0000
#define PCMCIA_DEF_MEMEND	0xFFFFFF
#define PCMCIA_DEF_MEMLEN	0x1000
#define REGSTR_VAL_PCMCIA_ALLOC TEXT("AllocMemWin")
#define REGSTR_VAL_PCMCIA_ATAD	TEXT("ATADelay")
#define REGSTR_VAL_PCMCIA_SIZ	TEXT("MinRegionSize")
#define PCMCIA_DEF_MIN_REGION	0x10000
#define REGSTR_VAL_P1284MDL TEXT("Model")
#define REGSTR_VAL_P1284MFG TEXT("Manufacturer")
#define	REGSTR_VAL_ISAPNP	TEXT("ISAPNP")
#define	REGSTR_VAL_ISAPNP_RDP_OVERRIDE	TEXT("RDPOverRide")
#define	REGSTR_VAL_PCI	TEXT("PCI")
#define	REGSTR_PCI_OPTIONS	TEXT("Options")
#define	REGSTR_PCI_DUAL_IDE	TEXT("PCIDualIDE")
#define	PCI_OPTIONS_USE_BIOS	1
#define	PCI_OPTIONS_USE_IRQ_STEERING	2
#define	PCI_FLAG_NO_VIDEO_IRQ	1
#define	PCI_FLAG_PCMCIA_WANT_IRQ	2
#define	PCI_FLAG_DUAL_IDE	4
#define	PCI_FLAG_NO_ENUM_AT_ALL	8
#define	PCI_FLAG_ENUM_NO_RESOURCE	16
#define	PCI_FLAG_NEED_DWORD_ACCESS	32
#define	PCI_FLAG_SINGLE_FUNCTION	64
#define	PCI_FLAG_ALWAYS_ENABLED	128
#define	PCI_FLAG_IS_IDE	256
#define	PCI_FLAG_IS_VIDEO	512
#define	PCI_FLAG_FAIL_START	1024
#define REGSTR_KEY_CRASHES	TEXT("Crashes")
#define REGSTR_KEY_DANGERS	TEXT("Dangers")
#define REGSTR_KEY_DETMODVARS	TEXT("DetModVars")
#define REGSTR_KEY_NDISINFO	TEXT("NDISInfo")
#define REGSTR_VAL_PROTINIPATH	TEXT("ProtIniPath")
#define REGSTR_VAL_RESOURCES	TEXT("Resources")
#define REGSTR_VAL_CRASHFUNCS	TEXT("CrashFuncs")
#define REGSTR_VAL_CLASS	TEXT("Class")
#define REGSTR_VAL_DEVDESC	TEXT("DeviceDesc")
#define REGSTR_VAL_BOOTCONFIG	TEXT("BootConfig")
#define REGSTR_VAL_DETFUNC	TEXT("DetFunc")
#define REGSTR_VAL_DETFLAGS	TEXT("DetFlags")
#define REGSTR_VAL_COMPATIBLEIDS TEXT("CompatibleIDs")
#define REGSTR_VAL_DETCONFIG	TEXT("DetConfig")
#define REGSTR_VAL_VERIFYKEY	TEXT("VerifyKey")
#define REGSTR_VAL_COMINFO	TEXT("ComInfo")
#define REGSTR_VAL_INFNAME	TEXT("InfName")
#define REGSTR_VAL_CARDSPECIFIC	TEXT("CardSpecific")
#define REGSTR_VAL_NETOSTYPE	TEXT("NetOSType")
#define REGSTR_DATA_NETOS_NDIS	TEXT("NDIS")
#define REGSTR_DATA_NETOS_ODI	TEXT("ODI")
#define REGSTR_DATA_NETOS_IPX	TEXT("IPX")
#define REGSTR_VAL_MFG TEXT("Mfg")
#define REGSTR_VAL_SCAN_ONLY_FIRST	TEXT("ScanOnlyFirstDrive")
#define REGSTR_VAL_SHARE_IRQ	TEXT("ForceIRQSharing")
#define REGSTR_VAL_NONSTANDARD_ATAPI	TEXT("NonStandardATAPI")
#define REGSTR_VAL_IDE_FORCE_SERIALIZE	TEXT("ForceSerialization")
#define	REGSTR_VAL_MAX_HCID_LEN	1024
#define REGSTR_VAL_HWREV TEXT("HWRevision")
#define REGSTR_VAL_ENABLEINTS TEXT("EnableInts")
#define REGDF_NOTDETIO	1
#define REGDF_NOTDETMEM 2
#define REGDF_NOTDETIRQ 4
#define REGDF_NOTDETDMA 8
#define REGDF_NOTDETALL	(REGDF_NOTDETIO | REGDF_NOTDETMEM | REGDF_NOTDETIRQ | REGDF_NOTDETDMA)
#define REGDF_NEEDFULLCONFIG	16
#define REGDF_GENFORCEDCONFIG	32
#define REGDF_NODETCONFIG	0x8000
#define REGDF_CONFLICTIO	0x10000
#define REGDF_CONFLICTMEM	0x20000
#define REGDF_CONFLICTIRQ	0x40000
#define REGDF_CONFLICTDMA	0x80000
#define	REGDF_CONFLICTALL	(REGDF_CONFLICTIO | REGDF_CONFLICTMEM | REGDF_CONFLICTIRQ | REGDF_CONFLICTDMA)
#define REGDF_MAPIRQ2TO9	0x100000
#define REGDF_NOTVERIFIED	0x80000000
#define REGSTR_VAL_APMBIOSVER	TEXT("APMBiosVer")
#define REGSTR_VAL_APMFLAGS	TEXT("APMFlags")
#define REGSTR_VAL_SLSUPPORT	TEXT("SLSupport")
#define REGSTR_VAL_MACHINETYPE	TEXT("MachineType")
#define REGSTR_VAL_SETUPMACHINETYPE TEXT("SetupMachineType")
#define REGSTR_MACHTYPE_UNKNOWN TEXT("Unknown")
#define REGSTR_MACHTYPE_IBMPC	TEXT("IBM PC")
#define REGSTR_MACHTYPE_IBMPCJR TEXT("IBM PCjr")
#define REGSTR_MACHTYPE_IBMPCCONV	TEXT("IBM PC Convertible")
#define REGSTR_MACHTYPE_IBMPCXT TEXT("IBM PC/XT")
#define REGSTR_MACHTYPE_IBMPCXT_286	TEXT("IBM PC/XT 286")
#define REGSTR_MACHTYPE_IBMPCAT TEXT("IBM PC/AT")
#define REGSTR_MACHTYPE_IBMPS2_25	TEXT("IBM PS/2-25")
#define REGSTR_MACHTYPE_IBMPS2_30_286	TEXT("IBM PS/2-30 286")
#define REGSTR_MACHTYPE_IBMPS2_30	TEXT("IBM PS/2-30")
#define REGSTR_MACHTYPE_IBMPS2_50	TEXT("IBM PS/2-50")
#define REGSTR_MACHTYPE_IBMPS2_50Z	TEXT("IBM PS/2-50Z")
#define REGSTR_MACHTYPE_IBMPS2_55SX	TEXT("IBM PS/2-55SX")
#define REGSTR_MACHTYPE_IBMPS2_60	TEXT("IBM PS/2-60")
#define REGSTR_MACHTYPE_IBMPS2_65SX	TEXT("IBM PS/2-65SX")
#define REGSTR_MACHTYPE_IBMPS2_70	TEXT("IBM PS/2-70")
#define REGSTR_MACHTYPE_IBMPS2_P70	TEXT("IBM PS/2-P70")
#define REGSTR_MACHTYPE_IBMPS2_70_80	TEXT("IBM PS/2-70/80")
#define REGSTR_MACHTYPE_IBMPS2_80	TEXT("IBM PS/2-80")
#define REGSTR_MACHTYPE_IBMPS2_90	TEXT("IBM PS/2-90")
#define REGSTR_MACHTYPE_IBMPS1	TEXT("IBM PS/1")
#define REGSTR_MACHTYPE_PHOENIX_PCAT	TEXT("Phoenix PC/AT Compatible")
#define REGSTR_MACHTYPE_HP_VECTRA	TEXT("HP Vectra")
#define REGSTR_MACHTYPE_ATT_PC	TEXT("AT&T PC")
#define REGSTR_MACHTYPE_ZENITH_PC	TEXT("Zenith PC")
#define REGSTR_VAL_APMMENUSUSPEND	TEXT("APMMenuSuspend")
#define APMMENUSUSPEND_DISABLED 0
#define APMMENUSUSPEND_ENABLED	1
#define APMMENUSUSPEND_UNDOCKED 2
#define APMMENUSUSPEND_NOCHANGE 128
#define REGSTR_VAL_BUSTYPE TEXT("BusType")
#define REGSTR_VAL_CPU TEXT("CPU")
#define REGSTR_VAL_NDP TEXT("NDP")
#define REGSTR_VAL_PNPBIOSVER TEXT("PnPBIOSVer")
#define REGSTR_VAL_PNPSTRUCOFFSET TEXT("PnPStrucOffset")
#define REGSTR_VAL_PCIBIOSVER TEXT("PCIBIOSVer")
#define REGSTR_VAL_HWMECHANISM TEXT("HWMechanism")
#define REGSTR_VAL_LASTPCIBUSNUM TEXT("LastPCIBusNum")
#define REGSTR_VAL_CONVMEM TEXT("ConvMem")
#define REGSTR_VAL_EXTMEM TEXT("ExtMem")
#define REGSTR_VAL_COMPUTERNAME TEXT("ComputerName")
#define REGSTR_VAL_BIOSNAME TEXT("BIOSName")
#define REGSTR_VAL_BIOSVERSION TEXT("BIOSVersion")
#define REGSTR_VAL_BIOSDATE TEXT("BIOSDate")
#define REGSTR_VAL_MODEL TEXT("Model")
#define REGSTR_VAL_SUBMODEL TEXT("Submodel")
#define REGSTR_VAL_REVISION TEXT("Revision")
#define REGSTR_VAL_FIFODEPTH	TEXT("FIFODepth")
#define REGSTR_VAL_RDINTTHRESHOLD	TEXT("RDIntThreshold")
#define REGSTR_VAL_WRINTTHRESHOLD	TEXT("WRIntThreshold")
#define REGSTR_VAL_PRIORITY	TEXT("Priority")
#define REGSTR_VAL_DRIVER	TEXT("Driver")
#define REGSTR_VAL_FUNCDESC	TEXT("FunctionDesc")
#define REGSTR_VAL_FORCEDCONFIG TEXT("ForcedConfig")
#define REGSTR_VAL_CONFIGFLAGS	TEXT("ConfigFlags")
#define REGSTR_VAL_CSCONFIGFLAGS TEXT("CSConfigFlags")
#define CONFIGFLAG_DISABLED	1
#define CONFIGFLAG_REMOVED	2
#define CONFIGFLAG_MANUAL_INSTALL 4
#define CONFIGFLAG_IGNORE_BOOT_LC 8
#define CONFIGFLAG_NET_BOOT	16
#define CONFIGFLAG_REINSTALL	32
#define CONFIGFLAG_FAILEDINSTALL	64
#define CONFIGFLAG_CANTSTOPACHILD	128
#define CONFIGFLAG_OKREMOVEROM	256
#define CONFIGFLAG_NOREMOVEEXIT	512
#define CSCONFIGFLAG_BITS	7
#define CSCONFIGFLAG_DISABLED	1
#define CSCONFIGFLAG_DO_NOT_CREATE	2
#define CSCONFIGFLAG_DO_NOT_START	4
#define DMSTATEFLAG_APPLYTOALL 1
#define	REGSTR_VAL_ROOT_DEVNODE	TEXT("HTREE\\ROOT\\0")
#define	REGSTR_VAL_RESERVED_DEVNODE	TEXT("HTREE\\RESERVED\\0")
#define	REGSTR_PATH_READDATAPORT	REGSTR_KEY_ISAENUM TEXT("\\ReadDataPort\\0")
#define	REGSTR_PATH_MULTI_FUNCTION	TEXT("MF")
#define	REGSTR_VAL_RESOURCE_MAP	TEXT("ResourceMap")
#define	REGSTR_PATH_CHILD_PREFIX	TEXT("Child")
#define	NUM_RESOURCE_MAP	256
#define	REGSTR_VAL_MF_FLAGS	TEXT("MFFlags")
#define	MF_FLAGS_EVEN_IF_NO_RESOURCE	1
#define	MF_FLAGS_NO_CREATE_IF_NO_RESOURCE	2
#define	MF_FLAGS_FILL_IN_UNKNOWN_RESOURCE	4
#define	MF_FLAGS_CREATE_BUT_NO_SHOW_DISABLED	8
#define	EISAFLAG_NO_IO_MERGE	1
#define	EISAFLAG_SLOT_IO_FIRST	2
#define	EISA_NO_MAX_FUNCTION	0xFF
#define	NUM_EISA_RANGES	4
#define REGSTR_VAL_DRVDESC	TEXT("DriverDesc")
#define REGSTR_VAL_DEVLOADER	TEXT("DevLoader")
#define REGSTR_VAL_STATICVXD	TEXT("StaticVxD")
#define REGSTR_VAL_PROPERTIES	TEXT("Properties")
#define REGSTR_VAL_MANUFACTURER TEXT("Manufacturer")
#define REGSTR_VAL_EXISTS	TEXT("Exists")
#define REGSTR_VAL_CMENUMFLAGS	TEXT("CMEnumFlags")
#define REGSTR_VAL_CMDRIVFLAGS	TEXT("CMDrivFlags")
#define	REGSTR_VAL_ENUMERATOR	TEXT("Enumerator")
#define	REGSTR_VAL_DEVICEDRIVER	TEXT("DeviceDriver")
#define REGSTR_VAL_PORTNAME	TEXT("PortName")
#define REGSTR_VAL_INFPATH TEXT("InfPath")
#define REGSTR_VAL_INFSECTION	TEXT("InfSection")
#define REGSTR_VAL_POLLING	TEXT("Polling")
#define REGSTR_VAL_DONTLOADIFCONFLICT TEXT("DontLoadIfConflict")
#define REGSTR_VAL_PORTSUBCLASS TEXT("PortSubClass")
#define REGSTR_VAL_NETCLEAN TEXT("NetClean")
#define REGSTR_VAL_IDE_NO_SERIALIZE TEXT("IDENoSerialize")
#define REGSTR_VAL_NOCMOSORFDPT TEXT("NoCMOSorFDPT")
#define REGSTR_VAL_COMVERIFYBASE TEXT("COMVerifyBase")
#define REGSTR_KEY_OVERRIDE	TEXT("Override")
#define	REGSTR_VAL_CONFIGMG	TEXT("CONFIGMG")
#define REGSTR_VAL_SYSDM	TEXT("SysDM")
#define REGSTR_VAL_SYSDMFUNC	TEXT("SysDMFunc")
#define	REGSTR_VAL_PRIVATE	TEXT("Private")
#define	REGSTR_VAL_PRIVATEFUNC	TEXT("PrivateFunc")
#define	REGSTR_VAL_DETECT	TEXT("Detect")
#define	REGSTR_VAL_DETECTFUNC	TEXT("DetectFunc")
#define	REGSTR_VAL_ASKFORCONFIG	TEXT("AskForConfig")
#define	REGSTR_VAL_ASKFORCONFIGFUNC TEXT("AskForConfigFunc")
#define	REGSTR_VAL_WAITFORUNDOCK TEXT("WaitForUndock")
#define	REGSTR_VAL_WAITFORUNDOCKFUNC TEXT("WaitForUndockFunc")
#define	REGSTR_VAL_REMOVEROMOKAY TEXT("RemoveRomOkay")
#define	REGSTR_VAL_REMOVEROMOKAYFUNC TEXT("RemoveRomOkayFunc")
#define REGSTR_VAL_CURCONFIG	TEXT("CurrentConfig")
#define REGSTR_VAL_FRIENDLYNAME TEXT("FriendlyName")
#define REGSTR_VAL_CURRENTCONFIG TEXT("CurrentConfig")
#define REGSTR_VAL_MAP	TEXT("Map")
#define REGSTR_VAL_ID	TEXT("CurrentID")
#define REGSTR_VAL_DOCKED	TEXT("CurrentDockedState")
#define REGSTR_VAL_CHECKSUM	TEXT("CurrentChecksum")
#define REGSTR_VAL_HWDETECT	TEXT("HardwareDetect")
#define REGSTR_VAL_INHIBITRESULTS TEXT("InhibitResults")
#define REGSTR_VAL_PROFILEFLAGS TEXT("ProfileFlags")
#define REGSTR_KEY_PCMCIA	TEXT("PCMCIA\\")
#define REGSTR_KEY_PCUNKNOWN	TEXT("UNKNOWN_MANUFACTURER")
#define REGSTR_VAL_PCSSDRIVER	TEXT("Driver")
#define REGSTR_KEY_PCMTD	TEXT("MTD-")
#define REGSTR_VAL_PCMTDRIVER	TEXT("MTD")
#define REGSTR_VAL_HARDWAREID	TEXT("HardwareID")
#define REGSTR_VAL_INSTALLER	TEXT("Installer")
#define REGSTR_VAL_INSICON	TEXT("Icon")
#define REGSTR_VAL_ENUMPROPPAGES TEXT("EnumPropPages")
#define REGSTR_VAL_BASICPROPERTIES TEXT("BasicProperties")
#define REGSTR_VAL_PRIVATEPROBLEM TEXT("PrivateProblem")
#define REGSTR_KEY_CURRENT	TEXT("Current")
#define REGSTR_KEY_DEFAULT	TEXT("Default")
#define REGSTR_KEY_MODES	TEXT("Modes")
#define REGSTR_VAL_MODE TEXT("Mode")
#define REGSTR_VAL_BPP	TEXT("BPP")
#define REGSTR_VAL_HRES TEXT("HRes")
#define REGSTR_VAL_VRES TEXT("VRes")
#define REGSTR_VAL_FONTSIZE	TEXT("FontSize")
#define REGSTR_VAL_DRV	TEXT("drv")
#define REGSTR_VAL_GRB	TEXT("grb")
#define REGSTR_VAL_VDD	TEXT("vdd")
#define REGSTR_VAL_VER	TEXT("Ver")
#define REGSTR_VAL_MAXRES	TEXT("MaxResolution")
#define REGSTR_VAL_DPMS TEXT("DPMS")
#define REGSTR_VAL_RESUMERESET TEXT("ResumeReset")
#define REGSTR_VAL_DESCRIPTION TEXT("Description")
#define REGSTR_KEY_SYSTEM	TEXT("System")
#define REGSTR_KEY_USER TEXT("User")
#define REGSTR_VAL_DPI	TEXT("dpi")
#define REGSTR_VAL_PCICOPTIONS	TEXT("PCICOptions")

#ifndef NEC_98
#define PCIC_DEFAULT_IRQMASK	0x4EB8
#else
#define PCIC_DEFAULT_IRQMASK	0x1468
#endif

#define PCIC_DEFAULT_NUMSOCKETS 0
#define REGSTR_VAL_PCICIRQMAP	TEXT("PCICIRQMap")
#define REGSTR_PATH_APPEARANCE	TEXT("Control Panel\\Appearance")
#define REGSTR_PATH_LOOKSCHEMES TEXT("Control Panel\\Appearance\\Schemes")
#define REGSTR_VAL_CUSTOMCOLORS TEXT("CustomColors")
#define REGSTR_PATH_SCREENSAVE TEXT("Control Panel\\Desktop")
#define REGSTR_VALUE_USESCRPASSWORD TEXT("ScreenSaveUsePassword")
#define REGSTR_VALUE_SCRPASSWORD TEXT("ScreenSave_Data")
#define REGSTR_VALUE_LOWPOWERTIMEOUT	TEXT("ScreenSaveLowPowerTimeout")
#define REGSTR_VALUE_POWEROFFTIMEOUT	TEXT("ScreenSavePowerOffTimeout")
#define REGSTR_VALUE_LOWPOWERACTIVE	TEXT("ScreenSaveLowPowerActive")
#define REGSTR_VALUE_POWEROFFACTIVE	TEXT("ScreenSavePowerOffActive")
#define REGSTR_PATH_WINDOWSAPPLETS TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Applets")
#define REGSTR_PATH_SYSTRAY TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Applets\\SysTray")
#define REGSTR_VAL_SYSTRAYSVCS TEXT("Services")
#define REGSTR_VAL_SYSTRAYBATFLAGS TEXT("PowerFlags")
#define REGSTR_VAL_SYSTRAYPCCARDFLAGS TEXT("PCMCIAFlags")
#define REGSTR_PATH_NETWORK_USERSETTINGS	TEXT("Network")
#define REGSTR_KEY_NETWORK_PERSISTENT	TEXT("\\Persistent")
#define REGSTR_KEY_NETWORK_RECENT	TEXT("\\Recent")
#define REGSTR_VAL_REMOTE_PATH	TEXT("RemotePath")
#define REGSTR_VAL_USER_NAME	TEXT("UserName")
#define REGSTR_VAL_PROVIDER_NAME	TEXT("ProviderName")
#define REGSTR_VAL_CONNECTION_TYPE	TEXT("ConnectionType")
#define REGSTR_VAL_UPGRADE	TEXT("Upgrade")
#define REGSTR_KEY_LOGON TEXT("\\Logon")
#define REGSTR_VAL_MUSTBEVALIDATED TEXT("MustBeValidated")
#define REGSTR_VAL_RUNLOGINSCRIPT	TEXT("ProcessLoginScript")
#define REGSTR_KEY_NETWORKPROVIDER TEXT("\\NetworkProvider")
#define REGSTR_PATH_NW32NETPROVIDER REGSTR_PATH_SERVICES TEXT("\\NWNP32" REGSTR_KEY_NETWORKPROVIDER
#define REGSTR_PATH_MS32NETPROVIDER REGSTR_PATH_SERVICES TEXT("\\MSNP32" REGSTR_KEY_NETWORKPROVIDER
#define REGSTR_VAL_AUTHENT_AGENT TEXT("AuthenticatingAgent")
#define REGSTR_VAL_PREFREDIR TEXT("PreferredRedir")
#define REGSTR_VAL_AUTOSTART TEXT("AutoStart")
#define REGSTR_VAL_AUTOLOGON TEXT("AutoLogon")
#define REGSTR_VAL_NETCARD TEXT("Netcard")
#define REGSTR_VAL_TRANSPORT TEXT("Transport")
#define REGSTR_VAL_DYNAMIC TEXT("Dynamic")
#define REGSTR_VAL_TRANSITION TEXT("Transition")
#define REGSTR_VAL_STATICDRIVE TEXT("StaticDrive")
#define REGSTR_VAL_LOADHI TEXT("LoadHi")
#define REGSTR_VAL_LOADRMDRIVERS TEXT("LoadRMDrivers")
#define REGSTR_VAL_SETUPN TEXT("SetupN")
#define REGSTR_VAL_SETUPNPATH TEXT("SetupNPath")
#define REGSTR_VAL_WRKGRP_FORCEMAPPING TEXT("WrkgrpForceMapping")
#define REGSTR_VAL_WRKGRP_REQUIRED TEXT("WrkgrpRequired")
#define REGSTR_PATH_CURRENT_CONTROL_SET	TEXT("System\\CurrentControlSet\\Control")
#define REGSTR_VAL_CURRENT_USER	TEXT("Current User")
#define REGSTR_PATH_PWDPROVIDER	TEXT("System\\CurrentControlSet\\Control\\PwdProvider")
#define REGSTR_VAL_PWDPROVIDER_PATH TEXT("ProviderPath")
#define REGSTR_VAL_PWDPROVIDER_DESC TEXT("Description")
#define REGSTR_VAL_PWDPROVIDER_CHANGEPWD TEXT("ChangePassword")
#define REGSTR_VAL_PWDPROVIDER_CHANGEPWDHWND TEXT("ChangePasswordHwnd")
#define REGSTR_VAL_PWDPROVIDER_GETPWDSTATUS TEXT("GetPasswordStatus")
#define REGSTR_VAL_PWDPROVIDER_ISNP TEXT("NetworkProvider")
#define REGSTR_VAL_PWDPROVIDER_CHANGEORDER TEXT("ChangeOrder")
#define REGSTR_PATH_POLICIES	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Policies")
#define REGSTR_PATH_UPDATE	TEXT("System\\CurrentControlSet\\Control\\Update")
#define REGSTR_VALUE_ENABLE	TEXT("Enable")
#define REGSTR_VALUE_VERBOSE	TEXT("Verbose")
#define REGSTR_VALUE_NETPATH	TEXT("NetworkPath")
#define REGSTR_VALUE_DEFAULTLOC	TEXT("UseDefaultNetLocation")
#define REGSTR_KEY_NETWORK	TEXT("Network")
#define REGSTR_KEY_SYSTEM	TEXT("System")
#define REGSTR_KEY_PRINTERS	TEXT("Printers")
#define REGSTR_KEY_WINOLDAPP	TEXT("WinOldApp")
#define REGSTR_VAL_NOFILESHARING	TEXT("NoFileSharing")
#define REGSTR_VAL_NOPRINTSHARING	TEXT("NoPrintSharing")
#define REGSTR_VAL_NOFILESHARINGCTRL	TEXT("NoFileSharingControl")
#define REGSTR_VAL_NOPRINTSHARINGCTRL	TEXT("NoPrintSharingControl")
#define REGSTR_VAL_HIDESHAREPWDS	TEXT("HideSharePwds")
#define REGSTR_VAL_DISABLEPWDCACHING	TEXT("DisablePwdCaching")
#define REGSTR_VAL_ALPHANUMPWDS	TEXT("AlphanumPwds")
#define REGSTR_VAL_NETSETUP_DISABLE	TEXT("NoNetSetup")
#define REGSTR_VAL_NETSETUP_NOCONFIGPAGE	TEXT("NoNetSetupConfigPage")
#define REGSTR_VAL_NETSETUP_NOIDPAGE	TEXT("NoNetSetupIDPage")
#define REGSTR_VAL_NETSETUP_NOSECURITYPAGE	TEXT("NoNetSetupSecurityPage")
#define REGSTR_VAL_SYSTEMCPL_NOVIRTMEMPAGE TEXT("NoVirtMemPage")
#define REGSTR_VAL_SYSTEMCPL_NODEVMGRPAGE TEXT("NoDevMgrPage")
#define REGSTR_VAL_SYSTEMCPL_NOCONFIGPAGE	TEXT("NoConfigPage")
#define REGSTR_VAL_SYSTEMCPL_NOFILESYSPAGE	TEXT("NoFileSysPage")
#define REGSTR_VAL_DISPCPL_NODISPCPL	TEXT("NoDispCPL")
#define REGSTR_VAL_DISPCPL_NOBACKGROUNDPAGE TEXT("NoDispBackgroundPage")
#define REGSTR_VAL_DISPCPL_NOSCRSAVPAGE TEXT("NoDispScrSavPage")
#define REGSTR_VAL_DISPCPL_NOAPPEARANCEPAGE TEXT("NoDispAppearancePage")
#define REGSTR_VAL_DISPCPL_NOSETTINGSPAGE TEXT("NoDispSettingsPage")
#define REGSTR_VAL_SECCPL_NOSECCPL	TEXT("NoSecCPL")
#define REGSTR_VAL_SECCPL_NOPWDPAGE	TEXT("NoPwdPage")
#define REGSTR_VAL_SECCPL_NOADMINPAGE	TEXT("NoAdminPage")
#define REGSTR_VAL_SECCPL_NOPROFILEPAGE	TEXT("NoProfilePage")
#define REGSTR_VAL_PRINTERS_HIDETABS	TEXT("NoPrinterTabs")
#define REGSTR_VAL_PRINTERS_NODELETE	TEXT("NoDeletePrinter")
#define REGSTR_VAL_PRINTERS_NOADD	TEXT("NoAddPrinter")
#define REGSTR_VAL_WINOLDAPP_DISABLED	TEXT("Disabled")
#define REGSTR_VAL_WINOLDAPP_NOREALMODE	TEXT("NoRealMode")
#define REGSTR_VAL_NOENTIRENETWORK	TEXT("NoEntireNetwork")
#define REGSTR_VAL_NOWORKGROUPCONTENTS	TEXT("NoWorkgroupContents")
#define REGSTR_VAL_MINPWDLEN	TEXT("MinPwdLen")
#define REGSTR_VAL_PWDEXPIRATION	TEXT("PwdExpiration")
#define REGSTR_VAL_WIN31PROVIDER	TEXT("Win31Provider")
#define REGSTR_VAL_DISABLEREGTOOLS	TEXT("DisableRegistryTools")
#define REGSTR_PATH_WINLOGON	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Winlogon")
#define REGSTR_VAL_LEGALNOTICECAPTION	TEXT("LegalNoticeCaption")
#define REGSTR_VAL_LEGALNOTICETEXT	TEXT("LegalNoticeText")
#define REGSTR_VAL_RESTRICTRUN	TEXT("RestrictRun")
#define REGSTR_KEY_POL_USERS	TEXT("Users")
#define REGSTR_KEY_POL_COMPUTERS	TEXT("Computers")
#define REGSTR_KEY_POL_USERGROUPS	TEXT("UserGroups")
#define REGSTR_KEY_POL_DEFAULT	TEXT(".default")
#define REGSTR_KEY_POL_USERGROUPDATA TEXT("GroupData\\UserGroups\\Priority")
#define REGSTR_PATH_TIMEZONE	TEXT("System\\CurrentControlSet\\Control\\TimeZoneInformation")
#define REGSTR_VAL_TZBIAS	TEXT("Bias")
#define REGSTR_VAL_TZDLTBIAS	TEXT("DaylightBias")
#define REGSTR_VAL_TZSTDBIAS	TEXT("StandardBias")
#define REGSTR_VAL_TZACTBIAS	TEXT("ActiveTimeBias")
#define REGSTR_VAL_TZDLTFLAG	TEXT("DaylightFlag")
#define REGSTR_VAL_TZSTDSTART	TEXT("StandardStart")
#define REGSTR_VAL_TZDLTSTART	TEXT("DaylightStart")
#define REGSTR_VAL_TZDLTNAME	TEXT("DaylightName")
#define REGSTR_VAL_TZSTDNAME	TEXT("StandardName")
#define REGSTR_VAL_TZNOCHANGESTART TEXT("NoChangeStart")
#define REGSTR_VAL_TZNOCHANGEEND TEXT("NoChangeEnd")
#define REGSTR_VAL_TZNOAUTOTIME TEXT("DisableAutoDaylightTimeSet")
#define REGSTR_PATH_FLOATINGPOINTPROCESSOR TEXT("HARDWARE\\DESCRIPTION\\System\\FloatingPointProcessor")
#define REGSTR_PATH_FLOATINGPOINTPROCESSOR0 TEXT("HARDWARE\\DESCRIPTION\\System\\FloatingPointProcessor\\0")
#define REGSTR_PATH_COMPUTRNAME TEXT("System\\CurrentControlSet\\Control\\ComputerName\\ComputerName")
#define REGSTR_VAL_COMPUTRNAME TEXT("ComputerName")
#define REGSTR_PATH_SHUTDOWN TEXT("System\\CurrentControlSet\\Control\\Shutdown")
#define REGSTR_VAL_FORCEREBOOT TEXT("ForceReboot")
#define REGSTR_VAL_SETUPPROGRAMRAN TEXT("SetupProgramRan")
#define REGSTR_VAL_DOES_POLLING TEXT("PollingSupportNeeded")
#define REGSTR_PATH_KNOWNDLLS	TEXT("System\\CurrentControlSet\\Control\\SessionManager\\KnownDLLs")
#define REGSTR_PATH_KNOWN16DLLS	TEXT("System\\CurrentControlSet\\Control\\SessionManager\\Known16DLLs")
#define REGSTR_PATH_CHECKVERDLLS TEXT("System\\CurrentControlSet\\Control\\SessionManager\\CheckVerDLLs")
#define REGSTR_PATH_WARNVERDLLS TEXT("System\\CurrentControlSet\\Control\\SessionManager\\WarnVerDLLs")
#define REGSTR_PATH_HACKINIFILE TEXT("System\\CurrentControlSet\\Control\\SessionManager\\HackIniFiles")
#define REGSTR_PATH_CHECKBADAPPS TEXT("System\\CurrentControlSet\\Control\\SessionManager\\CheckBadApps")
#define REGSTR_PATH_APPPATCH TEXT("System\\CurrentControlSet\\Control\\SessionManager\\AppPatches")
#define REGSTR_PATH_KNOWNVXDS	TEXT("System\\CurrentControlSet\\Control\\SessionManager\\KnownVxDs")
#define REGSTR_VAL_UNINSTALLER_DISPLAYNAME TEXT("DisplayName")
#define REGSTR_VAL_UNINSTALLER_COMMANDLINE TEXT("UninstallString")
#define REGSTR_PATH_DESKTOP	REGSTR_PATH_SCREENSAVE
#define REGSTR_PATH_MOUSE	TEXT("Control Panel\\Mouse")
#define REGSTR_PATH_KEYBOARD TEXT("Control Panel\\Keyboard")
#define REGSTR_PATH_COLORS	TEXT("Control Panel\\Colors")
#define REGSTR_PATH_SOUND	TEXT("Control Panel\\Sound")
#define REGSTR_PATH_METRICS	TEXT("Control Panel\\Desktop\\WindowMetrics")
#define REGSTR_PATH_ICONS TEXT("Control Panel\\Icons")
#define REGSTR_PATH_CURSORS TEXT("Control Panel\\Cursors")
#define REGSTR_PATH_CHECKDISK	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Applets\\Check Drive")
#define REGSTR_PATH_CHECKDISKSET TEXT("Settings")
#define REGSTR_PATH_CHECKDISKUDRVS TEXT("NoUnknownDDErrDrvs")
#define REGSTR_PATH_FAULT	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Fault")
#define REGSTR_VAL_FAULT_LOGFILE	TEXT("LogFile")
#define	REGSTR_PATH_AEDEBUG	TEXT("Software\\Microsoft\\Windows NT\\CurrentVersion\\AeDebug")
#define REGSTR_VAL_AEDEBUG_DEBUGGER	TEXT("Debugger")
#define REGSTR_VAL_AEDEBUG_AUTO	TEXT("Auto")
#define REGSTR_PATH_GRPCONV	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\GrpConv")
#define REGSTR_VAL_REGITEMDELETEMESSAGE TEXT("Removal Message")
#define REGSTR_PATH_LASTCHECK	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\LastCheck")
#define REGSTR_PATH_LASTOPTIMIZE	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\LastOptimize")
#define REGSTR_PATH_LASTBACKUP	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\LastBackup")
#define REGSTR_PATH_CHKLASTCHECK	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Applets\\Check Drive\\LastCheck")
#define REGSTR_PATH_CHKLASTSURFAN	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Applets\\Check Drive\\LastSurfaceAnalysis")
#define DTRESULTOK	0
#define DTRESULTFIX	1
#define DTRESULTPROB	2
#define DTRESULTPART	3
#define REGSTR_KEY_SHARES	TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Network\\LanMan")
#define REGSTR_VAL_SHARES_FLAGS TEXT("Flags")
#define REGSTR_VAL_SHARES_TYPE TEXT("Type")
#define REGSTR_VAL_SHARES_PATH TEXT("Path")
#define REGSTR_VAL_SHARES_REMARK TEXT("Remark")
#define REGSTR_VAL_SHARES_RW_PASS TEXT("Parm1")
#define REGSTR_VAL_SHARES_RO_PASS TEXT("Parm2")
#define REGSTR_PATH_PRINT TEXT("System\\CurrentControlSet\\Control\\Print")
#define REGSTR_PATH_PRINTERS TEXT("System\\CurrentControlSet\\Control\\Print\\Printers")
#define REGSTR_PATH_PROVIDERS TEXT("System\\CurrentControlSet\\Control\\Print\\Providers")
#define REGSTR_PATH_MONITORS TEXT("System\\CurrentControlSet\\Control\\Print\\Monitors")
#define REGSTR_PATH_ENVIRONMENTS TEXT("System\\CurrentControlSet\\Control\\Print\\Environments")
#define REGSTR_VAL_START_ON_BOOT TEXT("StartOnBoot")
#define REGSTR_VAL_PRINTERS_MASK TEXT("PrintersMask")
#define REGSTR_VAL_DOS_SPOOL_MASK TEXT("DOSSpoolMask")
#define REGSTR_KEY_CURRENT_ENV TEXT("\\Windows 4.0")
#define REGSTR_KEY_DRIVERS TEXT("\\Drivers")
#define REGSTR_KEY_PRINT_PROC TEXT("\\Print Processors")
#define REGSTR_PATH_EVENTLABELS TEXT("AppEvents\\EventLabels")
#define REGSTR_PATH_SCHEMES TEXT("AppEvents\\Schemes")
#define REGSTR_PATH_APPS REGSTR_PATH_SCHEMES TEXT("\\Apps")
#define REGSTR_PATH_APPS_DEFAULT REGSTR_PATH_SCHEMES TEXT("\\Apps\\.Default")
#define REGSTR_PATH_NAMES REGSTR_PATH_SCHEMES TEXT("\\Names")
#define REGSTR_PATH_MULTIMEDIA REGSTR_PATH_SETUP TEXT("\\Multimedia")
#define REGSTR_PATH_MULTIMEDIA_AUDIO TEXT("Software\\Microsoft\\Multimedia\\Audio")
#define REGSTR_PATH_MEDIARESOURCES REGSTR_PATH_CURRENT_CONTROL_SET TEXT("\\MediaResources")
#define REGSTR_PATH_MEDIAPROPERTIES REGSTR_PATH_CURRENT_CONTROL_SET TEXT("\\MediaProperties")
#define REGSTR_PATH_PRIVATEPROPERTIES REGSTR_PATH_MEDIAPROPERTIES TEXT("\\PrivateProperties")
#define REGSTR_PATH_PUBLICPROPERTIES REGSTR_PATH_MEDIAPROPERTIES TEXT("\\PublicProperties")
#define REGSTR_PATH_JOYOEM REGSTR_PATH_PRIVATEPROPERTIES TEXT("\\Joystick\\OEM")
#define REGSTR_PATH_JOYCONFIG REGSTR_PATH_MEDIARESOURCES TEXT("\\Joystick")
#define REGSTR_KEY_JOYCURR TEXT("CurrentJoystickSettings")
#define REGSTR_KEY_JOYSETTINGS TEXT("JoystickSettings")
#define REGSTR_VAL_JOYUSERVALUES TEXT("JoystickUserValues")
#define REGSTR_VAL_JOYCALLOUT	TEXT("JoystickCallout")
#define REGSTR_VAL_JOYNCONFIG	TEXT("Joystick%dConfiguration")
#define REGSTR_VAL_JOYNOEMNAME	TEXT("Joystick%dOEMName")
#define REGSTR_VAL_JOYNOEMCALLOUT TEXT("Joystick%dOEMCallout")
#define REGSTR_VAL_JOYOEMCALLOUT	TEXT("OEMCallout")
#define REGSTR_VAL_JOYOEMNAME	TEXT("OEMName")
#define REGSTR_VAL_JOYOEMDATA	TEXT("OEMData")
#define REGSTR_VAL_JOYOEMXYLABEL	TEXT("OEMXYLabel")
#define REGSTR_VAL_JOYOEMZLABEL	TEXT("OEMZLabel")
#define REGSTR_VAL_JOYOEMRLABEL	TEXT("OEMRLabel")
#define REGSTR_VAL_JOYOEMPOVLABEL	TEXT("OEMPOVLabel")
#define REGSTR_VAL_JOYOEMULABEL	TEXT("OEMULabel")
#define REGSTR_VAL_JOYOEMVLABEL	TEXT("OEMVLabel")
#define REGSTR_VAL_JOYOEMTESTMOVEDESC	TEXT("OEMTestMoveDesc")
#define REGSTR_VAL_JOYOEMTESTBUTTONDESC	TEXT("OEMTestButtonDesc")
#define REGSTR_VAL_JOYOEMTESTMOVECAP	TEXT("OEMTestMoveCap")
#define REGSTR_VAL_JOYOEMTESTBUTTONCAP	TEXT("OEMTestButtonCap")
#define REGSTR_VAL_JOYOEMTESTWINCAP	TEXT("OEMTestWinCap")
#define REGSTR_VAL_JOYOEMCALCAP	TEXT("OEMCalCap")
#define REGSTR_VAL_JOYOEMCALWINCAP	TEXT("OEMCalWinCap")
#define REGSTR_VAL_JOYOEMCAL1	TEXT("OEMCal1")
#define REGSTR_VAL_JOYOEMCAL2	TEXT("OEMCal2")
#define REGSTR_VAL_JOYOEMCAL3	TEXT("OEMCal3")
#define REGSTR_VAL_JOYOEMCAL4	TEXT("OEMCal4")
#define REGSTR_VAL_JOYOEMCAL5	TEXT("OEMCal5")
#define REGSTR_VAL_JOYOEMCAL6	TEXT("OEMCal6")
#define REGSTR_VAL_JOYOEMCAL7	TEXT("OEMCal7")
#define REGSTR_VAL_JOYOEMCAL8	TEXT("OEMCal8")
#define REGSTR_VAL_JOYOEMCAL9	TEXT("OEMCal9")
#define REGSTR_VAL_JOYOEMCAL10	TEXT("OEMCal10")
#define REGSTR_VAL_JOYOEMCAL11	TEXT("OEMCal11")
#define REGSTR_VAL_JOYOEMCAL12	TEXT("OEMCal12")

#ifndef NEC_98
#define REGSTR_KEY_ISAENUM	TEXT("ISAPnP")
#define REGSTR_KEY_EISAENUM	TEXT("EISA")
#define	REGSTR_VAL_EISA_RANGES	TEXT("EISARanges")
#define	REGSTR_VAL_EISA_FUNCTIONS	TEXT("EISAFunctions")
#define	REGSTR_VAL_EISA_FUNCTIONS_MASK	TEXT("EISAFunctionsMask")
#define	REGSTR_VAL_EISA_FLAGS	TEXT("EISAFlags")
#define	REGSTR_VAL_EISA_SIMULATE_INT15	TEXT("EISASimulateInt15")
#else
#define REGSTR_KEY_ISAENUM	TEXT("C98PnP")
#define REGSTR_KEY_EISAENUM	TEXT("NESA")
#define	REGSTR_VAL_EISA_RANGES	TEXT("NESARanges")
#define	REGSTR_VAL_EISA_FUNCTIONS	TEXT("NESAFunctions")
#define	REGSTR_VAL_EISA_FUNCTIONS_MASK	TEXT("NESAFunctionsMask")
#define	REGSTR_VAL_EISA_FLAGS	TEXT("NESAFlags")
#define	REGSTR_VAL_EISA_SIMULATE_INT15	TEXT("NESASimulateInt15")
#endif

typedef struct _DSKTLSYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
	WORD wResult;
} DSKTLSYSTEMTIME,*PDSKTLSYSTEMTIME,*LPDSKTLSYSTEMTIME;

#ifdef __cplusplus
}
#endif

#endif