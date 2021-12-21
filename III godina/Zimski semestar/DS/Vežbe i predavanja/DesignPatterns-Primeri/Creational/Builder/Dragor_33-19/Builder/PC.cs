using System;
namespace Builder
{
    public class PC
    {
        // Set by Builder
        public CPU cpu;
        public int gpuMemory;
        public int ramSize;
        public int ssdSize;
        public int psuPower;

        // States and behaviours
        public bool PoweredOn { get; private set; }

        public PC()
        {
            PoweredOn = false;
        }

        public void TogglePower()
        {
            PoweredOn = !PoweredOn;
        }

        public override string ToString()
        {
            return "PC\n cpu: " + cpu + "\n gpu: " + gpuMemory + "GB\n ram: " + ramSize + "GB\n ssd: " + ssdSize + "GB\n psu: " + psuPower + "W";
        }
    }
}
