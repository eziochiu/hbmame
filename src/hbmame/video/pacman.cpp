// license:BSD-3-Clause
// copyright-holders:Robbbert
#include "../mame/video/pacman.cpp"


VIDEO_START_MEMBER( pacman_state, pacmanx )
{
	init_save_state();
	m_charbank = 0;
	m_spritebank = 0;
	m_palettebank = 0;
	m_colortablebank = 0;
	m_flipscreen = 0;
	m_bgpriority = 0;
	m_inv_spr = 0;
	m_xoffsethack = 2;

	m_bg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(pacman_state::pacman_get_tile_info)), tilemap_mapper_delegate(*this, FUNC(pacman_state::pacman_scan_rows)),  16, 16, 36, 28 );

	m_bg_tilemap->set_scrolldx(0, 384*2 - 288*2 );
	m_bg_tilemap->set_scrolldy(0, 264*2 - 224*2 );
}

u32 pacman_state::screen_update_pacmanx(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	if (m_bgpriority)
		bitmap.fill(0,cliprect);
	else
		m_bg_tilemap->draw(screen, bitmap, cliprect, TILEMAP_DRAW_OPAQUE,0);

	if( m_spriteram )
	{
		u8 *spriteram = m_spriteram;
		u8 *spriteram_2 = m_spriteram2;
		int offs;

		rectangle spriteclip(2*2*8, 2*68*8-1, 0*8, 2*56*8-1);
		spriteclip &= cliprect;

		/* Draw the sprites. Note that it is important to draw them exactly in this */
		/* order, to have the correct priorities. */
		for (offs = m_spriteram.bytes() - 2;offs > 2*2;offs -= 2)
		{
			int color;
			int sx,sy;
			u8 fx,fy;

			if(m_inv_spr)
			{
				sx = spriteram_2[offs + 1]*2;
				sy = 480 - (spriteram_2[offs]*2);
			}
			else
			{
				sx = 544 - spriteram_2[offs + 1]*2;
				sy = (spriteram_2[offs] - 31)*2;
			}

			fx = (spriteram[offs] & 1) ^ m_inv_spr;
			fy = (spriteram[offs] & 2) ^ ((m_inv_spr) << 1);

			color = ( spriteram[offs + 1] & 0x1f ) | (m_colortablebank << 5) | (m_palettebank << 6 );

			m_gfxdecode->gfx(1)->transmask(bitmap,spriteclip,
					( spriteram[offs] >> 2 ) | (m_spritebank << 6),
					color,
					fx,fy,
					sx,sy,
					m_palette->transpen_mask(*m_gfxdecode->gfx(1), color & 0x3f, 0));

			/* also plot the sprite with wraparound (tunnel in Crush Roller) */
			m_gfxdecode->gfx(1)->transmask(bitmap,spriteclip,
					( spriteram[offs] >> 2 ) | (m_spritebank << 6),
					color,
					fx,fy,
					sx - 512,sy,
					m_palette->transpen_mask(*m_gfxdecode->gfx(1), color & 0x3f, 0));
		}
		/* In the Pac Man based games (NOT Pengo) the first two sprites must be offset */
		/* one pixel to the left to get a more correct placement */
		for (offs = 2*2;offs >= 0;offs -= 2)
		{
			int color;
			int sx,sy;
			u8 fx,fy;

			if(m_inv_spr)
			{
				sx = spriteram_2[offs + 1]*2;
				sy = 480 - (spriteram_2[offs]*2);
			}
			else
			{
				sx = 544 - spriteram_2[offs + 1]*2;
				sy = (spriteram_2[offs] - 31)*2;
			}
			color = ( spriteram[offs + 1] & 0x1f ) | (m_colortablebank << 5) | (m_palettebank << 6 );

			fx = (spriteram[offs] & 1) ^ m_inv_spr;
			fy = (spriteram[offs] & 2) ^ ((m_inv_spr) << 1);

			m_gfxdecode->gfx(1)->transmask(bitmap,spriteclip,
					( spriteram[offs] >> 2 ) | (m_spritebank << 6),
					color,
					fx,fy,
					sx,sy + m_xoffsethack,
					m_palette->transpen_mask(*m_gfxdecode->gfx(1), color & 0x3f, 0));

			/* also plot the sprite with wraparound (tunnel in Crush Roller) */
			m_gfxdecode->gfx(1)->transmask(bitmap,spriteclip,
					( spriteram[offs] >> 2 ) | (m_spritebank << 6),
					color,
					fy,fx,          //FIXME: flipping bits are really supposed to be inverted here?
					sx - 512,sy + m_xoffsethack,
					m_palette->transpen_mask(*m_gfxdecode->gfx(1), color & 0x3f, 0));
		}
	}

	if (m_bgpriority != 0)
		m_bg_tilemap->draw(screen, bitmap, cliprect, 0,0);
	return 0;
}





