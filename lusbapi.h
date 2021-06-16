//---------------------------------------------------------------------------
#ifndef __USBAPIH
#define __USBAPIH
// -----------------------------------------------------------------------------
// ---------------------------- COMMON PART ------------------------------------
// -----------------------------------------------------------------------------
#include <windows.h>
// ������ ����������
#define 	LC_VERMAJOR 				2    	// ������ ���� �����
#define 	LC_VERMINOR 				1		// ������ ���� �����
#define 	LC_CURRENT_VERSION     	((LC_VERMAJOR<<16)|LC_VERMINOR)
#define InitLDevice(Slot) OpenLDevice(Slot)
extern "C" DWORD WINAPI GetDllVersion(void);
extern "C" LPVOID WINAPI CreateInstance(const char *DeviceName);
// -----------------------------------------------------------------------------
// ------------------------------- E-440 ---------------------------------------
// -----------------------------------------------------------------------------
#pragma pack(1)
// ���������, �������� ����� ������ ��� ��� ������ E-440
struct ADC_PARS_E440
{
   WORD size;
   bool AdcEnabled;						// ����������/���������� ������ ���
   bool CorrectionEnabled;				// ���������� �������������� ������
   WORD InputMode;						// ����� ����� ����� � ���
   WORD SynchroAdType;					// ��� ���������� �������������
   WORD SynchroAdMode; 					// ����� ���������� ������������
   WORD SynchroAdChannel;  	    		// ����� ��� ��� ���������� �������������
   SHORT SynchroAdPorog; 				// ����� ������������ ��� ��� ���������� �������������
   WORD ChannelsQuantity;				// ����� �������� �������
   WORD ControlTable[128];				// ����������� ������� � ��������� ��������
   double AdcRate;	  			  		// ������� ������ ��� � ���
   double InterKadrDelay;		  		// ����������� �������� � ��
   double ChannelRate;					// ������� ������ ������
   WORD AdcFifoBaseAddress;	    		// ������� ����� FIFO ������ ���
   WORD AdcFifoLength;					// ����� FIFO ������ ���
   WORD CalibrKoefAdc[8];				// ���������������� ����. ��� ���
};                                      //
// ���������, �������� ����� ������ ��� ��� ������ E-440
struct DAC_PARS_E440                    //
{                                       //
   WORD size;                           //
   bool DacEnabled;						// ����������/���������� ������ ���
   double DacRate;	  			  		// ������� ������ ��� � ���
   WORD DacFifoBaseAddress;		    	// ������� ����� FIFO ������ ���
   WORD DacFifoLength;					// ����� FIFO ������ ���
};                                      //
// ���������, ���������� ���������� � �����, ������� �������� � ����. ����
struct MODULE_DESCR_E440                //
{                                       //
   WORD size;						 	// ������ ���������
   char SerialNumber[9];  				// �������� �����
   char Name[7];					 	// �������� �����
   char Revision;					 	// ������� �����
   char Dsp_Type[5];				 	// ��� �������������� DSP
   char IsDacPresented; 				// ������ ������� ���
   long QuartzFrequency; 				// ������� ������ � ��
   char ReservedWord[13];				// ���������������
   WORD CalibrKoefAdc[8];				// ���������������� ����. ��� ���
   WORD CalibrKoefDac[4];				// ���������������� ����. ��� ���
};
#pragma pack()
// ��������� ��� ������ E-440
struct ILE440
{
// ������� ������ ����������
	virtual HANDLE WINAPI GetModuleHandle(void) = 0;
	virtual bool WINAPI OpenLDevice(WORD VirtualSlot) = 0;
	virtual bool WINAPI CloseLDevice(void) = 0;
	virtual bool WINAPI GetModuleName(char *ModuleName) = 0;
	virtual bool WINAPI ReleaseLDevice(void) = 0;
	virtual bool WINAPI DSP_RESET(void) = 0;
	virtual bool WINAPI LOAD_LBIOS(PCHAR FileName = NULL) = 0;
	virtual bool WINAPI MODULE_TEST(void) = 0;
	virtual bool WINAPI GET_LBIOS_VERSION(DWORD *LbiosVersion) = 0;
	virtual bool WINAPI SEND_COMMAND(const WORD Command) = 0;
	virtual bool WINAPI GO_SLEEP(void) = 0;
// ������� ��� ������ � ���
	virtual bool WINAPI GET_CUR_ADC_PARS(ADC_PARS_E440 *am) = 0;
	virtual bool WINAPI FILL_ADC_PARS(ADC_PARS_E440 *am) = 0;
	virtual bool WINAPI START_ADC(void) = 0;
	virtual bool WINAPI STOP_ADC(void) = 0;
	virtual bool WINAPI ADC_KADR(SHORT *Data) = 0;
	virtual bool WINAPI ADC_SAMPLE(SHORT *Data, WORD Channel) = 0;
// ������� �������/������ ������ �/�� �����
	virtual bool WINAPI ReadData(SHORT *lpBuffer, DWORD *nNumberOfWordsToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) = 0;
	virtual bool WINAPI WriteData(WORD *lpBuffer, DWORD *nNumberOfWordsToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) = 0;
// ������� ��� ������ � ���
	virtual bool WINAPI GET_CUR_DAC_PARS(DAC_PARS_E440 *dm) = 0;
	virtual bool WINAPI FILL_DAC_PARS(DAC_PARS_E440 *dm) = 0;
	virtual bool WINAPI START_DAC(void) = 0;
	virtual bool WINAPI STOP_DAC(void) = 0;
	virtual bool WINAPI DAC_SAMPLE(WORD Data, WORD Channel) = 0;
// ������� ��� ������ � ��� �������
	virtual bool WINAPI ENABLE_TTL_OUT(bool EnableTtlOut) = 0;
	virtual bool WINAPI TTL_IN(WORD *TtlIn) = 0;
	virtual bool WINAPI TTL_OUT(WORD TtlOut) = 0;
// ������� ��� ������ ����
	virtual bool WINAPI ENABLE_FLASH_WRITE(bool EnableFlashWrite) = 0;
	virtual bool WINAPI READ_FLASH_WORD(WORD FlashAddress, SHORT *FlashWord) = 0;
	virtual bool WINAPI WRITE_FLASH_WORD(WORD FlashAddress, SHORT FlashWord) = 0;
// ������� ��� ������ �� ��������� ����������� �� ����
	virtual bool WINAPI GET_MODULE_DESCR(MODULE_DESCR_E440 *pd) = 0;
	virtual bool WINAPI SAVE_MODULE_DESCR(MODULE_DESCR_E440 *pd) = 0;
// ������� ��� ������ � ������� DSP
	virtual bool WINAPI PUT_LBIOS_WORD(const WORD Address, SHORT Data) = 0;
	virtual bool WINAPI GET_LBIOS_WORD(const WORD Address, SHORT *Data) = 0;
	virtual bool WINAPI PUT_DM_WORD(const WORD Address, SHORT Data) = 0;
	virtual bool WINAPI GET_DM_WORD(const WORD Address, SHORT *Data) = 0;
	virtual bool WINAPI PUT_PM_WORD(const WORD Address, long Data) = 0;
	virtual bool WINAPI GET_PM_WORD(const WORD Address, long *Data) = 0;
	virtual bool WINAPI PUT_DM_ARRAY(const WORD BaseAddress, const WORD NPoints, SHORT *Data) = 0;
	virtual bool WINAPI GET_DM_ARRAY(const WORD BaseAddress, const WORD NPoints, SHORT *Data) = 0;
	virtual bool WINAPI PUT_PM_ARRAY(const WORD BaseAddress, const WORD NPoints, long *Data) = 0;
	virtual bool WINAPI GET_PM_ARRAY(const WORD BaseAddress, const WORD NPoints, long *Data) = 0;
// ������� ������ ������ � ��������� �������
	virtual int WINAPI GetLastErrorString(LPTSTR lpBuffer, DWORD nSize) = 0;
};
// ��������� ���� ������������� ������ E-440
enum {	NO_SYNC_E440=0, TTL_START_SYNC_E440, TTL_KADR_SYNC_E440, ANALOG_SYNC_E440, INVALID_SYNC_E440 };
// ����� ������ �������� ����� ������ � ������ ��������
const WORD DataBaseAddress_E440 = 0x30;
// ���������� LBIOS ��� E-440 (������������ � ������ �������� DSP)
#define    	L_PROGRAM_BASE_ADDRESS_E440				    (DataBaseAddress_E440 + 0x0)
#define    	L_READY_E440 								(DataBaseAddress_E440 + 0x1)
#define	  	L_TMODE1_E440 								(DataBaseAddress_E440 + 0x2)
#define	  	L_TMODE2_E440 								(DataBaseAddress_E440 + 0x3)
#define	  	L_TEST_LOAD_E440	 						(DataBaseAddress_E440 + 0x4)
#define	  	L_COMMAND_E440	 			      			(DataBaseAddress_E440 + 0x5)

