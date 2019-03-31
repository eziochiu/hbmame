// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/bublbobl.cpp"

static INPUT_PORTS_START( bbaladar )
	PORT_INCLUDE( boblbobl )

	PORT_MODIFY( "DSW1" )
	PORT_BIT( 0xc0, IP_ACTIVE_LOW, IPT_UNKNOWN )
INPUT_PORTS_END

ROM_START( bbaladar )
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD( "bbaladar.3",   0x00000, 0x8000, CRC(31bfc6fb) SHA1(6a72086d415a69b9e5c003ec6cf7858e8c4b346f) )
	ROM_LOAD( "bbaladar.5",   0x10000, 0x8000, CRC(16386e9a) SHA1(77fa3f5ecce5c79ba52098c0870482459926b415) )
	ROM_LOAD( "bbaladar.4",   0x18000, 0x8000, CRC(0c4bcb07) SHA1(3e3f7fa098d6be61d265cab5258dbd0e279bd8ed) )

	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "a78-08.37",    0x0000, 0x08000, CRC(ae11a07b) SHA1(af7a335c8da637103103cc274e077f123908ebb7) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46",    0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )

	ROM_REGION( 0x0600, "plds", 0 )
	ROM_LOAD( "pal16r4.u36", 0x0000, 0x0104, CRC(22fe26ac) SHA1(bbbfcbe6faded4af7ceec57b800297c054a997da) )
	ROM_LOAD( "pal16l8.u38", 0x0200, 0x0104, CRC(c02d9663) SHA1(5d23cfd96f072981fd5fcf0dd7e98459da58b662) )
	ROM_LOAD( "pal16l8.u4",  0x0400, 0x0104, CRC(077d20a8) SHA1(8e568ffd6f66c3dd61708dd0f3be9c2ed488ae4b) )
ROM_END

ROM_START( bb2bmh )
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD( "a78-06.51", 	  0x00000, 0x08000, CRC(32c8305b) SHA1(6bf69b3edfbefd33cd670a762b4bf0b39629a220) )
	ROM_LOAD( "bb2bmh-05.52",    0x10000, 0x10000, CRC(d286f2e9) SHA1(ac293aa5bb3973738c7a48ce78c523154d650ded) )

	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "bb2bmh-08.37",    0x0000, 0x08000, CRC(ebce6c5c) SHA1(bd99a67a044763567c443b174115aae89957a60c) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46", 	  0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x0800, "mcu", 0 )
	ROM_LOAD( "68705.bin",    0x0000, 0x0800, CRC(78caa635) SHA1(a756e45b25b007843ba4f2204cad6081cf7260e9) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )
ROM_END

ROM_START( bbhackv1 )
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD( "a78-06.51", 	  0x00000, 0x08000, CRC(32c8305b) SHA1(6bf69b3edfbefd33cd670a762b4bf0b39629a220) )
	ROM_LOAD( "bbhackv1-05.52",  0x10000, 0x10000, CRC(8da82422) SHA1(385ccd427b101255bc865af0802672b4d8432339) )
	
	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "bbhackv1-08.37",  0x0000, 0x08000, CRC(419caf60) SHA1(95d680c2be15e813081d3f78f17c5d97eda8b60b) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46", 	  0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x0800, "mcu", 0 )
	ROM_LOAD( "68705.bin", 	  0x0000, 0x0800, CRC(78caa635) SHA1(a756e45b25b007843ba4f2204cad6081cf7260e9) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )
ROM_END

//Press P1+P2 while playing, to advance
ROM_START( bbredux1 )
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD( "bb3.1",        0x00000, 0x8000, CRC(b802046d) SHA1(93dba2507c67f3f61eca80908a7a4409d2cd1b75) )
	ROM_LOAD( "bb5",          0x10000, 0x8000, CRC(d29d3444) SHA1(3db694a6ba2ba2ed85d31c2bc4c7c94911b99b85) )
	ROM_LOAD( "bb4.1",        0x18000, 0x8000, CRC(19a5a0fa) SHA1(e7fff3643d7922a494ad8118d1a0f74e52443f9f) )

	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "a78-08.37",    0x0000, 0x08000, CRC(ae11a07b) SHA1(af7a335c8da637103103cc274e077f123908ebb7) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46",    0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )

	ROM_REGION( 0x0600, "plds", 0 )
	ROM_LOAD( "pal16r4.u36", 0x0000, 0x0104, CRC(22fe26ac) SHA1(bbbfcbe6faded4af7ceec57b800297c054a997da) )
	ROM_LOAD( "pal16l8.u38", 0x0200, 0x0104, CRC(c02d9663) SHA1(5d23cfd96f072981fd5fcf0dd7e98459da58b662) )
	ROM_LOAD( "pal16l8.u4",  0x0400, 0x0104, CRC(077d20a8) SHA1(8e568ffd6f66c3dd61708dd0f3be9c2ed488ae4b) )
