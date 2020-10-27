/* Simple ABP join for a LoRaWAN network
 *  
 *  In setup() below please replace the argument to LoRaWAN.begin()
 *  with your appropriate region specific band:
 *
 *  AS923
 *  AU915
 *  EU868
 *  IN865
 *  KR920
 *  US915
 *
 *  AU915/US915 networks have 64+8 channels. Typical gateways support only
 *  8 (9) channels. Hence it's a good idea to pick the proper channel
 *  subset via select via LoRaWAN.setSubBand(),
 *    
 *  EU868/IN865 have duty cycle restrictions. For debugging it makes sense
 *  to disable those via setDutyCycle(false);
 *    
 *  For an external antenna one should set the proper antenna gain
 *  (default is 2.0) via setAntennaGain().
 *    
 *  Please edit the keys below as they are just debugging samples.
 *    
 *    
 * This example code is in the public domain.
 */
// #define REGION_AS923_920_923 /* Japan, Malaysia, Singapore */
 #define REGION_AS923_923_925 /* Brunei, Cambodia, Hong Kong, Indonesia, Laos, Taiwan, Thailand, Vietnam */
// #define REGION_AU915
// #define REGION_EU868
// #define REGION_IN865
// #define REGION_KR920
// #define REGION_US915


#include "LoRaWAN.h"
#include "STM32L0.h"
#include "CayenneLPP.h"


CayenneLPP myLPP(64);



const char *devAddr = "0100000A";
const char *nwkSKey = "2B7E151628AED2A6ABF7158809CF4F3C";
const char *appSKey = "2B7E151628AED2A6ABF7158809CF4F3C";

//void setup( void )
//{
//    Serial.begin(115200);
//    
//    while (!Serial) { }
//
//    LoRaWAN.begin(AS923);
//    // LoRaWAN.setSubBand(2);
//    // LoRaWAN.setDutyCycle(false);
//    // LoRaWAN.setAntennaGain(2.0);
//    LoRaWAN.joinABP(devAddr, nwkSKey, appSKey);
//
//    Serial.println("JOIN( )");
//}

void setup( void )
{
#if defined(REGION_AS923_920_923)
    LoRaWAN.begin(AS923);
    LoRaWAN.addChannel(2, 922200000, 0, 5);
    LoRaWAN.addChannel(3, 922400000, 0, 5);
    LoRaWAN.addChannel(4, 922600000, 0, 5);
    LoRaWAN.addChannel(5, 922800000, 0, 5);
    LoRaWAN.addChannel(6, 923000000, 0, 5);
    LoRaWAN.addChannel(7, 922000000, 0, 5);
    LoRaWAN.addChannel(8, 922100000, 6, 6);
    LoRaWAN.addChannel(9, 921800000, 7, 7);
#endif

#if defined(REGION_AS923_923_925)
    LoRaWAN.begin(AS923);
    LoRaWAN.addChannel(2, 923200000, 0, 5);
    LoRaWAN.addChannel(3, 923400000, 0, 5);
    LoRaWAN.addChannel(4, 923600000, 0, 5);
    LoRaWAN.addChannel(5, 923800000, 0, 5);
    LoRaWAN.addChannel(6, 924200000, 0, 5);
    LoRaWAN.addChannel(7, 924400000, 0, 5);
    LoRaWAN.addChannel(8, 924600000, 0, 5);
#endif

#if defined(REGION_AU915)
    LoRaWAN.begin(AU915);
    LoRaWAN.setSubBand(2);
#endif

#if defined(REGION_EU868)
    LoRaWAN.begin(EU868);
    LoRaWAN.addChannel(1, 868300000, 0, 6);
    LoRaWAN.addChannel(3, 867100000, 0, 5);
    LoRaWAN.addChannel(4, 867300000, 0, 5);
    LoRaWAN.addChannel(5, 867500000, 0, 5);
    LoRaWAN.addChannel(6, 867700000, 0, 5);
    LoRaWAN.addChannel(7, 867900000, 0, 5);
    LoRaWAN.addChannel(8, 868800000, 7, 7);
    LoRaWAN.setRX2Channel(869525000, 3);
#endif

#if defined(REGION_IN865)
    LoRaWAN.begin(IN865);
#endif

#if defined(REGION_KR920)
    LoRaWAN.begin(KR920);
    LoRaWAN.addChannel(3, 922700000, 0, 5);
    LoRaWAN.addChannel(4, 922900000, 0, 5);
    LoRaWAN.addChannel(5, 923100000, 0, 5);
    LoRaWAN.addChannel(6, 923300000, 0, 5);
#endif

#if defined(REGION_US915)
    LoRaWAN.begin(US915);
    LoRaWAN.setSubBand(2);
#endif
    Serial.begin(115200);
      
    // LoRaWAN.setDutyCycle(false);     
    // LoRaWAN.setAntennaGain(2.0);
    LoRaWAN.joinABP(devAddr, nwkSKey, appSKey);

    Serial.println("JOIN( )");
}

void loop( void )
{
    if (LoRaWAN.joined() && !LoRaWAN.busy())
    {
        if (STM32L0.getVBUS()) 
        {
            LoRaWAN.setBatteryLevel(LORAWAN_BATTERY_LEVEL_EXTERNAL);
        }
        else
        {
            LoRaWAN.setBatteryLevel(LORAWAN_BATTERY_LEVEL_UNKNOWN);
        }

        Serial.print("TRANSMIT( ");
        Serial.print("TimeOnAir: ");
        Serial.print(LoRaWAN.getTimeOnAir());
        Serial.print(", NextTxTime: ");
        Serial.print(LoRaWAN.getNextTxTime());
        Serial.print(", MaxPayloadSize: ");
        Serial.print(LoRaWAN.getMaxPayloadSize());
        Serial.print(", DR: ");
        Serial.print(LoRaWAN.getDataRate());
        Serial.print(", TxPower: ");
        Serial.print(LoRaWAN.getTxPower(), 1);
        Serial.print("dbm, UpLinkCounter: ");
        Serial.print(LoRaWAN.getUpLinkCounter());
        Serial.print(", DownLinkCounter: ");
        Serial.print(LoRaWAN.getDownLinkCounter());
        Serial.println(" )");

//        LoRaWAN.beginPacket();
//        LoRaWAN.write(0xef);
//        LoRaWAN.write(0xbe);
//        LoRaWAN.write(0xad);
//        LoRaWAN.write(0xde);
//        LoRaWAN.endPacket();

            myLPP.reset();
            myLPP.addTemperature(0, 27);
            myLPP.addRelativeHumidity(0, 30);

            LoRaWAN.sendPacket(myLPP.getBuffer(), myLPP.getSize());

        
    }

 delay(30000);


}