#define		L_DAC_SCLK_DIV_E440							(DataBaseAddress_E440 + 0x7)
#define		L_DAC_RATE_E440								(DataBaseAddress_E440 + 0x8)
#define	  	L_ADC_RATE_E440  			      			(DataBaseAddress_E440 + 0x9)
#define		L_ADC_ENABLED_E440	 						(DataBaseAddress_E440 + 0xA)
#define		L_ADC_FIFO_BASE_ADDRESS_E440				(DataBaseAddress_E440 + 0xB)
#define		L_CUR_ADC_FIFO_LENGTH_E440					(DataBaseAddress_E440 + 0xC)
#define		L_ADC_FIFO_LENGTH_E440						(DataBaseAddress_E440 + 0xE)
#define		L_CORRECTION_ENABLED_E440					(DataBaseAddress_E440 + 0xF)
#define		L_LBIOS_VERSION_E440						(DataBaseAddress_E440 + 0x10)
#define		L_ADC_SAMPLE_E440							(DataBaseAddress_E440 + 0x11)
#define		L_ADC_CHANNEL_E440	 						(DataBaseAddress_E440 + 0x12)
#define		L_INPUT_MODE_E440							(DataBaseAddress_E440 + 0x13)
#define		L_SYNCHRO_AD_CHANNEL_E440					(DataBaseAddress_E440 + 0x16)
#define		L_SYNCHRO_AD_POROG_E440						(DataBaseAddress_E440 + 0x17)
#define		L_SYNCHRO_AD_MODE_E440 						(DataBaseAddress_E440 + 0x18)
#define		L_SYNCHRO_AD_TYPE_E440 						(DataBaseAddress_E440 + 0x19)

