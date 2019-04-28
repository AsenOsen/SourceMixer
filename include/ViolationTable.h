#ifndef VIOLATIONTABLE_H
#define VIOLATIONTABLE_H

struct BlackBox{
    int memoryRegionAppeaared = 0;
    int memoryProtectionChanged = 0;
    int memoryExecutableModified = 0;
    int memoryWritebleXRegion = 0;
    int debugBreakPointDetected = 0;
    int instrumentationDetected = 0;
};
struct WhiteBox{
};
struct GrayBox{
    int sandboxDetected = 0;
};

struct GlobalViolationTable{
    int securityWorkerLongCycle = 0;
    int threadsRunTooLate = 0;
};

struct ViolationTable
{
    BlackBox blackBox;
    WhiteBox whiteBox;
    GrayBox grayBox;
    static GlobalViolationTable* global;
};



#endif // VIOLATIONTABLE_H
