/*
 * scheduler.s
 *
 * Created: 23-Jun-21 
 *  Author: Ahmed Azazy
 */ 
.global startScheduler
startScheduler: 
		cli
		call getIdle
		mov XL , r24
		mov XH , r25
		ld r0 , X+
		ld r1 , X
		out 0x3d, r0
		out	0x3e , r1
		pop r31
		pop r30
		pop r29
		POP r28
		pop r27
		pop	r26
		pop r25
		pop r24
		pop r23
		pop r22
		pop r21
		pop	r20
		pop	r19
		pop	r18
		pop r17
		pop r16
		pop r15
		pop r14
		pop r13
		pop r12
		pop r11
		pop r10
		pop r9
		pop r8
		pop r7
		pop r6
		pop r5
		pop r4
		pop r3
		pop r2
		pop r1
		pop r0
		out 0x3f , r0
		pop r0 
		sei
        ret
.end   