ROM_END

// When you die for the last time, it momentarily says press P1. Do so, to continue.
ROM_START( bbredux2 )
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD( "bb3.2",        0x00000, 0x8000, CRC(198dc44e) SHA1(de9538b47703c468f85ba318deb8aa0b65174a26) )
	ROM_LOAD( "bb5",          0x10000, 0x8000, CRC(d29d3444) SHA1(3db694a6ba2ba2ed85d31c2bc4c7c94911b99b85) )
	ROM_LOAD( "bb4.2",        0x18000, 0x8000, CRC(9b819b62) SHA1(79d7208cb81fa36ed317f4776b1eda3082b1a21c) )

	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "a78-08.37",    0x0000, 0x08000, CRC(ae11a07b) SHA1(af7a335c8da637103103cc274e077f123908ebb7) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46",    0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )

	ROM_REGION( 0x0600, "plds", 0 )
	ROM_LOAD( "pal16r4.u36", 0x0000, 0x0104, CRC(22fe26ac) SHA1(bbbfcbe6faded4af7ceec57b800297c054a997da) )
	ROM_LOAD( "pal16l8.u38", 0x0200, 0x0104, CRC(c02d9663) SHA1(5d23cfd96f072981fd5fcf0dd7e98459da58b662) )
	ROM_LOAD( "pal16l8.u4",  0x0400, 0x0104, CRC(077d20a8) SHA1(8e568ffd6f66c3dd61708dd0f3be9c2ed488ae4b) )
ROM_END

// High score save is not working as yet
ROM_START( bbredux3 )
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD( "bb3.3",        0x00000, 0x8000, CRC(959cafca) SHA1(9c541e45326d27f4d25a1fd9d66f234ce7f969c9) )
	ROM_LOAD( "bb5",          0x10000, 0x8000, CRC(d29d3444) SHA1(3db694a6ba2ba2ed85d31c2bc4c7c94911b99b85) )
	ROM_LOAD( "bb4.3",        0x18000, 0x8000, CRC(3f350047) SHA1(7e23d1c9b1a29760d96dcc7f7784ae610ac860d9) )

	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "a78-08.37",    0x0000, 0x08000, CRC(ae11a07b) SHA1(af7a335c8da637103103cc274e077f123908ebb7) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46",    0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )

	ROM_REGION( 0x0600, "plds", 0 )
	ROM_LOAD( "pal16r4.u36", 0x0000, 0x0104, CRC(22fe26ac) SHA1(bbbfcbe6faded4af7ceec57b800297c054a997da) )
	ROM_LOAD( "pal16l8.u38", 0x0200, 0x0104, CRC(c02d9663) SHA1(5d23cfd96f072981fd5fcf0dd7e98459da58b662) )
	ROM_LOAD( "pal16l8.u4",  0x0400, 0x0104, CRC(077d20a8) SHA1(8e568ffd6f66c3dd61708dd0f3be9c2ed488ae4b) )
ROM_END

// issues since 2017-08-06: music keeps dropping out, reboots if you press ctrl instead of 1 at level select screen
ROM_START( sboblboblh )
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD( "bb3.u28",      0x00000, 0x08000, CRC(c23cd704) SHA1(a389ecc8d55d1b0c915fd3814d93338b9e402701) )
	ROM_LOAD( "bb5.s",        0x10000, 0x08000, CRC(13118eb1) SHA1(5a5da40c2cc82420f70bc58ffa32de1088c6c82f) )
	ROM_LOAD( "bbb-4.rom",    0x18000, 0x08000, CRC(94c75591) SHA1(7698bc4b7d20e554a73a489cd3a15ae61b350e37) )

	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "a78-08.37",    0x0000, 0x08000, CRC(ae11a07b) SHA1(af7a335c8da637103103cc274e077f123908ebb7) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46",    0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )
ROM_END

