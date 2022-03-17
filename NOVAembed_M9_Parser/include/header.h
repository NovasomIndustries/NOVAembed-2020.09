#define dts_header "\n\
\/dts-v1\/;\n\
"
#define dts_footer "\n\
/ {\n\
        model = \"NOVAsomIndustries M9\";\n\
        compatible = \"novasomindustries,m9\", \"rockchip,rk3399\";\n\
};\n\
\n\
&mach {\n\
        hwrev = <0>;\n\
        model = \"M9\";\n\
};\n\
\n\
"

#define dtsi_header "\n\
#include \"dt-bindings/pwm/pwm.h\"\n\
#include \"rk3399.dtsi\"\n\
#include \"rk3399-opp.dtsi\"\n\
#include \"rk3399-linux.dtsi\"\n\
#include <dt-bindings/input/input.h>\n\
\n\
/ {\n\
	model = \"NOVAsomIndustries boards based on Rockchip RK3399\";\n\
	compatible = \"novasomindustries,m9\",\n\
		   \"rockchip,rk3399\";\n\
\n\
	chosen {\n\
		bootargs = \"earlycon=uart8250,mmio32,0xff1a0000 swiotlb=1 console=ttyFIQ0 rootwait coherent_pool=1m\";\n\
	};\n\
\n\
	cpuinfo {\n\
		compatible = \"rockchip,cpuinfo\";\n\
		nvmem-cells = <&cpu_id>;\n\
		nvmem-cell-names = \"id\";\n\
	};\n\
\n\
	mach: board {\n\
		compatible = \"novasomindustries,m9\";\n\
		machine = \"M9\";\n\
		hwrev = <255>;\n\
		model = \"NOVAsomIndustries M9\";\n\
	};\n\
\n\
	aliases {\n\
		spi1 = &spi1;\n\
	};\n\
\n\
	fiq_debugger: fiq-debugger {\n\
		compatible = \"rockchip,fiq-debugger\";\n\
		rockchip,serial-id = <2>;\n\
		rockchip,signal-irq = <182>;\n\
		rockchip,wake-irq = <0>;\n\
		rockchip,irq-mode-enable = <1>; /* If enable uart uses irq instead of fiq */\n\
		rockchip,baudrate = <115200>;\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&uart2c_xfer>;\n\
	};\n\
\n\
	xin32k: xin32k {\n\
		compatible = \"fixed-clock\";\n\
		clock-frequency = <32768>;\n\
		clock-output-names = \"xin32k\";\n\
		#clock-cells = <0>;\n\
	};\n\
\n\
	clkin_gmac: external-gmac-clock {\n\
		compatible = \"fixed-clock\";\n\
		clock-frequency = <125000000>;\n\
		clock-output-names = \"clkin_gmac\";\n\
		#clock-cells = <0>;\n\
	};\n\
\n\
	ext_cam_clk: external-camera-clock {\n\
		compatible = \"fixed-clock\";\n\
		clock-frequency = <27000000>;\n\
		clock-output-names = \"CLK_CAMERA_27MHZ\";\n\
		#clock-cells = <0>;\n\
	};\n\
\n\
	vcc3v3_sys: vcc3v3-sys {\n\
		compatible = \"regulator-fixed\";\n\
		regulator-name = \"vcc3v3_sys\";\n\
		regulator-always-on;\n\
		regulator-boot-on;\n\
		regulator-min-microvolt = <3300000>;\n\
		regulator-max-microvolt = <3300000>;\n\
	};\n\
\n\
	vcc5v0_host: vcc5v0-host-regulator {\n\
		compatible = \"regulator-fixed\";\n\
		regulator-name = \"vcc5v0_host\";\n\
		regulator-always-on;\n\
		regulator-boot-on;\n\
		regulator-min-microvolt = <5000000>;\n\
		regulator-max-microvolt = <5000000>;\n\
	};\n\
\n\
	vcc5v0_sys: vcc5v0-sys {\n\
		compatible = \"regulator-fixed\";\n\
		regulator-name = \"vcc5v0_sys\";\n\
		regulator-always-on;\n\
		regulator-boot-on;\n\
		regulator-min-microvolt = <5000000>;\n\
		regulator-max-microvolt = <5000000>;\n\
	};\n\
\n\
	vccadc_ref: vccadc-ref {\n\
		compatible = \"regulator-fixed\";\n\
		regulator-name = \"vcc1v8_sys\";\n\
		regulator-always-on;\n\
		regulator-boot-on;\n\
		regulator-min-microvolt = <1800000>;\n\
		regulator-max-microvolt = <1800000>;\n\
	};\n\
\n\
	vcc_sd: vcc-sd {\n\
		compatible = \"regulator-fixed\";\n\
		enable-active-high;\n\
		gpio = <&gpio0 1 GPIO_ACTIVE_HIGH>;\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&vcc_sd_h>;\n\
		regulator-name = \"vcc_sd\";\n\
		regulator-min-microvolt = <3000000>;\n\
		regulator-max-microvolt = <3000000>;\n\
	};\n\
\n\
	vcc_phy: vcc-phy-regulator {\n\
		compatible = \"regulator-fixed\";\n\
		regulator-name = \"vcc_phy\";\n\
		regulator-always-on;\n\
		regulator-boot-on;\n\
	};\n\
\n\
	vcc_lcd: vcc-lcd {\n\
		compatible = \"regulator-fixed\";\n\
		regulator-name = \"vcc_lcd\";\n\
		gpio = <&gpio4 30 GPIO_ACTIVE_HIGH>;\n\
		startup-delay-us = <20000>;\n\
		enable-active-high;\n\
		regulator-min-microvolt = <3300000>;\n\
		regulator-max-microvolt = <3300000>;\n\
		regulator-boot-on;\n\
		vin-supply = <&vcc5v0_sys>;\n\
	};\n\
\n\
	vdd_log: vdd-log {\n\
		compatible = \"pwm-regulator\";\n\
		pwms = <&pwm2 0 25000 1>;\n\
		regulator-name = \"vdd_log\";\n\
		regulator-min-microvolt = <800000>;\n\
		regulator-max-microvolt = <1400000>;\n\
		regulator-always-on;\n\
		regulator-boot-on;\n\
\n\
		/* for rockchip boot on */\n\
		rockchip,pwm_id = <2>;\n\
		rockchip,pwm_voltage = <900000>;\n\
	};\n\
\n\
	rt5651_card: rt5651-sound {\n\
		status = \"okay\";\n\
		compatible = \"simple-audio-card\";\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&hp_det>;\n\
\n\
		simple-audio-card,name = \"realtek,rt5651-codec\";\n\
		simple-audio-card,format = \"i2s\";\n\
		simple-audio-card,mclk-fs = <256>;\n\
		simple-audio-card,hp-det-gpio = <&gpio4 28 GPIO_ACTIVE_HIGH>;\n\
\n\
		simple-audio-card,widgets =\n\
			\"Microphone\", \"Mic Jack\",\n\
			\"Headphone\", \"Headphone Jack\";\n\
		simple-audio-card,routing =\n\
			\"Mic Jack\", \"MICBIAS1\",\n\
			\"IN1P\", \"Mic Jack\",\n\
			\"Headphone Jack\", \"HPOL\",\n\
			\"Headphone Jack\", \"HPOR\";\n\
\n\
		simple-audio-card,cpu {\n\
			sound-dai = <&i2s0>;\n\
		};\n\
		simple-audio-card,codec {\n\
			sound-dai = <&rt5651>;\n\
		};\n\
	};\n\
\n\
	dw_hdmi_audio: dw-hdmi-audio {\n\
		status = \"disabled\";\n\
		compatible = \"rockchip,dw-hdmi-audio\";\n\
		#sound-dai-cells = <0>;\n\
	};\n\
\n\
	hdmi_sound: hdmi-sound {\n\
		status = \"okay\";\n\
		compatible = \"simple-audio-card\";\n\
		simple-audio-card,format = \"i2s\";\n\
		simple-audio-card,mclk-fs = <256>;\n\
		simple-audio-card,name = \"rockchip,hdmi\";\n\
\n\
		simple-audio-card,cpu {\n\
			sound-dai = <&i2s2>;\n\
		};\n\
		simple-audio-card,codec {\n\
			sound-dai = <&hdmi>;\n\
		};\n\
	};\n\
\n\
    #ifdef HAS_SPDIF\n\
	spdif-sound {\n\
		status = \"okay\";\n\
		compatible = \"simple-audio-card\";\n\
		simple-audio-card,name = \"ROCKCHIP,SPDIF\";\n\
		simple-audio-card,cpu {\n\
			sound-dai = <&spdif>;\n\
		};\n\
		simple-audio-card,codec {\n\
			sound-dai = <&spdif_out>;\n\
		};\n\
	};\n\
\n\
	spdif_out: spdif-out {\n\
		status = \"okay\";\n\
		compatible = \"linux,spdif-dit\";\n\
		#sound-dai-cells = <0>;\n\
	};\n\
	#endif \n\
	pwm_bl: backlight {\n\
		status = \"disabled\";\n\
		compatible = \"pwm-backlight\";\n\
		pwms = <&pwm0 0 25000 0>;\n\
		brightness-levels = <\n\
			  0   1   2   3   4   5   6   7\n\
			  8   9  10  11  12  13  14  15\n\
			 16  17  18  19  20  21  22  23\n\
			 24  25  26  27  28  29  30  31\n\
			 32  33  34  35  36  37  38  39\n\
			 40  41  42  43  44  45  46  47\n\
			 48  49  50  51  52  53  54  55\n\
			 56  57  58  59  60  61  62  63\n\
			 64  65  66  67  68  69  70  71\n\
			 72  73  74  75  76  77  78  79\n\
			 80  81  82  83  84  85  86  87\n\
			 88  89  90  91  92  93  94  95\n\
			 96  97  98  99 100 101 102 103\n\
			104 105 106 107 108 109 110 111\n\
			112 113 114 115 116 117 118 119\n\
			120 121 122 123 124 125 126 127\n\
			128 129 130 131 132 133 134 135\n\
			136 137 138 139 140 141 142 143\n\
			144 145 146 147 148 149 150 151\n\
			152 153 154 155 156 157 158 159\n\
			160 161 162 163 164 165 166 167\n\
			168 169 170 171 172 173 174 175\n\
			176 177 178 179 180 181 182 183\n\
			184 185 186 187 188 189 190 191\n\
			192 193 194 195 196 197 198 199\n\
			200 201 202 203 204 205 206 207\n\
			208 209 210 211 212 213 214 215\n\
			216 217 218 219 220 221 222 223\n\
			224 225 226 227 228 229 230 231\n\
			232 233 234 235 236 237 238 239\n\
			240 241 242 243 244 245 246 247\n\
			248 249 250 251 252 253 254 255>;\n\
		default-brightness-level = <200>;\n\
	};\n\
\n\
    #ifdef HAS_EDP\n\
	panel: edp-panel {\n\
		compatible = \"lcds\", \"simple-panel\";\n\
		status = \"okay\";\n\
\n\
		backlight = <&pwm_bl>;\n\
		power-supply = <&vcc_lcd>;\n\
		prepare-delay-ms = <20>;\n\
		enable-delay-ms = <20>;\n\
\n\
		ports {\n\
			edp_panel: endpoint {\n\
				remote-endpoint = <&edp_out>;\n\
			};\n\
		};\n\
	};\n\
	#endif \n\
\n\
	gpio-keys {\n\
		compatible = \"gpio-keys\";\n\
		#address-cells = <1>;\n\
		#size-cells = <0>;\n\
		autorepeat;\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&power_key>;\n\
		button@0 {\n\
			gpios = <&gpio0 5 GPIO_ACTIVE_LOW>;\n\
			linux,code = <KEY_POWER>;\n\
			label = \"GPIO Key Power\";\n\
			linux,input-type = <1>;\n\
			gpio-key,wakeup = <1>;\n\
			debounce-interval = <100>;\n\
		};\n\
	};\n\
\n\
	adc-keys {\n\
		compatible = \"adc-keys\";\n\
		io-channels = <&saradc 1>;\n\
		io-channel-names = \"buttons\";\n\
		poll-interval = <100>;\n\
		keyup-threshold-microvolt = <1800000>;\n\
\n\
		button-up {\n\
			label = \"Volume Up\";\n\
			linux,code = <KEY_VOLUMEUP>;\n\
			press-threshold-microvolt = <100000>;\n\
		};\n\
\n\
		button-down {\n\
			label = \"Volume Down\";\n\
			linux,code = <KEY_VOLUMEDOWN>;\n\
			press-threshold-microvolt = <300000>;\n\
		};\n\
	};\n\
\n\
	leds: gpio-leds {\n\
		compatible = \"gpio-leds\";\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 =<&leds_gpio>;\n\
\n\
		led@1 {\n\
			gpios = <&gpio0 13 GPIO_ACTIVE_HIGH>;\n\
			label = \"status_led\";\n\
			linux,default-trigger = \"heartbeat\";\n\
			linux,default-trigger-delay-ms = <0>;\n\
		};\n\
	};\n\
\n\
	sdio_pwrseq: sdio-pwrseq {\n\
		compatible = \"mmc-pwrseq-simple\";\n\
		clocks = <&rk808 1>;\n\
		clock-names = \"ext_clock\";\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&wifi_enable_h>;\n\
\n\
		reset-gpios = <&gpio0 10 GPIO_ACTIVE_LOW>;/* GPIO0_B2 */\n\
	};\n\
\n\
	rk_wlan: wireless-wlan {\n\
		compatible = \"wlan-platdata\";\n\
		rockchip,grf = <&grf>;\n\
		wifi_chip_type = \"ap6398\";\n\
		sdio_vref = <1800>;\n\
		WIFI,host_wake_irq = <&gpio0 3 GPIO_ACTIVE_HIGH>;/* GPIO0_a3 */\n\
        #ifdef WIFI_ENABLED\n\
        status = \"okay\";\n\
        #else\n\
        status = \"disabled\";\n\
        #endif\n\
	};\n\
\n\
	rk_bluetooth: wireless-bluetooth {\n\
		compatible = \"bluetooth-platdata\";\n\
		clocks = <&rk808 1>;\n\
		clock-names = \"ext_clock\";\n\
		/* wifi-bt-power-toggle; */ \n\
		uart_rts_gpios = <&gpio2 19 GPIO_ACTIVE_LOW>; /* GPIO2_C3 */\n\
		pinctrl-names = \"default\", \"rts_gpio\";\n\
		pinctrl-0 = <&uart0_rts>;\n\
		pinctrl-1 = <&uart0_gpios>;\n\
		/* BT,power_gpio  = <&gpio3 19 GPIO_ACTIVE_HIGH>;*//* GPIOx_xx */\n\
		BT,reset_gpio    = <&gpio0 9 GPIO_ACTIVE_HIGH>; /* GPIO0_B1 */\n\
		BT,wake_gpio     = <&gpio2 26 GPIO_ACTIVE_HIGH>; /* GPIO2_D2 */\n\
		BT,wake_host_irq = <&gpio0 4 GPIO_ACTIVE_HIGH>; /* GPIO0_A4 */\n\
        #ifdef BT_ENABLED\n\
        status = \"okay\";\n\
        #else\n\
        status = \"disabled\";\n\
        #endif\n\
	};\n\
};\n\
\n\
&cif_isp0 {\n\
	status = \"disabled\";\n\
};\n\
\n\
&cif_isp1 {\n\
	status = \"disabled\";\n\
};\n\
\n\
#if defined(HAS_CAM0) || defined(HAS_CAM1) \n\
#ifdef HAS_CAM0\n\
&i2c1 {\n\
	ov4689p0: ov4689@36 {\n\
		compatible = \"ovti,ov4689\";\n\
		status = \"okay\";\n\
		reg = <0x36>;\n\
		clocks = <&cru SCLK_CIF_OUT>;\n\
		clock-names = \"xvclk\";\n\
\n\
		reset-gpios = <&gpio2 27 GPIO_ACTIVE_HIGH>;\n\
		pwdn-gpios = <&gpio2 28 GPIO_ACTIVE_HIGH>;\n\
		pinctrl-names = \"rockchip,camera_default\", \"rockchip,camera_sleep\";\n\
		pinctrl-0 = <&cam0_default_pins &cif_clkout_a>;\n\
		pinctrl-1 = <&cam0_default_pins>;\n\
\n\
		port {\n\
			ucam_out0a: endpoint {\n\
				remote-endpoint = <&mipi_in_ucam0a>;\n\
				data-lanes = <1 2>;\n\
			};\n\
		};\n\
	};\n\
\n\
	ov13850p0: ov13850@10 {\n\
		compatible = \"ovti,ov13850\";\n\
		status = \"okay\";\n\
		reg = <0x10>;\n\
		clocks = <&cru SCLK_CIF_OUT>;\n\
		clock-names = \"xvclk\";\n\
\n\
		reset-gpios = <&gpio2 27 GPIO_ACTIVE_HIGH>;\n\
		pwdn-gpios = <&gpio2 28 GPIO_ACTIVE_HIGH>;\n\
		pinctrl-names = \"rockchip,camera_default\", \"rockchip,camera_sleep\";\n\
		pinctrl-0 = <&cam0_default_pins &cif_clkout_a>;\n\
		pinctrl-1 = <&cam0_default_pins>;\n\
\n\
		port {\n\
			ucam_out0b: endpoint {\n\
				remote-endpoint = <&mipi_in_ucam0b>;\n\
				data-lanes = <1 2>;\n\
			};\n\
		};\n\
	};\n\
\n\
	tc358749x: tc358749x@0f {\n\
		compatible = \"toshiba,tc358749\";\n\
		reg = <0x0f>;\n\
		clocks = <&ext_cam_clk>;\n\
		clock-names = \"refclk\";\n\
		power33-gpios = <&gpio1 0 GPIO_ACTIVE_HIGH>;\n\
		stanby-gpios = <&gpio2 6 GPIO_ACTIVE_HIGH>;\n\
		reset-gpios = <&gpio2 5 GPIO_ACTIVE_LOW>;\n\
		int-gpios = <&gpio0 2 GPIO_ACTIVE_HIGH>;\n\
		interrupt-parent = <&gpio0>;\n\
		interrupts = <2 IRQ_TYPE_LEVEL_LOW>;\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&hdmiin_gpios>;\n\
		status = \"disabled\";\n\
\n\
		port {\n\
			hdmiin_out0: endpoint {\n\
				remote-endpoint = <&mipi_in_ucam0c>;\n\
				data-lanes = <1 2 3 4>;\n\
				clock-noncontinuous;\n\
				link-frequencies = /bits/ 64 <297000000>;\n\
			};\n\
		};\n\
	};\n\
};\n\
\n\
&rkisp1_0 {\n\
	status = \"okay\";\n\
	resets = <&cru SRST_H_ISP0>, <&cru SRST_ISP0>;\n\
	reset-names = \"h_isp0\", \"isp0\";\n\
\n\
	port {\n\
		#address-cells = <1>;\n\
		#size-cells = <0>;\n\
\n\
		isp0_mipi_in: endpoint@0 {\n\
			reg = <0>;\n\
			remote-endpoint = <&dphy_rx0_out>;\n\
		};\n\
	};\n\
};\n\
\n\
&isp0_mmu {\n\
	status = \"okay\";\n\
};\n\
\n\
&mipi_dphy_rx0 {\n\
	status = \"okay\";\n\
\n\
	ports {\n\
		#address-cells = <1>;\n\
		#size-cells = <0>;\n\
\n\
		port@0 {\n\
			reg = <0>;\n\
			#address-cells = <1>;\n\
			#size-cells = <0>;\n\
\n\
			mipi_in_ucam0a: endpoint@0 {\n\
				reg = <0>;\n\
				remote-endpoint = <&ucam_out0a>;\n\
				data-lanes = <1 2>;\n\
			};\n\
\n\
			mipi_in_ucam0b: endpoint@1 {\n\
				reg = <1>;\n\
				remote-endpoint = <&ucam_out0b>;\n\
				data-lanes = <1 2>;\n\
			};\n\
\n\
			mipi_in_ucam0c: endpoint@2 {\n\
				reg = <2>;\n\
				remote-endpoint = <&hdmiin_out0>;\n\
				data-lanes = <1 2 3 4>;\n\
				status = \"disabled\";\n\
			};\n\
		};\n\
\n\
		port@1 {\n\
			reg = <1>;\n\
			#address-cells = <1>;\n\
			#size-cells = <0>;\n\
\n\
			dphy_rx0_out: endpoint@0 {\n\
				reg = <0>;\n\
				remote-endpoint = <&isp0_mipi_in>;\n\
			};\n\
		};\n\
	};\n\
};\n\
#endif \n\
\n\
#ifdef HAS_CAM1\n\
&i2c2 {\n\
	ov4689p1: ov4689@36 {\n\
		compatible = \"ovti,ov4689\";\n\
		status = \"okay\";\n\
		reg = <0x36>;\n\
		clocks = <&cru SCLK_CIF_OUT>;\n\
		clock-names = \"xvclk\";\n\
\n\
		reset-gpios = <&gpio0 8 GPIO_ACTIVE_HIGH>;\n\
		pwdn-gpios = <&gpio0 12 GPIO_ACTIVE_HIGH>;\n\
		pinctrl-names = \"rockchip,camera_default\", \"rockchip,camera_sleep\";\n\
		pinctrl-0 = <&cam1_default_pins &cif_clkout_a>;\n\
		pinctrl-1 = <&cam1_default_pins>;\n\
\n\
		port {\n\
			ucam_out1a: endpoint {\n\
				remote-endpoint = <&mipi_in_ucam1a>;\n\
				data-lanes = <1 2>;\n\
			};\n\
		};\n\
	};\n\
\n\
	ov13850p1: ov13850@10 {\n\
		compatible = \"ovti,ov13850\";\n\
		status = \"okay\";\n\
		reg = <0x10>;\n\
		clocks = <&cru SCLK_CIF_OUT>;\n\
		clock-names = \"xvclk\";\n\
\n\
		reset-gpios = <&gpio0 8 GPIO_ACTIVE_HIGH>;\n\
		pwdn-gpios = <&gpio0 12 GPIO_ACTIVE_HIGH>;\n\
		pinctrl-names = \"rockchip,camera_default\", \"rockchip,camera_sleep\";\n\
		pinctrl-0 = <&cam1_default_pins &cif_clkout_a>;\n\
		pinctrl-1 = <&cam1_default_pins>;\n\
\n\
		port {\n\
			ucam_out1b: endpoint {\n\
				remote-endpoint = <&mipi_in_ucam1b>;\n\
				data-lanes = <1 2>;\n\
			};\n\
		};\n\
	};\n\
};\n\
&rkisp1_1 {\n\
	status = \"okay\";\n\
	resets = <&cru SRST_H_ISP1>, <&cru SRST_ISP1>;\n\
	reset-names = \"h_isp1\", \"isp1\";\n\
\n\
	port {\n\
		#address-cells = <1>;\n\
		#size-cells = <0>;\n\
\n\
		isp1_mipi_in: endpoint@0 {\n\
			reg = <0>;\n\
			remote-endpoint = <&dphy_tx1rx1_out>;\n\
		};\n\
	};\n\
};\n\
\n\
&isp1_mmu {\n\
	status = \"okay\";\n\
};\n\
\n\
#ifdef HAS_DSI\n\
&mipi_dphy_tx1rx1 {\n\
	status = \"okay\";\n\
\n\
	ports {\n\
		#address-cells = <1>;\n\
		#size-cells = <0>;\n\
\n\
		port@0 {\n\
			reg = <0>;\n\
			#address-cells = <1>;\n\
			#size-cells = <0>;\n\
\n\
			mipi_in_ucam1a: endpoint@0 {\n\
				reg = <0>;\n\
				remote-endpoint = <&ucam_out1a>;\n\
				data-lanes = <1 2>;\n\
			};\n\
\n\
			mipi_in_ucam1b: endpoint@1 {\n\
				reg = <1>;\n\
				remote-endpoint = <&ucam_out1b>;\n\
				data-lanes = <1 2>;\n\
			};\n\
		};\n\
\n\
		port@1 {\n\
			reg = <1>;\n\
			#address-cells = <1>;\n\
			#size-cells = <0>;\n\
\n\
			dphy_tx1rx1_out: endpoint@0 {\n\
				reg = <0>;\n\
				remote-endpoint = <&isp1_mipi_in>;\n\
			};\n\
		};\n\
	};\n\
};\n\
#endif\n\
#endif\n\
#endif\n\
\n\
&cpu_l0 {\n\
	cpu-supply = <&vdd_cpu_l>;\n\
};\n\
\n\
&cpu_l1 {\n\
	cpu-supply = <&vdd_cpu_l>;\n\
};\n\
\n\
&cpu_l2 {\n\
	cpu-supply = <&vdd_cpu_l>;\n\
};\n\
\n\
&cpu_l3 {\n\
	cpu-supply = <&vdd_cpu_l>;\n\
};\n\
\n\
&cpu_b0 {\n\
	cpu-supply = <&vdd_cpu_b>;\n\
};\n\
\n\
&cpu_b1 {\n\
	cpu-supply = <&vdd_cpu_b>;\n\
};\n\
\n\
&dfi {\n\
	status = \"okay\";\n\
};\n\
\n\
&dmc {\n\
	status = \"okay\";\n\
	center-supply = <&vdd_center>;\n\
	upthreshold = <40>;\n\
	downdifferential = <20>;\n\
	system-status-freq = <\n\
		/*system status         freq(KHz)*/\n\
		SYS_STATUS_NORMAL       800000\n\
		SYS_STATUS_REBOOT       400000\n\
		SYS_STATUS_SUSPEND      400000\n\
		SYS_STATUS_VIDEO_1080P  400000\n\
		SYS_STATUS_VIDEO_4K     800000\n\
		SYS_STATUS_VIDEO_4K_10B 800000\n\
		SYS_STATUS_PERFORMANCE  800000\n\
		SYS_STATUS_BOOST        400000\n\
		SYS_STATUS_DUALVIEW     800000\n\
		SYS_STATUS_ISP          800000\n\
	>;\n\
	vop-bw-dmc-freq = <\n\
	/* min_bw(MB/s) max_bw(MB/s) freq(KHz) */\n\
		0       762      200000\n\
		763     1893     400000\n\
		1894    3012     600000\n\
		3013    99999    800000\n\
	>;\n\
	auto-min-freq = <400000>;\n\
};\n\
\n\
&gpu {\n\
	status = \"okay\";\n\
	mali-supply = <&vdd_gpu>;\n\
};\n\
\n\
&gmac {\n\
	phy-supply = <&vcc_phy>;\n\
	phy-mode = \"rgmii\";\n\
	clock_in_out = \"input\";\n\
	snps,reset-gpio = <&gpio3 15 GPIO_ACTIVE_LOW>;\n\
	snps,reset-active-low;\n\
	snps,reset-delays-us = <0 10000 50000>;\n\
	assigned-clocks = <&cru SCLK_RMII_SRC>;\n\
	assigned-clock-parents = <&clkin_gmac>;\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&rgmii_pins>;\n\
	tx_delay = <0x28>;\n\
	rx_delay = <0x11>;\n\
	status = \"okay\";\n\
};\n\
\n\
&uart0 {\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&uart0_xfer &uart0_cts>;\n\
	status = \"okay\";\n\
};\n\
\n\
#ifdef HAS_UART2 \n\
&uart2 {\n\
	status = \"okay\";\n\
};\n\
#endif \n\
\n\
#ifdef HAS_UART4 \n\
&uart4 {\n\
	status = \"okay\";\n\
};\n\
#endif \n\
\n\
&vopb {\n\
	status = \"okay\";\n\
};\n\
\n\
&vopb_mmu {\n\
	status = \"okay\";\n\
};\n\
\n\
&vopl {\n\
	status = \"okay\";\n\
};\n\
\n\
&vopl_mmu {\n\
	status = \"okay\";\n\
};\n\
\n\
&vpu {\n\
	status = \"okay\";\n\
	/* 0 means ion, 1 means drm */\n\
	/* allocator = <0>; */\n\
};\n\
\n\
&rkvdec {\n\
	status = \"okay\";\n\
	/* 0 means ion, 1 means drm */\n\
	/* allocator = <0> */\n\
};\n\
\n\
&rga {\n\
	status = \"disabled\";\n\
};\n\
\n\
&display_subsystem {\n\
	status = \"okay\";\n\
};\n\
\n\
#ifdef HAS_EDP\n\
&edp {\n\
	status = \"okay\";\n\
	force-hpd;\n\
	/delete-property/ pinctrl-0;\n\
\n\
	ports {\n\
		port@1 {\n\
			reg = <1>;\n\
\n\
			edp_out: endpoint {\n\
				remote-endpoint = <&edp_panel>;\n\
			};\n\
		};\n\
	};\n\
};\n\
\n\
&edp_in_vopl {\n\
	status = \"disabled\";\n\
};\n\
\n\
&route_edp {\n\
	status = \"okay\";\n\
	logo,mode = \"center\";\n\
};\n\
\n\
#endif \n\
&cdn_dp {\n\
	status = \"okay\";\n\
	extcon = <&fusb0>;\n\
	phys = <&tcphy0_dp>;\n\
};\n\
\n\
&hdmi {\n\
	/* remove the hdmi_i2c_xfer */\n\
	pinctrl-0 = <&hdmi_cec>;\n\
	#address-cells = <1>;\n\
	#size-cells = <0>;\n\
	#sound-dai-cells = <0>;\n\
	status = \"okay\";\n\
	ddc-i2c-bus = <&i2c7>;\n\
	rockchip,defaultmode = <16>;/* CEA 1920x1080@60Hz */\n\
};\n\
\n\
&route_hdmi {\n\
	status = \"okay\";\n\
	logo,mode = \"center\";\n\
};\n\
\n\
&i2c0 {\n\
	status = \"okay\";\n\
	i2c-scl-rising-time-ns = <160>;\n\
	i2c-scl-falling-time-ns = <30>;\n\
	clock-frequency = <400000>;\n\
\n\
	vdd_cpu_b: syr827@40 {\n\
		compatible = \"silergy,syr827\";\n\
		reg = <0x40>;\n\
		vin-supply = <&vcc3v3_sys>;\n\
		regulator-compatible = \"fan53555-reg\";\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&vsel1_gpio>;\n\
		vsel-gpios = <&gpio1 17 GPIO_ACTIVE_HIGH>;\n\
		regulator-name = \"vdd_cpu_b\";\n\
		regulator-min-microvolt = <712500>;\n\
		regulator-max-microvolt = <1500000>;\n\
		regulator-ramp-delay = <1000>;\n\
		fcs,suspend-voltage-selector = <1>;\n\
		regulator-always-on;\n\
		regulator-boot-on;\n\
		regulator-initial-state = <3>;\n\
			regulator-state-mem {\n\
			regulator-off-in-suspend;\n\
		};\n\
	};\n\
\n\
	vdd_gpu: syr828@41 {\n\
		compatible = \"silergy,syr828\";\n\
		reg = <0x41>;\n\
		vin-supply = <&vcc3v3_sys>;\n\
		regulator-compatible = \"fan53555-reg\";\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&vsel2_gpio>;\n\
		vsel-gpios = <&gpio1 14 GPIO_ACTIVE_HIGH>;\n\
		regulator-name = \"vdd_gpu\";\n\
		regulator-min-microvolt = <712500>;\n\
		regulator-max-microvolt = <1500000>;\n\
		regulator-ramp-delay = <1000>;\n\
		fcs,suspend-voltage-selector = <1>;\n\
		regulator-always-on;\n\
		regulator-boot-on;\n\
		regulator-initial-state = <3>;\n\
			regulator-state-mem {\n\
			regulator-off-in-suspend;\n\
		};\n\
	};\n\
\n\
	rk808: pmic@1b {\n\
		compatible = \"rockchip,rk808\";\n\
		reg = <0x1b>;\n\
		interrupt-parent = <&gpio1>;\n\
		interrupts = <21 IRQ_TYPE_LEVEL_LOW>;\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&pmic_int_l>;\n\
		rockchip,system-power-controller;\n\
		wakeup-source;\n\
		#clock-cells = <1>;\n\
		clock-output-names = \"rk808-clkout1\", \"rk808-clkout2\";\n\
\n\
		vcc1-supply = <&vcc3v3_sys>;\n\
		vcc2-supply = <&vcc3v3_sys>;\n\
		vcc3-supply = <&vcc3v3_sys>;\n\
		vcc4-supply = <&vcc3v3_sys>;\n\
		vcc6-supply = <&vcc3v3_sys>;\n\
		vcc7-supply = <&vcc3v3_sys>;\n\
		vcc8-supply = <&vcc3v3_sys>;\n\
		vcc9-supply = <&vcc3v3_sys>;\n\
		vcc10-supply = <&vcc3v3_sys>;\n\
		vcc11-supply = <&vcc3v3_sys>;\n\
		vcc12-supply = <&vcc3v3_sys>;\n\
		vddio-supply = <&vcc_3v0>;\n\
\n\
		regulators {\n\
			vdd_center: DCDC_REG1 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-min-microvolt = <750000>;\n\
				regulator-max-microvolt = <1350000>;\n\
				regulator-ramp-delay = <6001>;\n\
				regulator-name = \"vdd_center\";\n\
				regulator-state-mem {\n\
					regulator-off-in-suspend;\n\
				};\n\
			};\n\
\n\
			vdd_cpu_l: DCDC_REG2 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-min-microvolt = <750000>;\n\
				regulator-max-microvolt = <1350000>;\n\
				regulator-ramp-delay = <6001>;\n\
				regulator-name = \"vdd_cpu_l\";\n\
				regulator-state-mem {\n\
					regulator-off-in-suspend;\n\
				};\n\
			};\n\
\n\
			vcc_ddr: DCDC_REG3 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-name = \"vcc_ddr\";\n\
				regulator-state-mem {\n\
					regulator-on-in-suspend;\n\
				};\n\
			};\n\
\n\
			vcc_1v8: DCDC_REG4 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-min-microvolt = <1800000>;\n\
				regulator-max-microvolt = <1800000>;\n\
				regulator-name = \"vcc_1v8\";\n\
				regulator-state-mem {\n\
					regulator-on-in-suspend;\n\
					regulator-suspend-microvolt = <1800000>;\n\
				};\n\
			};\n\
\n\
			vcc1v8_dvp: LDO_REG1 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-min-microvolt = <1800000>;\n\
				regulator-max-microvolt = <1800000>;\n\
				regulator-name = \"vcc1v8_dvp\";\n\
				regulator-state-mem {\n\
					regulator-off-in-suspend;\n\
				};\n\
			};\n\
\n\
			vcc3v0_tp: LDO_REG2 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-min-microvolt = <3000000>;\n\
				regulator-max-microvolt = <3000000>;\n\
				regulator-name = \"vcc3v0_tp\";\n\
				regulator-state-mem {\n\
					regulator-off-in-suspend;\n\
				};\n\
			};\n\
\n\
			vcc1v8_pmu: LDO_REG3 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-min-microvolt = <1800000>;\n\
				regulator-max-microvolt = <1800000>;\n\
				regulator-name = \"vcc1v8_pmu\";\n\
				regulator-state-mem {\n\
					regulator-on-in-suspend;\n\
					regulator-suspend-microvolt = <1800000>;\n\
				};\n\
			};\n\
\n\
			vccio_sd: LDO_REG4 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-min-microvolt = <1800000>;\n\
				regulator-max-microvolt = <3000000>;\n\
				regulator-init-microvolt = <3000000>;\n\
				regulator-name = \"vccio_sd\";\n\
				regulator-state-mem {\n\
					regulator-on-in-suspend;\n\
					regulator-suspend-microvolt = <3000000>;\n\
				};\n\
			};\n\
\n\
			vcca3v0_codec: LDO_REG5 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-min-microvolt = <3000000>;\n\
				regulator-max-microvolt = <3000000>;\n\
				regulator-name = \"vcca3v0_codec\";\n\
				regulator-state-mem {\n\
					regulator-off-in-suspend;\n\
				};\n\
			};\n\
\n\
			vcc_1v5: LDO_REG6 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-min-microvolt = <1500000>;\n\
				regulator-max-microvolt = <1500000>;\n\
				regulator-name = \"vcc_1v5\";\n\
				regulator-state-mem {\n\
					regulator-on-in-suspend;\n\
					regulator-suspend-microvolt = <1500000>;\n\
				};\n\
			};\n\
\n\
			vcca1v8_codec: LDO_REG7 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-min-microvolt = <1800000>;\n\
				regulator-max-microvolt = <1800000>;\n\
				regulator-name = \"vcca1v8_codec\";\n\
				regulator-state-mem {\n\
					regulator-off-in-suspend;\n\
				};\n\
			};\n\
\n\
			vcc_3v0: LDO_REG8 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-min-microvolt = <3000000>;\n\
				regulator-max-microvolt = <3000000>;\n\
				regulator-name = \"vcc_3v0\";\n\
				regulator-state-mem {\n\
					regulator-on-in-suspend;\n\
					regulator-suspend-microvolt = <3000000>;\n\
				};\n\
			};\n\
\n\
			vcc3v3_s3: SWITCH_REG1 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-name = \"vcc3v3_s3\";\n\
				regulator-state-mem {\n\
					regulator-off-in-suspend;\n\
				};\n\
			};\n\
\n\
			vcc3v3_s0: SWITCH_REG2 {\n\
				regulator-always-on;\n\
				regulator-boot-on;\n\
				regulator-name = \"vcc3v3_s0\";\n\
				regulator-state-mem {\n\
					regulator-off-in-suspend;\n\
				};\n\
			};\n\
		};\n\
	};\n\
};\n\
\n\
&i2c1 {\n\
	status = \"okay\";\n\
	i2c-scl-rising-time-ns = <150>;\n\
	i2c-scl-falling-time-ns = <30>;\n\
	clock-frequency = <200000>;\n\
\n\
	rt5651: rt5651@1a {\n\
		#sound-dai-cells = <0>;\n\
		compatible = \"rockchip,rt5651\";\n\
		reg = <0x1a>;\n\
		clocks = <&cru SCLK_I2S_8CH_OUT>;\n\
		clock-names = \"mclk\";\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&i2s_8ch_mclk>;\n\
		status = \"okay\";\n\
	};\n\
};\n\
\n\
&i2c2 {\n\
	status = \"okay\";\n\
};\n\
\n\
&i2c4 {\n\
	status = \"okay\";\n\
	i2c-scl-rising-time-ns = <160>;\n\
	i2c-scl-falling-time-ns = <30>;\n\
	clock-frequency = <400000>;\n\
\n\
	fusb0: fusb30x@22 {\n\
		compatible = \"fairchild,fusb302\";\n\
		reg = <0x22>;\n\
		pinctrl-names = \"default\";\n\
		pinctrl-0 = <&fusb0_int>;\n\
		int-n-gpios = <&gpio1 2 GPIO_ACTIVE_HIGH>;\n\
		vbus-5v-gpios = <&gpio4 26 GPIO_ACTIVE_HIGH>;\n\
		status = \"okay\";\n\
	};\n\
\n\
	gt9xx: goodix_ts@5d {\n\
		compatible = \"goodix,gt9xx\";\n\
		reg = <0x5d>;\n\
		interrupt-parent = <&gpio1>;\n\
		interrupts = <20 IRQ_TYPE_EDGE_FALLING>;\n\
		goodix,irq-gpio = <&gpio1 20 GPIO_ACTIVE_HIGH>;\n\
		goodix,rst-gpio = <&gpio1 13 GPIO_ACTIVE_LOW>;\n\
		status = \"okay\";\n\
	};\n\
\n\
	ft5x06_ts@38 {\n\
		compatible = \"edt,edt-ft5x06\", \"ft5x06\";\n\
		reg = <0x38>;\n\
		interrupt-parent = <&gpio1>;\n\
		interrupts = <20 IRQ_TYPE_EDGE_FALLING>;\n\
		status = \"okay\";\n\
	};\n\
\n\
	/*onewire_ts@2f {*/\n\
		/*compatible = \"onewire\";*/\n\
		/*reg = <0x2f>;*/\n\
		/*interrupt-parent = <&gpio1>;*/\n\
		/*interrupts = <20 IRQ_TYPE_EDGE_FALLING>;*/\n\
	/*};*/\n\
};\n\
\n\
&spdif {\n\
	status = \"okay\";\n\
	pinctrl-0 = <&spdif_bus>;\n\
	i2c-scl-rising-time-ns = <450>;\n\
	i2c-scl-falling-time-ns = <15>;\n\
	#sound-dai-cells = <0>;\n\
};\n\
\n\
&i2s0 {\n\
	status = \"okay\";\n\
	rockchip,i2s-broken-burst-len;\n\
	rockchip,playback-channels = <8>;\n\
	rockchip,capture-channels = <8>;\n\
	#sound-dai-cells = <0>;\n\
};\n\
\n\
&i2s1 {\n\
	assigned-clocks = <&cru SCLK_I2SOUT_SRC>;\n\
	assigned-clock-parents = <&cru SCLK_I2S1_8CH>;\n\
};\n\
\n\
&i2s2 {\n\
	#sound-dai-cells = <0>;\n\
	status = \"okay\";\n\
};\n\
\n\
&io_domains {\n\
	status = \"okay\";\n\
\n\
	bt656-supply = <&vcc1v8_dvp>;		/* bt656_gpio2ab_ms */\n\
	audio-supply = <&vcca1v8_codec>;	/* audio_gpio3d4a_ms */\n\
	sdmmc-supply = <&vccio_sd>;         /* sdmmc_gpio4b_ms */\n\
	gpio1830-supply = <&vcc_3v0>;		/* gpio1833_gpio4cd_ms */\n\
};\n\
\n\
&pmu_io_domains {\n\
	status = \"okay\";\n\
	pmu1830-supply = <&vcc_3v0>;\n\
};\n\
\n\
#ifdef HAS_PCIE \n\
&pcie_phy {\n\
	status = \"okay\";\n\
	assigned-clocks = <&cru SCLK_PCIEPHY_REF>;\n\
	assigned-clock-parents = <&cru SCLK_PCIEPHY_REF100M>;\n\
	assigned-clock-rates = <100000000>;\n\
};\n\
\n\
&pcie0 {\n\
	status = \"okay\";\n\
	num-lanes = <2>;\n\
	max-link-speed = <2>;\n\
};\n\
#endif \n\
\n\
&pwm_bl {\n\
	status = \"okay\";\n\
	enable-gpios = <&gpio4 29 GPIO_ACTIVE_HIGH>;\n\
};\n\
\n\
&pwm0 {\n\
	status = \"okay\";\n\
};\n\
\n\
&pwm1 {\n\
	status = \"okay\";\n\
};\n\
\n\
&pwm2 {\n\
	status = \"okay\";\n\
	pinctrl-names = \"active\";\n\
	pinctrl-0 = <&pwm2_pin_pull_down>;\n\
};\n\
\n\
&rockchip_suspend {\n\
	status = \"okay\";\n\
	rockchip,sleep-debug-en = <1>;\n\
	rockchip,sleep-mode-config = <\n\
		(0\n\
		| RKPM_SLP_ARMPD\n\
		| RKPM_SLP_PERILPPD\n\
		| RKPM_SLP_DDR_RET\n\
		| RKPM_SLP_PLLPD\n\
		| RKPM_SLP_CENTER_PD\n\
		| RKPM_SLP_AP_PWROFF\n\
		)\n\
		>;\n\
	rockchip,wakeup-config = <\n\
		(0\n\
		| RKPM_GPIO_WKUP_EN\n\
		| RKPM_PWM_WKUP_EN\n\
		)\n\
		>;\n\
		rockchip,pwm-regulator-config = <\n\
		(0\n\
		| PWM2_REGULATOR_EN\n\
		)\n\
		>;\n\
		rockchip,power-ctrl =\n\
		<&gpio1 17 GPIO_ACTIVE_HIGH>,\n\
		<&gpio1 14 GPIO_ACTIVE_HIGH>;\n\
};\n\
\n\
&saradc {\n\
	status = \"okay\";\n\
	vref-supply = <&vccadc_ref>;/* TBD */\n\
};\n\
\n\
&sdhci {\n\
	bus-width = <8>;\n\
	mmc-hs400-1_8v;\n\
	supports-emmc;\n\
	non-removable;\n\
	keep-power-in-suspend;\n\
	mmc-hs400-enhanced-strobe;\n\
	status = \"okay\";\n\
};\n\
\n\
&emmc_phy {\n\
	status = \"okay\";\n\
};\n\
\n\
&sdio0 {\n\
	clock-frequency = <150000000>;\n\
	clock-freq-min-max = <100000 150000000>;\n\
	supports-sdio;\n\
	bus-width = <4>;\n\
	disable-wp;\n\
	cap-sd-highspeed;\n\
	cap-sdio-irq;\n\
	keep-power-in-suspend;\n\
	mmc-pwrseq = <&sdio_pwrseq>;\n\
	non-removable;\n\
	num-slots = <1>;\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&sdio0_bus4 &sdio0_cmd &sdio0_clk>;\n\
	sd-uhs-sdr104;\n\
	status = \"okay\";\n\
};\n\
\n\
&sdmmc {\n\
	clock-frequency = <150000000>;\n\
	clock-freq-min-max = <100000 150000000>;\n\
	supports-sd;\n\
	bus-width = <4>;\n\
	cap-mmc-highspeed;\n\
	cap-sd-highspeed;\n\
	disable-wp;\n\
	num-slots = <1>;\n\
	sd-uhs-sdr104;\n\
	vmmc-supply = <&vcc_sd>;\n\
	vqmmc-supply = <&vccio_sd>;\n\
	pinctrl-names = \"default\";\n\
	pinctrl-0 = <&sdmmc_clk &sdmmc_cmd &sdmmc_cd &sdmmc_bus4>;\n\
	status = \"okay\";\n\
};\n\
\n\
&tsadc {\n\
	/* tshut mode 0:CRU 1:GPIO */\n\
	rockchip,hw-tshut-mode = <1>;\n\
	/* tshut polarity 0:LOW 1:HIGH */\n\
	rockchip,hw-tshut-polarity = <1>;\n\
	status = \"okay\";\n\
};\n\
\n\
&tcphy0 {\n\
	extcon = <&fusb0>;\n\
	status = \"okay\";\n\
};\n\
\n\
&tcphy1 {\n\
	status = \"okay\";\n\
};\n\
\n\
&u2phy0 {\n\
	status = \"okay\";\n\
	extcon = <&fusb0>;\n\
\n\
	u2phy0_otg: otg-port {\n\
		status = \"okay\";\n\
	};\n\
\n\
	u2phy0_host: host-port {\n\
		phy-supply = <&vcc5v0_host>;\n\
		status = \"okay\";\n\
	};\n\
};\n\
\n\
&u2phy1 {\n\
	status = \"okay\";\n\
\n\
	u2phy1_otg: otg-port {\n\
		status = \"okay\";\n\
	};\n\
\n\
	u2phy1_host: host-port {\n\
		phy-supply = <&vcc5v0_host>;\n\
		status = \"okay\";\n\
	};\n\
};\n\
\n\
&usbdrd3_0 {\n\
	status = \"okay\";\n\
	extcon = <&fusb0>;\n\
};\n\
\n\
&usbdrd3_1 {\n\
	status = \"okay\";\n\
};\n\
\n\
&usbdrd_dwc3_0 {\n\
	status = \"okay\";\n\
};\n\
\n\
&usbdrd_dwc3_1 {\n\
	status = \"okay\";\n\
	dr_mode = \"host\";\n\
};\n\
\n\
&usb_host0_ehci {\n\
	status = \"okay\";\n\
};\n\
\n\
&usb_host0_ohci {\n\
	status = \"okay\";\n\
};\n\
\n\
&usb_host1_ehci {\n\
	status = \"okay\";\n\
};\n\
\n\
&usb_host1_ohci {\n\
	status = \"okay\";\n\
};\n\
\n\
&pinctrl {\n\
	edp {\n\
		/delete-node/ edp-hpd;\n\
	};\n\
\n\
	hdmi {\n\
		/delete-node/ hdmi-i2c-xfer;\n\
	};\n\
\n\
	pmic {\n\
		pmic_int_l: pmic-int-l {\n\
			rockchip,pins = <1 21 RK_FUNC_GPIO &pcfg_pull_up>;\n\
		};\n\
\n\
		vsel1_gpio: vsel1-gpio {\n\
			rockchip,pins = <1 17 RK_FUNC_GPIO &pcfg_pull_down>;\n\
		};\n\
		vsel2_gpio: vsel2-gpio {\n\
			rockchip,pins = <1 14 RK_FUNC_GPIO &pcfg_pull_down>;\n\
		};\n\
	};\n\
\n\
	vcc_sd {\n\
		vcc_sd_h: vcc-sd-h {\n\
			rockchip,pins = <0 1 RK_FUNC_GPIO &pcfg_pull_up>;\n\
		};\n\
	};\n\
\n\
	fusb30x {\n\
		fusb0_int: fusb0-int {\n\
			rockchip,pins = <1 2 RK_FUNC_GPIO &pcfg_pull_up>;\n\
		};\n\
	};\n\
\n\
	sdio-pwrseq {\n\
		wifi_enable_h: wifi-enable-h {\n\
			rockchip,pins = <0 10 RK_FUNC_GPIO &pcfg_pull_none>;\n\
		};\n\
	};\n\
\n\
	wireless-bluetooth {\n\
		uart0_gpios: uart0-gpios {\n\
			rockchip,pins = <2 19 RK_FUNC_GPIO &pcfg_pull_none>;\n\
		};\n\
	};\n\
\n\
	rockchip-key {\n\
		power_key: power-key {\n\
			rockchip,pins = <0 5 RK_FUNC_GPIO &pcfg_pull_up>;\n\
		};\n\
	};\n\
\n\
	lcd-panel {\n\
		lcd_panel_reset: lcd-panel-reset {\n\
			rockchip,pins = <4 30 RK_FUNC_GPIO &pcfg_pull_up>;\n\
		};\n\
	};\n\
\n\
	headphone {\n\
		hp_det: hp-det {\n\
			rockchip,pins = <4 28 RK_FUNC_GPIO &pcfg_pull_none>;\n\
		};\n\
	};\n\
\n\
	gpio-leds {\n\
		leds_gpio: leds-gpio {\n\
			rockchip,pins = <0 13 RK_FUNC_GPIO &pcfg_pull_none>;\n\
		};\n\
	};\n\
	hdmiin {\n\
		hdmiin_gpios: hdmiin-gpios {\n\
			rockchip,pins =\n\
				<1 0 RK_FUNC_GPIO &pcfg_output_high>,\n\
				<2 6 RK_FUNC_GPIO &pcfg_output_high>,\n\
				<2 5 RK_FUNC_GPIO &pcfg_pull_none>,\n\
				<0 2 RK_FUNC_GPIO &pcfg_pull_none>;\n\
		};\n\
	};\n\
    #if defined(HAS_CAM0) || defined(HAS_CAM1) \n\
	cam_pins {\n\
		cif_clkout_a: cif-clkout-a {\n\
			rockchip,pins = <2 11 RK_FUNC_3 &pcfg_pull_none>;\n\
		};\n\
\n\
		cif_clkout_a_sleep: cif-clkout-a-sleep {\n\
			rockchip,pins = <2 11 RK_FUNC_GPIO &pcfg_pull_none>;\n\
		};\n\
\n\
        #ifdef HAS_CAM0 \n\
		cam0_default_pins: cam0-default-pins {\n\
			rockchip,pins =\n\
				<2 28 RK_FUNC_GPIO &pcfg_pull_down>,\n\
				<2 27 RK_FUNC_GPIO &pcfg_pull_none>;\n\
		};\n\
		#endif \n\
        #ifdef HAS_CAM1 \n\
		cam1_default_pins: cam1-default-pins {\n\
			rockchip,pins =\n\
				<0 12 RK_FUNC_GPIO &pcfg_pull_down>,\n\
				<0  8 RK_FUNC_GPIO &pcfg_pull_none>;\n\
		};\n\
		#endif \n\
	};\n\
    #endif /* #if defined(HAS_CAM0) || defined(HAS_CAM1) */\n\
    #ifdef HAS_SPI \n\
	spi1 {\n\
		spi1_gpio: spi1-gpio {\n\
			rockchip,pins =\n\
				<1 7 RK_FUNC_GPIO &pcfg_output_low>,\n\
				<1 8 RK_FUNC_GPIO &pcfg_output_low>,\n\
				<1 9 RK_FUNC_GPIO &pcfg_output_low>,\n\
				<1 10 RK_FUNC_GPIO &pcfg_output_low>;\n\
		};\n\
	};\n\
    #endif /* HAS_SPI */\n\
    #ifdef HAS_PCIE\n\
	pcie {\n\
		pcie_gpios: pcie-gpios {\n\
			rockchip,pins =\n\
				<2 4 RK_FUNC_GPIO &pcfg_output_high>,\n\
				<2 3 RK_FUNC_GPIO &pcfg_pull_up>,\n\
				<2 2 RK_FUNC_GPIO &pcfg_pull_up>;\n\
		};\n\
	};\n\
    #endif\n\
};\n\
#ifdef HAS_I2C3\n\
&i2c3 {\n\
	clock-frequency = <100000>;\n\
	status = \"okay\";\n\
};\n\
#endif\n\
\n\
#ifdef HAS_I2C6\n\
&i2c6 {\n\
    i2c-scl-rising-time-ns = <450>;\n\
    i2c-scl-falling-time-ns = <15>;\n\
    clock-frequency = <400000>;\n\
	status = \"okay\";\n\
};\n\
#endif\n\
\n\
&i2c7 {\n\
	status = \"okay\";\n\
};\n\
\n\
#ifdef HAS_PCIE\n\
&pcie0 {\n\
        ep-gpios = <&gpio2 4 GPIO_ACTIVE_HIGH>;\n\
        pinctrl-names = \"default\";\n\
        pinctrl-0 = <&pcie_gpios>;\n\
        num-lanes = <4>;\n\
};\n\
#endif\n\
#ifdef HAS_SPI\n\
&spi1 {\n\
	status = \"disabled\";\n\
	pinctrl-names = \"default\", \"sleep\";\n\
	pinctrl-1 = <&spi1_gpio>;\n\
\n\
    #ifdef HAS_SPIDEV\n\
	spidev0: spidev@0 {\n\
		compatible = \"rockchip,spidev\";\n\
		reg = <0>;\n\
		spi-max-frequency = <10000000>;\n\
		status = \"okay\";\n\
	};\n\
    #endif\n\
};\n\
#endif\n\
"
