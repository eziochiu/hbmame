// license:BSD-3-Clause
// copyright-holders:David Haywood

// pcp8718 contains unsp code, but no obvious startup code / vectors, so it's probably booting from another device / bootstrapped
// these contain the same game selection as the games in unk6502_st2xxx.cpp but on updated hardware

// These use SPI ROMs and unSP2.0 instructions, so will be GeneralPlus branded parts, not SunPlus
// possibly the framebuffer based video ones rather than the ones with tile layers

/*

for pcp8728 long jumps are done indirect via a call to RAM

990c 20ec       r4 = 20ec
d9dd            [1d] = r4
990c 0007       r4 = 0007
d9de            [1e] = r4
fe80 28f7       goto 0028f7

this suggests the ROM gets copied to RAM at 0x20000, as all offsets need to be adjusted by that (or the device can see SPI directly at 0x20000)
this is logical for unSP2.0 based devices as the CS area typically starts at 0x20000 with everything below that being internal space for internal RAM/ROM/peripherals

*/

#include "emu.h"

#include "screen.h"
#include "emupal.h"
#include "speaker.h"
#include "cpu/unsp/unsp.h"


class pcp8718_state : public driver_device
{
public:
	pcp8718_state(const machine_config &mconfig, device_type type, const char *tag) :
		driver_device(mconfig, type, tag),
		m_maincpu(*this, "maincpu"),
		m_mainram(*this, "mainram"),
		m_palette(*this, "palette"),
		m_screen(*this, "screen")
	{ }

	void pcp8718(machine_config &config);

private:
	virtual void machine_start() override;
	virtual void machine_reset() override;

	uint32_t screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect);

	required_device<unsp_20_device> m_maincpu;
	required_shared_ptr<uint16_t> m_mainram;

	required_device<palette_device> m_palette;
	required_device<screen_device> m_screen;

	void map(address_map &map);

	uint16_t simulate_28f7_r();
};

uint32_t pcp8718_state::screen_update(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	return 0;
}




void pcp8718_state::machine_start()
{
}

static INPUT_PORTS_START( pcp8718 )
INPUT_PORTS_END

void pcp8718_state::map(address_map &map)
{
	// there are calls to 01xxx and 02xxx regions
	// (RAM populated by internal ROM?, TODO: check to make sure code copied there isn't from SPI ROM like the GPL16250 bootstrap
	//  does from NAND, it doesn't seem to have a header in the same format at least)
	map(0x000000, 0x006fff).ram().share("mainram");

	// registers at 7xxx are similar to GPL16250, but not identical? (different video system?)

	// there are calls to 0x0f000 (internal ROM?)
	map(0x008000, 0x00ffff).rom().region("maincpu", 0x00000);

	// seems to have same memory config registers etc. as GPL16250 so CS Space starts at 0x020000 and the 'bank' is likely at 0x200000 too
	map(0x020000, 0x3fffff).rom().region("spi", 0x00000);
}

uint16_t pcp8718_state::simulate_28f7_r()
{
	// jumps to 28f7 act as a long jump to the address stored in 1d/1e
	// (or possibly a data copy + execute??)

	if (!machine().side_effects_disabled())
	{
		uint16_t pc = m_maincpu->state_int(UNSP_PC);
		uint16_t sr = m_maincpu->state_int(UNSP_SR);

		int realpc = (pc | (sr << 16)) & 0x003fffff;
		if (realpc == 0x28f7)
		{
			address_space& mem = m_maincpu->space(AS_PROGRAM);
			int newpc = mem.read_word(0x001d);
			int newds = mem.read_word(0x001e);

			sr &= 0xfff0;
			sr |= (newds & 0x003f);

			m_maincpu->set_state_int(UNSP_PC, newpc);
			m_maincpu->set_state_int(UNSP_SR, sr);
		}
	}
	return m_mainram[0x28f7];
}




