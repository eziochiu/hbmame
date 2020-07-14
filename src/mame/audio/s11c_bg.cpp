// license:BSD-3-Clause
// copyright-holders:Barry Rodewald
/*
 * s11c_bg.cpp - Williams D-11581 "Audio Board" (M68B09E + YM2151 + HC55516 + DAC)
 * Used by Williams System 11A (F-14), all System 11B (except Jokerz) and all System 11C pinballs
 * Used by Midway Y-Unit Arcade Hardware (for Smash TV and High Impact Football)
 * Used by the prototype version of Funhouse pinball for the WPC Alphanumeric system
 *
 * The mixing resistors before the MC1458 differ between the D-11581, D-11581-20xx (System 11C), and D-1129x board schematics:
 *                 D-1129x    D-11581        D-11581-20xx
 * CPU_SOUND       R32 2.2k   R12 2.2k       R12 4.7k
 * YM2151 CH1      R33 10k    R14 10k        R14 20k
 * YM2151 CH2      R34 10k    R15 10k        R15 20k
 * MC1408 DAC      R35 10k    R16 6.3k       R16 13k
 * CVSD           [R30 10k]  [R13 4.99k 2%]  R13 4.99k 2%
 * MC1458 Feedback R38 10k    R17 10k        R17 10k
 * MC1458 +-to-gnd R36 4.7k   R11 4.7k       R11 4.7k
 * [] - if CVSD section present

 * Note that some D-11581 boards have the D-11297/8 mixing resistors in place, possibly those
 * originally intended for use as replacement parts for D-1129x boards
 * See https://pinwiki.com/wiki/images/f/fc/System_11_Sound_Board.JPG for an example, which
 * may have originally been a D-11298 replacement, as the CVSD section is unpopulated.

 * Note that the System11C D-11581-20xx boards have the mixing resistors changed to make the CVSD sound twice
 * as loud as it typically would be, by doubling the resistor values for the other mixer inputs, see
 * https://pinwiki.com/wiki/images/7/7e/System11CSoundBoard.jpg

 * D-11581 Jumpers:
 * W1 - exclusive w/W4, W6 : YM2151 reset comes from Board PIA CA2
 * W2 - exclusive w/W3     : EPROMS U4, U19, [U20] are 27512
 * W3 - exclusive w/W2     : EPROMS U4, U19, [U20] are 2764, 27128 or 27256 (where pin 1 must be high) [Pre-System 11C boards (i.e. D-11581) have a trace shorting W3 closed permanently which must be cut if 27512 EPROMs are to be used]
 * W4 -'exclusive'w/W4, W6 : YM2151 reset comes from PIA CB2/J4 P12 (internal or external)
 * W5                      : Board Reset comes from J4 P18 (if absent, Board Reset is generated from power up)
 * W6 - exclusive w/W4, W6 : YM2151 reset comes from Board Reset
 * W7                      : if present, the VCC/+5v rail is shorted to the +12v rail. (This is used in the case where the board is only run on +5v and -12v instead of +5v, +12v, and -12v)
 * W8 - exclusive w/W9     : U5 is a 6164 SRAM (pin 23/A11 is grounded)
 * W9 - exclusive w/W8     : U5 is a 6116 SRAM (pin 21, footprint pin 23, is /WE)
 These two jumpers are only on the D-11581-20xx (System 11C) version, and W2 and W3 do not affect U20 on this PCB version:
 * W10 - linked w/W2+W3    : (only if W2 is also set) EPROM U20 is a 27512
 * W11 - linked w/W2+W3    : EPROM U20 is a 2764, 27128 or 27256 (where pin 1 must be high)



 * Williams D-11297/D-11298 "BG Music & Speech Board":
 * D-11297/D-11298 is the predecessor to D-11581, and is fully compatible with it.
 * It is a larger board, physically.
 * It is used on the following Williams System 11A games:
 * D-11297 (CVSD populated)  : PIN*BOT
 * D-11298 (CVSD unpopulated): Millionaire!

 * Unlike the later D-11581 board which has mono output only, the D-11297/8 board
 * has provisions for stereo output from the ym2151, but it is unclear if these were
 * ever populated on any shipping boards.

 * D-1129x Jumpers:
 * W1                      : Board Reset comes from J4 P18 (if absent, Board Reset is generated from power up or a manual test switch sw1)
 * W2 - exclusive w/W3     : EPROMS U4, U19, U20 are 27512
 * W3 - exclusive w/W2     : EPROMS U4, U19, U20 are 2764, 27128 or 27256 (where pin 1 must be high)
 * W4                      : if present, the VCC/+5v rail is shorted to the +12v rail. (This is used in the case where the board is only run on +5v and -12v instead of +5v, +12v, and -12v)
 * W5 - exclusive w/W6, W7 : YM2151 reset comes from Board Reset
 * W6 -'exclusive'w/W5, W7 : YM2151 reset comes from PIA CB2/J4 P12 (internal or external)
 * W7 - exclusive w/W5, W6 : YM2151 reset comes from Board PIA CA2


 * The CVSD filter on all of these boards has the same components:
 *
 *                                     .--------+---------.                      .--------+---------.
 *                                     |        |         |                      |        |         |
 *                                     Z       --- c2     |                      Z       --- c12    |
 *                                     Z r3    --- 180pf  |                      Z r13   --- 1200pf |
 *                                     Z 180k   |         |                      Z 27k    |         |
 *          + c10     r1               |   r2   |  |\     |     r11              |   r12  |  |\     |
 *   In >----|(------ZZZZ----+---------+--ZZZZ--+  | \    +----ZZZZ----+---------+--ZZZZ--+  | \    |
 *            1uf     43k    |             36k  '--|- \   |     27k    |             15k  '--|- \   |   + c20
 *                          ---  c1                |   >--'           ---  c11               |   >--+----|(----> to mix resistor
 *                          ---  0uf[1]         .--|+ /               ---  4700pf         .--|+ /         10uf
 *                           |             r4   |  | /                 |             r14  |  | /
 *                          gnd        .--ZZZZ--'  |/                 gnd        .--ZZZZ--'  |/
 *                                     |   220k     MC1458                       |   27k      MC1458
 *                                    gnd                                       gnd
 *
 *
 * [1] Logically there should be a capacitor to ground at c1 of value 1800uf,
 *     but this was omitted on the D-11297 board, possibly in error, and this
 *     omission carried over to future sound boards including all versions of the D-11581.
 *     The WPC-AN sound board, A-12738-50xxx, fixed this by completely redesigning the filters
 *     for both the ym2151 and cvsd.
 *
 * This circuit would be a 4th order (cascaded 2nd order) op-amp multifeedback lowpass filter,
 *  but because of the capacitor omitted, it is actually a first order-with-gain lowpass,
 *  cascaded into a 2nd order lowpass, forming a 3rd order filter.
 *
 * This same exact circuit, same component values (but including the capacitor missing here),
 * appears on the System 11 and System 11A mainboards.
 * System 11B changed the components slightly, presumably so the CVSD produced on the mainboard
 * sounded a bit different tone-wise to the CVSD produced from the Audio Board.



 * Williams "BG Music Board" D-11197-542 16-8972
 *  * used on Williams System 11 'Road Kings' only
 *  * has DAC and YM2151/YM3012
 *  * PIA CA2 EPROM banking
 *  * This board, like D-1129x, has provisions for YM2151 stereo via two amplifiers to be
 *     populated on the board itself, but like D-1129x they and their supporting passives are not populated.

 * The mixing resistors on this board are the same as D-1129x, except the CPU_SOUND input resistor is 2.7k instead of 2.2k
 * There is no CVSD section at all.

 * D-11197 Jumpers:
 * W1                      : Board Reset comes from J4 P18 (if absent, Board Reset is generated from power up or a manual test switch sw1)
 * W2 - exclusive w/W3     : EPROMS U4 is a 27512
 * W3 - exclusive w/W2     : EPROMS U4 is a 2764, 27128 or 27256 (where pin 1 must be high)
 * W4                      : if present, the VCC/+5v rail is shorted to the +12v rail. (This is used in the case where the board is only run on +5v and -12v instead of +5v, +12v, and -12v)
 * W5 - exclusive w/W6, W7 : YM2151 reset comes from Board Reset
 * W6 -'exclusive'w/W5, W7 : YM2151 reset comes from PIA CB2/J4 P12 (internal or external)



 * Williams "BG Sound Board" C-11029/C-11030 5766-10929-00
 *  * used on Williams System 11 'High Speed' and 'Grand Lizard' only (as well as the "Wreck'n Ball" prototype, see https://www.ipdb.org/machine.cgi?id=6167 )
 *  * has DAC only
 *  * no EPROM banking hardware, 1 28-pin ROM socket (2764/27128/27256 only)
 *  * PIA CA1 and CA2 are labeled 'HAND1' and 'HAND2' on schematics and are tied high/unused.
 *  * This board has some provisions for what looks like incoming and outgoing octal latch
 *    for data to be read from/writen to by the PIA, but this is unpopulated/bypassed on the pcb

 * C-11029/C-11030 Jumpers:
 * W1                      : Board Reset comes from J4 P18 (if absent, Board Reset is generated from power up or a manual test switch sw1)



 *
 *  Created on: 2/10/2013
 *      Author: bsr
 *  Updated on: 7/6/2020
 *      Author: lord nightmare
 */

