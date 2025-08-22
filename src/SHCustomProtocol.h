#ifndef __SHCUSTOMPROTOCOL_H__
#define __SHCUSTOMPROTOCOL_H__

#include<Arduino.h>
#include <lvgl.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>

static lv_obj_t * ui_MENU;
static lv_obj_t * ui_TOUCH;
static lv_obj_t * ui_JIAOZHUN;
static lv_obj_t * ui_Label2;
static lv_obj_t * ui_Label;
static lv_obj_t * ui_Label3;
static lv_obj_t * ui_Labe2;
#define LCD_BL 46

static const uint16_t screenWidth  = 480;
static const uint16_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[ screenWidth * screenHeight / 5 ];

class LGFX : public lgfx::LGFX_Device
{
    lgfx::Panel_ILI9488 _panel_instance;
    lgfx::Bus_Parallel16 _bus_instance;
  public:
    LGFX(void)
    {
      {
        auto cfg = _bus_instance.config();
        cfg.port = 0;
        cfg.freq_write = 80000000;
        cfg.pin_wr = 18;
        cfg.pin_rd = 48;
        cfg.pin_rs = 45;

        cfg.pin_d0 = 47;
        cfg.pin_d1 = 21;
        cfg.pin_d2 = 14;
        cfg.pin_d3 = 13;
        cfg.pin_d4 = 12;
        cfg.pin_d5 = 11;
        cfg.pin_d6 = 10;
        cfg.pin_d7 = 9;
        cfg.pin_d8 = 3;
        cfg.pin_d9 = 8;
        cfg.pin_d10 = 16;
        cfg.pin_d11 = 15;
        cfg.pin_d12 = 7;
        cfg.pin_d13 = 6;
        cfg.pin_d14 = 5;
        cfg.pin_d15 = 4;
        _bus_instance.config(cfg);
        _panel_instance.setBus(&_bus_instance);
      }

      {
        auto cfg = _panel_instance.config();

        cfg.pin_cs = -1;
        cfg.pin_rst = -1;
        cfg.pin_busy = -1;
        cfg.memory_width = 320;
        cfg.memory_height = 480;
        cfg.panel_width = 320;
        cfg.panel_height = 480;
        cfg.offset_x = 0;
        cfg.offset_y = 0;
        cfg.offset_rotation = 2;
        cfg.dummy_read_pixel = 8;
        cfg.dummy_read_bits = 1;
        cfg.readable = true;
        cfg.invert = false;
        cfg.rgb_order = false;
        cfg.dlen_16bit = true;
        cfg.bus_shared = true;
        _panel_instance.config(cfg);
      }
      setPanel(&_panel_instance);
    }
};

class SHCustomProtocol {
private:
	LGFX tft;

public:
	static void display_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p ) {
		SHCustomProtocol *self = static_cast<SHCustomProtocol *>(disp->user_data);

		uint32_t w = ( area->x2 - area->x1 + 1 );
		uint32_t h = ( area->y2 - area->y1 + 1 );

		self->tft.startWrite();
		self->tft.setAddrWindow( area->x1, area->y1, w, h );
		self->tft.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
		self->tft.endWrite();

		lv_disp_flush_ready( disp );
	}

	void read() {
		String newStringData = FlowSerialReadStringUntil('\n');
	}

	void setup() {
		tft.begin();
		tft.setRotation(1);
		tft.fillScreen(TFT_BLACK);
		delay(500);
		pinMode(LCD_BL, OUTPUT);
		digitalWrite(LCD_BL, HIGH);

		lv_init();
		lv_disp_draw_buf_init( &draw_buf, buf, NULL, screenWidth * screenHeight / 5 );

		//Initialize the display
		static lv_disp_drv_t disp_drv;
		lv_disp_drv_init( &disp_drv );
		disp_drv.hor_res = screenWidth;
		disp_drv.ver_res = screenHeight;
		disp_drv.flush_cb = display_flush;
		disp_drv.user_data = this;   //Pass pointer to current instance
		disp_drv.draw_buf = &draw_buf;
		lv_disp_drv_register( &disp_drv );

		tft.print("Ready");
	}

	void loop() {
		delay(50);
	}

	void idle() { }
};

#endif