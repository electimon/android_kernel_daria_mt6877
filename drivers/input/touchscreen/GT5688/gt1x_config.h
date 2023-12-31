/* drivers/input/touchscreen/gt1x_generic.h
 *
 * 2010 - 2014 Goodix Technology.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be a reference
 * to you, when you are integrating the GOODiX's CTP IC into your system,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * Version: 1.0
 * Revision Record:
 *      V1.0:  first release. 2014/09/28.
 *
 */

#ifndef _GT1X_CONFIG_H_
#define _GT1X_CONFIG_H_

/***************************PART2:TODO define**********************************/
/*TODO: puts the config info corresponded to your TP here, the following is just
		a sample config, send this config should cause the chip can not work normally*/

/* TODO define your config for Sensor_ID == 0 here, if needed */
#define GTP_CFG_GROUP0 {\
0x4C,0xD0,0x02,0x18,0x06,0x05,0x3D,0x04,0x20,0x60,0x02,0x0F,\
0x50,0x32,0x33,0x01,0x00,0x00,0x00,0x00,0x28,0x82,0xA0,0xD2,\
0x18,0x04,0x03,0x00,0x1E,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x08,0x00,0x86,0x27,\
0x1C,0x4C,0x4E,0x7C,0x05,0x00,0x00,0x28,0x0D,0x43,0x24,0x00,\
0x03,0x39,0x6B,0xC0,0x94,0x02,0x00,0x03,0x53,0xAF,0x41,0x9C,\
0x49,0x8D,0x52,0x80,0x5A,0x76,0x62,0x6D,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0xF0,0x4C,0x3C,0xFF,0xFF,0x07,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x17,0x64,0x04,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0xEB,0x06,0x32,0x1E,0x1F,0x1D,0x1B,0x1A,\
0x19,0x18,0x17,0x16,0x15,0x14,0x13,0x12,0x10,0x0F,0x01,0x02,\
0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,\
0xFF,0xFF,0xFF,0xFF,0x12,0x13,0x14,0x15,0x17,0x18,0x19,0x1A,\
0x1B,0x1C,0x1D,0x1E,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,\
0xFF,0xFF,0x00,0x30,0x00,0x00,0x00,0xFF,0x14,0x64,0x00,0x00,\
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,\
0x00,0x00,0x00,0x00,0x78,0x03,0x04,0x32,0x0C,0xE0,0x14,0x50,\
0x00,0x54,0x10,0x00,0x00,0x00,0x00,0x00,0xD2,0x88,0x01\
}
	
/* TODO define your config for Sensor_ID == 1 here, if needed */
#define GTP_CFG_GROUP1 {\
    }
/* TODO define your config for Sensor_ID == 2 here, if needed */
#define GTP_CFG_GROUP2 {\
    }
/* TODO define your config for Sensor_ID == 3 here, if needed */
#define GTP_CFG_GROUP3 {\
    }
/* TODO define your config for Sensor_ID == 4 here, if needed */
#define GTP_CFG_GROUP4 {\
    }
/* TODO define your config for Sensor_ID == 5 here, if needed */
#define GTP_CFG_GROUP5 {\
    }

/*
  *         Charger Configs 
*/
/* TODO define your config for Sensor_ID == 0 here, if needed */
#define GTP_CHARGER_CFG_GROUP0 {\
}
/* TODO define your config for Sensor_ID == 1 here, if needed */
#define GTP_CHARGER_CFG_GROUP1 {\
}
/* TODO define your config for Sensor_ID == 2 here, if needed */
#define GTP_CHARGER_CFG_GROUP2 {\
}
/* TODO define your config for Sensor_ID == 3 here, if needed */
#define GTP_CHARGER_CFG_GROUP3 {\
}
/* TODO define your config for Sensor_ID == 4 here, if needed */
#define GTP_CHARGER_CFG_GROUP4 {\
}
/* TODO define your config for Sensor_ID == 5 here, if needed */
#define GTP_CHARGER_CFG_GROUP5 {\
}

/*
  *         Smart Cover Configs 
*/
/* TODO define your config for Sendor_ID == 0 here, if needed */
#define GTP_SMART_COVER_CFG_GROUP0 {\
}
/* TODO define your config for Sendor_ID == 0 here, if needed */
#define GTP_SMART_COVER_CFG_GROUP1 {\
}
/* TODO define your config for Sendor_ID == 0 here, if needed */
#define GTP_SMART_COVER_CFG_GROUP2 {\
}
/* TODO define your config for Sendor_ID == 0 here, if needed */
#define GTP_SMART_COVER_CFG_GROUP3 {\
}
/* TODO define your config for Sendor_ID == 0 here, if needed */
#define GTP_SMART_COVER_CFG_GROUP4 {\
}
/* TODO define your config for Sendor_ID == 0 here, if needed */
#define GTP_SMART_COVER_CFG_GROUP5 {\
}


#endif				/* _GT1X_CONFIG_H_ */
