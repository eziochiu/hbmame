// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/segas16b.cpp"

ROM_START( altbeastfr )
	ROM_REGION( 0x040000, "maincpu", 0 ) // 68000 code
	ROM_LOAD16_BYTE( "altbeastfr.a7", 0x000000, 0x20000, CRC(309d3a0a) SHA1(646dcafe7ac2831e241eb0643a06f8c32bdba77a) )
	ROM_LOAD16_BYTE( "altbeastfr.a5", 0x000001, 0x20000, CRC(39cd8368) SHA1(6b5890d44b549c3bbe18345ac86943c55f7b9d26) )

	ROM_REGION( 0x60000, "gfx1", 0 ) // tiles
	ROM_LOAD( "opr-11674.a14", 0x00000, 0x20000, CRC(a57a66d5) SHA1(5103583d48997abad12a0c5fee26431c486ced52) )
	ROM_LOAD( "opr-11675.a15", 0x20000, 0x20000, CRC(2ef2f144) SHA1(38d22d609db2d9b6067b5d12f6499436de4605cb) )
	ROM_LOAD( "opr-11676.a16", 0x40000, 0x20000, CRC(0c04acac) SHA1(87fe2a0dd9913f9550e9b4cbc7e7465b61640e07) )

	ROM_REGION16_BE( 0x100000, "sprites", 0 ) // sprites
	ROM_LOAD16_BYTE( "epr-11677.b1", 0x00001, 0x20000, CRC(a01425cd) SHA1(72be5ec29e476601f9bf6aaedef9b73cedeb42f0) )
	ROM_LOAD16_BYTE( "epr-11681.b5", 0x00000, 0x20000, CRC(d9e03363) SHA1(995a7c6a8f0c61468b57a3bb407461a2a3ae8adc) )
	ROM_LOAD16_BYTE( "epr-11678.b2", 0x40001, 0x20000, CRC(17a9fc53) SHA1(85a9a605742ae5aab86db37189b9ee4d54c70e56) )
	ROM_LOAD16_BYTE( "epr-11682.b6", 0x40000, 0x20000, CRC(e3f77c5e) SHA1(6b3cb7918ab0c7c97a51cc5ea19ced3374ff3914) )
	ROM_LOAD16_BYTE( "epr-11679.b3", 0x80001, 0x20000, CRC(14dcc245) SHA1(1ca1b6e0f2b7bedad2a8ab70f52da8c54d40d3cf) )
	ROM_LOAD16_BYTE( "epr-11683.b7", 0x80000, 0x20000, CRC(f9a60f06) SHA1(0cffcfdb02733feaa869198b7e668c58b47c321a) )
	ROM_LOAD16_BYTE( "epr-11680.b4", 0xc0001, 0x20000, CRC(f43dcdec) SHA1(2941500cf33afca487f19f2329033d5d17aad826) )
	ROM_LOAD16_BYTE( "epr-11684.b8", 0xc0000, 0x20000, CRC(b20c0edb) SHA1(6c8694d05e3adac37c9015037ab800233371db36) )

	ROM_REGION( 0x50000, "soundcpu", 0 ) // sound CPU
	ROM_LOAD( "epr-11671.a10",    0x00000, 0x08000, CRC(2b71343b) SHA1(8a657f787de2b9d5161ed2c109642a148348af09) )
	ROM_LOAD( "opr-11672.a11",    0x10000, 0x20000, CRC(bbd7f460) SHA1(bbc5c2219cb3a827d84062b19affd9780da2a3cf) )
	ROM_LOAD( "opr-11673.a12",    0x30000, 0x20000, CRC(400c4a36) SHA1(de4bdfa91734410e0a7f6a16bf8336db172f458a) )

	ROM_REGION( 0x1000, "mcu", 0 ) // Intel i8751 protection MCU
	ROM_LOAD( "317-0078.c2", 0x00000, 0x1000, CRC(8101925f) SHA1(a45d772ebe2fd1a577a6ccac8c6c76bb622258bb) )
ROM_END

GAME( 1988, altbeastfr, altbeast, system16b_i8751, altbeast, segas16b_state, generic_5521, ROT0, "Arkatrad", "Altered Beast (French)", MACHINE_NOT_WORKING )


//PSmame