/************************************************************************
  MULTIPAC adapted for HBMAME by Robbbert
 ************************************************************************/

TILE_GET_INFO_MEMBER(pacman_state::multipac_get_tile_info )
{
	int code = m_videoram[tile_index] | (m_charbank << 8);
	int attr = (m_colorram[tile_index] & 0x1f) | (m_colortablebank << 5);

	tileinfo.set(0,code,attr,0);
}

VIDEO_START_MEMBER( pacman_state, multipac )
{
	save_item(NAME(m_charbank));
	save_item(NAME(m_spritebank));
	save_item(NAME(m_palettebank));
	save_item(NAME(m_colortablebank));
	save_item(NAME(m_flipscreen));
	save_item(NAME(m_bgpriority));

	m_charbank = 0;
	m_spritebank = 0;
	m_colortablebank = 0;
	m_flipscreen = 0;
	m_bgpriority = 0;
	m_inv_spr = 0;
	m_xoffsethack = 1;

	m_bg_tilemap = &machine().tilemap().create(*m_gfxdecode, tilemap_get_info_delegate(*this, FUNC(pacman_state::multipac_get_tile_info)), tilemap_mapper_delegate(*this, FUNC(pacman_state::pacman_scan_rows)),  8, 8, 36, 28 );

	m_bg_tilemap->set_scrolldx(0, 384 - 288 );
	m_bg_tilemap->set_scrolldy(0, 264 - 224 );
}

void pacman_state::multipac_palette(palette_device &palette) const
{
	u16 i;
	static const int resistances[3] = { 1000, 470, 220 };
	double rweights[3], gweights[3], bweights[2];
	u8 bit0, bit1, bit2, r, g, b;
	u16 entries = palette.indirect_entries();
	u16 bank,banks = entries >> 5;
	const u8 *color_prom = machine().root_device().memregion("proms")->base();
	const u8 *m_p_prom = machine().root_device().memregion("proms")->base() + entries;

	/* compute the color output resistor weights */
	compute_resistor_weights(0, 255, -1.0,
			3, &resistances[0], rweights, 0, 0,
			3, &resistances[0], gweights, 0, 0,
			2, &resistances[1], bweights, 0, 0);

	for (bank = 0; bank < banks; bank++)
	{
		u16 obank = bank << 7;
		u16 ibank = bank << 5;

		/* create a lookup table for the palette */
		for (i = ibank; i < (ibank+32); i++)
		{
			/* red component */
			bit0 = BIT(color_prom[i], 0);
			bit1 = BIT(color_prom[i], 1);
			bit2 = BIT(color_prom[i], 2);
			r = combine_weights(rweights, bit0, bit1, bit2);

			/* green component */
			bit0 = BIT(color_prom[i], 3);
			bit1 = BIT(color_prom[i], 4);
			bit2 = BIT(color_prom[i], 5);
			g = combine_weights(gweights, bit0, bit1, bit2);

			/* blue component */
			bit0 = BIT(color_prom[i], 6);
			bit1 = BIT(color_prom[i], 7);
			b = combine_weights(bweights, bit0, bit1);

			palette.set_indirect_color(i, rgb_t(r, g, b));
		}

		for (i = obank;i < (obank+128);i++)
		{
			if (m_p_prom[i] & 15)
				palette.set_pen_indirect(i,(m_p_prom[i] & 15) | ibank);
			else
				palette.set_pen_indirect(i, 0);    /* preserve transparency */
		}
	}
}

