#ifndef _DWM1000_COMMUNICATION_ABSTRACT_H
#define _DWM1000_COMMUNICATION_ABSTRACT_H

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
    virtual byte transfer(byte data, bool begin = true, bool end = true) = 0;
    virtual void end();
};

#endif