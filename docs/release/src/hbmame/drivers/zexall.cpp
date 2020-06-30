// license:BSD-3-Clause
// copyright-holders:Robbbert
/******************************************************************************

2020-06-04 Added zex8085, it's a modified version of zexall, by Ian Bartholomew. CRCs were obtained by running it on a real machine.
http://www.vcfed.org/forum/showthread.php?74993

  Memory map:

  Ram 0000-FFFF (preloaded with binary)
  Special calls take place for three ram values (this interface was designed by kevtris):
  FFFD - 'ack' - shared ram with output device; z80 reads from here and considers the byte at FFFF read if this value incremented
  FFFE - 'req' - shared ram with output device; z80 writes an incrementing value to FFFE to indicate that there is a byte waiting at FFFF
                 and hence requesting the output device on the other end do something about it, until FFFD is incremented by the
                 output device to acknowledge receipt
  FFFF - 'data' - shared ram with output device; z80 writes the data to be sent to output device here
  One i/o port is used, but left unemulated:
  0001 - bit 0 controls whether interrupt timer is enabled (1) or not (0), this is a holdover from a project of kevtris' and can be ignored.

******************************************************************************/

#include "emu.h"
#include "cpu/i8085/i8085.h"
#include "machine/terminal.h"

class zexall_state : public driver_device
{
public:
	zexall_state(const machine_config &mconfig, device_type type, const char *tag)
		: driver_device(mconfig, type, tag)
		, m_maincpu(*this, "maincpu")
		, m_terminal(*this, "terminal")
		, m_main_ram(*this, "main_ram")
	{ }

	void zex8085(machine_config &config);

private:
	u8 output_ack_r();
	u8 output_req_r();
	u8 output_data_r();
	void output_ack_w(u8 data);
	void output_req_w(u8 data);
	void output_data_w(u8 data);

	void mem_map(address_map &map);

	required_device<cpu_device> m_maincpu;
	required_device<generic_terminal_device> m_terminal;
	required_shared_ptr<u8> m_main_ram;
	u8 m_out_data; // byte written to 0xFFFF
	u8 m_out_req; // byte written to 0xFFFE
	u8 m_out_req_last; // old value at 0xFFFE before the most recent write
	u8 m_out_ack; // byte written to 0xFFFC

	virtual void machine_start() override;
	virtual void machine_reset() override;
};


/******************************************************************************
 Machine Start/Reset
******************************************************************************/

void zexall_state::machine_start()
{
	// register for savestates
	save_item(NAME(m_out_ack));
	save_item(NAME(m_out_req));
	save_item(NAME(m_out_req_last));
	save_item(NAME(m_out_data));
}

void zexall_state::machine_reset()
{
	// zerofill
	m_out_ack = 0;
	m_out_req = 0;
	m_out_req_last = 0;
	m_out_data = 0;

	// program is self-modifying, so need to refresh it on each run
	u8 *program = memregion("maincpu")->base();
	memcpy(m_main_ram, program, 0x8000);
}


/******************************************************************************
 I/O Handlers
******************************************************************************/

u8 zexall_state::output_ack_r()
{
	// spit out the byte in out_byte if out_req is not equal to out_req_last
	if (m_out_req != m_out_req_last)
	{
		m_terminal->write(m_out_data);
		m_out_req_last = m_out_req;
		m_out_ack++;
	}
	return m_out_ack;
}

void zexall_state::output_ack_w(u8 data)
{
	m_out_ack = data;
}

u8 zexall_state::output_req_r()
{
	return m_out_req;
}

void zexall_state::output_req_w(u8 data)
{
	m_out_req_last = m_out_req;
	m_out_req = data;
}

u8 zexall_state::output_data_r()
{
	return m_out_data;
}

void zexall_state::output_data_w(u8 data)
{
	m_out_data = data;
}


/******************************************************************************
 Address Maps
******************************************************************************/

void zexall_state::mem_map(address_map &map)
{
	map(0x0000, 0xffff).ram().share("main_ram");
	map(0xfffd, 0xfffd).rw(FUNC(zexall_state::output_ack_r), FUNC(zexall_state::output_ack_w));
	map(0xfffe, 0xfffe).rw(FUNC(zexall_state::output_req_r), FUNC(zexall_state::output_req_w));
	map(0xffff, 0xffff).rw(FUNC(zexall_state::output_data_r), FUNC(zexall_state::output_data_w));
}


/******************************************************************************
 Input Ports
******************************************************************************/

static INPUT_PORTS_START( zexall )
INPUT_PORTS_END


/******************************************************************************
 Machine Drivers
******************************************************************************/

void zexall_state::zex8085(machine_config &config)
{
	/* basic machine hardware */
	I8085A(config, m_maincpu, XTAL(4'000'000));
	m_maincpu->set_addrmap(AS_PROGRAM, &zexall_state::mem_map);

	/* video hardware */
	GENERIC_TERMINAL(config, m_terminal, 0);
}


/******************************************************************************
 ROM Definitions
******************************************************************************/

ROM_START( zex8085 )
	ROM_REGION( 0x8000, "maincpu", ROMREGION_ERASEFF )
	ROM_LOAD( "int8085.bin",   0x0000, 0x0050, CRC(4184ad6d) SHA1(f958d2e603cacdad3b65676133b6af6ef4c6301f) )
	ROM_LOAD( "zex8085.bin",   0x0100, 0x1200, CRC(3545bdbd) SHA1(4d6a2205881b62fae459ed9d908ecf7479d1d06c) )
ROM_END


/******************************************************************************
 Drivers
******************************************************************************/

//    YEAR  NAME     PARENT  COMPAT  MACHINE  INPUT   CLASS         INIT        COMPANY                         FULLNAME                            FLAGS
COMP( 2020, zex8085, 0,      0,      zex8085,  zexall, zexall_state, empty_init, "Ian Bartholomew", "Zexall (i8085)", MACHINE_SUPPORTS_SAVE )
