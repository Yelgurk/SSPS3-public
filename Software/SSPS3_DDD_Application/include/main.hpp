#include <Arduino.h>

#include <Wire.h>
#include <PCF8574.h>
#include <RtcDS3231.h>
#include "../../SSPS3_DDD_Infrastructure/include/eeprom.hpp"
#include "../../SSPS3_DDD_Domain/include/dateTimeModel.hpp"
#include "../../SSPS3_DDD_Core/include/IOService.hpp"
#include "../../SSPS3_DDD_Core/include/DBService.hpp"
#include "../../SSPS3_DDD_Core/include/KBService.hpp"
#include "../../SSPS3_DDD_Core/include/RTCService.hpp"

#include "./lv_helper.hpp"
#include "./lv_resources.hpp"

#include "./UIService.hpp"
#include "./NaviService.hpp"
#include "./TaskService.hpp"
#include "./NotificationService.hpp"

#define SDA 40
#define SCL 39