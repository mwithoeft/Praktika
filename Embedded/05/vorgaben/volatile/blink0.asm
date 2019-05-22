
blink.elf:     file format elf32-littlearm

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000324  00000000  00000000  00010000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .init         00000004  00000324  00000324  00010324  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  2 .fini         00000004  00000328  00000328  00010328  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  3 .bss          00000104  20000000  20000000  00020000  2**2
                  ALLOC
  4 .ARM.attributes 0000002a  00000000  00000000  0001032c  2**0
                  CONTENTS, READONLY
  5 .comment      0000007f  00000000  00000000  00010356  2**0
                  CONTENTS, READONLY

Disassembly of section .text:

00000000 <g_pfnVectors>:
   0:	00 01 00 20 c9 02 00 00 bd 02 00 00 c1 02 00 00     ... ............
  10:	c5 02 00 00 c5 02 00 00 c5 02 00 00 00 00 00 00     ................
	...
  2c:	c5 02 00 00 c5 02 00 00 00 00 00 00 c5 02 00 00     ................
  3c:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
  4c:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
  5c:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
  6c:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
  7c:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
  8c:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
  9c:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
  ac:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
  bc:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
  cc:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
  dc:	c5 02 00 00 c5 02 00 00 c5 02 00 00 00 00 00 00     ................
  ec:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
  fc:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 10c:	c5 02 00 00 00 00 00 00 00 00 00 00 c5 02 00 00     ................
 11c:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 12c:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 13c:	c5 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00     ................
 14c:	00 00 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 15c:	c5 02 00 00 00 00 00 00 00 00 00 00 00 00 00 00     ................
	...
 1b0:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 1c0:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 1d0:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 1e0:	c5 02 00 00 c5 02 00 00 c5 02 00 00 00 00 00 00     ................
 1f0:	00 00 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 200:	c5 02 00 00 c5 02 00 00 00 00 00 00 00 00 00 00     ................
 210:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 220:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 230:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 240:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 250:	c5 02 00 00 c5 02 00 00 c5 02 00 00 c5 02 00 00     ................
 260:	c5 02 00 00 c5 02 00 00 c5 02 00 00                 ............

0000026c <main>:
 26c:	4b0d      	ldr	r3, [pc, #52]	; (2a4 <main+0x38>)
 26e:	480e      	ldr	r0, [pc, #56]	; (2a8 <main+0x3c>)
 270:	4d0e      	ldr	r5, [pc, #56]	; (2ac <main+0x40>)
 272:	490f      	ldr	r1, [pc, #60]	; (2b0 <main+0x44>)
 274:	4a0f      	ldr	r2, [pc, #60]	; (2b4 <main+0x48>)
 276:	4c10      	ldr	r4, [pc, #64]	; (2b8 <main+0x4c>)
 278:	2620      	movs	r6, #32
 27a:	601e      	str	r6, [r3, #0]
 27c:	681b      	ldr	r3, [r3, #0]
 27e:	6003      	str	r3, [r0, #0]
 280:	2308      	movs	r3, #8
 282:	602b      	str	r3, [r5, #0]
 284:	600b      	str	r3, [r1, #0]
 286:	6811      	ldr	r1, [r2, #0]
 288:	4b0b      	ldr	r3, [pc, #44]	; (2b8 <main+0x4c>)
 28a:	f041 0108 	orr.w	r1, r1, #8
 28e:	6011      	str	r1, [r2, #0]
 290:	3b01      	subs	r3, #1
 292:	d1fd      	bne.n	290 <main+0x24>
 294:	6004      	str	r4, [r0, #0]
 296:	6813      	ldr	r3, [r2, #0]
 298:	f023 0308 	bic.w	r3, r3, #8
 29c:	6013      	str	r3, [r2, #0]
 29e:	6004      	str	r4, [r0, #0]
 2a0:	e7f1      	b.n	286 <main+0x1a>
 2a2:	bf00      	nop
 2a4:	400fe108 	.word	0x400fe108
 2a8:	20000100 	.word	0x20000100
 2ac:	40025400 	.word	0x40025400
 2b0:	4002551c 	.word	0x4002551c
 2b4:	400253fc 	.word	0x400253fc
 2b8:	00030d40 	.word	0x00030d40

000002bc <NmiSR>:
 2bc:	e7fe      	b.n	2bc <NmiSR>
 2be:	bf00      	nop

000002c0 <FaultISR>:
 2c0:	e7fe      	b.n	2c0 <FaultISR>
 2c2:	bf00      	nop

000002c4 <IntDefaultHandler>:
 2c4:	e7fe      	b.n	2c4 <IntDefaultHandler>
 2c6:	bf00      	nop

000002c8 <ResetISR>:
 2c8:	4b10      	ldr	r3, [pc, #64]	; (30c <zero_loop+0x1a>)
 2ca:	4a11      	ldr	r2, [pc, #68]	; (310 <zero_loop+0x1e>)
 2cc:	4293      	cmp	r3, r2
 2ce:	d20c      	bcs.n	2ea <ResetISR+0x22>
 2d0:	43d8      	mvns	r0, r3
 2d2:	4410      	add	r0, r2
 2d4:	f020 0003 	bic.w	r0, r0, #3
 2d8:	3004      	adds	r0, #4
 2da:	4a0e      	ldr	r2, [pc, #56]	; (314 <zero_loop+0x22>)
 2dc:	4418      	add	r0, r3
 2de:	f852 1b04 	ldr.w	r1, [r2], #4
 2e2:	f843 1b04 	str.w	r1, [r3], #4
 2e6:	4283      	cmp	r3, r0
 2e8:	d1f9      	bne.n	2de <ResetISR+0x16>
 2ea:	480c      	ldr	r0, [pc, #48]	; (31c <zero_loop+0x2a>)
 2ec:	490c      	ldr	r1, [pc, #48]	; (320 <zero_loop+0x2e>)
 2ee:	f04f 0200 	mov.w	r2, #0

000002f2 <zero_loop>:
 2f2:	4288      	cmp	r0, r1
 2f4:	bfb8      	it	lt
 2f6:	f840 2b04 	strlt.w	r2, [r0], #4
 2fa:	dbfa      	blt.n	2f2 <zero_loop>
 2fc:	4a06      	ldr	r2, [pc, #24]	; (318 <zero_loop+0x26>)
 2fe:	6813      	ldr	r3, [r2, #0]
 300:	f443 0370 	orr.w	r3, r3, #15728640	; 0xf00000
 304:	6013      	str	r3, [r2, #0]
 306:	f7ff bfb1 	b.w	26c <main>
 30a:	bf00      	nop
 30c:	20000000 	.word	0x20000000
 310:	20000000 	.word	0x20000000
 314:	00000324 	.word	0x00000324
 318:	e000ed88 	.word	0xe000ed88
 31c:	20000000 	.word	0x20000000
 320:	20000104 	.word	0x20000104

Disassembly of section .init:

00000324 <_init>:
 324:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 326:	bf00      	nop

Disassembly of section .fini:

00000328 <_fini>:
 328:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 32a:	bf00      	nop