u32 pacman_state::screen_update_multipac(screen_device &screen, bitmap_ind16 &bitmap, const rectangle &cliprect)
{
	if (m_bgpriority != 0)
		bitmap.fill(0, cliprect);
	else
		m_bg_tilemap->draw(screen, bitmap, cliprect, TILEMAP_DRAW_OPAQUE,0);

	if( m_spriteram != NULL )
	{
		u8 *spriteram = m_spriteram;
		u8 *spriteram_2 = m_spriteram2;
		int offs;

		rectangle spriteclip(2*8, 34*8-1, 0*8, 28*8-1);
		spriteclip &= cliprect;

		/* Draw the sprites. Note that it is important to draw them exactly in this */
		/* order, to have the correct priorities. */
		for (offs = m_spriteram.bytes() - 2;offs > 2*2;offs -= 2)
		{
			int color;
			int sx,sy;
			u8 fx,fy;

			if(m_inv_spr)
			{
				sx = spriteram_2[offs + 1];
				sy = 240 - (spriteram_2[offs]);
			}
			else
			{
				sx = 272 - spriteram_2[offs + 1];
				sy = spriteram_2[offs] - 31;
			}

			fx = (spriteram[offs] & 1) ^ m_inv_spr;
			fy = (spriteram[offs] & 2) ^ ((m_inv_spr) << 1);

			color = ( spriteram[offs + 1] & 0x1f ) | (m_colortablebank << 5) | (m_palettebank << 6 );

			m_gfxdecode->gfx(1)->transmask(bitmap,spriteclip,
					( spriteram[offs] >> 2 ) | (m_spritebank << 6),
					color,
					fx,fy,
					sx,sy,
					m_palette->transpen_mask(*m_gfxdecode->gfx(1), color, 0));

			/* also plot the sprite with wraparound (tunnel in Crush Roller) */
			m_gfxdecode->gfx(1)->transmask(bitmap,spriteclip,
					( spriteram[offs] >> 2 ) | (m_spritebank << 6),
					color,
					fx,fy,
					sx - 256,sy,
					m_palette->transpen_mask(*m_gfxdecode->gfx(1), color, 0));
		}
		/* In the Pac Man based games (NOT Pengo) the first two sprites must be offset */
		/* one pixel to the left to get a more correct placement */
		for (offs = 2*2;offs >= 0;offs -= 2)
		{
			int color;
			int sx,sy;
			u8 fx,fy;

			if(m_inv_spr)
			{
				sx = spriteram_2[offs + 1];
				sy = 240 - (spriteram_2[offs]);
			}
			else
			{
				sx = 272 - spriteram_2[offs + 1];
				sy = spriteram_2[offs] - 31;
			}
			color = ( spriteram[offs + 1] & 0x1f ) | (m_colortablebank << 5) | (m_palettebank << 6 );

			fx = (spriteram[offs] & 1) ^ m_inv_spr;
			fy = (spriteram[offs] & 2) ^ ((m_inv_spr) << 1);

			m_gfxdecode->gfx(1)->transmask(bitmap,spriteclip,
					( spriteram[offs] >> 2 ) | (m_spritebank << 6),
					color,
					fx,fy,
					sx,sy,
					m_palette->transpen_mask(*m_gfxdecode->gfx(1), color, 0));

			/* also plot the sprite with wraparound (tunnel in Crush Roller) */
			m_gfxdecode->gfx(1)->transmask(bitmap,spriteclip,
					( spriteram[offs] >> 2 ) | (m_spritebank << 6),
					color,
					fx,fy,
					sx - 256,sy,
					m_palette->transpen_mask(*m_gfxdecode->gfx(1), color, 0));
		}
	}

	if (m_bgpriority != 0)
		m_bg_tilemap->draw(screen, bitmap, cliprect, 0,0);
	return 0;
}


void pacman_state::multipac_gfxbank_w(u8 data)
{
	m_charbank = data;
	m_spritebank = data;
}

/* multipac passes bankselect info for the 4a and 7f roms on separate bytes. MAME can only use one of them */
void pacman_state::multipac_palbank_w(offs_t offset, u8 data)
{
	if (offset) m_colortablebank = data;
}


/* =============================================
    96in1 / Mad Pac by Robbbert, July 2007
   ============================================= */


void pacman_state::m96in1b_gfxbank_w ( u8 gfxbank )
{
	u8 banks[] = { 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 7, 4, 2, 3, 5, 6, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0 };
	m_charbank = gfxbank;
	m_spritebank = gfxbank;
	m_colortablebank = banks[gfxbank];
}

void pacman_state::madpac_gfxbank_w ( u8 gfxbank )
{
	m_charbank = gfxbank;
	m_spritebank = gfxbank;

	if (gfxbank > 15)
		m_colortablebank = gfxbank - 15;
	else
		m_colortablebank = 0;
}
