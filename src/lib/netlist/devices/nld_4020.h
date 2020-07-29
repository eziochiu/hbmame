// license:GPL-2.0+
// copyright-holders:Couriersud
/*
 * nld_4020.h
 *
 *  CD4020: 14-Stage Ripple Carry Binary Counters
 *
 *          +--------------+
 *      Q12 |1     ++    16| VDD
 *      Q13 |2           15| Q11
 *      Q14 |3           14| Q10
 *       Q6 |4    4020   13| Q8
 *       Q5 |5           12| Q9
 *       Q7 |6           11| RESET
 *       Q4 |7           10| IP (Input pulses)
 *      VSS |8            9| Q1
 *          +--------------+
 *
 *
 *  CD4024: 7-Stage Ripple Carry Binary Counters
 *
 *          +--------------+
 *       IP |1     ++    14| VDD
 *    RESET |2           13| NC
 *       Q7 |3           12| Q1
 *       Q6 |4    4024   11| Q2
 *       Q5 |5           10| NC
 *       Q4 |6            9| Q3
 *      VSS |7            8| NC
 *          +--------------+
 *
 *
 *  Naming conventions follow Texas Instruments datasheet
 *
 *  FIXME: Timing depends on VDD-VSS
 *         This needs a cmos d-a/a-d proxy implementation.
 *
 */

#ifndef NLD_4020_H_
#define NLD_4020_H_

#include "netlist/nl_setup.h"

/* FIXME: only used in mario.c */
#define CD4020_WI(name, cIP, cRESET, cVDD, cVSS)                                \
		NET_REGISTER_DEV(CD4020_WI, name)                                       \
		NET_CONNECT(name, IP, cIP)                                              \
		NET_CONNECT(name, RESET,  cRESET)                                       \
		NET_CONNECT(name, VDD,  cVDD)                                           \
		NET_CONNECT(name, VSS,  cVSS)

#define CD4020(name)                                                            \
		NET_REGISTER_DEV(CD4020, name)

#define CD4024(name)                                                            \
		NET_REGISTER_DEV(CD4024, name)

#endif /* NLD_4020_H_ */