#include "emu.h"
#include "s11c_bg.h"
#include "sound/dac.h"
#include "sound/volt_reg.h"


DEFINE_DEVICE_TYPE(S11C_BG, s11c_bg_device, "s11c_bg", "Williams System 11C Background Music")

s11c_bg_device::s11c_bg_device(const machine_config &mconfig, const char *tag, device_t *owner, uint32_t clock)
	: device_t(mconfig, S11C_BG,tag,owner,clock)
	, device_mixer_interface(mconfig, *this)
	, m_cpu(*this, "bgcpu")
	, m_ym2151(*this, "ym2151")
	, m_hc55516(*this, "hc55516_bg")
	, m_pia40(*this, "pia40")
	, m_cpubank(*this, "bgbank")
	, m_rom(*this, finder_base::DUMMY_TAG)
	, m_cb2_cb(*this)
	, m_pb_cb(*this)
{
}

void s11c_bg_device::s11c_bg_map(address_map &map)
{
	map(0x0000, 0x07ff).mirror(0x1800).ram();
	map(0x2000, 0x2001).mirror(0x1ffe).rw(m_ym2151, FUNC(ym2151_device::read), FUNC(ym2151_device::write));
	map(0x4000, 0x4003).mirror(0x1ffc).rw("pia40", FUNC(pia6821_device::read), FUNC(pia6821_device::write));
	map(0x6000, 0x6000).mirror(0x07ff).w(FUNC(s11c_bg_device::bg_cvsd_clock_set_w));
	map(0x6800, 0x6800).mirror(0x07ff).w(FUNC(s11c_bg_device::bg_cvsd_digit_clock_clear_w));
	map(0x7800, 0x7800).mirror(0x07ff).w(FUNC(s11c_bg_device::bgbank_w));
	map(0x8000, 0xffff).bankr("bgbank");
}