#define		L_CONTROL_TABLE_LENGHT_E440				    (DataBaseAddress_E440 + 0x1B)
#define		L_FIRST_SAMPLE_DELAY_E440					(DataBaseAddress_E440 + 0x1C)
#define		L_INTER_KADR_DELAY_E440						(DataBaseAddress_E440 + 0x1D)

#define		L_DAC_SAMPLE_E440							(DataBaseAddress_E440 + 0x20)
#define		L_DAC_ENABLED_E440					 		(DataBaseAddress_E440 + 0x21)
#define		L_DAC_FIFO_BASE_ADDRESS_E440				(DataBaseAddress_E440 + 0x22)
#define		L_CUR_DAC_FIFO_LENGTH_E440					(DataBaseAddress_E440 + 0x24)
#define		L_DAC_FIFO_LENGTH_E440						(DataBaseAddress_E440 + 0x25)

#define		L_FLASH_ENABLED_E440 						(DataBaseAddress_E440 + 0x26)
#define		L_FLASH_ADDRESS_E440 						(DataBaseAddress_E440 + 0x27)
#define		L_FLASH_DATA_E440 							(DataBaseAddress_E440 + 0x28)

#define		L_ENABLE_TTL_OUT_E440						(DataBaseAddress_E440 + 0x29)
#define		L_TTL_OUT_E440								(DataBaseAddress_E440 + 0x2A)
#define		L_TTL_IN_E440								(DataBaseAddress_E440 + 0x2B)

#define		L_SCALE_E440								(DataBaseAddress_E440 + 0x30)
#define		L_ZERO_E440									(DataBaseAddress_E440 + 0x34)

#define		L_CONTROL_TABLE_E440						0x80






















