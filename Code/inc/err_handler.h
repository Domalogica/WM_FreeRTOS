#ifndef _ERROR_HANDLER_H_
#define _ERROR_HANDLER_H_

#define	SYSTEM_OK				             	0x00
#define	SYSTEM_FAILTURE              	0x01

#define	STATUS_OK                    	0x00
#define	STATUS_ACTIVE                	0x01
#define	STATUS_VALID_DATA            	0x02
#define	STATUS_NO_CHANGE             	0x03
#define	STATUS_ABORTED               	0x04
#define	STATUS_BUSY                  	0x05
#define	STATUS_SUSPEND               	0x06
#define	STATUS_FAILTURE              	0x07

#define	ERR_NO_WATER									0x0A		//Нет воды
#define	ERR_WATER_LEAK         				0x0B		//Утечка воды 
#define	ERR_ENGINE_OVERHEATING				0x0C		//Перегрев двигателя 
#define	ERR_DRAINAGE_IS_BLOCKED				0x0D		//Дренаж закрыт
#define	ERR_INPUT_FLOWMETER						0x0E		//Не работает входной расходомер
#define	ERR_OUTPUT_FLOWMETER					0x0F		//Не работает выходной расходомер
#define	ERR_DRAINAGE_FLOWMETER				0x10		//Не работает дренажный расходомер
#define	ERR_DRAINAGE_LEAK							0x11		//Утечка в линии дренажа

#define	ERR_IO_ERROR                 	-1		// I/O error
#define	ERR_FLUSHED                  	-2		// Request flushed from queue
#define	ERR_TIMEOUT                  	-3		// Operation timed out
#define	ERR_BAD_DATA                 	-4		// Data integrity check failed
#define	ERR_PROTOCOL                	-5		// Protocol error
#define	ERR_UNSUPPORTED_DEV          	-6		// Unsupported device
#define	ERR_NO_MEMORY                	-7		// Insufficient memory
#define	ERR_INVALID_ARG              	-8		// Invalid argument
#define	ERR_BAD_ADDRESS              	-9		// Bad address
#define	ERR_BUSY                     	-10	// Resource is busy
#define	ERR_BAD_FORMAT               	-11	// Data format not recognized
#define	ERR_NO_TIMER                 	-12	// No timer available
#define	ERR_TIMER_ALREADY_RUNNING    	-13	// Timer already running
#define	ERR_TIMER_NOT_RUNNING        	-14	// Timer not running
#define	ERR_NOT_FOUND                	-15
#define	ERR_BAD_FRQ                	 	-16
#define	ERR_DENIED                   	-17
#define	ERR_ALREADY_INITIALIZED    	 	-18
#define	ERR_OVERFLOW                 	-19
#define	ERR_NOT_INITIALIZED          	-20
#define	ERR_BAUDRATE_UNAVAILABLE     	-21
#define	ERR_PACKET_COLLISION         	-22



#endif /* _ERROR_HANDLER_H_ */
