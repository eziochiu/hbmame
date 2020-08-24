// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/segag80r.cpp"

ROM_START( astrob2h ) // same as astrob2 except u2 and u4
	ROM_REGION( 0xc000, "maincpu", 0 )
	ROM_LOAD( "829b.cpu-u25",   0x0000, 0x0800, CRC(14ae953c) SHA1(eb63d1b95faa5193db7fa6ab245e99325d519b5e) )
	ROM_LOAD( "888a.prom-u1",   0x0800, 0x0800, CRC(42601744) SHA1(6bb58384c28b2105746a2f410f5e0979609db9bf) )
	ROM_LOAD( "889b2h.u2",      0x1000, 0x0800, CRC(9fcdc62f) SHA1(6dbf7e1ad62548263ca5edaa81d38cbc7a9a281f) )
	ROM_LOAD( "890.prom-u3",    0x1800, 0x0800, CRC(26f5b4cf) SHA1(be45e802f976b8847689ae8de7159843ac9100eb) )
	ROM_LOAD( "891b2h.u4",      0x2000, 0x0800, CRC(74f906dc) SHA1(edf9efc0ec25f578214b26010d99385c0bace3ad) )
	ROM_LOAD( "892.prom-u5",    0x2800, 0x0800, CRC(2d3c949b) SHA1(17e3c5300793f2345ff6e28e82cd7a22f1d6e41f) )
	ROM_LOAD( "893.prom-u6",    0x3000, 0x0800, CRC(ccdb1a76) SHA1(1c8f0555e397c5558bbfca1fa1487cc32aca8592) )
	ROM_LOAD( "894.prom-u7",    0x3800, 0x0800, CRC(66ae5ced) SHA1(81bb6e3adcc76ffbeafefecce5fe5541a7eefc37) )
	ROM_LOAD( "895.prom-u8",    0x4000, 0x0800, CRC(202cf3a3) SHA1(26fcccfb3e94b2a01d38c14daa66713c223efb18) )
	ROM_LOAD( "896.prom-u9",    0x4800, 0x0800, CRC(b603fe23) SHA1(3128877355a9c5bba5cd22e9addf4c8b79ee39d2) )
	ROM_LOAD( "897.prom-u10",   0x5000, 0x0800, CRC(989198c6) SHA1(3344bf7272e388571026c4e68a2e4e5e0ebbc5e3) )
	ROM_LOAD( "898.prom-u11",   0x5800, 0x0800, CRC(ef2bab04) SHA1(108a9812cb9d1ec4629b0306c45ba164f94ab426) )
	ROM_LOAD( "899.prom-u12",   0x6000, 0x0800, CRC(e0d189ee) SHA1(dcab31d64e6b2d248a82cbae9e37afe031dfc6cd) )
	ROM_LOAD( "900.prom-u13",   0x6800, 0x0800, CRC(682d4604) SHA1(6ac0d2d8ff407cc7e10b460736ae7fbc21148640) )
	ROM_LOAD( "901.prom-u14",   0x7000, 0x0800, CRC(9ed11c61) SHA1(dd965c06d2013acdabd958e713109eeb049d5d5e) )
	ROM_LOAD( "902.prom-u15",   0x7800, 0x0800, CRC(b4d6c330) SHA1(922a562b5f1a8a286e6777ba7d141bd0db6e2a92) )
	ROM_LOAD( "903a.prom-u16",  0x8000, 0x0800, CRC(84acc38c) SHA1(86bed143ac2d95116e50e77b5c262d67156c6a59) )
	ROM_LOAD( "904.prom-u17",   0x8800, 0x0800, CRC(5eba3097) SHA1(e785d1c1cea50aa25e5eea5e58a0c48fd53208c6) )
	ROM_LOAD( "905.prom-u18",   0x9000, 0x0800, CRC(4f08f9f4) SHA1(755a825b18ed50caa7bf274a0a5c3a1b00b1c070) )
	ROM_LOAD( "906.prom-u19",   0x9800, 0x0800, CRC(58149df1) SHA1(2bba56576a225ca47ce31a5b6dcc491546dfffec) )

	ROM_REGION( 0x0800, "speech:cpu", 0 )
	ROM_LOAD( "808b.speech-u7", 0x0000, 0x0800, CRC(5988c767) SHA1(3b91a8cd46aa7e714028cc40f700fea32287afb1) )

	ROM_REGION( 0x0020, "speech:proms", 0 )
	ROM_LOAD( "pr84.speech-u30",     0x0000, 0x0020, CRC(adcb81d0) SHA1(74b0efc7e8362b0c98e54a6107981cff656d87e1) )

	ROM_REGION( 0x4000, "speech:data", 0 )
	ROM_LOAD( "809a.speech-u6", 0x0000, 0x0800, CRC(893f228d) SHA1(41c08210d322105f5446cfaa1258c194dd078a34) )
	ROM_LOAD( "810.speech-u5",  0x0800, 0x0800, CRC(ff0163c5) SHA1(158a12f9bf01d25c7e98f34fce56df51d49e5a85) )
	ROM_LOAD( "811.speech-u4",  0x1000, 0x0800, CRC(219f3978) SHA1(728edb9251f7cde237fa3b005971366a099c6342) )
	ROM_LOAD( "812a.speech-u3", 0x1800, 0x0800, CRC(410ad0d2) SHA1(9b5f05bb64a6ecfe3543025a10c6ec67de797333) )

	ROM_REGION( 0x0420, "proms", 0 )
	ROM_LOAD( "316-0806.video1-u52", 0x0000, 0x0020, CRC(358128b6) SHA1(b6b4b9ecfdcc69b45e69e7a8614153d83be4c62b) )
	ROM_LOAD( "316-0764.cpu-u15",    0x0400, 0x0020, CRC(c609b79e) SHA1(49dbcbb607079a182d7eb396c0da097166ea91c9) )
ROM_END

GAME( 1981, astrob2h, astrob, astrob, astrob2, segag80r_state, init_astrob, ROT270, "Clay Cowgill", "Astro Blaster (ver 2 Hack)", 0 )