TIMER_CALLBACK_MEMBER(s11c_bg_device::deferred_cb2_w)
{
	if (!m_cb2_cb.isnull())
		m_cb2_cb(param);
	else
		logerror("S11C_BG CB2 writeback called, but callback is not registered!\n");
}

TIMER_CALLBACK_MEMBER(s11c_bg_device::deferred_pb_w)
{
	if (!m_pb_cb.isnull())
		m_pb_cb(param);
	else
		logerror("S11C_BG PB writeback called, but callback is not registered!\n");
}


WRITE_LINE_MEMBER( s11c_bg_device::pia40_cb2_w)
{
	machine().scheduler().synchronize(timer_expired_delegate(FUNC(s11c_bg_device::deferred_cb2_w),this), state);
}

void s11c_bg_device::pia40_pb_w(uint8_t data)
{
	machine().scheduler().synchronize(timer_expired_delegate(FUNC(s11c_bg_device::deferred_pb_w),this), data);
}


WRITE_LINE_MEMBER( s11c_bg_device::extra_w )
{
	m_pia40->cb2_w(state);
}

WRITE_LINE_MEMBER( s11c_bg_device::ctrl_w )
{
	m_pia40->cb1_w(state);
}

void s11c_bg_device::data_w(uint8_t data)
{
	m_pia40->portb_w(data);
}

