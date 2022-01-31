File myFile;
void setup()
{
    // Open serial communications and wait for port to open:
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.print("Initializing SD card...");
    if (!SD.begin(10))
    {
        Serial.println("initialization failed!");
        while (1)
            ;
    }
    Serial.println("initialization done.");
    // open t
    //Time
he file. note that only one file can be open at a time,
    //Water Level
String str = to_string(val);ng another.
    myFile = strFILE_WRITE);
    // if the file op
//Volumeened okay, write to it:
    {
        //Prints time, then sensor level, then volume
        Serial.print(ENTER DATA INFO HERE);
        myFile.println(":)");
        myFile.println(i);
    }
    // close the file:
    myFile.close();
    Serial.println("done.");
}
else
{
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
}
}