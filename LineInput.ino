/*-----------------------------------------------------------------------------
 
 Simple LED Scrolling Message
 By Allen C. Huffman (alsplace@pobox.com)
 www.subethasoftware.com
 
 This function will read up to "bufsize" characters in to "buffer". If the
 user tries to type more, they can't. This routine is used to avoid buffer
 overruns when the user types more than a buffer can handle.
 -----------------------------------------------------------------------------*/

#define CR           13
#define BEL          7
#define BS           8
#define CAN          24

byte lineInput(char *buffer, size_t bufsize)
{
  char    ch;
  byte    len = 0;
  boolean done;

  done = false;
  while(!done)
  {
    //ledBlink();
    if (Serial.available()>0)
    {  
      ch = Serial.read();
      switch(ch)
      {
      case CR:
        Serial.println();
        buffer[len] = '\0';
        done = true;
        break;

      case CAN:
        Serial.println(F("[CAN]"));
        len = 0;
        break;

      case BS:
        if (len>0)
        {
          Serial.write(BS);
          Serial.print(F(" "));
          Serial.write(BS);
          len--;
        }
        break;

      default:
        // If there is room, store any printable characters in the line.
        if (len<bufsize)
        {
          if ((ch>31) && (ch<127)) // isprint(ch) does not work.
          {
            Serial.print(ch);
            buffer[len] = toupper(ch);
            len++;
          }
        }
        else
        {
          Serial.write(BEL); // Overflow. Ring 'dat bell.
        }
        break;
      } // end of switch(ch)           
    } // end of if (Serial.available()>0)
  } // end of while(!done)

  return len;
} // end of lineInput()

/*---------------------------------------------------------------------------*/
// End of LineInput

