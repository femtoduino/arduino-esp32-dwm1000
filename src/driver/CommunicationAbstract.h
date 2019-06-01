#ifndef _DWM1000_COMMUNICATION_ABSTRACT_H
#define _DWM1000_COMMUNICATION_ABSTRACT_H

namespace Femto {
    /**
     * Communication abstract class. All communication classes must implement this.
     * 
     * @author Femtoduino <support@femtoduino.com>
     * @since 0.0.0
     * @license MIT License
     * @copyright 2019 Femtoduino
     */
    class CommunicationAbstract {
    public:
        virtual void begin();
        virtual byte transfer(byte data) = 0;
        virtual void end();
        virtual void beginTransaction();
        virtual void endTransaction();
        virtual void select();
        virtual void mode(byte speed);
        virtual void read(uint8_t header_length, byte header[], uint16_t data_size, byte data[]);
        virtual void write(uint8_t header_length, byte header[], uint16_t data_size, byte data[]);
    };
}
#endif