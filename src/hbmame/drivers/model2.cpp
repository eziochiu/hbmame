// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/drivers/model2.cpp"

ROM_START( srallyp )
	ROM_REGION( 0x200000, "maincpu", 0 ) // i960 program
	ROM_LOAD32_WORD( "srallyp.ic12", 0x000000, 0x080000, CRC(926632ab) SHA1(7a37813f3d59b8e6e68220aa3120460b1ce5b33d) )
	ROM_LOAD32_WORD( "srallyp.ic13", 0x000002, 0x080000, CRC(c93b33f1) SHA1(8477a05e44c1c9ee5e99eaa9d31cd9905ebf8c26) )

	ROM_REGION32_LE( 0x2400000, "user1", 0 ) // Data
	ROM_LOAD32_WORD( "mpr-17746.10", 0x000000, 0x200000, CRC(8fe311f4) SHA1(f4ada8e5c906fc384bed1b96f09cdf313f89e825) )
	ROM_LOAD32_WORD( "mpr-17747.11", 0x000002, 0x200000, CRC(543593fd) SHA1(5ba63a77e9fc70569af21d50b3171bc8ff4522b8) )
	ROM_LOAD32_WORD( "mpr-17744.8",  0x400000, 0x200000, CRC(71fed098) SHA1(1d187cad375121a45348d640edd3cc7dce658d28) )
	ROM_LOAD32_WORD( "mpr-17745.9",  0x400002, 0x200000, CRC(8ecca705) SHA1(ed2b3298aad6f4e52dc672a0168183e457564b43) )
	ROM_LOAD32_WORD( "mpr-17884.6",  0x800000, 0x200000, CRC(4cfc95e1) SHA1(81d927b8c4f9d0c4c5e29d676b30f30f83751fdc) )
	ROM_LOAD32_WORD( "mpr-17885.7",  0x800002, 0x200000, CRC(a08d2467) SHA1(9449ac8f8f9ce8d8e536b05a91e46841fed7f2d0) )

	ROM_REGION( 0x800000, "tgp", 0 ) // TGP program? (COPRO socket)
	ROM_LOAD32_WORD( "mpr-17754.28", 0x000000, 0x200000, CRC(81a84f67) SHA1(c0a9b690523a529e4015e9af10dc3fb2a1726f08) )
	ROM_LOAD32_WORD( "mpr-17755.29", 0x000002, 0x200000, CRC(2a6e7da4) SHA1(e60803ae951489fe47d66731d15c32249ca547b4) )

	ROM_REGION( 0x010000, "drivecpu", 0 ) // Drive I/O program
	ROM_LOAD( "epr-17891.ic12", 0x000000, 0x010000, CRC(9a33b437) SHA1(3e8f210aa5159e78f640126cb5ce7f05f22560f2) )

	ROM_REGION( 0x2000000, "user2", 0 ) // Models
	ROM_LOAD32_WORD( "mpr-17748.16", 0x000000, 0x200000, CRC(3148a2b2) SHA1(283cc49bfb6c6381a7ead9273fd097dca5b981b6) )
	ROM_LOAD32_WORD( "mpr-17750.20", 0x000002, 0x200000, CRC(232aec29) SHA1(4d470e71df61298282c356814e2d151fda323fb6) )
	ROM_LOAD32_WORD( "mpr-17749.17", 0x400000, 0x200000, CRC(0838d184) SHA1(704175c8b29e4c989afcb7be42e7e0e096740eaf) )
	ROM_LOAD32_WORD( "mpr-17751.21", 0x400002, 0x200000, CRC(ed87ac62) SHA1(601542149d33ca52a47536b4b0af47bf1fd87eb2) )

	ROM_REGION( 0x1000000, "user3", 0 ) // Textures
	ROM_LOAD32_WORD( "mpr-17753.25", 0x000000, 0x200000, CRC(6db0eb36) SHA1(dd5fd3c9592360d3e95623ac2491e6faabe9dbcb) )
	ROM_LOAD32_WORD( "mpr-17752.24", 0x000002, 0x200000, CRC(d6aa86ce) SHA1(1d342f87d1af1e5438d1ae818b1b14268e765897) )

	ROM_REGION( 0x20000, "cpu4", 0) // Communication program
	ROM_LOAD( "epr-16726.bin", 0x000000, 0x020000, CRC(c179b8c7) SHA1(86d3e65c77fb53b1d380b629348f4ab5b3d39228) )

	ROM_REGION( 0x100000, "audiocpu", 0 ) // Sound program
	ROM_LOAD16_WORD_SWAP( "epr-17890a.30", 0x080000, 0x040000, CRC(5bac3fa1) SHA1(3635333d36463b6fab25560ed918e05138f964dc) )

	ROM_REGION( 0x800000, "scsp", 0 ) // Samples
	ROM_LOAD( "mpr-17756.31", 0x000000, 0x200000, CRC(7725f111) SHA1(1f1ee3f19a6bcf57bc5a1c7dd64ee83f8b81f084) )
	ROM_LOAD( "mpr-17757.32", 0x200000, 0x200000, CRC(1616e649) SHA1(1d3a0e441d150ada0535a9d50e2f69dd4b99c584) )
	ROM_LOAD( "mpr-17886.36", 0x400000, 0x200000, CRC(54a72923) SHA1(103c4838b27378c834c08d29d6fb6ba95e7f9d03) )
	ROM_LOAD( "mpr-17887.37", 0x600000, 0x200000, CRC(38c31fdd) SHA1(a85f05160b060d9d4a431aaa73cfc03f24214fb9) )

	MODEL2_CPU_BOARD
	MODEL2A_VID_BOARD
ROM_END



GAME( 2000?, srallyp,  srallyc, srallyc, srallyc, model2_state, srallyc, ROT0, "Kyle Hodgetts", "Sega Rally Pro Drivin'", 0 )
