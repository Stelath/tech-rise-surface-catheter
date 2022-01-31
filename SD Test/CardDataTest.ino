/*
    I would suggest taking a look at this link it seems to have both the read and write
    capabilities you are looking for, remember you at least need to open up the file at some point
    so you dont erase existing data.
    https://create.arduino.cc/projecthub/electropeak/sd-card-module-with-arduino-how-to-read-write-data-37f390
*/

// void setup()
// {
//     // Open serial communications and wait for port to open:
//     Serial.begin(9600);
//     while (!Serial)
//     {
//         ; // wait for serial port to connect. Needed for native USB port only
//     }
//     Serial.print("Initializing SD card...");
//     if (!SD.begin(10))
//     {
//         Serial.println("initialization failed!");
//         while (1)
//             ;
//     }
//     Serial.println("initialization done.");
//     // open t
//     //Time
// he file. note that only one file can be open at a time,
//     //Water Level
// String str = to_string(val);ng another.
//     myFile = strFILE_WRITE);
//     // if the file op
// //Volumeened okay, write to it:
//     {
//         //Prints time, then sensor level, then volume
//         Serial.print(ENTER DATA INFO HERE);
//         myFile.println(":)");
//         myFile.println(i);
//     }
//     // close the file:
//     myFile.close();
//     Serial.println("done.");
// }
// else
// {
//     // if the file didn't open, print an error:
//     Serial.println("error opening test.txt");
// }
// }