void s11c_bg_device::device_add_mconfig(machine_config &config)
{
	MC6809E(config, m_cpu, XTAL(8'000'000) / 4); // MC68B09E
	m_cpu->set_addrmap(AS_PROGRAM, &s11c_bg_device::s11c_bg_map);
	config.set_maximum_quantum(attotime::from_hz(50));

	YM2151(config, m_ym2151, XTAL(3'579'545)); // "3.58 MHz" on schematics and parts list
	m_ym2151->irq_handler().set(m_pia40, FUNC(pia6821_device::ca1_w)).invert(); // IRQ is not true state
	m_ym2151->add_route(ALL_OUTPUTS, *this, 0.1);

	MC1408(config, "dac", 0).add_route(ALL_OUTPUTS, *this, 0.25);
	voltage_regulator_device &vref(VOLTAGE_REGULATOR(config, "vref"));
	vref.add_route(0, "dac", 1.0, DAC_VREF_POS_INPUT);
	vref.add_route(0, "dac", -1.0, DAC_VREF_NEG_INPUT);

	HC55516(config, m_hc55516, 0).add_route(ALL_OUTPUTS, *this, 0.6);

	PIA6821(config, m_pia40, 0);
	m_pia40->writepa_handler().set("dac", FUNC(dac_byte_interface::data_w));
	m_pia40->writepb_handler().set(FUNC(s11c_bg_device::pia40_pb_w));
	m_pia40->ca2_handler().set(m_ym2151, FUNC(ym2151_device::reset_w));
	m_pia40->cb2_handler().set(FUNC(s11c_bg_device::pia40_cb2_w));
	m_pia40->irqa_handler().set_inputline(m_cpu, M6809_FIRQ_LINE);
	m_pia40->irqb_handler().set_inputline(m_cpu, INPUT_LINE_NMI);
}

void s11c_bg_device::device_start()
{
	/* resolve lines */
	m_cb2_cb.resolve();
	m_pb_cb.resolve();
}

void s11c_bg_device::device_reset()
{
	m_cpubank->configure_entries(0, 8, &m_rom[0x10000], 0x8000);
	m_cpubank->set_entry(0);
	// reset the CPU again, so that the CPU are starting with the right vectors (otherwise sound may die on reset)
	m_cpu->pulse_input_line(INPUT_LINE_RESET, attotime::zero);
}

void s11c_bg_device::bg_cvsd_clock_set_w(uint8_t data)
{
	m_hc55516->clock_w(1);
}

void s11c_bg_device::bg_cvsd_digit_clock_clear_w(uint8_t data)
{
	m_hc55516->clock_w(0);
	m_hc55516->digit_w(data&1);
}

void s11c_bg_device::bgbank_w(uint8_t data)
{
	uint8_t bank = ((data & 0x04) >> 2) | ((data & 0x03) << 1);
	m_cpubank->set_entry(bank);
}