void pcp8718_state::machine_reset()
{
	// this looks like it might actually be part of the IRQ handler (increase counter at 00 at the very start) rather than where we should end up after startup
	// it also looks like (from the pc = 2xxx opcodes) that maybe this code should be being executed in RAM as those don't give correct offsets in the data segment.
	m_maincpu->set_state_int(UNSP_PC, 0x0042);
	m_maincpu->set_state_int(UNSP_SR, 0x0002);

	uint16_t* ROM = (uint16_t*)memregion("maincpu")->base();
	ROM[0x7000] = 0x9a90; // retf from internal ROM call to 0xf000 (unknown purpose)	

	// there doesn't appear to be any code to set the SP, so it must be done by the internal ROM
	m_maincpu->set_state_int(UNSP_SP, 0x5fff);

	address_space& mem = m_maincpu->space(AS_PROGRAM);
	mem.write_word(0x2a46, 0x9a90); // retf from RAM call (unknown purpose)

	mem.write_word(0x28f7, 0xf165); // goto to RAM, for long jump / call (simulated),  could also be 'copy code at this address into RAM to execute'

	m_maincpu->space(AS_PROGRAM).install_read_handler(0x28f7, 0x28f7, read16smo_delegate(*this, FUNC(pcp8718_state::simulate_28f7_r)));

}

void pcp8718_state::pcp8718(machine_config &config)
{

	UNSP_20(config, m_maincpu, 20000000); // unknown CPU, unsp20 based
	m_maincpu->set_addrmap(AS_PROGRAM, &pcp8718_state::map);

	SCREEN(config, m_screen, SCREEN_TYPE_RASTER);
	m_screen->set_refresh_hz(60);
	m_screen->set_vblank_time(ATTOSECONDS_IN_USEC(0));
	m_screen->set_size(64*8, 32*8);
	m_screen->set_visarea(0*8, 40*8-1, 0*8, 30*8-1);
	m_screen->set_screen_update(FUNC(pcp8718_state::screen_update));
	m_screen->set_palette(m_palette);

	PALETTE(config, m_palette).set_format(palette_device::xBGR_555, 0x200);
}

ROM_START( pcp8718 )
	ROM_REGION( 0x800000, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "internal.rom", 0x000000, 0x10000, NO_DUMP ) // exact size unknown

	ROM_REGION16_BE( 0x800000, "spi", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "8718_en25f32.bin", 0x000000, 0x400000, CRC(cc138db4) SHA1(379af3d94ae840f52c06416d6cf32e25923af5ae) ) // dump needs verifying, dumper mentioned it was possibly bad (unit failed in process)
ROM_END

ROM_START( pcp8728 )
	ROM_REGION( 0x800000, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "internal.rom", 0x000000, 0x10000, NO_DUMP ) // exact size unknown

	ROM_REGION16_BE( 0x800000, "spi", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "pcp 8728 788 in 1.bin", 0x000000, 0x400000, CRC(60115f21) SHA1(e15c39f11e442a76fae3823b6d510178f6166926) )
ROM_END

ROM_START( unkunsp )
	ROM_REGION( 0x800000, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "internal.rom", 0x000000, 0x10000, NO_DUMP ) // exact size unknown

	ROM_REGION16_BE( 0x800000, "spi", ROMREGION_ERASEFF )
	ROM_LOAD16_WORD_SWAP( "fm25q16a.bin", 0x000000, 0x200000, CRC(aeb472ac) SHA1(500c24b725f6d3308ef8cbdf4259f5be556c7c92) )
ROM_END




CONS( 200?, pcp8718,      0,       0,      pcp8718,   pcp8718, pcp8718_state, empty_init, "PCP", "PCP 8718 - 788 in 1", MACHINE_IS_SKELETON ) // "HD 360 degrees rocker palm eyecare console"
CONS( 200?, pcp8728,      0,       0,      pcp8718,   pcp8718, pcp8718_state, empty_init, "PCP", "PCP 8728 - 788 in 1", MACHINE_IS_SKELETON )
CONS( 200?, unkunsp,      0,       0,      pcp8718,   pcp8718, pcp8718_state, empty_init, "<unknown>", "unknown unSP based handheld", MACHINE_IS_SKELETON )