ROM_START( bublbobf )
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD( "bublbobf-06.51",    0x00000, 0x08000, CRC(9ced3d8f) SHA1(d445f218fca822e7083a9347abd4a4e049b6555b) )
	ROM_LOAD( "bublbobf-05.52",    0x10000, 0x10000, CRC(56197d88) SHA1(b1b750df33835df012b2550585edcd6ea58db186) )

	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "a78-08.37",    0x0000, 0x08000, CRC(ae11a07b) SHA1(af7a335c8da637103103cc274e077f123908ebb7) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46",    0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x10000, "mcu", 0 )
	ROM_LOAD( "a78-01.17",    0xf000, 0x1000, CRC(b1bfb53d) SHA1(31b8f31acd3aa394acd80db362774749842e1285) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )
ROM_END

ROM_START( bublboblu )
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD( "a78-06u.51",    0x00000, 0x08000, CRC(a6345edd) SHA1(144f33002ee40acdbfa6a49119092a319048bb00) )
	ROM_LOAD( "a78-05u.52",    0x10000, 0x10000, CRC(b31d2edc) SHA1(b7d317c0b5b86c0bf39b18cfe584bca9d22d4eba) )

	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "a78-08u.37",    0x0000, 0x08000, CRC(d544be2e) SHA1(1472db52dcd9e17a866ea2766cfea500d8f712ab) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46",    0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x10000, "mcu", 0 )
	ROM_LOAD( "a78-01.17",    0xf000, 0x1000, CRC(b1bfb53d) SHA1(31b8f31acd3aa394acd80db362774749842e1285) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )
ROM_END

ROM_START( bub68705a )
	ROM_REGION( 0x30000, "maincpu", 0 )
	ROM_LOAD( "a78-06.51",    0x00000, 0x08000, CRC(32c8305b) SHA1(6bf69b3edfbefd33cd670a762b4bf0b39629a220) )
	ROM_LOAD( "3-1.bin",        0x10000, 0x08000, CRC(980c2615) SHA1(3670cf3e4e73028aadf4460ad887a0b544bcdbc4) )
	ROM_LOAD( "3.bin",          0x18000, 0x08000, CRC(e6c698f2) SHA1(8df116075f5891f74d0da8966ed11c597b5f544f) )

	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "a78-08.37",    0x0000, 0x08000, CRC(ae11a07b) SHA1(af7a335c8da637103103cc274e077f123908ebb7) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46",    0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x800, "mcu", 0 )
	ROM_LOAD( "68705a.bin",    0x000, 0x800, CRC(32bffbf4) SHA1(25f9c9224d8e8d7844ef496a7207e7a55554c653) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )
ROM_END


GAME( 2012, bbaladar,   bublbobl, boblbobl, bbaladar, bublbobl_state, init_common, ROT0, "Aladar", "Bubble Bobble (Bootleg)", MACHINE_SUPPORTS_SAVE )
GAME( 2000, bb2bmh,     bublbobl, bub68705, bublbobl, bub68705_state, init_common, ROT0, "Unknown", "Bubble Bobble (Memories Hack)", MACHINE_SUPPORTS_SAVE )
GAME( 2000, bbhackv1,   bublbobl, bub68705, bublbobl, bub68705_state, init_common, ROT0, "Unknown", "Bubble Bobble (Level Hack)", MACHINE_SUPPORTS_SAVE )
GAME( 2013, bbredux1,   bublbobl, boblbobl, boblbobl, bublbobl_state, init_common, ROT0, "Punji", "Bobble Bobble Redux (Level Skip)", MACHINE_SUPPORTS_SAVE )
GAME( 2013, bbredux2,   bublbobl, boblbobl, boblbobl, bublbobl_state, init_common, ROT0, "Punji", "Bobble Bobble Redux (Game Continue)", MACHINE_SUPPORTS_SAVE )
GAME( 2013, bbredux3,   bublbobl, boblbobl, boblbobl, bublbobl_state, init_common, ROT0, "Punji", "Bobble Bobble Redux (High Score)", MACHINE_SUPPORTS_SAVE )
GAME( 19??, sboblboblh, bublbobl, boblbobl, boblbobl, bublbobl_state, init_common, ROT0, "Unknown", "Super Bobble Bobble (Level Select)", MACHINE_NOT_WORKING | MACHINE_SUPPORTS_SAVE )
GAME( 2007, bublbobf,   bublbobl, bublbobl, bublbobl, bublbobl_state, init_common, ROT0, "Arkatrad", "Bubble Bobble (French)", MACHINE_SUPPORTS_SAVE )
GAME( 1986, bublboblu,  bublbobl, bublbobl, bublbobl, bublbobl_state, init_common, ROT0, "bootleg", "Bubble Bobble (Ultra Version, Hack)", MACHINE_SUPPORTS_SAVE )
GAME( 1986, bub68705a,  bublbobl, bub68705, bublbobl, bub68705_state, init_common, ROT0, "bootleg", "Bubble Bobble (Bootleg with 68705, set 2)", MACHINE_SUPPORTS_SAVE )


