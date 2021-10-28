/*
 * IR_Receiver.h
 *
 * Created: 25.04.2017 1:22:03
 *  Author: Sergei Biletnikov
 */ 


#ifndef IR_RECEIVER_H_
#define IR_RECEIVER_H_

// port for connecting IR receiver
#define IRR_PORT PORTD
#define IRR_DDR DDRD
#define IRR_PIN PD2
#define IRR_PIN_PORT PIND
#define IRR_INT INT0
#define IRR_VECT INT0_vect
#define IRR_ISC ISC00
// init IR receiver pin port
#define init_IRR_PIN()  \
IRR_DDR&=~(1<<IRR_PIN); \
IRR_PORT|=(1<<IRR_PIN); \
EICRA|=(1<<IRR_ISC); \
EIMSK|=(1<<IRR_INT);
//
#define NEC_MAX_PACKET_BIT_NUMBER 32

//uncomment this to use a led to indicate when IR packet received, it blinks shortly for 100 ms
//#define IR_STATUS_LED

// Status led initialization, if it is defined
#ifdef IR_STATUS_LED
#define IR_STATUS_LED_PORT PORTB
#define IR_STATUS_LED_DDR DDRB
#define IR_STATUS_LED_PIN PB1
#define IR_STATUS_LED_ON IR_STATUS_LED_PORT|=(1<<IR_STATUS_LED_PIN)
#define IR_STATUS_LED_OFF IR_STATUS_LED_PORT&=~(1<<IR_STATUS_LED_PIN)
#define IR_STATUS_LED_TOGGLE IR_STATUS_LED_PORT^=(1<<IR_STATUS_LED_PIN)
#endif // IR_STATUS_LED


// Packet of data
struct IR_Packet
{
	uint16_t addr; // address, for standard NEC it is only one byte address (the value in the lowest byte), for extended protocol the address takes 2 bytes
	uint8_t command; // command 
	uint8_t repeat; // 0 if the packet is not repeat	
};

// init receiver
#ifdef __cplusplus
extern "C" void init_receiver();
#else
extern void init_receiver(void);
#endif

// check if new data packet received
// 0 - no, otherwise yes
// received_packet is a pointer to the IR_Packet structure to receive the data
// the packet updated only if the function result is not 0
#ifdef __cplusplus
extern "C" uint8_t check_new_packet(struct IR_Packet * received_packet);
#else
extern uint8_t check_new_packet(struct IR_Packet * received_packet);
#endif

#endif /* IR_RECEIVER_H_ */