ROM_START( altbeasts01 )
	ROM_REGION( 0x40000, "maincpu", 0 ) // 68000 code
	ROM_LOAD16_BYTE( "epr-11907hc01.a7", 0x000000, 0x20000, CRC(309d3a0a) SHA1(646dcafe7ac2831e241eb0643a06f8c32bdba77a) )
	ROM_LOAD16_BYTE( "epr-11906hc01.a5", 0x000001, 0x20000, CRC(39cd8368) SHA1(6b5890d44b549c3bbe18345ac86943c55f7b9d26) )

	ROM_REGION( 0x60000, "gfx1", 0 ) // tiles
	ROM_LOAD( "opr-11674.a14", 0x00000, 0x20000, CRC(a57a66d5) SHA1(5103583d48997abad12a0c5fee26431c486ced52) )
	ROM_LOAD( "opr-11675.a15", 0x20000, 0x20000, CRC(2ef2f144) SHA1(38d22d609db2d9b6067b5d12f6499436de4605cb) )
	ROM_LOAD( "opr-11676.a16", 0x40000, 0x20000, CRC(0c04acac) SHA1(87fe2a0dd9913f9550e9b4cbc7e7465b61640e07) )

	ROM_REGION16_BE( 0x100000, "sprites", 0 ) // sprites
	ROM_LOAD16_BYTE( "epr-11677.b1", 0x00001, 0x20000, CRC(a01425cd) SHA1(72be5ec29e476601f9bf6aaedef9b73cedeb42f0) )
	ROM_LOAD16_BYTE( "epr-11681.b5", 0x00000, 0x20000, CRC(d9e03363) SHA1(995a7c6a8f0c61468b57a3bb407461a2a3ae8adc) )
	ROM_LOAD16_BYTE( "epr-11678.b2", 0x40001, 0x20000, CRC(17a9fc53) SHA1(85a9a605742ae5aab86db37189b9ee4d54c70e56) )
	ROM_LOAD16_BYTE( "epr-11682.b6", 0x40000, 0x20000, CRC(e3f77c5e) SHA1(6b3cb7918ab0c7c97a51cc5ea19ced3374ff3914) )
	ROM_LOAD16_BYTE( "epr-11679.b3", 0x80001, 0x20000, CRC(14dcc245) SHA1(1ca1b6e0f2b7bedad2a8ab70f52da8c54d40d3cf) )
	ROM_LOAD16_BYTE( "epr-11683.b7", 0x80000, 0x20000, CRC(f9a60f06) SHA1(0cffcfdb02733feaa869198b7e668c58b47c321a) )
	ROM_LOAD16_BYTE( "epr-11680.b4", 0xc0001, 0x20000, CRC(f43dcdec) SHA1(2941500cf33afca487f19f2329033d5d17aad826) )
	ROM_LOAD16_BYTE( "epr-11684.b8", 0xc0000, 0x20000, CRC(b20c0edb) SHA1(6c8694d05e3adac37c9015037ab800233371db36) )

	ROM_REGION( 0x50000, "soundcpu", 0 ) // sound CPU
	ROM_LOAD( "epr-11671.a10", 0x00000, 0x08000, CRC(2b71343b) SHA1(8a657f787de2b9d5161ed2c109642a148348af09) )
	ROM_LOAD( "opr-11672.a11", 0x10000, 0x20000, CRC(bbd7f460) SHA1(bbc5c2219cb3a827d84062b19affd9780da2a3cf) )
	ROM_LOAD( "opr-11673.a12", 0x30000, 0x20000, CRC(400c4a36) SHA1(de4bdfa91734410e0a7f6a16bf8336db172f458a) )

	ROM_REGION( 0x1000, "mcu", 0 )  // Intel i8751 protection MCU
	ROM_LOAD( "317-0078.c2", 0x00000, 0x1000, CRC(8101925f) SHA1(a45d772ebe2fd1a577a6ccac8c6c76bb622258bb) )
ROM_END

/*************************************
 *
 *  Game driver(s)
 *
 *************************************/
// Proyecto Shadows Mame Build Plus
/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// Altered Beast
GAME( 1988, altbeasts01,   altbeast,        system16b_i8751,     altbeast, segas16b_state,generic_5521,       ROT0,   "hacks", "Altered Beast (set 8) (Translation-French)", 0 )