// PSmame (c) gaston90 used with permission

 /****************************************************
         Proyecto Shadows Mame Build Plus
*****************************************************/

ROM_START( bublbobls01 )
	ROM_REGION( 0x30000, "maincpu", 0 ) // There's no French text in this set
	ROM_LOAD( "bublbobf-06.51",    0x00000, 0x08000, CRC(9ced3d8f) SHA1(d445f218fca822e7083a9347abd4a4e049b6555b) )
	ROM_LOAD( "a78-05-1hc01.52",    0x10000, 0x10000, CRC(b8f43b09) SHA1(96abd923e712078c70a452ba51513577cc0bdb08) )

	ROM_REGION( 0x10000, "subcpu", 0 )
	ROM_LOAD( "a78-08.37",    0x0000, 0x08000, CRC(ae11a07b) SHA1(af7a335c8da637103103cc274e077f123908ebb7) )

	ROM_REGION( 0x10000, "audiocpu", 0 )
	ROM_LOAD( "a78-07.46",    0x0000, 0x08000, CRC(4f9a26e8) SHA1(3105b34b88a7134493c2b3f584729f8b0407a011) )

	ROM_REGION( 0x10000, "mcu", 0 )
	ROM_LOAD( "a78-01.17",    0xf000, 0x1000, CRC(b1bfb53d) SHA1(31b8f31acd3aa394acd80db362774749842e1285) )

	ROM_REGION( 0x80000, "gfx1", ROMREGION_INVERT )
	ROM_LOAD( "a78-09.12",    0x00000, 0x8000, CRC(20358c22) SHA1(2297af6c53d5807bf90a8e081075b8c72a994fc5) )
	ROM_LOAD( "a78-10.13",    0x08000, 0x8000, CRC(930168a9) SHA1(fd358c3c3b424bca285f67a1589eb98a345ff670) )
	ROM_LOAD( "a78-11.14",    0x10000, 0x8000, CRC(9773e512) SHA1(33c1687ee575d66bf0e98add45d06da827813765) )
	ROM_LOAD( "a78-12.15",    0x18000, 0x8000, CRC(d045549b) SHA1(0c12077d3ddc2ce6aa45a0224ad5540f3f218446) )
	ROM_LOAD( "a78-13.16",    0x20000, 0x8000, CRC(d0af35c5) SHA1(c5a89f4d73acc0db86654540b3abfd77b3757db5) )
	ROM_LOAD( "a78-14.17",    0x28000, 0x8000, CRC(7b5369a8) SHA1(1307b26d80e6f36ebe6c442bebec41d20066eaf9) )
	ROM_LOAD( "a78-15.30",    0x40000, 0x8000, CRC(6b61a413) SHA1(44eddf12fb46fceca2addbe6da929aaea7636b13) )
	ROM_LOAD( "a78-16.31",    0x48000, 0x8000, CRC(b5492d97) SHA1(d5b045e3ebaa44809757a4220cefb3c6815470da) )
	ROM_LOAD( "a78-17.32",    0x50000, 0x8000, CRC(d69762d5) SHA1(3326fef4e0bd86681a3047dc11886bb171ecb609) )
	ROM_LOAD( "a78-18.33",    0x58000, 0x8000, CRC(9f243b68) SHA1(32dce8d311a4be003693182a999e4053baa6bb0a) )
	ROM_LOAD( "a78-19.34",    0x60000, 0x8000, CRC(66e9438c) SHA1(b94e62b6fbe7f4e08086d0365afc5cff6e0ccafd) )
	ROM_LOAD( "a78-20.35",    0x68000, 0x8000, CRC(9ef863ad) SHA1(29f91b5a3765e4d6e6c3382db1d8d8297b6e56c8) )

	ROM_REGION( 0x0100, "proms", 0 )
	ROM_LOAD( "a71-25.41",    0x0000, 0x0100, CRC(2d0f8545) SHA1(089c31e2f614145ef2743164f7b52ae35bc06808) )
ROM_END

/*    YEAR  NAME            PARENT    MACHINE        INPUT       INIT             MONITOR COMPANY                 FULLNAME FLAGS */
// Bubble Bobble
GAME( 2007, bublbobls01,   bublbobl,        bublbobl, bublbobl,   bublbobl_state, init_common, ROT0,  "S.Arkames",     "Bubble Bobble (Translation French)", MACHINE_SUPPORTS_SAVE )