// -----------------------------------------------------------------------------
// ------------------------------- E-140 ---------------------------------------
// -----------------------------------------------------------------------------
#pragma pack(1)
// ���������, �������� ����� ������ ��� ��� ������ E-140
struct ADC_PARS_E140 {                  //
    WORD ClkSource;                     // �������� �������� ��������� ��� ������� ���
    WORD EnableClkOutput;               // ���������� ���������� �������� ��������� ������� ���
	WORD InputMode;						// ����� ����� ����� � ���
	WORD SynchroAdType;					// ��� ���������� �������������
	WORD SynchroAdMode; 				// ����� ���������� ������������
	WORD SynchroAdChannel;  			// ����� ��� ��� ���������� �������������
	SHORT SynchroAdPorog; 				// ����� ������������ ��� ��� ���������� �������������
    WORD ChannelsQuantity;				// ����� �������� �������
    WORD ControlTable[128];				// ����������� ������� � ��������� ��������
    double AdcRate;	  			  		// ������� ������ ��� � ���
    double InterKadrDelay;		  		// ����������� �������� � ��
	double ChannelRate;					// ������� ������ ������
};                                      //
// ���������, ���������� ���������� � �����, ������� �������� � ����. ����
struct MODULE_DESCR_E140                //
{                                       //
 char Name[11];				    		// �������� �����
 char SerialNumber[9];	    			// �������� �����
 char Revision;					    	// ������� �����
 char CpuType[11];					    // ��� �������������� DSP
 long QuartzFrequency; 		    		// ������� ������ � ��
 bool IsDacPresented; 			    	// ������ ������� ���
 double CalibrKoefAdc[8];	      		// ���������������� ����. ��� ���
 double CalibrKoefDac[4];	      		// ���������������� ����. ��� ���
};                                      //
#pragma pack()
// ��������� ���� ������������� ������ E-140
enum {	NO_SYNC_E140=0, TTL_START_SYNC_E140, TTL_KADR_SYNC_E140, ANALOG_SYNC_E140, INVALID_SYNC_E140 };
// ��������� ��� ������ E-440
struct ILE140
{
// ������� ������ ����������
	virtual HANDLE WINAPI GetModuleHandle(void) = 0;
	virtual bool WINAPI OpenLDevice(WORD VirtualSlot) = 0;
	virtual bool WINAPI CloseLDevice(void) = 0;
	virtual bool WINAPI ReleaseLDevice(void) = 0;
	virtual bool WINAPI GET_LBIOS_VERSION(DWORD *LbiosVersion) = 0;
// ������� ��� ������ � ���
	virtual bool WINAPI GET_CUR_ADC_PARS(ADC_PARS_E140 *am) = 0;
	virtual bool WINAPI FILL_ADC_PARS(ADC_PARS_E140 *am) = 0;
	virtual bool WINAPI START_ADC(void) = 0;
	virtual bool WINAPI STOP_ADC(void) = 0;
	virtual bool WINAPI ADC_KADR(SHORT *Data) = 0;
	virtual bool WINAPI ADC_SAMPLE(SHORT *Data, WORD Channel) = 0;
// ������� �������/������ ������ �/�� �����
	virtual bool WINAPI ReadData(SHORT *lpBuffer, LPDWORD nNumberOfWordsToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) = 0;
// ������� ��� ������ � ���
	virtual bool WINAPI DAC_SAMPLE(WORD Data, WORD Channel) = 0;
// ������� ��� ������ � ��� �������
	virtual bool WINAPI ENABLE_TTL_OUT(bool EnableTtlOut) = 0;
	virtual bool WINAPI TTL_IN(WORD *TtlIn) = 0;
	virtual bool WINAPI TTL_OUT(WORD TtlOut) = 0;
// ������� ��� ������ ����
	virtual bool WINAPI ENABLE_FLASH_WRITE(bool EnableFlashWrite) = 0;
	virtual bool WINAPI READ_FLASH_WORD(WORD FlashAddress, SHORT *FlashWord) = 0;
	virtual bool WINAPI WRITE_FLASH_WORD(WORD FlashAddress, SHORT FlashWord) = 0;
// ������� ��� ������ �� ��������� ����������� �� ����
	virtual bool WINAPI GET_MODULE_DESCR(MODULE_DESCR_E140 *pd) = 0;
	virtual bool WINAPI SAVE_MODULE_DESCR(MODULE_DESCR_E140 *pd) = 0;
// ������� ������ ������ � ��������� �������
	virtual int WINAPI GetLastErrorString(LPTSTR lpBuffer, DWORD nSize) = 0;
// �������������� �������
    virtual bool WINAPI SetSuspendModeFlag(bool SuspendModeFlag) = 0;
// ������� ����������� ��� ������� ������
    virtual bool WINAPI GetModuleName(char *ModuleName) = 0;
    virtual bool WINAPI ReadArray (BYTE *Buf, WORD Size, WORD Address)=0;
    virtual bool WINAPI WriteArray(BYTE *Buf, WORD Size, WORD Address)=0;
};
#endif
