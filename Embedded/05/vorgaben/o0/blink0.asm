
blink.elf:     file format elf32-littlearm

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         00000370  00000000  00000000  00010000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .init         00000004  00000370  00000370  00010370  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  2 .fini         00000004  00000374  00000374  00010374  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  3 .bss          00000104  20000000  20000000  00020000  2**2
                  ALLOC
  4 .ARM.attributes 0000002a  00000000  00000000  00010378  2**0
                  CONTENTS, READONLY
  5 .comment      0000007f  00000000  00000000  000103a2  2**0
                  CONTENTS, READONLY

Disassembly of section .text:

00000000 <g_pfnVectors>:
   0:	00 01 00 20 f1 02 00 00 55 03 00 00 5b 03 00 00     ... ....U...[...
  10:	61 03 00 00 61 03 00 00 61 03 00 00 00 00 00 00     a...a...a.......
	...
  2c:	61 03 00 00 61 03 00 00 00 00 00 00 61 03 00 00     a...a.......a...
  3c:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
  4c:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
  5c:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
  6c:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
  7c:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
  8c:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
  9c:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
  ac:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
  bc:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
  cc:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
  dc:	61 03 00 00 61 03 00 00 61 03 00 00 00 00 00 00     a...a...a.......
  ec:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
  fc:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
 10c:	61 03 00 00 00 00 00 00 00 00 00 00 61 03 00 00     a...........a...
 11c:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
 12c:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
 13c:	61 03 00 00 00 00 00 00 00 00 00 00 00 00 00 00     a...............
 14c:	00 00 00 00 61 03 00 00 61 03 00 00 61 03 00 00     ....a...a...a...
 15c:	61 03 00 00 00 00 00 00 00 00 00 00 00 00 00 00     a...............
	...
 1b0:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
 1c0:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
 1d0:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
 1e0:	61 03 00 00 61 03 00 00 61 03 00 00 00 00 00 00     a...a...a.......
 1f0:	00 00 00 00 61 03 00 00 61 03 00 00 61 03 00 00     ....a...a...a...
 200:	61 03 00 00 61 03 00 00 00 00 00 00 00 00 00 00     a...a...........
 210:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
 220:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
 230:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
 240:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
 250:	61 03 00 00 61 03 00 00 61 03 00 00 61 03 00 00     a...a...a...a...
 260:	61 03 00 00 61 03 00 00 61 03 00 00                 a...a...a...

0000026c <delay>:
 26c:	b480      	push	{r7}
 26e:	af00      	add	r7, sp, #0
 270:	4b08      	ldr	r3, [pc, #32]	; (294 <delay+0x28>)
 272:	2200      	movs	r2, #0
 274:	601a      	str	r2, [r3, #0]
 276:	e004      	b.n	282 <delay+0x16>
 278:	4b06      	ldr	r3, [pc, #24]	; (294 <delay+0x28>)
 27a:	681b      	ldr	r3, [r3, #0]
 27c:	3301      	adds	r3, #1
 27e:	4a05      	ldr	r2, [pc, #20]	; (294 <delay+0x28>)
 280:	6013      	str	r3, [r2, #0]
 282:	4b04      	ldr	r3, [pc, #16]	; (294 <delay+0x28>)
 284:	681b      	ldr	r3, [r3, #0]
 286:	4a04      	ldr	r2, [pc, #16]	; (298 <delay+0x2c>)
 288:	4293      	cmp	r3, r2
 28a:	d9f5      	bls.n	278 <delay+0xc>
 28c:	bf00      	nop
 28e:	46bd      	mov	sp, r7
 290:	bc80      	pop	{r7}
 292:	4770      	bx	lr
 294:	20000100 	.word	0x20000100
 298:	00030d3f 	.word	0x00030d3f

0000029c <main>:
 29c:	b580      	push	{r7, lr}
 29e:	af00      	add	r7, sp, #0
 2a0:	4b0e      	ldr	r3, [pc, #56]	; (2dc <main+0x40>)
 2a2:	2220      	movs	r2, #32
 2a4:	601a      	str	r2, [r3, #0]
 2a6:	4b0d      	ldr	r3, [pc, #52]	; (2dc <main+0x40>)
 2a8:	681b      	ldr	r3, [r3, #0]
 2aa:	4a0d      	ldr	r2, [pc, #52]	; (2e0 <main+0x44>)
 2ac:	6013      	str	r3, [r2, #0]
 2ae:	4b0d      	ldr	r3, [pc, #52]	; (2e4 <main+0x48>)
 2b0:	2208      	movs	r2, #8
 2b2:	601a      	str	r2, [r3, #0]
 2b4:	4b0c      	ldr	r3, [pc, #48]	; (2e8 <main+0x4c>)
 2b6:	2208      	movs	r2, #8
 2b8:	601a      	str	r2, [r3, #0]
 2ba:	4a0c      	ldr	r2, [pc, #48]	; (2ec <main+0x50>)
 2bc:	4b0b      	ldr	r3, [pc, #44]	; (2ec <main+0x50>)
 2be:	681b      	ldr	r3, [r3, #0]
 2c0:	f043 0308 	orr.w	r3, r3, #8
 2c4:	6013      	str	r3, [r2, #0]
 2c6:	f7ff ffd1 	bl	26c <delay>
 2ca:	4a08      	ldr	r2, [pc, #32]	; (2ec <main+0x50>)
 2cc:	4b07      	ldr	r3, [pc, #28]	; (2ec <main+0x50>)
 2ce:	681b      	ldr	r3, [r3, #0]
 2d0:	f023 0308 	bic.w	r3, r3, #8
 2d4:	6013      	str	r3, [r2, #0]
 2d6:	f7ff ffc9 	bl	26c <delay>
 2da:	e7ee      	b.n	2ba <main+0x1e>
 2dc:	400fe108 	.word	0x400fe108
 2e0:	20000100 	.word	0x20000100
 2e4:	40025400 	.word	0x40025400
 2e8:	4002551c 	.word	0x4002551c
 2ec:	400253fc 	.word	0x400253fc

000002f0 <ResetISR>:
 2f0:	b580      	push	{r7, lr}
 2f2:	b082      	sub	sp, #8
 2f4:	af00      	add	r7, sp, #0
 2f6:	4b13      	ldr	r3, [pc, #76]	; (344 <zero_loop+0x24>)
 2f8:	607b      	str	r3, [r7, #4]
 2fa:	4b13      	ldr	r3, [pc, #76]	; (348 <zero_loop+0x28>)
 2fc:	603b      	str	r3, [r7, #0]
 2fe:	e007      	b.n	310 <ResetISR+0x20>
 300:	683b      	ldr	r3, [r7, #0]
 302:	1d1a      	adds	r2, r3, #4
 304:	603a      	str	r2, [r7, #0]
 306:	687a      	ldr	r2, [r7, #4]
 308:	1d11      	adds	r1, r2, #4
 30a:	6079      	str	r1, [r7, #4]
 30c:	6812      	ldr	r2, [r2, #0]
 30e:	601a      	str	r2, [r3, #0]
 310:	683b      	ldr	r3, [r7, #0]
 312:	4a0e      	ldr	r2, [pc, #56]	; (34c <zero_loop+0x2c>)
 314:	4293      	cmp	r3, r2
 316:	d3f3      	bcc.n	300 <ResetISR+0x10>
 318:	4813      	ldr	r0, [pc, #76]	; (368 <IntDefaultHandler+0x8>)
 31a:	4914      	ldr	r1, [pc, #80]	; (36c <IntDefaultHandler+0xc>)
 31c:	f04f 0200 	mov.w	r2, #0

00000320 <zero_loop>:
 320:	4288      	cmp	r0, r1
 322:	bfb8      	it	lt
 324:	f840 2b04 	strlt.w	r2, [r0], #4
 328:	dbfa      	blt.n	320 <zero_loop>
 32a:	4a09      	ldr	r2, [pc, #36]	; (350 <zero_loop+0x30>)
 32c:	4b08      	ldr	r3, [pc, #32]	; (350 <zero_loop+0x30>)
 32e:	681b      	ldr	r3, [r3, #0]
 330:	f443 0370 	orr.w	r3, r3, #15728640	; 0xf00000
 334:	6013      	str	r3, [r2, #0]
 336:	f7ff ffb1 	bl	29c <main>
 33a:	bf00      	nop
 33c:	3708      	adds	r7, #8
 33e:	46bd      	mov	sp, r7
 340:	bd80      	pop	{r7, pc}
 342:	bf00      	nop
 344:	00000370 	.word	0x00000370
 348:	20000000 	.word	0x20000000
 34c:	20000000 	.word	0x20000000
 350:	e000ed88 	.word	0xe000ed88

00000354 <NmiSR>:
 354:	b480      	push	{r7}
 356:	af00      	add	r7, sp, #0
 358:	e7fe      	b.n	358 <NmiSR+0x4>

0000035a <FaultISR>:
 35a:	b480      	push	{r7}
 35c:	af00      	add	r7, sp, #0
 35e:	e7fe      	b.n	35e <FaultISR+0x4>

00000360 <IntDefaultHandler>:
 360:	b480      	push	{r7}
 362:	af00      	add	r7, sp, #0
 364:	e7fe      	b.n	364 <IntDefaultHandler+0x4>
 366:	0000      	.short	0x0000
 368:	20000000 	.word	0x20000000
 36c:	20000104 	.word	0x20000104

Disassembly of section .init:

00000370 <_init>:
 370:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 372:	bf00      	nop

Disassembly of section .fini:

00000374 <_fini>:
 374:	b5f8      	push	{r3, r4, r5, r6, r7, lr}
 376:	bf00      	nop
