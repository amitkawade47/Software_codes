int main(void);
typedef union 
	{
	 uint8_t     all_flags;      /* Allows us to refer to the flags 'en masse' */
	 struct
	 {
	  uint8_t  combineWord         		: 1,       // Current State of MOTOR
	           heaterState        		: 1,       // Current State of HEATER
	           fanInletState      		: 1,       // Current State of FAN INLET
	           fanOutletState     		: 1,       // Current State of FAN OUTLET
			   heaterMasterState	    : 1,       // Current State of MASTER HEATER 
	           motorNextState     		: 1,       // Next State of MOTOR
	           heaterNextState    		: 1,       // Next State of HEATER
	           fanInletNextState  		: 1;       // Next State of FAN INLET
	   	 };
	} STATE_FLAGS;
	
	volatile STATE_FLAGS Flags;  /* Allocation for the Flags */        					// Serial Intialisation
